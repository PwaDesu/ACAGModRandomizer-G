# Hoyoverse Mod Randomizer

This is a lightweight tool that allows you to randomize your active mods in **Genshin Impact**, **Zenless Zone Zero**, and **Honkai: Star Rail**.
The tool is made to work with 3DMigoto-based mod-loaders and will not work with another kind of loader (I am not aware of any other though).
This is tested on both **GI** and **ZZZ**, but it should also work on **HSR**.

# How to use

> [!WARNING]
> The toggles of mods you were already using will be reset after installation of this tool

## With XXMI

* Download the latest version of the tool from the [Releases](https://github.com/PwaDesu/ACAGModRandomizer-G/releases) tab of this repository
* Open the folder where your XXMI is installed, go to the relevant folder (`GIMI` for **Genshin**, `ZZMI` for **ZZZ**) and extract the tool there
* Make sure to read the `README - MOD RANDOMIZER.txt` file and ensure the tool is in the correct folder (It should be at the same level as the `Mods` folder)
* Make a backup of your `Mods` folder so you can rollback in case bad things happen
* Create a new `Random Mods` folder next to your `Mods` folder
* For each character you have mods for, create a folder with the name of the character and place the character's mods in it
* Your `Random Mods` folder should look like:
  * `Random Mods`
    * `Furina`
      * `Sleepwear Furina`
      * `Winter Outfit`
* Delete all the mods within the `Mods` folder, the folder will be populated automatically by the tool 
* Open XXMI and configure it to run the tool using the following command in the "Run Pre-Launch" setting: `start /d "[path to the tool folder]" ACAGModRandomizer-G.exe`
![image](https://github.com/user-attachments/assets/0e642260-e6ee-4967-bf3c-80ff8d512ae4)

The tool will now run automatically whenever you launch the game through XXMI.
Do note that you need to repeat those steps for each game; if the tool is only installed in the `ZZMI` folder for example, it will not work for Genshin

## Without XXMI

* Download the latest version of the tool from the [Releases](https://github.com/PwaDesu/ACAGModRandomizer-G/releases) tab of this repository
* Open the folder where your 3DMigoto Loader for the game you want is located
* Make sure to read the `README - MOD RANDOMIZER.txt` file and ensure the tool is in the correct folder (It should be at the same level as the `Mods` folder)
* Make a backup of your `Mods` folder so you can rollback in case bad things happen
* Create a new `Random Mods` folder next to your `Mods` folder
* For each character you have mods for, create a folder with the name of the character and place the character's mods in it
* Your `Random Mods` folder should look like:
  * `Random Mods`
    * `Furina`
      * `Sleepwear Furina`
      * `Winter Outfit`
* Delete all the mods within the `Mods` folder, the folder will be populated automatically by the tool

Instead of launching `3DMigoto Loader.exe` before launching the game, you should now launch the tool (`ACAGModRandomizer-G.exe`), it will randomize the mods and then launch the 3DMigoto loader on its own.

# What does the tool do exactly

In order, the tool does the following:
* It reads your `d3dx_user.ini` file to see which mod toggles you've enabled
* It then goes through all the mods in your `Random Mods` folder and updates the configuration file of each mod accordingly
  * This is done because otherwise, the 3DMigoto loader would reset the toggles of mods that aren't currently loaded
* Once that is done, the tool goes through the folders in `Random Mods` and picks one random for each character in the folder
* Finally, the tool creates a shortcut within the `Mods` folder for each mod that was picked

> [!CAUTION]
> I use this tool daily and have not encountered any problems. This does not mean however that there are no risks.
> If there is a mod formatted in a way that the tool does not expect, it's possible that the tool will get confused
> and corrupt the mod's configuration file. Remember to make backups often.
