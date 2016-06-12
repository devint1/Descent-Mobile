Descent (1994) Mobile
=====================

This is a source port of the original DOS game “Descent” for Android and iOS. You will need the game files from a licensed copy in order to play it. **See it in action: https://youtu.be/Lueh3Czj8_Y Or, an older software-rendered version: https://youtu.be/DRo6iyHhG3M**

Parallax Notice
---------------
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.

Requirements
------------
- Android
    - Android Studio 2.1.2.0 or later
    - SDK 19 or later (KitKat)
    - NDK r12 or later
- iOS
    - Xcode 7.1 or later
    - iOS 9.1 or later
    - If you want to run on an iDevice: http://www.apple.com/ios/whats-new/#compatibility

Building (Android)
------------------
Copy DESCENT.HOG and DESCENT.PIG to `Descent/src/main/assets`, then open the project in Android Studio. If needed, install the required build tools and NDK. From there, simply build/run the project. The Android version only supports the OpenGL ES renderer. Tested on an NVIDIA Shield Tablet K1 running Android 6.0.1 (Marshmallow) and an HP Slate 8 Pro running Android 4.4 (KitKat).

Building (iOS)
--------------
Copy DESCENT.HOG and DESCENT.PIG to the “Descent” directory, then open the Xcode workspace “Descent-iOS.xcworkspace.” You may wish to select the renderer (OpenGL ES or software) prior to building; select a scheme from the Product → Scheme menu. Once this is done, select your platform and build. This was tested on an iPhone 5s running iOS 9.1. Apple now allows you to run on an iDevice for free, so long as you have an Apple ID.

Issues and Limitations
----------------------
Please see the “Issues” section in GitHub.

Special Thanks
--------------
- Merlin Silver soundfont for MIDI instrument playback on iOS - http://www.soundfonts.gonet.biz
- HMP to MIDI conversion code - Hans de Goede, d1x project
