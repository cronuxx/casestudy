#include <sensor.h>

/*

1- Sensörlerden veriyi oku (1 Hz)
2- Veriyi median filter ile filtrele
3- Datayı buffer içinde sakla
4- Bluetooth ile data gönder (30 Sn)


*/

LM75A_TEMP_SENSOR tempSensor = {0x48, 0x00, 0, 0, 0};


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  generateTemperatureData(&tempSensor);
  decodeTemperatureData(&tempSensor);
  printTemperatureData(&tempSensor);
}
