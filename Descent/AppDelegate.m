//
//  AppDelegate.m
//  Descent
//
//  Created by Devin Tuchsen on 10/18/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#import "AppDelegate.h"

#include "cfile.h"
#include "inferno.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

// Launches Descent!
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
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
		
		// HACK! HACK! HACK! Emulating command line arguments!
		char w[6], h[6];
		sprintf(w, "%d", (int)screenWidth);
		sprintf(h, "%d", (int)screenHeight);
		const char *args[] = { "", "-width", w, "-height", h };
		
		descent_main(5, (char**)args);
	});
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
	// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
	// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
