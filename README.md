Descent (1994) Mobile
=====================

This is a source port of the original DOS game “Descent” for Android and iOS. You will need the game files from a licensed copy in order to play it. **See it in action: https://youtu.be/Lueh3Czj8_Y Or, an older software-rendered version: https://youtu.be/DRo6iyHhG3M**

License
-------
Please see "COPYING."

Building (Android)
------------------
Copy DESCENT.HOG and DESCENT.PIG to `Descent/src/main/assets`, then open the project in Android Studio. If needed, install the required build tools, SDK, and NDK. From there, simply build/run the project. The Android version only supports the OpenGL ES renderer. Tested on an NVIDIA Shield Tablet K1 running Android 6.0.1 (Marshmallow) and a Nexus 6P also running 6.0.1.

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
