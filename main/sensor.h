#ifndef SENSOR_H
#define SENSOR_H

#define LM75A_I2C_ADDRESS                0x48
#define LM75A_TEMPERATURE_REGISTER       0x00
#define Si7021_A20_I2C_ADDRESS           0x40
#define Si7021_A20_HUMIDITY_REGISTER     0xE5
#define NPI_19_I2C_ADDRESS               0x28

#define UFT_BUFFER_SIZE 5
#define CT_BUFFER_SIZE  5

extern float unfilteredCircularTemperatureBuffer[UFT_BUFFER_SIZE];
extern float circularTemperatureBuffer[CT_BUFFER_SIZE];

void filter_sensor_value(float *raw_sensor_value, uint8_t window_size);
/*
float i2c_sensor_read(uint8_t device_address, enum sensor_t sensor_type);
float filter_sensor_value(float raw_sensor_value, uint8_t window_size);”
int buffer_get_value(struct buf_handle_t *p_handle, float *p_sensor_data);”. (Returns 0 on success)
*/




/*

      ****************************************************************
      **      Since i don't have physical version of sensors        **            
      ** program will generate the datas randomly and decode itself **
      ****************************************************************

*/



//---------------------------- TEMPERATURE SENSOR ----------------------------

/*
                        LM75A Digital Temperature Sensor 
Datasheet: 
https://www.ti.com/lit/ds/symlink/lm75a.pdf?ts=1743784006061&ref_url=https%253A%252F%252Fwww.google.com%252F

*/

typedef struct{
  uint8_t i2cAddress;          // 8 bit i2c device's address
  uint8_t temperatureRegister; // 8 bit i2c address of temperature register 
  bool MSB;                    // Sign of the temperature           
  uint8_t LSB;                 // Magnitude of temperature              
  float measuredValue;         // Measured sensor value
}LM75A_TEMP_SENSOR;

// Randomly generating 9 bit i2c data for simulating
int generateTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor); 

// Decoding i2c data to get real temperature
void decodeTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor);

// Printing real temperature
void printTemperatureData(LM75A_TEMP_SENSOR *temperatureSensor);

//---------------------------- HUMIDITY SENSOR ----------------------------

/*
                   Si7021 I2C Humidity and Temperature Sensor
Datasheet: 
https://www.silabs.com/documents/public/data-sheets/Si7021-A20.pdf

*/


typedef struct{
  uint8_t i2cAddress;          // 8 bit i2c device's address
  uint8_t humidityRegister;    // 8 bit i2c address of humidity register 
  uint8_t MSB;                 // Most significant byte of the humidity           
  uint8_t LSB;                 // Least significant byte of humidity              
  float measuredValue;         // Measured sensor value
}Si7021_A20_HUMIDITY_SENSOR;

// Randomly generating 16 bit i2c data for simulating
int generateHumidityData(Si7021_A20_HUMIDITY_SENSOR *humiditySensor); 

// Decoding i2c data to get real humidity
void decodeHumidityData(Si7021_A20_HUMIDITY_SENSOR *humiditySensor);

// Printing relative humidity
void printHumidityData(Si7021_A20_HUMIDITY_SENSOR *humiditySensor);


//---------------------------- PRESSURE SENSOR ----------------------------

/*
                   
                      NPI-19 Digital I2C Pressure Sensors

Datasheet: 
https://www.amphenol-sensors.com/hubfs/AAS-920-699F-NovaSensor-NPI-19-I2C-061322-web.pdf

*/

typedef struct{
  uint8_t i2cAddress;          // 8 bit i2c device's address
  uint8_t pressureRegister;    // 8 bit i2c address of humidity register 
  uint8_t MSB;                 // Most significant byte of the humidity           
  uint8_t LSB;                 // Least significant byte of humidity              
  float measuredValue;         // Measured sensor value
}NPI_19_PRESSURE_SENSOR;

// Randomly generating 14 bit i2c data for simulating
int generatePressureData(NPI_19_PRESSURE_SENSOR *pressureSensor); 

// Decoding i2c data to get pressure
void decodePressureData(NPI_19_PRESSURE_SENSOR *pressureSensor);

// Printing pressure
void printPressureData(NPI_19_PRESSURE_SENSOR *pressureSensor);


#endif 