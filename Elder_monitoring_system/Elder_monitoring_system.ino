#include <Wire.h>
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
int val;
int pulsesensorpin = A0; //Pulse Sensor Pin Connected at A0 Pin

int heartval = 0;

void setup() {
  Serial.begin(9600);
}
void loop() {

  val = analogRead(pulsesensorpin); //Read Analog values and Store in val variable
  Serial.println("Pulse Sensorvalue=  "); // Start Printing on Pulse sensor value on LCD
  Serial.println(val); // Start Printing on Pulse sensor value on LCD

  boolean heartrate = false;


  if (val > 600)
  {
    heartval++;
    if (heartval == 3)
    {
      Serial.println("HIGH PREASURE DETECTED");
      message();
    }
  }


  void updateSerial()
  {
    delay(500);
    while (Serial.available())
    {
      mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
    }
    while (mySerial.available())
    {
      Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
    }
  }

  void message()
  {
    Serial.begin(9600);

    //Begin serial communication with Arduino and SIM800L
    mySerial.begin(9600);

    Serial.println("Initializing...");
    delay(1000);

    mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();

    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+xxxxxxxxxxx\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print("HIGH PREASURE DETECTED"); //text content
    updateSerial();
    mySerial.write(26);
  }
