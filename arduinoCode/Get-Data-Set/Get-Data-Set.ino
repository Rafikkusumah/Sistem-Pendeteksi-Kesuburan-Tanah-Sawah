#include <SD.h> //mengicludekan library SDcard
#include <SPI.h> //mengicludekan library SDcard
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
#define HUMADITY_SENSOR A1
#define PH_SENSOR A2
#define CHIP_SELECT 53
// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define SENSOR_OUT 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int outputHumaditySensorValue = 0;
int humaditySensorValue = 0;
int phSensorValue = 0;
float outputPhSensorValue = 0.0;

void setup() {

  ds18b20.begin();
  Serial.begin(115200);

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(SENSOR_OUT, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.println("Initializing SD card...");

  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

}

void loop() {

  // Kelembaban Tanah
  outputHumaditySensorValue = analogRead(HUMADITY_SENSOR);
  humaditySensorValue = 1023 - outputHumaditySensorValue;

  Serial.print(humaditySensorValue);
  Serial.print(" ");

  // Sensor Suhu
  ds18b20.requestTemperatures();
  Serial.print(ds18b20.getTempCByIndex(0));
  Serial.print(" ");

  // read the analog in value:
  phSensorValue = analogRead(PH_SENSOR);

  outputPhSensorValue = (-0.0127 * phSensorValue) + 7.3855;

  //  Sensor PH
  Serial.print(outputPhSensorValue);
  Serial.print(" ");

  //red color
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(SENSOR_OUT, LOW);
  redColor = map(redFrequency, 1023, 0, 0, 128);

  //green color
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(SENSOR_OUT, LOW);
  greenColor = map(greenFrequency, 1023, 0, 0, 120);

  //blue color
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(SENSOR_OUT, LOW);
  blueColor = map(blueFrequency, 1023, 0, 0, 111);

  Serial.print(redColor);
  Serial.print(" ");
  Serial.print(greenColor);
  Serial.print(" ");
  Serial.println(blueColor);

  // Simpan ke file
  File datalog = SD.open("dataset.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (datalog) {

    datalog.print("Suhu = ");
    datalog.print(ds18b20.getTempCByIndex(0));
    datalog.print(",");

    datalog.print("Kelembaban = ");
    datalog.print(humaditySensorValue);
    datalog.print(",");

    datalog.print("PH = ");
    datalog.print(outputPhSensorValue);
    datalog.print(",");

    datalog.print("R = ");
    datalog.print(redColor);
    datalog.print(",");

    datalog.print("G = ");
    datalog.print(greenColor);
    datalog.print(",");

    datalog.print("B = ");
    datalog.println(blueColor);
    datalog.close();

  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening dataset.txt");
  }


  delay(5000);

}
