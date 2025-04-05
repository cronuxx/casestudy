#include <Arduino.h>
#include <sensor.h>

// SENSOR FILTER DATA 

float unfilteredCircularTemperatureBuffer[] = {0, 0, 0, 0, 0};
float circularTemperatureBuffer[] = {0, 0, 0, 0, 0};


void bubble_sort(float arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


float find_median(float *unfilteredWindow, int n){
    bubble_sort(unfilteredWindow, n);

    if (n % 2 == 1) {
        return unfilteredWindow[n / 2]; // Tek elemanlı ise ortadaki eleman
    } else {
        return (unfilteredWindow[n/2 - 1] + unfilteredWindow[n/2]) / 2.0; // Çiftse ortadaki iki elemanın ortalaması
    }
  // use bubble sort
  // find median
  // return median
};


void filter_sensor_value(float *raw_sensor_value, uint8_t window_size){

  float temporaryWindow[window_size];

  for (int i = 0; i < CT_BUFFER_SIZE; i++){
    for (int j = 0; j < window_size; j++){
      
      int windowLocation = i - 1 + j;
      if (windowLocation < 0){
        windowLocation = 0;
      }
      if (windowLocation >= CT_BUFFER_SIZE){
        windowLocation = CT_BUFFER_SIZE - 1;
      }
      temporaryWindow[j] = *(raw_sensor_value + windowLocation);
    }
    circularTemperatureBuffer[i] = find_median(temporaryWindow, window_size);
  }
};



// TEMPERATURE SENSOR 

int bufferLocation = 0;

int generateTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor){

  // Checking if user wants to read data from correct register address. 
  // if (temperatureSensor->temperatureRegister != LM75A_TEMPERATURE_REGISTER){
  //   // return false conditiong if user trying to access wrong register. 
  //   return -1; 
  // }
  // randomSeed(analogRead(0));

  // Randomly generating 9 bit I2C data. 
  // uint8_t msb = random(0, 2); // Generates a random number between 0 and 1
  // temperatureSensor->MSB = msb;
  // uint8_t lsb = random(0, 255);  // Generates a random number between 0 and 255
  // temperatureSensor->LSB = lsb;

  // For seeing effect of filtering process, Program will generate degree between 
  // 23 to 28 degree and randomly it will generate random noise effect such as -10 degree or 50 degree.

  temperatureSensor->measuredValue = random(22,29);
  temperatureSensor->measuredValue += random(0,10) * 0.1;

  // %20 possibilty to generate random noise
  if (random(1,6) == 1){
    if (random(0,2) == 1){
      temperatureSensor->measuredValue -= 20;
    }
    else{
      temperatureSensor->measuredValue += 20;
    }
  }
  
  // Inserting unfiltered data to unfiltered circular buffer
  if (bufferLocation < UFT_BUFFER_SIZE){
    unfilteredCircularTemperatureBuffer[bufferLocation] = temperatureSensor->measuredValue;
    bufferLocation++;
  }
  else if(bufferLocation == UFT_BUFFER_SIZE){
    bufferLocation = 0;
    unfilteredCircularTemperatureBuffer[bufferLocation] = temperatureSensor->measuredValue;
    bufferLocation++;
  }


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
  Serial.print("Temperature: ");
  Serial.println(temperatureSensor->measuredValue);
};


// HUMIDITY SENSOR 

// Randomly generating 9 bit i2c data for simulating
int generateHumidityData(Si7021_A20_HUMIDITY_SENSOR *humiditySensor){
  // Checking if user wants to read data from correct register address. 
  if (humiditySensor->humidityRegister != Si7021_A20_HUMIDITY_REGISTER){
    // return false conditiong if user trying to access wrong register. 
    return -1; 
  }

  randomSeed(analogRead(0));
  
  // Randomly generating 16 bit I2C data. 
  uint8_t msb = random(0, 256); // Generates a random number between 0 and 1
  humiditySensor->MSB = msb;
  
  uint8_t lsb = random(0,256);  // Generates a random number between 0 and 255
  humiditySensor->LSB = lsb;

  return 0;
};

// Decoding i2c data to get real temperature
void decodeHumidityData(Si7021_A20_HUMIDITY_SENSOR *humiditySensor){
  /*
    Formula:
    Relative Humidity = ((125 * Raw_Humidity_Data) / 65536) - 6
  */
  uint16_t rawHumidity = (uint16_t) humiditySensor->MSB << 8 |  humiditySensor->MSB;
  float relativeHumidity = (125 * rawHumidity / 65536) - 6;
  humiditySensor->measuredValue = relativeHumidity;   

  /*
  Due to normal variations in RH accuracy of the device as described in Table 4, it is possible for the measured value
  of %RH to be slightly less than 0 when the actual RH level is close to or equal to 0. Similarly, the measured value
  of %RH may be slightly greater than 100 when the actual RH level is close to or equal to 100. This is expected
  behavior, and it is acceptable to limit the range of RH results to 0 to 100%RH in the host software by truncating
  values that are slightly outside of this range

  https://www.silabs.com/documents/public/data-sheets/Si7021-A20.pdf
  */

};

// Printing relative humidity
void printHumidityData(Si7021_A20_HUMIDITY_SENSOR *humiditySensor){
  Serial.print("Relative Humidity: ");
  Serial.println(humiditySensor->measuredValue);
};

// PRESSURE SENSOR

// Randomly generating 9 bit i2c data for simulating
int generatePressureData(NPI_19_PRESSURE_SENSOR *pressureSensor){

  randomSeed(analogRead(0));
  
  // Randomly generating 14 bit I2C data. 
  uint8_t msb = random(0, 255); // Generates a random number between 0 and 255
  pressureSensor->MSB = msb;
  
  uint8_t lsb = random(0,64);  // Generates a random number between 0 and 64
  pressureSensor->LSB = lsb;

  return 0;
};

// Decoding i2c data to get real pressure in term of PSI
void decodePressureData(NPI_19_PRESSURE_SENSOR *pressureSensor){
  uint16_t rawPressure = (uint16_t) pressureSensor->MSB << 6 |  pressureSensor->LSB;
  float pressurePsi = (rawPressure - 1638.0) * 30.0 / (14745 - 1638);
  pressureSensor->measuredValue = pressurePsi;   

};

// Printing PSI
void printPressureData(NPI_19_PRESSURE_SENSOR *pressureSensor){
  Serial.print("PSI: ");
  Serial.println(pressureSensor->measuredValue);
};





