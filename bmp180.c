#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;

void setup() 
{
  Serial.begin(9600);

  if (!bmp180.begin())
   {
    Serial.println("Error: BMP180 initialization failed!");
    while (1); // Stop execution if initialization fails
   } 
  else 
  {
    Serial.println("BMP180 initialized successfully");
  }
}

void loop() 
{
  char status;
  double temperature, pressure;
  
  // Start temperature measurement
  status = bmp180.startTemperature();
  if (status != 0) 
  {
    // Wait for temperature measurement to complete
    delay(status);
    // Get temperature data
    status = bmp180.getTemperature(temperature);
    if (status != 0) 
    {
      // Start pressure measurement
      status = bmp180.startPressure(3);
      if (status != 0) 
      {
        // Wait for pressure measurement to complete
        delay(status);
        // Get pressure data
        status = bmp180.getPressure(pressure, temperature);
        if (status != 0) 
        {
          // Print temperature and pressure data
          Serial.print("Temperature: ");
          Serial.print(temperature);
          Serial.println(" C");
          Serial.print("Pressure: ");
          Serial.print(pressure);
          Serial.println(" hPa");
        } 
        else 
        {
          Serial.println("Error: Unable to read pressure data");
        }
      }
       else
        {
        Serial.println("Error: Unable to start pressure measurement");
      }
    }
     else 
     {
      Serial.println("Error: Unable to read temperature data");
    }
  } 
  else
   {
    Serial.println("Error: Unable to start temperature measurement");
  }

  // Wait before taking the next measurement
  delay(1000);
}
