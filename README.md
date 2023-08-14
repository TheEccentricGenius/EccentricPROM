# EccentricPROM
My modified version of the [TommyPROM](https://github.com/TomNisbet/TommyPROM/tree/master) for the Arduino Ben Eater EEPROM programmers.
My complete testing has proved all commands work, however transferring large files and writing/reading EEPROM is slow due to the circuits hardware issues....CE is always LOW, leading to a 10 millisecond delay on read/writes.

SDP(Software Data Protection) is fully working....I have to only acquire some 27Cxx EPROM/Flash to test the 27Cxx code,
It should work, but remains untested.

A better schematic is coming soon... For now use the link below.
The link to wiring up the [Ben Eater EEPROM
Programmer](https://github.com/beneater/eeprom-programmer).

The aim of this project is to use the Ben Eater EEPROM Programmer design, but have the functionality of the TommyPROM design.
The project will only support 28 pin EEPROM, UV PROM, or PROM....An adapter board will be designed to provide the 12V VPP
signal for chips that require more then 5V programming voltage.

A possible design change may be to use CE....

Documentation will be moved here....For now visit the repo below.
For more documentation please visit [TommyPROM docs](https://github.com/TomNisbet/TommyPROM/tree/master/docs).
