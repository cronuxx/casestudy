#include <Arduino.h>
#include <sensor.h>


int generateTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){

  // Checking if user wants to read data from correct register address. 
  if (temperatureSensor->temperatureRegister != LM75A_TEMPERATURE_REGISTER){
    // return false conditiong if user trying to access wrong register. 
    return -1; 
  }
  randomSeed(analogRead(0));
  
  // Randomly generating 8 bit I2C data. 
  // Result in: [0, 255]
  uint8_t msb = random(0,255); // Generates a random number between 0 and 255
  temperatureSensor->MSB = msb;
  
  uint8_t lsb = random(0,255);  // Generates a random number between 0 and 255
  temperatureSensor->LSB = lsb;

  return 0;
}; 

void decodeTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){
  // Converting I2C data to real temperature data. 
  // Formula: rawData / 256.0. 
  uint16_t rawData = (temperatureSensor->MSB << 8) | temperatureSensor->LSB;
  float temperature = rawData / 256.0;
  temperatureSensor->measuredValue = temperature;
};


void printTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){
  Serial.println(temperatureSensor->measuredValue);
}