# Pokemon Sword/Shield auto hatcher

## Overview

This project is outdated and is **no longer actively being developed**. I can answer questions related to this project but further changes to this repository are no longer being made. This is as a result of [my new version of this project](https://github.com/ironandstee1/swemu-plus-plus) which improves on this one in almost every way but is only compatible with ATMega32u4 boards. This new project has all the scripts shown here with more optimization and a handful of new ones as well. 

Automatically hatches pokemon in sword and shield with the aim of allowing users to farm shinies overnight. 

Scripts are currently complete for the following:
* 10240 base egg steps multi hatching (~10:00 for 3-5 eggs)
* 2560 base egg steps multiple egg hatching **Teensy++ 2.0**
* 3840 base egg steps multiple egg hatching (~2:15/1 egg) **Teensy++ 2.0**
* 5120 base egg steps multiple egg hatching **Teensy++ 2.0**
* 7680 base egg steps multiple egg hatching **Teensy++ 2.0**
* 2560 base egg steps single egg hatching (~1:50/1 egg) **Teensy++ 2.0, ATMega32U4**
* 3840 base egg steps single egg hatching (~2:15/1 egg) **Teensy++ 2.0, ATMega32U4**
* 5120 base egg steps single egg hatching **Teensy++ 2.0, ATMega32U4**
* 7680 base egg steps single egg hatching **Teensy++ 2.0, ATMega32U4**
* 10240 base egg steps single egg hatching **Teensy++ 2.0, ATMega32U4**
* 5 box release (releases 5 consecutive boxes of pokemon) **Teensy++ 2.0, ATMega32U4**
* Watt farming **Teensy++ 2.0, ATMega32U4**

All scripts support Teensy++ 2.0 in the makefile  Most scripts can be made to support a board with an ATMega32U4 (Arduino Leonardo, Pro Micro). The others will be fixed for this soon. Some of the less intense scripts support chips with an ATMega16U2 (Arduino Uno), but if this optimization doesn't happen in the second pass it never will. 


If you would like to just download the hex files for flashing, go [here](https://github.com/ironandstee1/pkmn-hexes). The directions on thie Readme are specifically for people who want to make the files themselves, either for the purpose of understanding or changing the code. This code is also more updated than the hex files. I only bring the hex files up to date every so often. The instuctions below require knowledge of how to install and use a gcc. A link/tutorial is provided for windows. 

### State of the scripts

Currently, all of the above scripts are complete. 

Optimized scripts:

1. Watt farming
1. 5 box release

If a script is non-optimized then the entire script is written in the STEP_1 enum, and you will have to uncomment it and ensure the state transitions back to BREATHE after each run. This is the default under case 1. These scripts are not all compatible with ATMega32U4. In the next several weeks all scripts will be made to be compatible. You will have to uncomment each part of the script in each enum value and each PROCESS_X state. These are labelled. 


## Requirements

### Hardware
One or the other of:

* Teensy++ 2.0 
  * Available on amazon
  * Must also have one of those fatter microUSB cables
* Arduino/pro micro/something with a compatible chip (ATMega16U2, ATMega32U4, etc)
  * Code will be optimized to be compatible for ATMega32U4. Not all code will be compatible with ATMega16U2. 
  
### Software
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
* [Atmel Gnu Toolchain](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html)
  * This is necessary if you want to build the code or edit the scripts in any way on windows exclusively
  * There are issues with this and building for Arduino. If you want to build for Arduino follow my Installing Ubuntu + building guide below
  * I followed this tutorial up to installing avrdude
* [Git for windows](https://gitforwindows.org/)
  * Again, only necessary if you want to build the code or edit the scripts in any way
  * Can be used to clone this repo as well, but downloading as zip will do

## How to use this

### Installing Ubuntu on Windows Subsystem for Linux + building for ATMega and other boards

This is only necessary if you want to build the scripts yourself. Windows subsystem for linux isn't the easiest to interface with USB, so I'll be showing you how to make the files here and flash them with your program of choice (teensy loader, atmel flip) on windows. 

1. Open the microsoft store and install Ubuntu 
1. Let it set up and create a username and password for yourself
1. Enter this code once you're all set up
``` 
sudo apt-get update
sudo apt-get install -y make gcc-avr-libc
sudo apt-get install git
mkdir git
cd git
git clone https://github.com/ironandstee1/pkmn-auto-hatcher.git
cd pkmn-auto-hatcher
```
Edit the mcu in the makefile to be whatever you want it to be that's compatible (atmega16u2, etc). When you try the below steps, if you've typed the wrong one, it will tell you in the console. 
```
make clean
make
```
1. Open your windows file explorer and navigate to C:/Users/yourusername/AppData/Local/Packages/CanonicalGroupLimited.UbuntuOnWindows.../LocalState/rootfs/home/yourubuntuusername/git/pkmnauto-hatcher
1. Get your Joystick.hex file and move it to wherever is convenient for you
1. Create a shortcut or pin this location
1. Load it using atmel flip, QMK Toolbox, or whatever the internet tells you. I had luck with atmel flip for an arduino uno. 

### Making and loading for Teensy++ 2.0
1. Clone the repo to your local machine
1. Navigate to the directory
1. Uncomment the code you want or add your own script
1. Run "make clean"
1. Run make
1. Load the Teensy Loader program
1. Click the Open Hex File button (a little gray list) and select the hex file
1. Press the button on the Teensy++ 2.0. You should now see it appear in the Teensy Loader program
1. Press the program button (green arrow going into the hole) 

### Loading the script (no build) on Teensy++ 2.0
1. Download the appropriate hex file for your pokemon's egg steps.
  * Hex files can be found [here](https://github.com/ironandstee1/pkmn-hexes)
  * A list of pokemon egg steps can be found [here](https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_Egg_cycles)
1. Plug your Teensy++ 2.0 into your computer
1. Load the Teensy Loader program
1. Click the Open Hex File button (a little gray list) and select the hex file
1. Press the button on the Teensy++ 2.0. You should now see it appear in the Teensy Loader program
1. Press the program button (green arrow going into the hole) 

### Egg hatching preparation

1. Get the oval charm. Multi hatch scripts avoid some of the pitfalls of not having this, but this improves the efficiency. 
1. Get a pokemon with flame body in your party slot 6. I grabbed carkoal from the mine tracks as they can be easily caught due to low level and some already have the ability.
1. Make sure that your party is full and there are no eggs. 
1. Put your pokemon to breed in the daycare (look up the Shiny Charm and Masuda method - both will help your shiny chances)
1. Run around until the day care lady has an egg but don't grab it just yet. 
1. Warp to route 5. Make sure you are not on your bike. Make sure that when you open the menu that "Town Map" is where your selection defaults to when you press X. Don't move from in front of the camp. The script is pretty sensitive to positioning. If you need to, warp again once you're ready. 
1. Turn off your controller and plug in your microcontroller

### Watt farming preparation

1. Set your date to sometime early. If you plan to run this all night you will need > 10 years spare, so I recommend setting your date to 1/1/2000. 
1. Go to an empty wishing well with no pokemon around it and no beam coming from it. 
1. Throw a wishing piece into the well. 
1. Go to menu, vs battle, battle stadium, and start a ranked battle
1. Immediately run from a ranked battle
1. Stand directly in front of the well
1. Make sure there are no watts in the hole
1. Exit to menu and change the date one year forward (1/1/2001)
1. Collect the watts and stand in front of the wishing well
1. Turn off your controller and plug in your mircocontroller

This script will proceed to farm 2000 watts every 30 seconds or so. You could manually do this in ~20 seconds. ~10 seconds worth of code is dedicated to making sure there are no errors. 

### Box release preparation

1. Put the pokemon in 5 full consecutive boxes
1. Make sure that the top left space in the box before the one you want to empty has a pokemon in it
1. Make sure there's no eggs in your pokemon pile
1. Place your selector on the top left pokemon in the first box of pokemon you want to release
1. Turn off your controller and plug in your microcontroller

## Improvements from past scripts

* Added C macros
  * Simplifies the process of calling repetitive actions
  * Improves readability and editability of scripts
  * Main scripting work has been shifted off to the header file instead of the c file
* Added states
  * Supports far more intensive and robust scripts while significantly lowering system requirements 
  * Probably makes the code harder to edit for yourself so if you want to try your hand at making a basic script you should grab code from the parent repo 
* Added new buttons and button macros - not a large improvement, but these are available

### Thanks

Thanks to Shiny Quagsire for his [Splatoon post printer](https://github.com/shinyquagsire23/Switch-Fightstick) and progmem for his [original discovery](https://github.com/progmem/Switch-Fightstick).

Thanks to [bertrandom](https://github.com/bertrandom/snowball-thrower/) the foundation of this script/method.

Thanks as well to all other contributors to previous projects. 

## How can you help?

### Suggest new scripts for pokemon or other games

Do you have an idea for a script for this game or another game? Let me know by adding comments somewhere here. I am willing to make scripts or even new projects if the call is there. 
