// Credit goes to Hans de Goede for d1x HMP->MID conversion code
#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "hmp.h"
#include "types.h"
#include "byteswap.h"
#include "Music.h"

#if 0
#define CFILE FILE
#define cfopen fopen
#define cfseek fseek
#define cfread fread
#define cfclose fclose
#else
#include "cfile.h"
#endif

// This is the free Merlin Silver soundfont from http://www.soundfonts.gonet.biz
#define SOUNDFONT_FILE "/merlin_silver.sf2"

static MusicPlayer musicPlayer;
static MusicSequence musicSequence;
static AUGraph graph;
static AUNode samplerNode[HMP_TRACKS], mixerNode, ioNode;
static AudioUnit samplerUnit[HMP_TRACKS], mixerUnit, ioUnit;
static AUSamplerBankPresetData presetData[HMP_TRACKS];
static CFURLRef sf2Url;

void hmp_init() {
	Boolean initialized, running;
	int i;
	UInt32 numBuses = HMP_TRACKS;
	CFMutableStringRef path;
	
	// Initialize sountfont path
	path = CFStringCreateMutable(NULL, 0);
	CFStringAppend(path, CFStringCreateWithCString(NULL, Resource_path, kCFStringEncodingASCII));
	CFStringAppend(path, CFStringCreateWithCString(NULL, SOUNDFONT_FILE, kCFStringEncodingASCII));
	sf2Url = CFURLCreateWithString(NULL, path, NULL);
	
	// Create a new AU graph
	NewAUGraph(&graph);
	
	// Add sampler nodes to the graph
	AudioComponentDescription description = { kAudioUnitType_MusicDevice, kAudioUnitSubType_Sampler, kAudioUnitManufacturer_Apple, 0, 0 };
	for (i = 0; i < HMP_TRACKS; ++i) {
		AUGraphAddNode(graph, &description, &samplerNode[i]);
	}
	
	// Add mixer to the graph
	AudioComponentDescription mixerDescription = { kAudioUnitType_Mixer, kAudioUnitSubType_MultiChannelMixer, kAudioUnitManufacturer_Apple, 0, 0 };
	AUGraphAddNode(graph, &mixerDescription, &mixerNode);
	
	// Add an output node to the graph
	AudioComponentDescription ioDescription = { kAudioUnitType_Output, kAudioUnitSubType_RemoteIO, kAudioUnitManufacturer_Apple, 0, 0 };
	AUGraphAddNode(graph, &ioDescription, &ioNode);
	
	// Open the graph
	AUGraphOpen(graph);
	
	// Link the mixer node and unit
	AUGraphNodeInfo(graph, mixerNode, NULL, &mixerUnit);
	
	// Set the number of busses on the mixer and connect the sampler nodes to it
	AudioUnitSetProperty(mixerUnit, kAudioUnitProperty_ElementCount, kAudioUnitScope_Input, 0, &numBuses, sizeof(numBuses));
	for (i = 0; i < HMP_TRACKS; ++i) {
		AUGraphConnectNodeInput(graph, samplerNode[i], 0, mixerNode, i);
	}
	
	// Connect the mixer to the output node and link sampler nodes to units
	AUGraphConnectNodeInput (graph, mixerNode, 0, ioNode, 0);
	for (i = 0; i < HMP_TRACKS; ++i) {
		AUGraphNodeInfo(graph, samplerNode[i], 0, &samplerUnit[i]);
	}
	
	// Connect the output node to unit
	AUGraphNodeInfo(graph, ioNode, 0, &ioUnit);
	
	// Get the graph going!
	AUGraphIsInitialized(graph, &initialized);
	if (!initialized) {
		AUGraphInitialize(graph);
	}
	AUGraphIsRunning(graph, &running);
	if (!running) {
		AUGraphStart(graph);
	}
	
	// Initialize presets
	for (int i = 0; i < HMP_TRACKS; ++i) {
		presetData[i] = (AUSamplerBankPresetData){ sf2Url, kAUSampler_DefaultMelodicBankMSB, kAUSampler_DefaultBankLSB, 0, 0 };
		if (i == 9) {
			presetData[i].bankMSB = kAUSampler_DefaultPercussionBankMSB;
		}
		AudioUnitSetProperty(samplerUnit[i], kAUSamplerProperty_LoadPresetFromBank, kAudioUnitScope_Global, 0, &presetData[i], sizeof(AUSamplerBankPresetData));
	}
}

hmp_file *hmp_open(const char *filename) {
	int i;
	char buf[256];
	int32_t	data;
	CFILE *fp;
	hmp_file *hmp;
	int num_tracks;
	unsigned char *p;

	if (!(fp = cfopen((char *)filename, "rb")))
		return NULL;

	hmp = malloc(sizeof(hmp_file));
	if (!hmp) {
		cfclose(fp);
		return NULL;
	}

	memset(hmp, 0, sizeof(*hmp));

	if ((cfread(buf, 1, 8, fp) != 8) || (memcmp(buf, "HMIMIDIP", 8)))
		goto err;

	if (cfseek(fp, 0x30, SEEK_SET))
		goto err;

	if (cfread(&num_tracks, 4, 1, fp) != 1)
		goto err;

	if ((num_tracks < 1) || (num_tracks > HMP_TRACKS))
		goto err;

	hmp->num_trks = num_tracks;
	hmp->tempo = 120;

	if (cfseek(fp, 0x308, SEEK_SET))
		goto err;

	for (i = 0; i < num_tracks; i++) {
		if ((cfseek(fp, 4, SEEK_CUR)) || (cfread(&data, 4, 1, fp) != 1))
			goto err;

		data -= 12;

#if 0
		if (i == 0)  /* track 0: reserve length for tempo */
			data += sizeof(hmp_tempo);
#endif

		hmp->trks[i].len = data;

		if (!(p = hmp->trks[i].data = malloc(data)))
			goto err;

#if 0
		if (i == 0) { /* track 0: add tempo */
			memcpy(p, hmp_tempo, sizeof(hmp_tempo));
			p += sizeof(hmp_tempo);
			data -= sizeof(hmp_tempo);
		}
#endif
		/* finally, read track data */
		if ((cfseek(fp, 4, SEEK_CUR)) || (cfread(p, data, 1, fp) != 1))
			goto err;
	}
	cfclose(fp);
	return hmp;

err:
	cfclose(fp);
	hmp_close(hmp);
	return NULL;
}

void hmp_stop(hmp_file *hmp) {
	MusicPlayerStop(musicPlayer);
	stopLoop();
}

void hmp_close(hmp_file *hmp) {
	int i;

	for (i = 0; i < hmp->num_trks; i++)
		if (hmp->trks[i].data)
			free(hmp->trks[i].data);
	free(hmp);
}

void hmp_setvolume(hmp_file *hmp, int volume) {
	AudioUnitSetParameter(mixerUnit, kMultiChannelMixerParam_Volume, kAudioUnitScope_Output, 0, (float)volume / 128.0, 0);
}

static unsigned int hmptrk2mid(ubyte* data, int size, unsigned char **midbuf, unsigned int *midlen, hmp_track *trks)
{
	ubyte *dptr = data;
	ubyte lc1 = 0,last_com = 0;
	uint d;
	int n1, n2;
	unsigned int offset = *midlen;
	
	while (data < dptr + size)
	{
		if (data[0] & 0x80) {
			ubyte b = (data[0] & 0x7F);
			*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
			memcpy(&(*midbuf)[*midlen], &b, 1);
			*midlen += 1;
		}
		else {
			d = (data[0] & 0x7F);
			n1 = 0;
			while ((data[n1] & 0x80) == 0) {
				n1++;
				d += (data[n1] & 0x7F) << (n1 * 7);
			}
			n1 = 1;
			while ((data[n1] & 0x80) == 0) {
				n1++;
				if (n1 == 4)
					return 0;
			}
			for(n2 = 0; n2 <= n1; n2++) {
				ubyte b = (data[n1 - n2] & 0x7F);
				
				if (n2 != n1)
					b |= 0x80;
				*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
				memcpy(&(*midbuf)[*midlen], &b, 1);
				*midlen += 1;
			}
			data += n1;
		}
		data++;
		if (*data == 0xFF) { //meta?
			*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 3 + data[2]);
			memcpy(&(*midbuf)[*midlen], data, 3 + data[2]);
			*midlen += 3 + data[2];
			if (data[1] == 0x2F)
				break;
		}
		else {
			lc1=data[0] ;
			if ((lc1&0x80) == 0)
				return 0;
			switch (lc1 & 0xF0) {
				case 0x80:
				case 0x90:
				case 0xA0:
				case 0xB0:
				case 0xE0:
					if (lc1 != last_com)
					{
						*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
						memcpy(&(*midbuf)[*midlen], &lc1, 1);
						*midlen += 1;
					}
					*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 2);
					memcpy(&(*midbuf)[*midlen], data + 1, 2);
					*midlen += 2;
					data += 3;
					break;
				case 0xC0:
				case 0xD0:
					if (lc1 != last_com)
					{
						*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
						memcpy(&(*midbuf)[*midlen], &lc1, 1);
						*midlen += 1;
					}
					*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
					memcpy(&(*midbuf)[*midlen], data + 1, 1);
					*midlen += 1;
					data += 2;
					break;
				default:
					return 0;
			}
			last_com = lc1;
		}
	}
	return (*midlen - offset);
}

ubyte tempo [19] = {'M','T','r','k',0,0,0,11,0,0xFF,0x51,0x03,0x18,0x80,0x00,0,0xFF,0x2F,0};

void hmp2mid(hmp_file *hmp, unsigned char **midbuf, unsigned int *midlen)
{
	int mi, i, j;
	short ms, time_div = 0xC0;
	
	*midlen = 0;
	time_div = hmp->tempo*1.6;
	
	// write MIDI-header
	*midbuf = (unsigned char *) malloc(4);
	memcpy(&(*midbuf)[*midlen], "MThd", 4);
	*midlen += 4;
	mi = swapint(6);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(mi));
	memcpy(&(*midbuf)[*midlen], &mi, sizeof(mi));
	*midlen += sizeof(mi);
	ms = swapshort(1);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(ms));
	memcpy(&(*midbuf)[*midlen], &ms, sizeof(ms));
	*midlen += sizeof(ms);
	ms = swapshort(hmp->num_trks);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(ms));
	memcpy(&(*midbuf)[*midlen], &ms, sizeof(ms));
	*midlen += sizeof(ms);
	ms = swapshort(time_div);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(ms));
	memcpy(&(*midbuf)[*midlen], &ms, sizeof(ms));
	*midlen += sizeof(ms);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(tempo));
	memcpy(&(*midbuf)[*midlen], &tempo, sizeof(tempo));
	*midlen += sizeof(tempo);
	
	// tracks
	for (i = 1; i < hmp->num_trks; i++)
	{
		int midtrklenpos = 0;
		
		*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 4);
		memcpy(&(*midbuf)[*midlen], "MTrk", 4);
		*midlen += 4;
		midtrklenpos = *midlen;
		mi = 0;
		*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(mi));
		*midlen += sizeof(mi);
		mi = hmptrk2mid(hmp->trks[i].data, hmp->trks[i].len, midbuf, midlen, hmp->trks);
		mi = swapint(mi);
		memcpy(&(*midbuf)[midtrklenpos], &mi, 4);
	}
}

void midi_notify_callback(const MIDINotification  *message, void *refCon) {
	printf("MIDI NOTIFICATION: %d", message->messageID);
}

static void midi_read_callback(const MIDIPacketList *pktlist, void *refCon, void *connRefCon) {
	MIDIPacket *packet = (MIDIPacket *)pktlist->packet;
	Byte status, command, channel;
	OSStatus osStatus;
	bool presetChange;
	int tries;
	
	for (int i=0; i < pktlist->numPackets; i++) {
		status = packet->data[0];
		command = status >> 4;
		channel = status & 0x0F;
		osStatus = 0;
		presetChange = false;
		tries = 0;
		switch (command) {
			case 0x0B: // Control change
				if ((packet->data[1] & 0x7F) == 0x00) {
					presetData[channel].bankMSB = packet->data[2] & 0x7F;
					presetChange = true;
				} else if ((packet->data[1] & 0x7F) == 0x20) {
					presetData[channel].bankLSB = packet->data[2] & 0x7F;
					presetChange = true;
				}
				break;
			case 0x0C: // Program change
				presetData[channel].presetID = packet->data[1] & 0x7F;
				presetChange = true;
				break;
		}
		while (presetChange && !osStatus && tries < 3) {
			osStatus = AudioUnitSetProperty(samplerUnit[channel], kAUSamplerProperty_LoadPresetFromBank, kAudioUnitScope_Global, 0, &presetData[channel], sizeof(AUSamplerBankPresetData));
			if (osStatus) { // CRAP! Try to fall back to something that might work
				presetData[channel] = (struct AUSamplerBankPresetData){ sf2Url, kAUSampler_DefaultMelodicBankMSB, kAUSampler_DefaultBankLSB, 0, 0 };
				if (channel == 9) {
					presetData[channel].bankMSB = kAUSampler_DefaultPercussionBankMSB;
				}
				osStatus = 0;
			} else {
				break;
			}
			++tries;
		} if (!presetChange) {
			MusicDeviceMIDIEvent(samplerUnit[channel], status, packet->data[1] & 0x7F, packet->data[2] & 0x7F, 0);
		}
		packet = MIDIPacketNext(packet);
	}
}

int hmp_play(hmp_file *hmp, bool loop) {
	MusicTrack track;
	CFDataRef data;
	UInt32 numTracks;
	UInt32 trackLengthDataLength;
	MusicTimeStamp trackLength = 0.0;
	MIDIClientRef virtualMidi;
	MIDIEndpointRef virtualEndpoint;
	unsigned char *midbuf;
	unsigned int midlen;

	MIDIClientCreate(CFSTR("Client"), midi_notify_callback,  NULL, &virtualMidi);
	MIDIDestinationCreate(virtualMidi, CFSTR("Destination"), midi_read_callback, NULL, &virtualEndpoint);
	NewMusicSequence(&musicSequence);
	MusicSequenceSetAUGraph(musicSequence, graph);
	hmp2mid(hmp, &midbuf, &midlen);
	data = CFDataCreateWithBytesNoCopy(NULL, midbuf, midlen, NULL);
	MusicSequenceFileLoadData(musicSequence, data, kMusicSequenceFile_MIDIType, kMusicSequenceLoadSMF_ChannelsToTracks);
	MusicSequenceSetMIDIEndpoint(musicSequence, virtualEndpoint);
	MusicSequenceGetTrackCount(musicSequence, &numTracks);
	for(int i = 0; i < numTracks && loop; ++i) {
		MusicSequenceGetIndTrack(musicSequence, i, &track);
		MusicTrackGetProperty(track, kSequenceTrackProperty_TrackLength, &trackLength, &trackLengthDataLength);
	}
	NewMusicPlayer(&musicPlayer);
	MusicPlayerSetSequence(musicPlayer, musicSequence);
	MusicPlayerStart(musicPlayer);
	if (loop) {
		startLoop(trackLength * 1.6, &musicPlayer);
	}
	free(midbuf);
	return 0;
}
