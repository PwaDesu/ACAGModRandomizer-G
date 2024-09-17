Program: "A Certain Anime Game Mod Randomizer - Genshin" (Genshin Mod Randomizer)
Author: Pwa
Supported platforms: Windows
Unknown platform support: Linux, MacOS
Package includes:
	- ACAGModRandomizer-G.exe
	- "README - MOD RANDOMIZER.txt" (this readme)

== Description ==

This simple program picks a random available mod for each available character before launching 3DMigoto.

== Instructions ==

1 - Put the files of this package in the 3DMigoto folder, they should be next to the "3DMigoto Loader.exe" file.
2 - Create a "Random Mods" folder (case-sensitive) next to the "Mods" folder
3 - For each character you have mods you want to randomize for, create a folder, and put the mods inside. It should look like this:

|
|= 3DMigoto Loader.exe
|= Mods
|= Random Mods
|=== Mona
|===== Date Attire
|===== Default Skin (Hat Removed)
|=== Furina
|===== Streetwear
|===== Winter Clothing

4 - Remove the mods you want to be randomized from the "Mods" folder, you can keep any mod you want to always be loaded
5 - You're all set, run "Prepare mods.bat" whenever you want to play Genshin with mods; the script will launch 3DMigoto for you so you only need to launch Genshin after running this script.

Note: The script does not perform any destructive operation. All files in the "Random Mods" folder will be untouched, and only the shortcuts created by the previous run of the script in the "Mods" folder are removed when running the script again.

== Troubleshooting ==

If the program closes unexpectedly:
1) Make sure that you've followed the instructions correctly
2) Try putting 3DMigoto and this program in a different drive; Some types of storage drives do not support symlinks
3) The program expects 3DMigoto to be named "3DMigoto Loader.exe", if you renamed it, don't.

== Known issues ==

- The previous mod's toggles are reset when a different one for the same character is selected. This is due to however 3DMigoto saves that data, and I do not currently know how to fix it.