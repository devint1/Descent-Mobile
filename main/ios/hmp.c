// Credit goes to Hans de Goede for d1x HMP->MID conversion code

#ifndef ANDROID_NDK
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

extern void hmp2mid(hmp_file *hmp, unsigned char **midbuf, unsigned int *midlen);

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

void hmp_stop(hmp_file *hmp) {
	MusicPlayerStop(musicPlayer);
	stopLoop();
}

void hmp_setvolume(hmp_file *hmp, int volume) {
	AudioUnitSetParameter(mixerUnit, kMultiChannelMixerParam_Volume, kAudioUnitScope_Output, 0, (float)volume / 128.0, 0);
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
#endif
