/*
  MUSIEmonLib.cpp - Library for electric power monitoring
  Created by Lluís Bernat, May 16 2021
  GNU GPL License

  Depends on the fantastic EmonLib library 
  that you can install from 
  Arduino IDE library manager or from 
  https://github.com/openenergymonitor/EmonLib.git

*/

#ifndef _MUSIEmonLib_h_
#define _MUSIEmonLib_h_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// The base class is defined into: 
//
#include "EmonLib.h"

// Print (Serial) debug messages? 
//
#define _DEBUG_MUSIEmonLib_

// Number of samples to test ADC speed.
// Increase for better accuracy 
//
#define _CALC_ADC_SPEED_ 500

// Max number of samples to waste in training the DC filter
//
#define _MAX_TRAIN_ 5000

// Our class defines some additional functions and behaviours
//
class MUSIEnergyMonitor: public EnergyMonitor
{
  public:
    //
    // New methods: 
    //
    /*
    unsigned long setDuration(unsigned long DURATION)

      Allows to sample by the desired ms DURATION

      Returns the equivalent number of samples
      (also retriveable using getNumSamples() method)
    */
    unsigned long setDuration(unsigned long _DURATION);
    /*
      unsigned long getNumSamples()
    
      Getter for the equivalent duration in number of samples
    */
    unsigned long getNumSamples();
    /*
      void tranFilter(void)

      Trains the reject DC filter to obtain better accuracy 
      on first samples and avoid outliers
    */
    void trainFilter();
    /*
      double calcIrms(void)

      New overcharged method to sample current 
      by the previously setted duration
      (see setDuration() method)
    */
    double calcIrms();
    /*
      double calcIrms(unsigned int NUMBER_OF_SAMPLES);

      The original calcIrms function (below) left untouched, 
      but we overcharge the method to (re)define it without 
      arguments to mean that we wish sample for the previously 
      established duration by setDuration()
    */
    double calcIrms(unsigned int _NUMBER_OF_SAMPLES);
    /*
      void current(unsigned int _inPinI, double _ICAL)
      
      Redefined constructor to accommodate new internal variables
      DURATION and NUM_SAMPLES values
    */
    void current(unsigned int _inPinI, double _ICAL);
  private:
    // Now we can set the duration of the sampling!
    unsigned long DURATION;
    // But we need to translate the DURATION to 
    // a number of samples, that will depend on 
    // our arduino speed (CPU and ADC)
    unsigned long NUM_SAMPLES;
    // This translation (a try and calc) is made by the setDuration() method
};

#endif
