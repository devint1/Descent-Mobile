//
//  ViewController.m
//  Descent
//
//  Created by Devin Tuchsen on 10/18/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import "ViewController.h"
#include "key.h"
#include "game.h"

extern void key_handler(unsigned char scancode, bool down);
extern void mouse_handler(short x, short y, bool down);

@interface ViewController ()

@end

@implementation ViewController {
	NSUInteger lastTextLength;
}

#pragma mark UIViewController methods

- (void)viewDidLoad {
	[[self view ] setMultipleTouchEnabled:YES];

	// Start refreshing the window at 60 FPS
	[NSTimer scheduledTimerWithTimeInterval:(1.0/60.0) target:self.view selector:@selector(setNeedsDisplay) userInfo:nil repeats:YES];

	[super viewDidLoad];
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
