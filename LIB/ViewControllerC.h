//
//  ViewControllerC.h
//  Descent
//
//  Created by Devin Tuchsen on 10/20/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef ViewControllerC_h
#define ViewControllerC_h

#ifdef OGLES
#import <OpenGLES/ES1/gl.h>
#endif

int textIsActive();
void activateText();
void deactivateText();
#ifdef OGLES
void getRenderBufferSize(GLint *width, GLint *height);
void showRenderBuffer();
#endif

#endif /* ViewControllerC_h */
