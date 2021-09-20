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
