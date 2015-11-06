//
//  ViewControllerC.h
//  Descent
//
//  Created by Devin Tuchsen on 10/20/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef ViewControllerC_h
#define ViewControllerC_h

int textIsActive();
void activateText();
void deactivateText();
#ifdef OGLES
void showRenderBuffer();
#endif

#endif /* ViewControllerC_h */
