# [MUSIEmonLib](https://github.com/llbernat/MUSIEmonLib.git)

## A library to access analog current sensors

Based on the excellent library 
[EmonLib](https://github.com/openenergymonitor/EmonLib.git)

This library has been inspired by the subject 
_Application Areas of IoT_ of the 
_Master's Degree in Intelligent Systems_ (course 2020-21) of the 
University of the Balearic Islands (Spain)

## Overview

MUSIEmonLib enhances EmonLib, because allows to: 

* Reduce initial outliers by training the instance 
using its new class trainFilter() method.

* Now you can also sample by time instead of by the number of samples. 
You only need to call the method setDuration(), 
passing it the desired duration in milliseconds.

See the included example to view this excinting new features in action.

### Installation

Download the MUSIEmonLib.zip to Arduino IDE 'libraries' folder and uncompress. 
Restart of IDE is required.

You can also (recommended) use git clone and git pull 
to keep the library up-to-date changes.

### Dependencies

MUSIEmonlLib depends on [EmonLib](https://github.com/openenergymonitor/EmonLib.git)
That is, you also need to install EmonLib from the Arduino lib manager or 
its (github) source.

### New or refurbished methods

* current(unsigned int inPinI, double ICAL): original EmonLib behaviour, but also initializes new needed private variables
* setDuration(unsigned long DURATION): tells MUSIEmonLib instance to sample by time (ms)
* getNumSamples(void): gets the number of samples needed to achieve sampling duration
* trainFilter(void): trains the internal software DC filter to reduce outliers in initial IRMS calculations
* calcIrms(void): called without arguments, it samples by the setted duration
* calcIrms(unsigned long num_samples): original EmonLib behaviour, it calcs current IRMS using num_samples samples

