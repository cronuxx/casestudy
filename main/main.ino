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

float maxTemperature, medianTemperature, minTemperature, standartDevTemp;
float maxHumidity, medianHumidity, minHumidity, standartDevHumidity;
float maxPressure, medianPressure, minPressure, standartDevPressure;



void setup(){
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {

  generateTemperatureData(&tempSensor);
  // decodeTemperatureData(&tempSensor);
  printTemperatureData(&tempSensor);
  filter_sensor_value(unfilteredCircularTemperatureBuffer, circularTemperatureBuffer, WINDOW_SIZE);

  generateHumidityData(&humiditySensor);
  decodeHumidityData(&humiditySensor);
  printHumidityData(&humiditySensor);
  filter_sensor_value(unfilteredCircularHumidityBuffer, circularHumidityBuffer, WINDOW_SIZE);

  generatePressureData(&pressureSensor);
  decodePressureData(&pressureSensor);
  printPressureData(&pressureSensor);
  filter_sensor_value(unfilteredCircularPressureBuffer, circularPressureBuffer, WINDOW_SIZE);

  Serial.println("----------UNFILTERED TEMPERATUR----------");
  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(unfilteredCircularTemperatureBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println("----------FILTERED TEMPERATURE----------");
  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(circularTemperatureBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();

  // ////////////////////
  Serial.println("----------UNFILTERED HUMIDITY----------");
  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(unfilteredCircularHumidityBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println("----------FILTERED HUMIDITY----------");
  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(circularHumidityBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();
  /////////////////////
  Serial.println("----------UNFILTERED PRESSURE----------");
  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(unfilteredCircularPressureBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("----------FILTERED PRESSURE----------");
  for (int i = 0; i < UFT_BUFFER_SIZE; i++){
    Serial.print(circularPressureBuffer[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();




  maxTemperature = findMax(circularTemperatureBuffer, CT_BUFFER_SIZE);
  medianTemperature = find_median(circularTemperatureBuffer, CT_BUFFER_SIZE);
  minTemperature = findMin(circularTemperatureBuffer, CT_BUFFER_SIZE);
  standartDevTemp = findStandardDeviation(circularTemperatureBuffer, CT_BUFFER_SIZE);

  Serial.print("Max Temperature: ");
  Serial.println(maxTemperature);
  Serial.print("Median Temperature: ");
  Serial.println(medianTemperature);
  Serial.print("Min Temperature: ");
  Serial.println(minTemperature);
  Serial.print("Standart Deviation of Temperature: ");
  Serial.println(standartDevTemp);

  Serial.println();

  maxHumidity = findMax(circularHumidityBuffer, CT_BUFFER_SIZE);
  medianHumidity = find_median(circularHumidityBuffer, CT_BUFFER_SIZE);
  minHumidity = findMin(circularHumidityBuffer, CT_BUFFER_SIZE);
  standartDevHumidity = findStandardDeviation(circularHumidityBuffer, CT_BUFFER_SIZE);

  Serial.print("Max Humidity: ");
  Serial.println(maxHumidity);
  Serial.print("Median Humidity: ");
  Serial.println(medianHumidity);
  Serial.print("Min Humidity: ");
  Serial.println(minHumidity);
  Serial.print("Standart Deviation of Humidity: ");
  Serial.println(standartDevHumidity);

  Serial.println();

  maxPressure = findMax(circularPressureBuffer, CT_BUFFER_SIZE);
  medianPressure = find_median(circularPressureBuffer, CT_BUFFER_SIZE);
  minPressure = findMin(circularPressureBuffer, CT_BUFFER_SIZE);
  standartDevPressure = findStandardDeviation(circularPressureBuffer, CT_BUFFER_SIZE);

  Serial.print("Max Pressure: ");
  Serial.println(maxPressure);
  Serial.print("Median Pressure: ");
  Serial.println(medianPressure);
  Serial.print("Min Pressure: ");
  Serial.println(minPressure);
  Serial.print("Standart Deviation of Pressure: ");
  Serial.println(standartDevPressure);

  sleep(1);
}


// int maxTemperature, medianTemperature, minTemperature, standartDevTemp;
// int maxHumidity, medianHumidity, minHumidity, standartDevHumidity;
// int maxPressure, medianPressure, minPressure, standartDevPressure;


