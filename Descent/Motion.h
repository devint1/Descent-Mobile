//
//  Motion.h
//  Descent
//
//  Created by Devin Tuchsen on 10/22/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef Motion_h
#define Motion_h

extern void startMotion();
extern void stopMotion();
extern void getAcceleration(double *x, double *y, double *z);
extern int haveGyroscope();

#endif /* Motion_h */
