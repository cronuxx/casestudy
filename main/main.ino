#include <sensor.h>

/*
1- Sensörlerden veriyi oku (1 Hz)
2- Veriyi median filter ile filtrele
3- Datayı buffer içinde sakla
4- Bluetooth ile data gönder (30 Sn)
*/

LM75A_TEMP_SENSOR tempSensor = {LM75A_I2C_ADDRESS, 0x00, 0, 0, 0};
Si7021_A20_HUMIDITY_SENSOR humiditySensor = {Si7021_A20_I2C_ADDRESS, 0xE5, 0, 0, 0};
NPI_19_PRESSURE_SENSOR pressureSensor = {NPI_19_I2C_ADDRESS, 0, 0, 0, 0};




void setup(){

  Serial.begin(9600);


  
  // put your setup code here, to run once:
}

void loop() {

  generateTemperatureData(&tempSensor);
  // decodeTemperatureData(&tempSensor);
  printTemperatureData(&tempSensor);
  filter_sensor_value(unfilteredCircularTemperatureBuffer, 3);

  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(unfilteredCircularTemperatureBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(circularTemperatureBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();


  // for (int i = 0; i < UFT_BUFFER_SIZE; i++){
  //   Serial.print(circularTemperatureBuffer[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();

  // generateHumidityData(&humiditySensor);
  // decodeHumidityData(&humiditySensor);
  // printHumidityData(&humiditySensor);

  // generatePressureData(&pressureSensor);
  // decodePressureData(&pressureSensor);
  // printPressureData(&pressureSensor);
  sleep(1);
}
