//Don't forget to download libray MFRC522 from  https://github.com/miguelbalboa/rfid  thanks to her/him/they/them 
#include <WiFi.h>
#include <HTTPClient.h>

char *ssid = "********"; // your wifi ssid
char *pwd = "*********"; // your wifi password

String HOST = "192.168.241.9";
unsigned long time_req = 0;
const int server_port = 80;
String strID = "";
String strIDc = "";
int old;
#include <SPI.h>
#include "MFRC522.h"
unsigned int coti = 0;
#define SS_PIN  5  // ESP32 pin GIOP5 
#define RST_PIN 27 // ESP32 pin GIOP27 
#define BUZZER_PIN 33 
#define s1 32
#define s2 35
#define s3 34
int money = 0;
int user = 1;  //user var
MFRC522 rfid(SS_PIN, RST_PIN);

bool collectingData = false;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  WiFi.begin(ssid, pwd);

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}
void sa(){          //write value
 // Construct the URL
  String url = "http://" + HOST +"/php_connect/write"+String(user)+".php?money=" + String(money);
  Serial.println(String(user)+"  "+String(money));
  //Serial.println(url);
  
  // Create an HTTPClient object
  HTTPClient http;
  http.begin(url.c_str());
  // Specify request destination
  http.begin(HOST, server_port, url);
  // Send the request
  int httpResponseCode = http.GET();
  
  // Check for response
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  // End HTTP connection
  http.end();
}
int rea_se() {    //read value
  HTTPClient http;
  String url = "http://" + HOST + "/php_connect/read" + String(user) + ".php";
  http.begin(url.c_str());
// Serial.println(url);
  int httpCode = http.GET();
  int result = 0; // Initialize result to 0

  if (httpCode > 0) {
    String response = http.getString();
    result = response.toInt(); // Convert response to integer
  }

  http.end();
  return result;
}

void CLC(){        //collect data
  while(strID != strIDc){
     
     if (rfid.PICC_IsNewCardPresent()){
      if (rfid.PICC_ReadCardSerial()) {
        Serial.println("Wrong card");
      strIDc = "";
      for (int i = 0; i < rfid.uid.size; i++) {
        strIDc += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i != 3 ? ":" : "");
      }
      strIDc.toUpperCase();
     }
    }
    coti = millis();
   
    int ss1 = digitalRead(s1);
    int ss2 = digitalRead(s2);
    int ss3 = digitalRead(s3);
    if (ss1 == 1 && coti >=200) {
      Serial.println("1b detected");
      money+=1;
      tone(BUZZER_PIN, 1000);
      delay(100);
      tone(BUZZER_PIN, 0);
      coti = 0;
      }
    if (ss2 == 1 && coti >=200) {
      Serial.println("5b detected");
      money+=5;
      tone(BUZZER_PIN, 1000);
      delay(100);
      tone(BUZZER_PIN, 0);
      coti = 0;
      }
    if (ss3 == 1 && coti >=200) {
      Serial.println("10b detected");
      money+=10;
      tone(BUZZER_PIN, 1000);
      delay(100);
      tone(BUZZER_PIN, 0);
      coti = 0;
      }
    delay(10);
      

      
  } 
  int old = rea_se();
  Serial.println(String(user)+"  "+String(old));
  money += old;
  sa();

  money = 0;
  strIDc ="";
  strID="";
  tone(BUZZER_PIN, 250);
  delay(100);
  tone(BUZZER_PIN, 0);
  delay(250);
  tone(BUZZER_PIN, 750);
  delay(100);
  tone(BUZZER_PIN, 0);
  delay(1000);
}
void loop() {
  // Check if a new card is present
  strID="";
  if (rfid.PICC_IsNewCardPresent()) { 
    // Read the card's UID
    if (rfid.PICC_ReadCardSerial()) {
      // Store the UID in strID
      strID = "";
      for (int i = 0; i < rfid.uid.size; i++) {
        strID += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i != 3 ? ":" : "");
      }
      strID.toUpperCase();
      
      // Process based on the UID
      if (strID == "E7:36:63:F2") {
        Serial.println("Tacineh");
        tone(BUZZER_PIN, 1000);
        delay(200);
        tone(BUZZER_PIN, 0);
        user = 1;
        delay(1000);
        CLC();
      } else if (strID == "47:0E:38:F2") {
        Serial.println("Hectin");
        tone(BUZZER_PIN, 500);
        delay(100);
        tone(BUZZER_PIN, 0);
        user = 2;
        delay(1000);
        CLC();
      } else {
        Serial.println("Fake card");
        tone(BUZZER_PIN, 1000);
        delay(200);
        tone(BUZZER_PIN, 0);
      }

      // Wait until the card is removed
      while (rfid.PICC_IsNewCardPresent()) {
        delay(100);
      }

      // Clear the card ID
      strID = "";

      // Halt the card and stop crypto
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }
  /*String str = rea_se();
  if(str!= ""){
    Serial.println(str);
    }*/
}


