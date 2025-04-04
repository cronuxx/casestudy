#include <Arduino.h>
#include <sensor.h>


int generateTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){

  // Checking if user wants to read data from correct register address. 
  if (temperatureSensor->temperatureRegister != LM75A_TEMPERATURE_REGISTER){
    // return false conditiong if user trying to access wrong register. 
    return -1; 
  }
  randomSeed(analogRead(0));
  
  // Randomly generating 9 bit I2C data. 
  uint8_t msb = random(0, 2); // Generates a random number between 0 and 1
  temperatureSensor->MSB = msb;
  
  uint8_t lsb = random(0,255);  // Generates a random number between 0 and 255
  temperatureSensor->LSB = lsb;

  return 0;
}; 

void decodeTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){
  // Converting I2C data to real temperature data. 
  uint16_t rawData = temperatureSensor->LSB;
  float temperature = rawData * 0.5;
  if (temperatureSensor->MSB == 1){
    temperature *= -1;
  }
  temperatureSensor->measuredValue = temperature;
};


void printTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){
  Serial.println(temperatureSensor->measuredValue);
}