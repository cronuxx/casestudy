#ifndef SENSOR_H
#define SENSOR_H

#define LM75A_I2C_ADDRESS          0x48
#define LM75A_TEMPERATURE_REGISTER 0x00


/*
3 farklı sensör tanımla
bunların adresleri olsun

float i2c_sensor_read(uint8_t device_address, enum sensor_t sensor_type);
float filter_sensor_value(float raw_sensor_value, uint8_t window_size);”
int buffer_get_value(struct buf_handle_t *p_handle, float *p_sensor_data);”. (Returns 0 on success)

sensor tipi enum ile seçilmeli ?
*/

/*

      ****************************************************************
      **      Since i don't have physical version of sensors        **            
      ** program will generate the datas randomly and decode itself **
      ****************************************************************

*/



//---------------------------- TEMPERATURE SENSOR ----------------------------

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

// struct LM75A_TEMP_SENSOR{};
// struct LM75A_TEMP_SENSOR{};


#endif 