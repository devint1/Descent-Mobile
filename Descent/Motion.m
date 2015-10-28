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

void getAttitude(double *roll, double *pitch, double *yaw) {
	CMAttitude *attitude = motionManager.deviceMotion.attitude;
	*roll = attitude.roll;
	*pitch = attitude.pitch;
	*yaw = attitude.yaw;
	if ([[UIApplication sharedApplication] statusBarOrientation] == UIInterfaceOrientationLandscapeLeft) {
		*roll *= -1;
		*pitch *= -1;
	}
}

void getRotationRate(double *x, double *y, double *z) {
	CMRotationRate rotationRate = motionManager.deviceMotion.rotationRate;
	*x = rotationRate.x;
	*y = rotationRate.y;
	*z = rotationRate.z;
}

void getAcceleration(double *x, double *y, double *z) {
	CMAcceleration acceleration = motionManager.deviceMotion.userAcceleration;
	*x = acceleration.x;
	*y = acceleration.y;
	*z = acceleration.z;
}
