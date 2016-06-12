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
	[motionManager startGyroUpdates];
}

void stopMotion() {
	if (!motionManager) {
		motionManager = [[CMMotionManager alloc] init];
	}
	[motionManager startGyroUpdates];
}

int haveGyroscope() {
    if (!motionManager) {
        motionManager = [[CMMotionManager alloc] init];
    }
    return motionManager.gyroAvailable;
}

void getRotationRate(double *x, double *y, double *z) {
	if (haveGyroscope()) {
        CMRotationRate rotationRate = motionManager.gyroData.rotationRate;
		*x = rotationRate.x;
		*y = rotationRate.y;
		*z = rotationRate.z;
	} else {
		*x = 0;
		*y = 0;
		*z = 0;
	}
}
