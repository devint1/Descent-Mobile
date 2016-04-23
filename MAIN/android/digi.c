/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 * $Source: f:/miner/source/main/rcs/digi.c $
 * $Revision: 2.5 $
 * $Author: john $
 * $Date: 1996/01/05 16:51:51 $
 * 
 * Routines to access digital sound hardware
 * 
 * $Log: digi.c $
 * Revision 2.5  1996/01/05  16:51:51  john
 * Made the midi handler lock down to +4K.
 * 
 * Revision 2.4  1996/01/05  16:46:54  john
 * Made code lock down midicallback +4K.
 * 
 * Revision 2.3  1995/05/26  16:16:03  john
 * Split SATURN into define's for requiring cd, using cd, etc.
 * Also started adding all the Rockwell stuff.
 * 
 * Revision 2.2  1995/03/30  16:36:04  mike
 * text localization.
 * 
 * Revision 2.1  1995/03/15  11:41:23  john
 * Better Saturn CD-ROM support.
 * 
 * Revision 2.0  1995/02/27  11:29:15  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.172  1995/02/15  09:57:53  john
 * Fixed bug with loading new banks while song is playing.
 * 
 * Revision 1.171  1995/02/14  16:36:26  john
 * Fixed bug with countdown voice getting cut off.
 * 
 * Revision 1.170  1995/02/13  20:34:51  john
 * Lintized
 * 
 * Revision 1.169  1995/02/13  15:18:21  john
 * Added code to reset sounds.
 * 
 * Revision 1.168  1995/02/13  12:53:11  john
 * Fixed bug with demos recording wrong volumes.
 * 
 * Revision 1.167  1995/02/11  15:04:29  john
 * Made FM files load as if you have FM card.
 * 
 * Revision 1.166  1995/02/11  12:41:35  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.165  1995/02/10  16:24:58  john
 * MAde previous change only reverse for RAP10.
 * 
 * Revision 1.164  1995/02/10  13:47:37  john
 * Made digi init before midi to maybe fix RAP10 bug.
 * 
 * Revision 1.163  1995/02/08  21:05:22  john
 * Added code that loads patches for every FM song.
 * 
 * Revision 1.162  1995/02/03  17:17:51  john
 * Made digi lowmem default to off.
 * 
 * Revision 1.161  1995/02/03  17:08:22  john
 * Changed sound stuff to allow low memory usage.
 * Also, changed so that Sounds isn't an array of digi_sounds, it
 * is a ubyte pointing into GameSounds, this way the digi.c code that
 * locks sounds won't accidentally unlock a sound that is already playing, but
 * since it's Sounds[soundno] is different, it would erroneously be unlocked.
 * 
 * Revision 1.160  1995/02/01  22:37:06  john
 * Reduced sound travel distance to 1.25 times original.
 * 
 * Revision 1.159  1995/02/01  22:20:41  john
 * Added digi_is_sound_playing.
 * 
 * Revision 1.158  1995/01/28  15:56:56  john
 * Made sounds carry 1.5 times farther.
 * 
 * Revision 1.157  1995/01/27  17:17:09  john
 * Made max sounds relate better to MAX_SOUND_OBJECTS
 * 
 * Revision 1.156  1995/01/25  12:18:06  john
 * Fixed bug with not closing MIDI files when midi volume is 0.
 * 
 * Revision 1.155  1995/01/24  17:52:17  john
 * MAde midi music stop playing when volume is 0.
 * 
 * Revision 1.154  1995/01/21  21:22:31  mike
 * Correct bogus error message.
 * 
 * Revision 1.153  1995/01/17  14:53:38  john
 * IFDEF'D out digital drums.
 * 
 * Revision 1.152  1995/01/11  16:26:50  john
 * Restored MIDI pausing to actually setting volume to 0,.
 * 
 * Revision 1.151  1995/01/10  16:38:46  john
 * Made MIDI songs pause, not lower volume when pausing, and
 * had to fix an HMI bug by clearing the TRACKINFO array or something.
 * 
 * Revision 1.150  1995/01/05  19:46:27  john
 * Added code to reset the midi tracks to use the ones 
 * in the midi file before each song is played.
 * 
 * Revision 1.149  1994/12/21  15:08:59  matt
 * Bumped MAX_SOUND_OBJECTS back up to match v1.00 of shareware
 * 
 * Revision 1.148  1994/12/20  18:22:54  john
 * Added code to support non-looping songs, and put
 * it in for endlevel and credits.
 * 
 * Revision 1.147  1994/12/19  17:58:19  john
 * Changed Assert for too many sounds to gracefully exit.
 * 
 * Revision 1.146  1994/12/14  16:03:27  john
 * Made the digi/midi deinit in reverse order for anything
 * other than GUS.
 * 
 * Revision 1.145  1994/12/14  14:51:06  john
 * Added assert.
 * 
 * Revision 1.144  1994/12/14  12:14:40  john
 * Relplaced a bunch of (a*b)/c with fixmuldiv
 * to get rid of a overflow bug mike found.
 * 
 * Revision 1.143  1994/12/13  17:30:16  john
 * Made the timer rate be changed right after initializing it.
 * 
 * Revision 1.142  1994/12/13  14:08:35  john
 * Made Pause key set midi volume to 0.
 * Made digi_init set midi volume to proper level.
 * 
 * Revision 1.141  1994/12/13  12:42:31  jasen
 * Fixed sound priority bugs... -john
 * 
 * Revision 1.140  1994/12/13  12:11:38  john
 * Added debugging code.
 * 
 * Revision 1.139  1994/12/13  11:45:19  john
 * Disabled interrupts around the midisetvolume because awe32
 * hangs if you don't.
 * 
 * Revision 1.138  1994/12/13  11:33:45  john
 * MAde so that sounds with volumes > f1_0 don't cut off.
 * 
 * Revision 1.137  1994/12/13  02:24:29  matt
 * digi_init() now doesn't return error when no sound card
 * 
 * Revision 1.136  1994/12/13  00:46:27  john
 * Split digi and midi volume into 2 seperate functions.
 * 
 * Revision 1.135  1994/12/12  22:19:20  john
 * Made general midi versions of files load...
 * .hmq instead of .hmp.
 * 
 * Revision 1.134  1994/12/12  21:32:49  john
 * Made volume work better by making sure volumes are valid
 * and set correctly at program startup.
 * 
 * Revision 1.133  1994/12/12  20:52:35  john
 * Fixed bug with pause calling set mastervolume to 0.
 * 
 * Revision 1.132  1994/12/12  20:39:52  john
 * Changed so that instead of using MasterVolume for 
 * digital sounds, I just scale the volume I play the
 * sound by.
 * 
 * Revision 1.131  1994/12/12  13:58:21  john
 * MAde -nomusic work.
 * Fixed GUS hang at exit by deinitializing digi before midi.
 * 
 * Revision 1.130  1994/12/11  23:29:39  john
 * *** empty log message ***
 * 
 * Revision 1.129  1994/12/11  23:18:07  john
 * Added -nomusic.
 * Added RealFrameTime.
 * Put in a pause when sound initialization error.
 * Made controlcen countdown and framerate use RealFrameTime.
 * 
 * Revision 1.128  1994/12/11  13:35:26  john
 * Let sounds play louder than F1_0.  btw, 4*f1_0 is maxed.
 * 
 * Revision 1.127  1994/12/11  00:43:45  john
 * Fixed bug with sounds taking over channels that sound objects own.
 * 
 * Revision 1.126  1994/12/10  20:35:03  john
 * Added digi_kill_sound_linked_to_object.
 * 
 * Revision 1.125  1994/12/10  15:44:20  john
 * Added max_distance passing for sound objects.
 * 
 * Revision 1.124  1994/12/09  20:16:37  john
 * Made it so that when Mike's AI code passes bogus values, the
 * digi code will saturate them.
 * 
 * Revision 1.123  1994/12/09  17:07:52  john
 * Fixed abrupt fan cutoff.
 * 
 * Revision 1.122  1994/12/08  17:19:14  yuan
 * Cfiling stuff.
 * 
 * Revision 1.121  1994/12/06  19:24:08  john
 * CLosed HMI timer after making our not call it.
 * 
 * Revision 1.120  1994/12/06  19:00:42  john
 * Moved digi_reset_sounds to reset instead of digi_close.
 * 
 * Revision 1.119  1994/12/06  18:23:48  matt
 * Don't pause midi songs, becuase it can lock up
 * 
 * Revision 1.118  1994/12/06  16:07:09  john
 * MAde the gus pats only load if using midi==midi_gus.
 * 
 * Revision 1.117  1994/12/06  10:17:07  john
 * MAde digi_close call reset_sounds.
 * 
 * Revision 1.116  1994/12/05  23:36:50  john
 * Took out lock down of GETDS, because, I, john, was wrong, and it
 * was me, not the HMI people, that was calling GETDS in an interrupt.
 * I un-formally apologize to HMI.
 * 
 * Revision 1.115  1994/12/05  22:50:09  john
 * Put in code to lock down GETDS, because the HMI
 * people don't lock it down, even tho they use it 
 * in their timerhandler interrupt.
 * 
 * Revision 1.114  1994/12/05  18:54:09  john
 * *** empty log message ***
 * 
 * Revision 1.113  1994/12/05  18:52:11  john
 * Locked down the TrackMap array, since SOS references it in an interupt.
 * Added -noloadpats command line option.
 * 
 * Revision 1.112  1994/12/05  16:55:45  john
 * Made so that digi_init_System is  called before 
 * the timer system calls the timer handler.
 * 
 * Revision 1.111  1994/12/05  12:56:19  john
 * Made the intruments patches only load for FM devices.
 * 
 * Revision 1.110  1994/12/05  12:17:16  john
 * Added code that locks/unlocks digital sounds on demand.
 * 
 * Revision 1.109  1994/12/04  14:30:10  john
 * Added hooks for music..
 * 
 * Revision 1.108  1994/12/02  13:58:27  matt
 * Put in Int3()s when try to play a non-existant sound
 * 
 * Revision 1.107  1994/12/02  10:35:58  john
 * Took out loadpats.c
 * 
 * Revision 1.106  1994/12/01  02:22:33  john
 * Incorporated LOADPATS.EXE into our code.
 * 
 * Revision 1.105  1994/12/01  00:59:51  john
 * Fixed some pot. bugs with closing.
 * 
 * Revision 1.104  1994/11/30  23:54:40  rob
 * Tweaked some volume params due to a fix in find_connected_distance.
 * 
 * Revision 1.103  1994/11/30  19:36:44  john
 * Made Gravis Ultrasound work again.  Made the scores blink
 * at a constant rate.  Revamped the newmenu background storage,
 * which hopefully fixed some bugs.  Made menus in ame not pause
 * sound, except for the pause key.               ^== Game!
 * 
 * Revision 1.102  1994/11/30  15:14:25  rob
 * Removed unused include file..
 * 
 * Revision 1.101  1994/11/30  15:08:45  john
 * Changed some open/close stuff with sound.
 * 
 * Revision 1.100  1994/11/29  13:35:41  john
 * Test code.
 * 
 * Revision 1.99  1994/11/29  03:46:32  john
 * Added joystick sensitivity; Added sound channels to detail menu.  Removed -maxchannels
 * command line arg.
 * 
 * Revision 1.98  1994/11/28  18:37:59  john
 * Made sample play once work.
 * 
 * Revision 1.97  1994/11/28  18:35:19  john
 * Made the digi_max_channels cut of an old sound instead of
 * not playing a new sound.
 * 
 * Revision 1.96  1994/11/28  01:32:02  mike
 * use quick form of matrix function.
 * 
 * Revision 1.95  1994/11/27  23:12:14  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.94  1994/11/22  17:13:31  john
 * Fixed bug with the digital drums hanging.
 * 
 * Revision 1.93  1994/11/21  19:09:21  john
 * Made so if digi and midi both 0, same as -nosound.
 * 
 * Revision 1.92  1994/11/21  16:46:46  john
 * Limited digital channels to 10.
 * 
 * Revision 1.91  1994/11/21  16:28:42  john
 * Fixed bug with digi_close hanging.
 * 
 * Revision 1.90  1994/11/21  15:40:28  john
 * Locked down the instrument data.
 * 
 * Revision 1.89  1994/11/21  14:43:55  john
 * Fixed some bugs with setting volumes even when -nosound was used. Duh!
 * 
 * Revision 1.88  1994/11/21  11:55:26  john
 * Fixed some sound pausing in menus bugs.
 * 
 * Revision 1.87  1994/11/21  11:02:21  john
 * Made fan sounds be 1/2 the volume so that they
 * don'
 * don't carry as far.
 * 
 * Revision 1.86  1994/11/20  17:47:51  john
 * Fixed a potential bug with sound initializing.
 * 
 * Revision 1.85  1994/11/20  17:29:07  john
 * Fixed bug with page fault during digi_close.
 * 
 * Revision 1.84  1994/11/19  15:19:24  mike
 * rip out unused code and data.
 * 
 * Revision 1.83  1994/11/16  23:38:33  mike
 * new improved boss teleportation behavior.
 * 
 * Revision 1.82  1994/11/14  18:12:46  john
 * Took out some sound objects stuff.
 * 
 */

static char rcsid[] = "$Id: digi.c 2.5 1996/01/05 16:51:51 john Exp $";
#pragma unused(rcsid)

#ifdef ANDROID_NDK
#include <SLES/OpenSLES_Android.h>
#else
#include <OpenAL/OpenAL.h>
#endif
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
//#include<bios.h>
#include<string.h>
#include<ctype.h>
#include <math.h>

#include "fix.h"
#include "object.h"
#include "mono.h"
#include "timer.h"
#include "joy.h"
#include "digi.h"
#include "sounds.h"
#include "args.h"
#include "key.h"
#include "newdemo.h"
#include "game.h"
#include "dpmi.h"
#include "error.h"
#include "wall.h"
#include "cfile.h"
#include "piggy.h"
#include "text.h"
#include "hmp.h"

#pragma pack (4)						// Use 32-bit packing!
#pragma off (check_stack);			// No stack checking!
//*************************************************
//#include "sos.h"
//#include "sosm.h"
//The above two includes are part of a commercial 
//sound library, so they cannot be included in a public 
//release of the source code. -KRB
#include "no_sos.h" //Added by KRB
//*************************************************
#include "kconfig.h"
//#include "soscomp.h"

#define DIGI_PAUSE_BROKEN 1		//if this is defined, don't pause MIDI songs

#define _VOLUME 0x100
#define _PANNING 0x200
#define _DIGI_SAMPLE_FLAGS (_VOLUME | _PANNING )
#define _CENTER_CHANNEL 0

#define _DIGI_MAX_VOLUME (16384.0f)	//16384

// patch files
#define  _MELODIC_PATCH       "melodic.bnk"
#define  _DRUM_PATCH          "drum.bnk"
#define  _DIGDRUM_PATCH       "drum32.dig"

#define _MAX_VOICES 24
#define _LOOPING 0xBADF00D
 
static int	Digi_initialized 		= 0;

int digi_driver_board				= 0;
int digi_driver_port					= 0;
int digi_driver_irq					= 0;
int digi_driver_dma					= 0;
int digi_midi_type					= 0;			// Midi driver type
int digi_midi_port					= 0;			// Midi driver port
static int digi_max_channels		= 8;
static unsigned int digi_driver_rate		= 11025;			// rate to use driver at
int digi_timer_rate					= 9943;			// rate for the timer to go off to handle the driver system (120 Hz)
int digi_lomem 						= 0;
static int digi_volume				= _DIGI_MAX_VOLUME;		// Max volume
static int midi_volume				= 128/2;						// Max volume
static int digi_system_initialized		= 0;
static int timer_system_initialized		= 0;
static int digi_sound_locks[MAX_SOUNDS];
static int digi_midi_playing = false;
char digi_last_midi_song[16] = "";
char digi_last_melodic_bank[16] = "";
char digi_last_drum_bank[16] = "";
hmp_file *cur_hmp = NULL;

// handle for the initialized MIDI song
SLint16    wSongHandle = 0xffff;
ubyte		*SongData=NULL;
int		SongSize;

// OpenSL ES stuff
SLObjectItf engine_obj;
SLEngineItf engine;
SLObjectItf output_mix_obj;
SLDataFormat_PCM format;
SLDataLocator_OutputMix out_loc;
SLDataSink dst;

// OpenSL ES Sound objects
static int next_handle = 0;
static SLObjectItf PlayerObjs[_MAX_VOICES];
static SLPlayItf Players[_MAX_VOICES];
static SLDataLocator_AndroidSimpleBufferQueue In_locs[_MAX_VOICES];
static SLAndroidSimpleBufferQueueItf BufferQueues[_MAX_VOICES];
static SLDataSource Sources[_MAX_VOICES];
static SLVolumeItf Volumes[_MAX_VOICES];
static bool SoundDone[_MAX_VOICES];
static int SoundNums[_MAX_VOICES] = { -1 };
static struct sound_object *SoundObjPtrs[_MAX_VOICES];

#define SOF_USED				1 		// Set if this sample is used
#define SOF_PLAYING			2		// Set if this sample is playing on a channel
#define SOF_LINK_TO_OBJ		4		// Sound is linked to a moving object. If object dies, then finishes play and quits.
#define SOF_LINK_TO_POS		8		// Sound is linked to segment, pos
#define SOF_PLAY_FOREVER	16		// Play forever (or until level is stopped), otherwise plays once

typedef struct sound_object {
	short			signature;		// A unique signature to this sound
	ubyte			flags;			// Used to tell if this slot is used and/or currently playing, and how long.
	fix			max_volume;		// Max volume that this sound is playing at
	fix			max_distance;	// The max distance that this sound can be heard at...
	int			volume;			// Volume that this sound is playing at
	int			pan;				// Pan value that this sound is playing at
	int		handle;			// What handle this sound is playing on.  Valid only if SOF_PLAYING is set.
	short			soundnum;		// The sound number that is playing
	union {	
		struct {
			short			segnum;				// Used if SOF_LINK_TO_POS field is used
			short			sidenum;				
			vms_vector	position;
		};
		struct {
			short			objnum;				// Used if SOF_LINK_TO_OBJ field is used
			short			objsignature;
		};
	};
	void *sample_data;
	SLuint32 data_size;
} sound_object;

typedef struct _SOS_START_SAMPLE {
	int wLoopCount;
	int wChannel;
	long wVolume;
	int wSampleID;
	SLuint32 dwSampleSize;
	long dwSampleByteLength;
	ubyte *lpSamplePtr;
	void *lpCallback;
	int wSamplePanLocation;
	int wSamplePanSpeed;
	int wSampleFlags;
} _SOS_START_SAMPLE;

#define MAX_SOUND_OBJECTS _MAX_VOICES
sound_object SoundObjects[MAX_SOUND_OBJECTS];
short next_signature=0;

int digi_sounds_initialized=0;
//this block commented out by KRB


void * testLoadFile( char * szFileName, int * length );

//NOT_MIDI_CHECKushort MIDI_CRC;
//NOT_MIDI_CHECKubyte MIDI_SAVED_DATA[100*1024];
/*


*/

int digi_xlat_sound(int soundno)
{
	if ( soundno < 0 ) return -1;

	if ( digi_lomem )	{
		soundno = AltSounds[soundno];
		if ( soundno == 255 ) return -1;
	}
	return Sounds[soundno];
}


void digi_close_midi() {
	hmp_stop(cur_hmp);
	hmp_close(cur_hmp);
}

void digi_close_digi() {
	int i;
	
	for (i = 0; i < _MAX_VOICES; ++i) {
		if (PlayerObjs[i]) {
			(*PlayerObjs[i])->Destroy(PlayerObjs[i]);
			PlayerObjs[i] = NULL;
			Players[i] = NULL;
			Volumes[i] = NULL;
			BufferQueues[i] = NULL;
			SoundDone[i] = false;
		}
	}
	(*output_mix_obj)->Destroy( output_mix_obj );
	output_mix_obj = NULL;

	(*engine_obj)->Destroy( engine_obj );
	engine_obj = NULL;
	engine = NULL;
	digi_driver_board = 0;
}


void digi_close() {
	if (!Digi_initialized) return;
	if (timer_system_initialized) {
		// Remove timer...
		timer_set_function(NULL);
	}

	digi_close_digi();
	digi_close_midi();

	digi_system_initialized = 0;
	timer_system_initialized = 0;
	Digi_initialized = 0;
}

extern int loadpats( char * filename );

int digi_load_fm_banks( char * melodic_file, char * drum_file ) {
	// Don't need this old-school stuff anymore
	return 0;
}

int digi_init_midi() {
	hmp_init();
	digi_midi_type = 1;
	return 0;
}

int digi_init_digi() {
	int i;

	slCreateEngine(&engine_obj, 0, NULL, 0, NULL, NULL);
	(*engine_obj)->Realize(engine_obj, SL_BOOLEAN_FALSE);
	(*engine_obj)->GetInterface(engine_obj, SL_IID_ENGINE, &engine);
	(*engine)->CreateOutputMix(engine, &output_mix_obj, 0, NULL, NULL);
	(*output_mix_obj)->Realize(output_mix_obj, SL_BOOLEAN_FALSE);
	format.formatType = SL_DATAFORMAT_PCM;
	format.numChannels = 1;
	format.samplesPerSec = digi_driver_rate * 1000;
	format.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_8;
	format.containerSize = 8;
	format.channelMask = SL_SPEAKER_FRONT_CENTER;
	format.endianness = SL_BYTEORDER_LITTLEENDIAN;
	out_loc.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	out_loc.outputMix = output_mix_obj;
	dst.pLocator = &out_loc;
	dst.pFormat = NULL;
	Digi_initialized = 1;
	digi_driver_board = 1;

	for (i = 0; i < MAX_SOUND_OBJECTS; ++i) {
		SoundObjects[i].handle = -1;
	}
	for (i = 0; i < _MAX_VOICES; ++i) {
		PlayerObjs[i] = NULL;
		Players[i] = NULL;
		Volumes[i] = NULL;
		BufferQueues[i] = NULL;
		SoundDone[i] = false;
		SoundObjPtrs[i] = NULL;
	}
	return 0;
}

int digi_init()
{
	digi_init_digi();
	digi_init_midi();
	return 0;
}

// Toggles sound system on/off
void digi_reset() {

}

int digi_total_locks = 0;

// Is this needed?
ubyte * digi_lock_sound_data( int soundnum ) {
	return NULL;
}

// Or this?
void digi_unlock_sound_data( int soundnum ) {

}

void digi_reset_digi_sounds()
{
	int i;
	SLuint32 state;

	if ( !Digi_initialized ) return;
	if ( digi_driver_board <= 0 )	return;

	for (i=0; i<_MAX_VOICES; i++ )	{
		if (PlayerObjs[i])	{
			(*Players[i])->GetPlayState(Players[i], &state);
			if ( state == SL_PLAYSTATE_PLAYING ) {
				(*PlayerObjs[i])->Destroy(PlayerObjs[i]);
				PlayerObjs[i] = NULL;
				Players[i] = NULL;
				Volumes[i] = NULL;
				BufferQueues[i] = NULL;
				SoundDone[i] = false;
			}
		}
		if ( SoundNums[i] != -1 )	{
			digi_unlock_sound_data(SoundNums[i]);
			SoundNums[i] = -1;
		}
	}
	for (i=0; i<MAX_SOUNDS; i++ )	{
		Assert( digi_sound_locks[i] == 0 );
	}
}

void reset_sounds_on_channel( int channel )
{
}


void digi_set_max_channels(int n)
{
	digi_max_channels	= n;

	if ( digi_max_channels < 1 ) 
		digi_max_channels = 1;
	digi_max_channels = _MAX_VOICES;

	if ( !Digi_initialized ) return;
	if ( digi_driver_board <= 0 )	return;

	digi_reset_digi_sounds();
}

int digi_get_max_channels()
{
	return digi_max_channels;
}

SLmillibel gain_to_attenuation( float gain ) {
	return (SLmillibel)(gain < 0.01f ? -96.0f : 20 * log10f(gain));
}

void SLAPIENTRY loop_callback( SLPlayItf player,
							  void *context, SLuint32 event ) {
	bool *need_loop = context;

	if(event & SL_PLAYEVENT_HEADATEND) {
		*need_loop = true;
	}
}

int digi_start_sound(_SOS_START_SAMPLE *sampledata, short soundnum) {
	const SLInterfaceID ids[] = {SL_IID_VOLUME, SL_IID_ANDROIDSIMPLEBUFFERQUEUE};
	const SLboolean req[] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	int retval;
	SLpermille pan;
	SLresult result;

	In_locs[next_handle].locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	In_locs[next_handle].numBuffers = 1;
	Sources[next_handle].pLocator = &In_locs[next_handle];
	Sources[next_handle].pFormat = &format;
	if (PlayerObjs[next_handle] != NULL) {
		(*PlayerObjs[next_handle])->Destroy(PlayerObjs[next_handle]);
		PlayerObjs[next_handle] = NULL;
		Players[next_handle] = NULL;
		Volumes[next_handle] = NULL;
		BufferQueues[next_handle] = NULL;
		SoundDone[next_handle] = false;
		if (SoundObjPtrs[next_handle] != NULL) {
			SoundObjPtrs[next_handle]->handle = -1;
			SoundObjPtrs[next_handle]->flags &= ~SOF_PLAYING;
			SoundObjPtrs[next_handle] = NULL;
		}
	}
	(*engine)->CreateAudioPlayer(engine, &PlayerObjs[next_handle], &Sources[next_handle], &dst,
								 2, ids, req);
	result = (*PlayerObjs[next_handle])->Realize(PlayerObjs[next_handle], SL_BOOLEAN_FALSE);
	if (result != SL_RESULT_SUCCESS) {
		--next_handle;
		if (next_handle < 0) next_handle = 0;
		return -1;
	}
	(*PlayerObjs[next_handle])->GetInterface(PlayerObjs[next_handle], SL_IID_PLAY,
											 &Players[next_handle]);
	(*PlayerObjs[next_handle])->GetInterface(PlayerObjs[next_handle], SL_IID_VOLUME,
											 &Volumes[next_handle]);
	(*PlayerObjs[next_handle])->GetInterface(PlayerObjs[next_handle],
											 SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
											 &BufferQueues[next_handle]);
	(*Volumes[next_handle])->SetVolumeLevel(Volumes[next_handle], gain_to_attenuation(
			(digi_volume / _DIGI_MAX_VOLUME) * (sampledata->wVolume / _DIGI_MAX_VOLUME)) *
																  (SLmillibel) 100);
	pan = (SLpermille) (((sampledata->wSamplePanLocation * 2000) / 0xffff) - 1000);
	(*Volumes[next_handle])->EnableStereoPosition(Volumes[next_handle], SL_BOOLEAN_TRUE);
	(*Volumes[next_handle])->SetStereoPosition(Volumes[next_handle], pan);
	(*BufferQueues[next_handle])->Enqueue(BufferQueues[next_handle], sampledata->lpSamplePtr,
										  sampledata->dwSampleSize);
	(*Players[next_handle])->RegisterCallback(Players[next_handle], loop_callback,
											  &SoundDone[next_handle]);
	(*Players[next_handle])->SetCallbackEventsMask(Players[next_handle],
												   SL_PLAYEVENT_HEADATEND);
	(*Players[next_handle])->SetPlayState(Players[next_handle], SL_PLAYSTATE_PLAYING);
	retval = next_handle++;
	if (next_handle >= _MAX_VOICES) {
		next_handle = 0;
	}
	return retval;
}

int digi_is_sound_playing(int soundno)
{
	soundno = digi_xlat_sound(soundno);
	SLuint32 state;

	if (!Digi_initialized) return 0;
	if (digi_driver_board<1) return 0;

	if (soundno < 0 ) return 0;
	if (GameSounds[soundno].data==NULL) {
		Int3();
		return 0;
	}

	return SoundDone[soundno];
}

void digi_play_sample_once( int soundno, fix max_volume )	
{
	digi_sound *snd;
	_SOS_START_SAMPLE sSOSSampleData;

#ifdef NEWDEMO
	if ( Newdemo_state == ND_STATE_RECORDING )
		newdemo_record_sound( soundno );
#endif
	soundno = digi_xlat_sound(soundno);

	if (!Digi_initialized) return;
	if (digi_driver_board<1) return;
	if (soundno < 0 ) return;
	snd = &GameSounds[soundno];
	if (snd==NULL) {
		Int3();
		return;
	}

	memset( &sSOSSampleData, 0, sizeof(_SOS_START_SAMPLE));
	sSOSSampleData.wLoopCount 				= 0x00;
	sSOSSampleData.wChannel 				= _CENTER_CHANNEL;
	sSOSSampleData.wVolume					= fixmuldiv(max_volume,digi_volume,F1_0);
	sSOSSampleData.wSampleID				= soundno;
	sSOSSampleData.dwSampleSize 			= snd->length;
	sSOSSampleData.lpSamplePtr				= snd->data;
	sSOSSampleData.lpCallback				= NULL;		//sosDIGISampleCallback;
	sSOSSampleData.wSamplePanLocation	= (int)(0xffff/2);
	sSOSSampleData.wSamplePanSpeed 		= 0;
	sSOSSampleData.wSampleFlags			= _DIGI_SAMPLE_FLAGS;

//	if ( sosDIGISamplesPlaying(hSOSDigiDriver) >= digi_max_channels )
//		return;

	// start the sample playing
	SoundObjPtrs[digi_start_sound( &sSOSSampleData, soundno )] = NULL;
}

void digi_play_sample(int soundno, fix max_volume) {

	digi_sound *snd = NULL;
	_SOS_START_SAMPLE sSOSSampleData;

#ifdef NEWDEMO
	if (Newdemo_state == ND_STATE_RECORDING)
		newdemo_record_sound(soundno);
#endif
	soundno = digi_xlat_sound(soundno);

	if (!Digi_initialized) return;
	// if (digi_driver_board < 1) return; // Irrellevant
	if (soundno < 0) return;
	snd = &GameSounds[soundno];
	if (snd == NULL) {
		Int3();
		return;
	}

	//mprintf( (0, "Playing sample of length %d\n", snd->length ));
	memset(&sSOSSampleData, 0, sizeof(_SOS_START_SAMPLE));
	sSOSSampleData.wLoopCount = 0x00;
	sSOSSampleData.wChannel = _CENTER_CHANNEL;
	sSOSSampleData.wVolume = fixmuldiv(max_volume, digi_volume, F1_0);
	sSOSSampleData.wSampleID = soundno;
	sSOSSampleData.dwSampleSize = snd->length;
	sSOSSampleData.lpSamplePtr = snd->data;
	sSOSSampleData.lpCallback = NULL;		//sosDIGISampleCallback;
	sSOSSampleData.wSamplePanLocation = (int)(0xffff / 2);
	sSOSSampleData.wSamplePanSpeed = 0;
	sSOSSampleData.wSampleFlags = _DIGI_SAMPLE_FLAGS;

	//	if ( sosDIGISamplesPlaying(hSOSDigiDriver) >= digi_max_channels )
	//		return;

	   // start the sample playing
	digi_start_sound(&sSOSSampleData, soundno);
}


void digi_play_sample_3d( int soundno, int angle, int volume, int no_dups )	
{
	_SOS_START_SAMPLE sSOSSampleData;
	digi_sound *snd;

	no_dups = 1;

#ifdef NEWDEMO
	if ( Newdemo_state == ND_STATE_RECORDING )		{
		if ( no_dups )
			newdemo_record_sound_3d_once( soundno, angle, volume );
		else
			newdemo_record_sound_3d( soundno, angle, volume );
	}
#endif
	soundno = digi_xlat_sound(soundno);

	if (!Digi_initialized) return;
	//if (digi_driver_board<1) return;
	if (soundno < 0 ) return;
	snd = &GameSounds[soundno];
	if (snd==NULL) {
		Int3();
		return;
	}

	if (volume < 10 ) return;

	memset( &sSOSSampleData, 0, sizeof(_SOS_START_SAMPLE));
	sSOSSampleData.wLoopCount 		= 0x00;
	sSOSSampleData.wChannel 		= _CENTER_CHANNEL;
	sSOSSampleData.wSampleID		= soundno;
	sSOSSampleData.dwSampleSize 	= snd->length;
	sSOSSampleData.dwSampleByteLength 	= ( long )snd->length;
	sSOSSampleData.lpSamplePtr		= snd->data;
	sSOSSampleData.lpCallback		= NULL;		//sosDIGISampleCallback;
	sSOSSampleData.wSamplePanLocation	= angle;			// 0 - 0xFFFF
	sSOSSampleData.wSamplePanSpeed 		= 0;
	sSOSSampleData.wVolume					= fixmuldiv(volume,digi_volume,F1_0);;					// 0 - 0x7fff
	sSOSSampleData.wSampleFlags			= _DIGI_SAMPLE_FLAGS;

   // start the sample playing
	digi_start_sound( &sSOSSampleData, soundno );
}

void digi_set_midi_volume( int mvolume )
{
	if ( mvolume > 127 )
		midi_volume = 127;
	else if ( mvolume < 0 )
		midi_volume = 0;
	else
		midi_volume = mvolume;

	hmp_setvolume(cur_hmp, midi_volume);
}

void digi_set_digi_volume( int dvolume )
{
	dvolume = fixmuldiv( dvolume, _DIGI_MAX_VOLUME, 0x7fff);
	if ( dvolume > _DIGI_MAX_VOLUME )
		digi_volume = _DIGI_MAX_VOLUME;
	else if ( dvolume < 0 )
		digi_volume = 0;
	else
		digi_volume = dvolume;

	if ( !Digi_initialized ) return;
	//if ( digi_driver_board <= 0 )	return;

	digi_sync_sounds();
}


// 0-0x7FFF 
void digi_set_volume( int dvolume, int mvolume )	
{
	digi_set_midi_volume( mvolume );
	digi_set_digi_volume( dvolume );
//	mprintf(( 1, "Volume: 0x%x and 0x%x\n", digi_volume, midi_volume ));
}

// allocate memory for file, load file, create far pointer
// with DS in selector.
void * testLoadFile( char * szFileName, int * length )
{
	/*char  pDataPtr;
	CFILE * fp;
	
   // open file
   fp  =  cfopen( szFileName, "rb" );
	if ( !fp ) return NULL;

   *length  =  cfilelength(fp);

   pDataPtr =  malloc( *length );
	if ( !pDataPtr ) return NULL;

   // read in driver
   cfread( &pDataPtr, *length, 1, fp);

   // close driver file
   cfclose( fp );

   // return 
   return( pDataPtr );*/
	return NULL;
}

void digi_stop_current_song() {
	if (!digi_midi_playing)
		return;
	hmp_stop(cur_hmp);
	digi_midi_playing = 0;
}

int digi_play_midi_song(char * filename, char * melodic_bank, char * drum_bank, int loop) {
	digi_stop_current_song();
	if (!filename) {
		return 0;
	}
	if ((cur_hmp = hmp_open(filename))) {
		if (hmp_play(cur_hmp, loop) != 0)
			return 0;	// error
		digi_midi_playing = 1;
		digi_set_midi_volume(midi_volume);
	}
	return 1;
}

void digi_get_sound_loc( vms_matrix * listener, vms_vector * listener_pos, int listener_seg, vms_vector * sound_pos, int sound_seg, fix max_volume, int *volume, int *pan, fix max_distance )	
{	  
	vms_vector	vector_to_sound;
	fix angle_from_ear, cosang,sinang;
	fix distance;
	fix path_distance;

	*volume = 0;
	*pan = 0;

	max_distance = (max_distance*5)/4;		// Make all sounds travel 1.25 times as far.

	//	Warning: Made the vm_vec_normalized_dir be vm_vec_normalized_dir_quick and got illegal values to acos in the fang computation.
	distance = vm_vec_normalized_dir_quick( &vector_to_sound, sound_pos, listener_pos );
		
	if (distance < max_distance )	{
		int num_search_segs = f2i(max_distance/20);
		if ( num_search_segs < 1 ) num_search_segs = 1;

		path_distance = find_connected_distance(listener_pos, listener_seg, sound_pos, sound_seg, num_search_segs, WID_RENDPAST_FLAG );
		if ( path_distance > -1 )	{
			*volume = max_volume - fixdiv(path_distance,max_distance);
			//mprintf( (0, "Sound path distance %.2f, volume is %d / %d\n", f2fl(distance), *volume, max_volume ));
			if (*volume > 0 )	{
				angle_from_ear = vm_vec_delta_ang_norm(&listener->rvec,&vector_to_sound,&listener->uvec);
				fix_sincos(angle_from_ear,&sinang,&cosang);
				//mprintf( (0, "volume is %.2f\n", f2fl(*volume) ));
				if (Config_channels_reversed) cosang *= -1;
				*pan = (cosang + F1_0)/2;
			} else {
				*volume = 0;
			}
		}
	}																					  
}


void digi_init_sounds()
{
	int i;

	if (!Digi_initialized) return;
	if (digi_driver_board<1) return;

	digi_reset_digi_sounds();

	for (i=0; i<MAX_SOUND_OBJECTS; i++ ) {
		if (digi_sounds_initialized) {
			if (SoundObjects[i].flags & SOF_PLAYING && SoundObjects[i].handle != -1 && PlayerObjs[SoundObjects[i].handle]) {
				(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
				PlayerObjs[SoundObjects[i].handle] = NULL;
				Players[SoundObjects[i].handle] = NULL;
				Volumes[SoundObjects[i].handle] = NULL;
				BufferQueues[SoundObjects[i].handle] = NULL;
				SoundDone[SoundObjects[i].handle] = false;
				SoundObjects[i].handle = -1;
			}
		}
		SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
	}
	digi_sounds_initialized = 1;
}

void digi_start_sound_object(int i)
{
	// start sample structures 
	_SOS_START_SAMPLE sSOSSampleData;

	memset( &sSOSSampleData, 0, sizeof(_SOS_START_SAMPLE));

	if (!Digi_initialized) return;
	if (digi_driver_board<1) return;

	if (!dpmi_lock_region( GameSounds[SoundObjects[i].soundnum].data, GameSounds[SoundObjects[i].soundnum].length ))
		Error( "Error locking sound object %d\n", SoundObjects[i].soundnum );
	
	// Sound is not playing, so we must start it again
	SoundObjects[i].signature=next_signature++;
	sSOSSampleData.wChannel 		= _CENTER_CHANNEL;
	sSOSSampleData.wSampleID		= SoundObjects[i].soundnum;
	sSOSSampleData.dwSampleSize 	= GameSounds[SoundObjects[i].soundnum].length;
	sSOSSampleData.lpSamplePtr		= GameSounds[SoundObjects[i].soundnum].data;
	sSOSSampleData.lpCallback		= NULL;		//sosDIGISampleCallback;
	sSOSSampleData.wSamplePanLocation	= SoundObjects[i].pan;			// 0 - 0xFFFF
	sSOSSampleData.wSamplePanSpeed 		= 0;
	sSOSSampleData.wVolume					= fixmuldiv(SoundObjects[i].volume,digi_volume,F1_0);					// 0 - 0x7fff
	sSOSSampleData.wSampleFlags			= _DIGI_SAMPLE_FLAGS;
	if (SoundObjects[i].flags & SOF_PLAY_FOREVER )	{
		sSOSSampleData.wLoopCount 		= -1;				// loop forever.
		sSOSSampleData.wSampleFlags |= _LOOPING; 		// Mark it as a looper.
	}

	// start the sample playing
	SoundObjects[i].sample_data = sSOSSampleData.lpSamplePtr;
	SoundObjects[i].data_size = sSOSSampleData.dwSampleSize;
	SoundObjects[i].handle = digi_start_sound(&sSOSSampleData, SoundObjects[i].soundnum);
	SoundObjPtrs[SoundObjects[i].handle] = &SoundObjects[i];

	if (SoundObjects[i].handle != -1 )		{
		SoundObjects[i].flags |= SOF_PLAYING;
		//mprintf(( 0, "Starting sound object %d on channel %d\n", i, SoundObjects[i].handle ));
		reset_sounds_on_channel( SoundObjects[i].handle );
	}
//	else
//		mprintf( (1, "[Out of channels: %i] ", i ));
}

int digi_link_sound_to_object2( int org_soundnum, short objnum, int forever, fix max_volume, fix  max_distance )
{
	int i,volume,pan;
	object * objp;
	int soundnum;

	soundnum = digi_xlat_sound(org_soundnum);

	if ( max_volume < 0 ) return -1;
//	if ( max_volume > F1_0 ) max_volume = F1_0;

	if (!Digi_initialized) return -1;
	if (soundnum < 0 ) return -1;
	if (GameSounds[soundnum].data==NULL) {
		Int3();
		return -1;
	}
	if ((objnum<0)||(objnum>Highest_object_index))
		return -1;
	//if (digi_driver_board<1) return -1;

	if ( !forever )	{
		// Hack to keep sounds from building up...
		digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, &Objects[objnum].pos, Objects[objnum].segnum, max_volume,&volume, &pan, max_distance );
		digi_play_sample_3d( org_soundnum, pan, volume, 0 );
		return -1;
	}

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )
		if (SoundObjects[i].flags==0)
			break;
	
	if (i==MAX_SOUND_OBJECTS) {
		mprintf((1, "Too many sound objects!\n" ));
		return -1;
	}

	SoundObjects[i].signature=next_signature++;
	SoundObjects[i].flags = SOF_USED | SOF_LINK_TO_OBJ;
	if ( forever )
		SoundObjects[i].flags |= SOF_PLAY_FOREVER;
	SoundObjects[i].objnum = objnum;
	SoundObjects[i].objsignature = Objects[objnum].signature;
	SoundObjects[i].max_volume = max_volume;
	SoundObjects[i].max_distance = max_distance;
	SoundObjects[i].volume = 0;
	SoundObjects[i].pan = 0;
	SoundObjects[i].soundnum = soundnum;

	objp = &Objects[SoundObjects[i].objnum];
	digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, 
                       &objp->pos, objp->segnum, SoundObjects[i].max_volume,
                       &SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance );

	digi_start_sound_object(i);

	return SoundObjects[i].signature;
}

int digi_link_sound_to_object( int soundnum, short objnum, int forever, fix max_volume )
{																									// 10 segs away
	return digi_link_sound_to_object2( soundnum, objnum, forever, max_volume, 256*F1_0  );
}

int digi_link_sound_to_pos2( int org_soundnum, short segnum, short sidenum, vms_vector * pos, int forever, fix max_volume, fix max_distance )
{
	int i, volume, pan;
	int soundnum;

	soundnum = digi_xlat_sound(org_soundnum);

	if ( max_volume < 0 ) return -1;
//	if ( max_volume > F1_0 ) max_volume = F1_0;

	if (!Digi_initialized) return -1;
	if (soundnum < 0 ) return -1;
	if (GameSounds[soundnum].data==NULL) {
		Int3();
		return -1;
	}
	// Ignore!
	//if (digi_driver_board<1) return -1;

	if ((segnum<0)||(segnum>Highest_segment_index))
		return -1;

	if ( !forever )	{
		// Hack to keep sounds from building up...
		digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, pos, segnum, max_volume, &volume, &pan, max_distance );
		digi_play_sample_3d( org_soundnum, pan, volume, 0 );
		return -1;
	}

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )
		if (SoundObjects[i].flags==0)
			break;
	
	if (i==MAX_SOUND_OBJECTS) {
		mprintf((1, "Too many sound objects!\n" ));
		return -1;
	}


	SoundObjects[i].signature=next_signature++;
	SoundObjects[i].flags = SOF_USED | SOF_LINK_TO_POS;
	if ( forever )
		SoundObjects[i].flags |= SOF_PLAY_FOREVER;
	SoundObjects[i].segnum = segnum;
	SoundObjects[i].sidenum = sidenum;
	SoundObjects[i].position = *pos;
	SoundObjects[i].soundnum = soundnum;
	SoundObjects[i].max_volume = max_volume;
	SoundObjects[i].max_distance = max_distance;
	SoundObjects[i].volume = 0;
	SoundObjects[i].pan = 0;
	digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, 
                       &SoundObjects[i].position, SoundObjects[i].segnum, SoundObjects[i].max_volume,
                       &SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance );
	
	digi_start_sound_object(i);

	return SoundObjects[i].signature;
}

int digi_link_sound_to_pos( int soundnum, short segnum, short sidenum, vms_vector * pos, int forever, fix max_volume )
{
	return digi_link_sound_to_pos2( soundnum, segnum, sidenum, pos, forever, max_volume, F1_0 * 256 );
}


void digi_kill_sound_linked_to_segment( int segnum, int sidenum, int soundnum ) {
	int i,killed;

	soundnum = digi_xlat_sound(soundnum);

	if (!Digi_initialized) return;
	if (digi_driver_board<1) return;

	killed = 0;

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
		if ( (SoundObjects[i].flags & SOF_USED) && (SoundObjects[i].flags & SOF_LINK_TO_POS) )	{
			if ((SoundObjects[i].segnum == segnum) && (SoundObjects[i].soundnum==soundnum ) && (SoundObjects[i].sidenum==sidenum) )	{
				if ( SoundObjects[i].flags & SOF_PLAYING && SoundObjects[i].handle != -1 )	{
					(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
					PlayerObjs[SoundObjects[i].handle] = NULL;
					Players[SoundObjects[i].handle] = NULL;
					Volumes[SoundObjects[i].handle] = NULL;
					BufferQueues[SoundObjects[i].handle] = NULL;
					SoundDone[SoundObjects[i].handle] = false;
					SoundObjects[i].handle = -1;
				}
				SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
				killed++;
			}
		}
	}
	// If this assert happens, it means that there were 2 sounds
	// that got deleted. Weird, get John.
	if ( killed > 1 )	{
		mprintf( (1, "ERROR: More than 1 sounds were deleted from seg %d\n", segnum ));
	}
}

void digi_kill_sound_linked_to_object( int objnum ) {
	int i,killed;

	if (!Digi_initialized) return;
	if (digi_driver_board<1) return;

	killed = 0;

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
		if ( (SoundObjects[i].flags & SOF_USED) && (SoundObjects[i].flags & SOF_LINK_TO_OBJ ) )	{
			if (SoundObjects[i].objnum == objnum)	{
				if ( SoundObjects[i].flags & SOF_PLAYING && SoundObjects[i].handle != -1 )	{
					(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
					PlayerObjs[SoundObjects[i].handle] = NULL;
					Players[SoundObjects[i].handle] = NULL;
					Volumes[SoundObjects[i].handle] = NULL;
					BufferQueues[SoundObjects[i].handle] = NULL;
					SoundDone[SoundObjects[i].handle] = false;
					SoundObjects[i].handle = -1;
				}
				SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
				killed++;
			}
		}
	}
	// If this assert happens, it means that there were 2 sounds
	// that got deleted. Weird, get John.
	if ( killed > 1 )	{
		mprintf( (1, "ERROR: More than 1 sounds were deleted from object %d\n", objnum ));
	}
}


//--unused-- void digi_kill_sound( int signature )
//--unused-- {
//--unused-- 	int i;
//--unused-- 	if (!Digi_initialized) return;
//--unused-- 
//--unused-- 	for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
//--unused-- 		if ( SoundObjects[i].flags & SOF_USED )	{
//--unused-- 			if (SoundObjects[i].signature == signature )	{
//--unused-- 				if ( SoundObjects[i].flags & SOF_PLAYING )	{
//--unused-- 					sosDIGIStopSample( hSOSDigiDriver, SoundObjects[i].handle );
//--unused-- 				}
//--unused-- 				SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
//--unused-- 			}
//--unused-- 		}
//--unused-- 	}
//--unused-- }

void digi_sync_sounds()
{
	int i;
	int oldvolume, oldpan;
	SLuint32 state;
	SLpermille pan;

	if (!Digi_initialized) return;
	if (digi_driver_board<1) return;

//NOT_MIDI_CHECK	if (SongData)	{
//NOT_MIDI_CHECK		ushort new_crc;
//NOT_MIDI_CHECK		new_crc = netmisc_calc_checksum( &SongData, SongSize );
//NOT_MIDI_CHECK		if ( new_crc != MIDI_CRC )	{
//NOT_MIDI_CHECK			for (i=0; i<SongSize; i++ )	{
//NOT_MIDI_CHECK				if ( MIDI_SAVED_DATA[i] != SongData[i] )	{
//NOT_MIDI_CHECK					mprintf(( 0, "MIDI[%d] CHANGED FROM 0x%x to 0x%x\n", i, MIDI_SAVED_DATA[i], SongData[i] ));
//NOT_MIDI_CHECK					MIDI_SAVED_DATA[i] = SongData[i];
//NOT_MIDI_CHECK				}
//NOT_MIDI_CHECK			}		
//NOT_MIDI_CHECK			//Int3();		// Midi data changed!!!!
//NOT_MIDI_CHECK			MIDI_CRC=new_crc;
//NOT_MIDI_CHECK		}
//NOT_MIDI_CHECK	}

	for (i = 0; i < MAX_SOUND_OBJECTS; i++) {
		if (SoundObjects[i].flags & SOF_USED) {
			oldvolume = SoundObjects[i].volume;
			oldpan = SoundObjects[i].pan;

			if (SoundDone[SoundObjects[i].handle]) {
				SoundObjects[i].flags &= ~SOF_PLAYING;
			}
			if (!(SoundObjects[i].flags & SOF_PLAY_FOREVER)) {
				// Check if its done.
				if (SoundObjects[i].flags & SOF_PLAYING && SoundObjects[i].handle != -1) {
					(*Players[SoundObjects[i].handle])->GetPlayState(SoundObjects[i].handle, &state);
					if (state == SL_PLAYSTATE_PLAYING) {
						(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
						PlayerObjs[SoundObjects[i].handle] = NULL;
						Players[SoundObjects[i].handle] = NULL;
						Volumes[SoundObjects[i].handle] = NULL;
						BufferQueues[SoundObjects[i].handle] = NULL;
						SoundDone[SoundObjects[i].handle] = false;
						SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
						SoundObjects[i].handle = -1;
						continue;		// Go on to next sound...
					}
				}
			} else if (SoundObjects[i].handle != -1 && SoundDone[SoundObjects[i].handle]) {
				(*BufferQueues[SoundObjects[i].handle])->Enqueue(
						BufferQueues[SoundObjects[i].handle], SoundObjects[i].sample_data,
						SoundObjects[i].data_size);
				(*Players[SoundObjects[i].handle])->SetPlayState(
						Players[SoundObjects[i].handle], SL_PLAYSTATE_PLAYING);
				(*Players[SoundObjects[i].handle])->RegisterCallback(
						Players[SoundObjects[i].handle], loop_callback,
						&SoundDone[SoundObjects[i].handle]);
				(*Players[SoundObjects[i].handle])->SetCallbackEventsMask(
						Players[SoundObjects[i].handle],
						SL_PLAYEVENT_HEADATEND);
				SoundDone[SoundObjects[i].handle] = false;
				SoundObjects[i].flags |= SOF_PLAYING;
			}

			if (SoundObjects[i].flags & SOF_LINK_TO_POS) {
				digi_get_sound_loc(&Viewer->orient, &Viewer->pos, Viewer->segnum,
					&SoundObjects[i].position, SoundObjects[i].segnum, SoundObjects[i].max_volume,
					&SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance);
			}
			else if (SoundObjects[i].flags & SOF_LINK_TO_OBJ) {
				object *objp;

				objp = &Objects[SoundObjects[i].objnum];

				if ((objp->type == OBJ_NONE) || (objp->signature != SoundObjects[i].objsignature)) {
					// The object that this is linked to is dead, so just end this sound if it is looping.
					if ((SoundObjects[i].flags & SOF_PLAYING) && (SoundObjects[i].flags & SOF_PLAY_FOREVER) && SoundObjects[i].handle != -1) {
						(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
						PlayerObjs[SoundObjects[i].handle] = NULL;
						Players[SoundObjects[i].handle] = NULL;
						Volumes[SoundObjects[i].handle] = NULL;
						BufferQueues[SoundObjects[i].handle] = NULL;
						SoundDone[SoundObjects[i].handle] = false;
						SoundObjects[i].handle = -1;
					}
					SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
					continue;		// Go on to next sound...
				}
				else {
					digi_get_sound_loc(&Viewer->orient, &Viewer->pos, Viewer->segnum,
						&objp->pos, objp->segnum, SoundObjects[i].max_volume,
						&SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance);
				}
			}

			if (oldvolume != SoundObjects[i].volume) {
				if (SoundObjects[i].volume < 1) {
					// Sound is too far away, so stop it from playing.
					if ((SoundObjects[i].flags & SOF_PLAYING) && (SoundObjects[i].flags & SOF_PLAY_FOREVER) && SoundObjects[i].handle != -1) {
						(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
						PlayerObjs[SoundObjects[i].handle] = NULL;
						Players[SoundObjects[i].handle] = NULL;
						Volumes[SoundObjects[i].handle] = NULL;
						BufferQueues[SoundObjects[i].handle] = NULL;
						SoundDone[SoundObjects[i].handle] = false;
						SoundObjects[i].flags &= ~SOF_PLAYING;		// Mark sound as not playing
						SoundObjects[i].handle = -1;
					}
				}
				else {
					if (!(SoundObjects[i].flags & SOF_PLAYING)) {
						digi_start_sound_object(i);
					}
					else if (SoundObjects[i].handle != -1) {
						(*Volumes[SoundObjects[i].handle])->SetVolumeLevel(
								Volumes[SoundObjects[i].handle], gain_to_attenuation(
								(digi_volume / _DIGI_MAX_VOLUME) *
								(SoundObjects[i].volume / _DIGI_MAX_VOLUME)) * (SLmillibel) 100);
					}
				}
			}

			if (oldpan != SoundObjects[i].pan) {
				if (SoundObjects[i].flags & SOF_PLAYING && SoundObjects[i].handle != 0xffff) {
					pan = (SLpermille)(((SoundObjects[i].pan * 2000) / 0xffff) - 1000);
					(*Volumes[SoundObjects[i].handle])->SetStereoPosition(
							Volumes[SoundObjects[i].handle], pan);
				}
			}
		}
	}
}


int sound_paused = 0;

void digi_pause_all() {

	int i;

	if (!Digi_initialized) return;

	if (sound_paused==0)	{
		if ( digi_midi_type > 0 )	{
			// pause here
			//if (wSongHandle < 0xFFFF)	{
			//	// stop the last MIDI song from playing
			//	_disable();
			//	sosMIDIPauseSong( wSongHandle, _TRUE );
			//	_enable();
		  	//	mprintf(( 0, "Paused song %d\n", wSongHandle ));
		   //}
			hmp_setvolume(cur_hmp, 0);
		}
		if (digi_driver_board>0)	{
			for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
				if ( (SoundObjects[i].flags & SOF_USED) && (SoundObjects[i].flags & SOF_PLAYING)&& (SoundObjects[i].flags & SOF_PLAY_FOREVER) && SoundObjects[i].handle != -1)	{
					(*Players[SoundObjects[i].handle])->SetPlayState(Players[SoundObjects[i].handle], SL_PLAYSTATE_PAUSED);
					SoundObjects[i].flags &= ~SOF_PLAYING;		// Mark sound as not playing
				}			
			}
		}
	}
	sound_paused++;
}

void digi_resume_all() {
	int i;
	
	if (!Digi_initialized) return;

	Assert( sound_paused > 0 );

	if (sound_paused==1)	{
		// resume sound here
		if ( digi_midi_type > 0 )	{
			//if (wSongHandle < 0xffff )	{
			//   // stop the last MIDI song from playing
			//	_disable();
			//	sosMIDIResumeSong( wSongHandle );
			//	_enable();
			//	mprintf(( 0, "Resumed song %d\n", wSongHandle ));
			//}
			hmp_setvolume(cur_hmp, midi_volume);
		}
		if (digi_driver_board>0)	{
			for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
				if ( (SoundObjects[i].flags & SOF_USED) && (SoundObjects[i].flags & ~SOF_PLAYING)&& (SoundObjects[i].flags & SOF_PLAY_FOREVER) && SoundObjects[i].handle != -1 )	{
					(*Players[SoundObjects[i].handle])->SetPlayState(Players[SoundObjects[i].handle], SL_PLAYSTATE_PLAYING);
					SoundObjects[i].flags &= SOF_PLAYING;		// Mark sound as not playing
				}
			}
		}
	}
	sound_paused--;
}


void digi_stop_all() {
	int i;

	if (!Digi_initialized) return;

	if (digi_midi_type > 0) {
		if (wSongHandle < 0xffff) {
			// stop the last MIDI song from playing
			hmp_stop(cur_hmp);
			// uninitialize the last MIDI song
			hmp_close(cur_hmp);
			wSongHandle = 0xffff;
		}
		if (SongData) {
			free(SongData);
			SongData = NULL;
		}
	}

	if (digi_driver_board>0)	{
		for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
			if ( SoundObjects[i].flags & SOF_USED )	{
				if ( SoundObjects[i].flags & SOF_PLAYING && SoundObjects[i].handle != -1)	{
					(*PlayerObjs[SoundObjects[i].handle])->Destroy(PlayerObjs[SoundObjects[i].handle]);
					PlayerObjs[SoundObjects[i].handle] = NULL;
					Players[SoundObjects[i].handle] = NULL;
					Volumes[SoundObjects[i].handle] = NULL;
					BufferQueues[SoundObjects[i].handle] = NULL;
					SoundDone[SoundObjects[i].handle] = false;
					SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
					SoundObjects[i].handle = -1;
				}
				SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
			}
		}
	}
}

#ifndef NDEBUG
int verify_sound_channel_free( int channel )
{
	int i;
	if (digi_driver_board>0)	{
		for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
			if ( SoundObjects[i].flags & SOF_USED )	{
				if ( SoundObjects[i].flags & SOF_PLAYING )	{
					if ( SoundObjects[i].handle == channel )	{
						mprintf(( 0, "ERROR STARTING SOUND CHANNEL ON USED SLOT!!\n" ));
						Int3();	// Get John!
					}
				}
			}
		}
	}
	return 0;
}
#endif
