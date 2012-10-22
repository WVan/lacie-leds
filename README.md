lacie-leds
==========

Small linux utility to allow changing the LED modes on a LaCie 5big Atom based NAS/Home Server running linux.

I own a LaCie 5big Office+ Home Server and recently I got tired of the Windows Storage Server Essentials OS it came with, so I decided to install Ubuntu 12.04 server on it instead.  
This worked fine except for the fact that the big LED at the front kept blinking.  
In Windows this gets switched off or set to constant when the LaCie service has booted up, but linux has no such equivalent since this is based on some LaCie custom hardware and (Windows)software.  
Thus I tried finding out how to switch it off from linux and this little utility is the result.  
I got my information from:  
http://www.coreboot.org/Superiotool  
https://launchpad.net/~sguinot/+archive/net5big-xp

DISCLAIMER
----------
I wrote this utility purely for my own use, but since it took me a while to figure out how to do it I thought I would publish it so that others may benefit.  
I am not responsible for any damage you may do to your system (hardware or software), usage is at your own risc!  
The code was only tested on my own LaCie 5big Office+ running Ubuntu 12.04, no other systems have been tested but in theory it should work for any linux distro and any LaCie 5big system based on an Intel Atom (I think).  

I'm sure a lot of things about this code could be better since I'm no expert linux programmer.  
Feel free to modify, extend, or redistribute the code in any way.  
Just don't come back and bite me...  

Usage
-----
First compile it the simple way (I'm to lazy to write a makefile for this)

    gcc lacie-leds.c -o lacie-leds


Usage: lacie-leds \<led\> \<mode\>  
Possible \<led\> values: front, hdd1, hdd2, hdd3, hdd4, hdd5  
Possible \<mode\> values: 0-7, off, blue, red, blue-blink-even, red-blink-even, blue-red-blink-uneven, blue-red-blink-even, blue-blink-uneven
