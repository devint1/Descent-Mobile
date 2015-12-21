//
//  ViewController.m
//  Descent
//
//  Created by Devin Tuchsen on 10/18/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import "ViewController.h"
#import "RenderView.h"
#include "key.h"
#include "game.h"
#include "cfile.h"
#include "inferno.h"

extern void key_handler(unsigned char scancode, bool down);
extern void mouse_handler(short x, short y, bool down);

static BOOL descentIsRunning = NO;

@interface ViewController () {
	CADisplayLink *displayLink;
}

@end

@implementation ViewController {
	NSUInteger lastTextLength;
}

#pragma mark UIViewController methods

- (void)viewDidLoad {
	SEL drawer;
	
	[super viewDidLoad];
	[[self view] setMultipleTouchEnabled:YES];
	
#ifdef OGLES
	drawer = @selector(drawView);
#else
	drawer = @selector(setNeedsDisplay);
#endif
	
	// Start rendering the window at 60 FPS
	displayLink = [CADisplayLink displayLinkWithTarget:self.view selector:drawer];
	[displayLink setFrameInterval:1 / 60.0f];
	[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
	
	if(!descentIsRunning) {
		// Launch Descent!!
		dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
			Resource_path = [[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSASCIIStringEncoding];
			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
			Document_path = [paths.firstObject cStringUsingEncoding:NSASCIIStringEncoding];
			
			// Get screen resolution
			CGRect screenRect = [[UIScreen mainScreen] bounds];
			CGFloat screenWidth = screenRect.size.width;
			CGFloat screenHeight = screenRect.size.height;
			
#ifdef NORETINA
			CGFloat screenScale = 1;
#else
			CGFloat screenScale = [[UIScreen mainScreen] scale];
#endif
			
			screenWidth *= screenScale;
			screenHeight *= screenScale;
			
			// Swap width/height if portrait
			UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
			if(UIDeviceOrientationIsPortrait(orientation)) {
				CGFloat temp;
				temp = screenWidth;
				screenWidth = screenHeight;
				screenHeight = temp;
			}
			
#ifdef OGLES
			// Set the OpenGLES context for this thread
			[EAGLContext setCurrentContext:((RenderView*)self.view).context];
#endif
			
			// HACK! HACK! HACK! Emulating command line arguments!
			char w[6], h[6];
			sprintf(w, "%d", (int)screenWidth);
			sprintf(h, "%d", (int)screenHeight);
			const char *args[] = { "", "-width", w, "-height", h };
			
			// Run Descent!
			descent_main(5, (char**)args);
		});
		descentIsRunning = YES;
	}
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

-(BOOL)prefersStatusBarHidden{
	return YES;
}

- (BOOL)shouldAutorotate {
	return Game_mode != GM_NORMAL || In_screen;
}

#pragma mark UIResponder methods

- (void)touchesBegan:(NSSet<UITouch *>*)touches withEvent:(UIEvent*)event {
	CGPoint point;
	
#ifdef NORETINA
	CGFloat screenScale = 1;
#else
	CGFloat screenScale = [[UIScreen mainScreen] scale];
#endif
	
	for(UITouch *touch in touches) {
		point = [touch locationInView:[self view]];
		mouse_handler(point.x * screenScale, point.y * screenScale, true);
	}
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
	CGPoint point;
	
#ifdef NORETINA
	CGFloat screenScale = 1;
#else
	CGFloat screenScale = [[UIScreen mainScreen] scale];
#endif
	
	for(UITouch *touch in touches) {
		point = [touch locationInView:[self view]];
		mouse_handler(point.x * screenScale, point.y * screenScale, false);
	}
}

#pragma mark IBAction methods

- (IBAction)textChanged:(id)sender {
	UITextField *textField = (UITextField*)sender;
	NSUInteger length = [[textField text] length];

	// Simulate backspace if length is smaller, otherwise send text
	if(lastTextLength > length) {
		key_handler(KEY_BACKSP, true);
		key_handler(KEY_BACKSP, false);
	} else {
		unichar c = [[textField text] characterAtIndex:length - 1];
		key_handler(c, true);
		key_handler(c, false);
	}

	lastTextLength = length;
}

- (IBAction)editingEnded:(id)sender {
	lastTextLength = 0;
}

- (IBAction)doneEditing:(id)sender {
	UITextField *textField = (UITextField*)sender;
	[textField setText:@""];
	
	// Simulate pressing the enter key
	key_handler(KEY_ENTER, true);
	key_handler(KEY_ENTER, false);
	
	[textField resignFirstResponder];
}

@end
