//
//  ViewControllerC.c
//  Descent
//
//  Created by Devin Tuchsen on 10/20/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import "AppDelegate.h"
#import "ViewController.h"
#import "RenderView.h"

#include "key.h"
#include "ViewControllerC.h"

int textIsActive() {
	AppDelegate	*appDelegate = [[UIApplication sharedApplication] delegate];
	ViewController *viewController = (ViewController*)[[appDelegate window] rootViewController];
	return [[viewController dummyTextField] isFirstResponder];
}


void activateText() {
	AppDelegate	*appDelegate = [[UIApplication sharedApplication] delegate];
	ViewController *viewController = (ViewController*)[[appDelegate window] rootViewController];
	dispatch_async(dispatch_get_main_queue(), ^{
		[[viewController dummyTextField] becomeFirstResponder];
	});
}

void deactivateText() {
	AppDelegate	*appDelegate = [[UIApplication sharedApplication] delegate];
	ViewController *viewController = (ViewController*)[[appDelegate window] rootViewController];
	dispatch_async(dispatch_get_main_queue(), ^{
		[[viewController dummyTextField] setText:@""];
		[[viewController dummyTextField] resignFirstResponder];
	});
}

#ifdef OGLES
void showRenderBuffer() {
	AppDelegate	*appDelegate = [[UIApplication sharedApplication] delegate];
	RenderView *view = (RenderView*)[[[appDelegate window] rootViewController] view];
	[[view context] presentRenderbuffer:GL_RENDERBUFFER_OES];
}
#endif
