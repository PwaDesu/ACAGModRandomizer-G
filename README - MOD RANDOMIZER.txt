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

1 - Put the files of this package in the 3DMigoto folder, they should be next to the "3DMigoto Loader.exe" file (if you use a launcher instead, wherever the "Mods" folder is).
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
5 - You're all set, run "ACAGModRandomizer-G.exe" whenever you want to play Genshin with mods; the program will launch GIMI for you if it's present so you only need to launch Genshin afterwards.

Note: You can set it to run with XXMI in the launcher's "Advanced" => "Run Pre-Launch" settings.

== Troubleshooting ==

If the program closes unexpectedly:
1) Make sure that you've followed the instructions correctly
2) Try putting 3DMigoto and this program in a different drive; Some types of storage drives do not support symlinks

== Warning ==

The 1.0 version of this program did not perform any action with a possibly destructive potential, note that this is no longer the case.
There was an issue with the 1.0 version where mod toggles would be reset whenever another mod for the same character would be picked. 
This was because GIMI clears out the toggles it has saved for a mod if it does not find the mod when you launch the game. 

To solve this, version 1.1 and onwards of this program read GIMI's save file and update each individual mod's default toggles values based on that. 
While that solves the problem, because C++ is still very foreign to me, this adds the possibility that the program incorrectly updates a mod's toggles and corrupts its data file.
I have not had that happen to me but I do still recommend backing up your mods first. It's hardly world-ending if a mod's data file gets corrupted, but still annoying as you'd need to redownload it and replace it.