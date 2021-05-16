/*
  MUSIEmonLib.cpp - Library for electric power monitoring
  Created by Lluís Bernat, May 16 2021
  GNU GPL License

  Depends on the fantastic EmonLib library 
  that you can install from 
  Arduino IDE library manager or from 
  https://github.com/openenergymonitor/EmonLib.git

*/

#include "MUSIEmonLib.h"

//#include "WProgram.h" un-comment for use on older versions of Arduino IDE
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


//--------------------------------------------------------------------------------------
// Calls parent constructor and sets null DURATION and NUM_SAMPLES
//--------------------------------------------------------------------------------------
void MUSIEnergyMonitor::current(unsigned int _inPinI, double _ICAL)
{
  EnergyMonitor::current(_inPinI, _ICAL);
  DURATION = 0;
  NUM_SAMPLES = 0;
}

//--------------------------------------------------------------------------------------
// Sets DURATION and converts to a NUM_SAMPLES, needed for the calcIrms method
//--------------------------------------------------------------------------------------
unsigned long MUSIEnergyMonitor::setDuration(unsigned long _DURATION)
{
  unsigned long t1, t2, dt;

  DURATION = _DURATION;
  if (DURATION > 0) 
  {
    t1 = millis();
    calcIrms(_CALC_ADC_SPEED_);
    t2 = millis();
    dt = t2 - t1;
    if (dt == 0) 
      NUM_SAMPLES = DURATION * _CALC_ADC_SPEED_;
    else
      NUM_SAMPLES = DURATION * _CALC_ADC_SPEED_ / dt;
  }
  else
    NUM_SAMPLES = 0;

  return NUM_SAMPLES;
}

//--------------------------------------------------------------------------------------
// Gets the sampling DURATION in samples, not in time units
//--------------------------------------------------------------------------------------
unsigned long MUSIEnergyMonitor::getNumSamples()
{
  // getter for number of samples to make to complete a timed sampling
  return NUM_SAMPLES;
}

void MUSIEnergyMonitor::trainFilter()
{
  unsigned long int batch = _MAX_TRAIN_ / 10;
  uint8_t i = 1;
  double oldAmp = 0.0, newAmp;

  if (batch == 0) batch = 1;

  newAmp = calcIrms(batch);

  while ((i < 10) and abs(newAmp - oldAmp) > 0.5)
  {
    oldAmp = newAmp;
    newAmp = calcIrms(batch);
    i++;
  }
  #ifdef _DEBUG_MUSIEmonLib_
  Serial.print("MUSIEnergyMonitor::trainFilter() trained in ");
  Serial.print(i * batch); 
  Serial.println(" samples");
  #endif
}

double MUSIEnergyMonitor::calcIrms()
{
  double amperes;

  if (NUM_SAMPLES > 0)
    amperes = calcIrms(NUM_SAMPLES);
  else
  {
    amperes = -1.0;
    #ifdef _DEBUG_MUSIEmonLib_
    Serial.println("MUSIEnergyMonitor::calcIrms(): " \
                   "please setDuration(sampling_duration_in_ms)");
    #endif
  }

  return amperes;
}

double MUSIEnergyMonitor::calcIrms(unsigned int _NUMBER_OF_SAMPLES) {
  // stub method, simply calls parent 

  return EnergyMonitor::calcIrms(_NUMBER_OF_SAMPLES);
};
 