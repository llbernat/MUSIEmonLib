// 
// MUSIEmonLib example. Licence GNU GPL V3
//

#include <MUSIEmonLib.h>  // Include MUSIEmon Library

MUSIEnergyMonitor emon1;  // Create an instance

void setup()
{  
  Serial.begin(9600);

  // Tell the input pin and the calibration 
  // Calibration value depends on the sensitivity of 
  // our sensor. Its a try-and-adjust process
  // To view a practical case, read: 
  // https://programarfacil.com/blog/arduino-blog/sct-013-consumo-electrico-arduino/
  //
  emon1.current(PIN_A2, 122.80);
  
  // This method tries to sense the DC level
  // to avoid initial outliers
  //
  emon1.trainFilter();

  // We can set the sampling duration in ms
  // It must be a multiple of a complete current cycle
  //
  // For example @50Hz: 
  // Duration: 1000ms -> 50 cycles
  //            500ms -> 25 cycles
  //            280ms -> 14 cycles
  
  emon1.setDuration(500); // 25 cycles @50Hz or 30 cycles @60Hz
}

void loop()
{
  double Irms = emon1.calcIrms();  // Sample sensor and calculate Irms

  Serial.print("Apparent power: ");
  Serial.print(Irms*230.0);
  Serial.print(" IRMS current value: ");
  Serial.println(Irms);
  
  delay(5000);
}