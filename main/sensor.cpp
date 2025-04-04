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
  int16_t rawData = temperatureSensor->LSB;
  
  // if Most Significant Bit is 1, Temperature is negative
  // So according to datasheet we need to apply 2's complementary.
  if (temperatureSensor->MSB == 1){
    rawData = ~rawData + 1;
  }
  
  float temperature = rawData * 0.5;
  temperatureSensor->measuredValue = temperature;
};


void printTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){
  Serial.print("MSB: ");
  Serial.println(temperatureSensor->MSB);
  Serial.print("LSB: ");
  Serial.println(temperatureSensor->LSB);
  Serial.print("Temperature: ");
  Serial.println(temperatureSensor->measuredValue);
}