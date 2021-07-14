#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
SoftwareSerial NeoSixM(8, 9);
String fileName = "0LH.txt";

void(* resetFunc) (void) = 0;

void setup() {
  //Serial.begin(9600);
  NeoSixM.begin(9600);
  if (!SD.begin(10)) {
    SPI.end();
    pinMode(LED_BUILTIN, OUTPUT);
    for (uint8_t i = 0; i < 50; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    resetFunc();
  }
  for (long i = 0; SD.exists(fileName); i++) fileName = String(i) + "LH.txt";
}

void loop() {
  if (NeoSixM.available() > 0) {
    File dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
      while (NeoSixM.available() > 0) {
        char gpsData = NeoSixM.read();
        dataFile.print(gpsData);
        //Serial.print(gpsData);
      }
      dataFile.close();
    }
  }
}
