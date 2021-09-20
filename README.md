This code aims to fix a few problems that Deadlock 2 has on newer systems.

1) DirectDraw was not truly utilized by the DL2 developers. They basically used it to set the display mode to 640x480, and that's about it.
This DLL can be used to eliminate DirectDraw from DL2 completely.

2) Since DirectDraw is no longer changing the resolution of the user's screen, it will be displayed in Windowed mode. The code 
creates the main game window with a system menu bar instead of a frameless, pop-up style window that the developers used.

3) It also provides a no-cd patch (i.e. you can play the game w/o the CD inserted). Many people don't have CD-ROMs anymore,
so it is a big pain to have to have the CD inserted to play.
Note: You will still need to copy the *.cam, *.hdd, and *.hdx files from your CD to the game folder(s). These files will NOT be provided.

4) When trying to play the patched 1.20 version, the screen typically goes black for most users and won't display correctly.
This is due to the code that they used to show the blue cursor. This code prevents the cursor from loading, and instead
allows you to use the normal Windows cursor.

How do I use this?
1) You can either try to download the compiled DLLs found in the DL2_* folders, or
2) You can download the source code and compile the DLLs for yourself (recommended to reduce chance of compatibility errors).

Put the correct "ddraw.dll" into the game folder. The following lists which dll goes with which version:
DL2_256 = Original CD release version 1.0.
DL2_288 = Version 1.20 patched version.
DL2_DEMO = Demo version of the game.

The included DLLs were compiled against Windows 10 SDK version 10.0.16299.0, so they might not work on Windows 7 or earlier. If they don't, you will need to compile them yourself against a different Windows SDK.

The code uses Microsoft Detours to hook functions, so you may or may not need to install that to use these DLLs. It can be found on their Github repo (https://github.com/microsoft/Detours) if needed.
