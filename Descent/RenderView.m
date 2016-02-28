//
//  RenderView.m
//  Descent
//
//  Created by Devin Tuchsen on 10/19/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import "RenderView.h"
#import "ControlsView.h"
#include "types.h"
#include "game.h"

#ifndef OGLES
// Graphics stuff from Descent to be rendered
extern CGContextRef bitmap_context;
extern ubyte gr_current_pal[256*3];
extern unsigned char * gr_video_memory;
#endif

@implementation RenderView {
	ControlsView *contolsView;
#ifdef OGLES
	CAEAGLLayer* eaglLayer;
	GLuint depthRenderBuffer;
	GLuint framebuffer;
#endif
	bool lastInScreen;
	int lastGameMode;
}

#ifdef OGLES
+ (Class)layerClass {
	return [CAEAGLLayer class];
}
#endif

- (id)initWithCoder:(NSCoder *)aDecoder {
	self = [super initWithCoder:aDecoder];
#ifdef OGLES
	GLint backingWidth, backingHeight;
	CGFloat screenScale;
	
#ifdef NORETINA
	screenScale = 1;
#else
	screenScale = [[UIScreen mainScreen] scale];
#endif
	
	// Set up EAGL layer
	eaglLayer = (CAEAGLLayer*) self.layer;
	eaglLayer.opaque = YES;
	eaglLayer.contentsScale = screenScale;
	eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
	
	// Set up EAGL context
	_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	[EAGLContext setCurrentContext:_context];
	
	// Set up color render buffer
	glGenRenderbuffersOES(1, &_colorRenderBuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _colorRenderBuffer);
	
	// Set up frame buffer
	glGenFramebuffersOES(1, &framebuffer);
	glBindFramebufferOES(GL_FRAMEBUFFER_OES, framebuffer);
	[_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, _colorRenderBuffer);
	
	// Set up depth buffer
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	glGenRenderbuffersOES(1, &depthRenderBuffer);
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderBuffer);
	glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
	glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderBuffer);
	
	// Clear to back
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// Viewport is screen bounds
	glViewport(0, 0, self.bounds.size.width * screenScale, self.bounds.size.height * screenScale);
	
	// Enable blending for alphas
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Disable depth mask (otherwise get artifacts with 3D sprites)
	glDepthMask(GL_FALSE);

	// Show the initial render buffer
	glBindRenderbufferOES(GL_RENDERBUFFER_OES, _colorRenderBuffer);
	[_context presentRenderbuffer:GL_RENDERBUFFER_OES];
#endif
	lastInScreen = false;
	lastGameMode = GM_UNKNOWN;
	contolsView = [[ControlsView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	[self addSubview:contolsView];
	return self;
}

- (void)doControls {
	if (lastGameMode != Game_mode || lastInScreen != In_screen) {
		[contolsView setNeedsDisplay];
		lastInScreen = In_screen;
		lastGameMode = Game_mode;
	}
}

#ifndef OGLES
- (void)drawRect:(CGRect)rect {
	CGContextRef currentContext = UIGraphicsGetCurrentContext();
	if(bitmap_context) {
		// Get what we need from the bitmap context
		unsigned char* data = CGBitmapContextGetData(bitmap_context);
		size_t width = CGBitmapContextGetWidth(bitmap_context);
		size_t height = CGBitmapContextGetHeight(bitmap_context);
		size_t nPixels = width * height;
		
		// Write to bitmap via palette
		for (size_t i = 0; i < nPixels; ++i) {
			data[i * 4 + 1] = gr_current_pal[gr_video_memory[i] * 3] * 4;
			data[i * 4 + 2] = gr_current_pal[gr_video_memory[i] * 3 + 1] * 4;
			data[i * 4 + 3] = gr_current_pal[gr_video_memory[i] * 3 + 2] * 4;
		}
		
		// Create image to render to
		CGImageRef image = CGBitmapContextCreateImage(bitmap_context);
		
		// Need to flip the image
		CGRect bounds = [self bounds];
		CGContextTranslateCTM(currentContext, 0, bounds.size.height);
		CGContextScaleCTM(currentContext, 1.0, -1.0);
		
		// Draw it!
		CGContextDrawImage(currentContext, bounds, image);
		
		// Done
		CGImageRelease(image);
	}
	[self doControls];
}
#else
- (void)drawView {
	[self doControls];
}
#endif

@end
