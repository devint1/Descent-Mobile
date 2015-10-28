//
//  Music.m
//  Descent
//
//  Created by Devin Tuchsen on 10/24/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//
//  This is a really gross way of doing looping since kSequenceTrackProperty_LoopInfo
//  was not working. Let me know if you can get it to work...

#import <Foundation/Foundation.h>
#import "Music.h"

@interface LoopOperation: NSOperation

@end

@implementation LoopOperation {
	MusicPlayer *musicPlayer;
	unsigned int interval;
}

- (id)initWithInterval:(unsigned int)interv withMusicPlayer:(MusicPlayer*)player {
	self->interval = interv;
	self->musicPlayer = player;
	return [super init];
}

- (void)main {
	@autoreleasepool {
		while (1) {
			sleep(interval);
			if([self isCancelled]) {
				return;
			}
			MusicPlayerSetTime(*musicPlayer, 0);
		}
	}
}
@end

LoopOperation *looper;
NSOperationQueue *queue;

void startLoop(unsigned int interval, MusicPlayer *musicPlayer) {
	looper = [[LoopOperation alloc] initWithInterval:interval withMusicPlayer:musicPlayer];
	if (!queue) {
		queue = [[NSOperationQueue alloc] init];
	}
	[queue addOperation:looper];
}

void stopLoop() {
	[queue cancelAllOperations];
}
