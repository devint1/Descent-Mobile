//
//  Motion.m
//  Descent
//
//  Created by Devin Tuchsen on 10/22/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import <CoreMotion/CoreMotion.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

CMMotionManager *motionManager;

void startMotion() {
	if (!motionManager) {
		motionManager = [[CMMotionManager alloc] init];
	}
	[motionManager startDeviceMotionUpdates];
}

void startMotion() {
	if (!motionManager) {
		motionManager = [[CMMotionManager alloc] init];
	}
	[motionManager stopDeviceMotionUpdates];
}

void getAcceleration(double *x, double *y, double *z) {
	if (haveGyroscope()) {
		CMAcceleration acceleration = motionManager.deviceMotion.userAcceleration;
		*x = acceleration.x;
		*y = acceleration.y;
		*z = acceleration.z;
	} else {
		*x = 0;
		*y = 0;
		*z = 0;
	}
}

int haveGyroscope() {
	if (!motionManager) {
		motionManager = [[CMMotionManager alloc] init];
	}
	return motionManager.gyroAvailable;
}
