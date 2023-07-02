#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

String apiKey = "WY9PUVPTLWWLZSTE";

//const char *ssid = "HUAWEI-pRV2"; //ganti nama hotspot
//const char *pass = "5tB2CN9c";//ganti password
const char *ssid = "Redmi8"; //ganti nama hotspot
const char *pass = "09101998";//ganti password
const char* server = "api.thingspeak.com";
const char* resource = "/update?api_key=";

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.print(" Connect to : ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("….");
  }
  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("Connect to : ");
  Serial.println(ssid);

  Wire.begin(2, 0);
  lcd.begin();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.print(" Hello Makers "); // Start Printing

}


void loop() {

  String getDataSet;

  while (Serial.available() > 0) {
    getDataSet += char(Serial.read());
  }

  String getDataSet1 = getValue(getDataSet, ' ', 0);
  String getDataSet2 = getValue(getDataSet, ' ', 1);
  String getDataSet3 = getValue(getDataSet, ' ', 2);
  String getDataSet4 = getValue(getDataSet, ' ', 3);
  String getDataSet5 = getValue(getDataSet, ' ', 4);
  String getDataSet6 = getValue(getDataSet, ' ', 5);

  Serial.print("\nConnecting to ");
  Serial.print(server);
  Serial.print("\n");

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(getDataSet1);
    postStr += "&field2=";
    postStr += String(getDataSet2);
    postStr += "&field3=";
    postStr += String(getDataSet3);
    postStr += "&field4=";
    postStr += String(getDataSet4);
    postStr += "&field5=";
    postStr += String(getDataSet5);
    postStr += "&field6=";
    postStr += String(getDataSet6);

    client.print(String("GET ") + resource + apiKey + "&field1=" + getDataSet1 + "&field2=" + getDataSet2 + "&field3=" + getDataSet3 + "&field4=" + getDataSet4 + "&field5=" + getDataSet5 + "&field6=" + getDataSet6 +
                 " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.print("Send Data to Thingspeak. ");
    Serial.print(postStr);
    Serial.print("\nSuccess ");
  }

  Serial.print("Waiting...");
  Serial.println("\nclosing connection");
  client.stop();
  delay(5000);
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
