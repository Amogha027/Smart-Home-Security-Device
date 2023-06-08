#include "Servo.h"
#include "DHT.h"
#include <time.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ThingSpeak.h>
#include <PubSubClient.h>

int inputPin = 4;   // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0;        // variable for reading the pin status
int count=0;

char *wifi="testwifi";
char *password="madhavtank";

const char* server = "mqtt3.thingspeak.com";

const char* mqttUserName = "MDUdHA0bJjQnLTw0Jgg0CTM";

const char* mqttPass = "/0YBE79XJcN4Y//9KK/JbmJ0";

const char* clientID="MDUdHA0bJjQnLTw0Jgg0CTM";

long writeChannelID = 1783435;
const char* writeAPIKey = "L286XWBLT3UXAHD4";

int port = 1883;
 
WiFiClient client;
PubSubClient mqttClient(client);

String CSEIP=" 192.168.178.84";
//String CSEIP="127.0.0.1";
String CsePort="8080";

String Server="http://" + CSEIP + ":" + CsePort + "/~/in-cse/in-name/";
String ae="Project_Data";
String cnt="Node1";
String cnt2="Node2";
String cnt3="Node3";

#define dht_dpin 21              // change dht pin from 4..~~
#define DHTTYPE DHT11

 DHT dht(dht_dpin, DHTTYPE);

 int servo_pin = 27;

 Servo servo_obj;
 int angle = 10;

const int trigpin1 = 32;
const int echopin1 = 23;

const int trigpin2 = 12;
const int echopin2 = 13;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration1;
float distance1;
long duration2;
float distance2;

//void CreateCI(String &temperature, String &humidity, String &count)
void CreateCI2(String humidity)
{
  HTTPClient http;
  http.begin(Server+ae+"/"+cnt2+"/");
  Serial.println(Server+ae+"/"+cnt2+"/");
  http.addHeader("X-M2M-Origin", "admin:admin"); 
  http.addHeader("Content-Type", "application/json;ty=4");

  int humid=http.POST("{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + humidity + "}}");
  Serial.println(humid);
  if(humid==-1){
    Serial.println("Unable to connect");
  }
  http.end();
}

void CreateCI(String temperature)
{
  HTTPClient http;
  http.begin(Server+ae+"/"+cnt+"/");
  Serial.println(Server+ae+"/"+cnt+"/");
  http.addHeader("X-M2M-Origin", "admin:admin"); 
  http.addHeader("Content-Type", "application/json;ty=4");

  int temp=http.POST("{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + temperature + "}}");
  Serial.println(temp);
  if(temp==-1){
    Serial.println("Unable to connect");
  }
  http.end();
}

void CreateCI3(String count)
{
  HTTPClient http;
  http.begin(Server+ae+"/"+cnt3+"/");
  Serial.println(Server+ae+"/"+cnt3+"/");
  http.addHeader("X-M2M-Origin", "admin:admin"); 
  http.addHeader("Content-Type", "application/json;ty=4");

  int counter=http.POST("{\"m2m:cin\": {\"cnf\": \"application/json\",\"con\": " + count + "}}");
  Serial.println(counter);
  if(counter == -1){
    Serial.println("Unable to connect");
  }

  http.end();
}

void setup()
{
    Serial.begin(9600);
    Serial.print("ConneD: ");
    Serial.println(wifi);
    pinMode(dht_dpin,INPUT);
    pinMode(inputPin, INPUT); // declare pir sensor as input
    pinMode(trigpin1, OUTPUT);
    pinMode(trigpin2, OUTPUT);
    pinMode(echopin1, INPUT); // Sets the echopin1 as an Input
    pinMode(echopin2, INPUT); // Sets the echopin2 as an Input
    servo_obj.attach(servo_pin);
    dht.begin();
    Serial.print("Connecting to SSID: ");
    Serial.println(wifi);
    Serial.print("Password: ");
    Serial.println(password);
    
    WiFi.begin(wifi,password);
    while(WiFi.status() != WL_CONNECTED){
      Serial.println("Retrying to connect...");
      WiFi.begin(wifi,password);
      delay(3000);
      }
    Serial.print("Connected!");
        mqttClient.setServer(server,port);
    delay(1000);
}

void loop()
{
      while(mqttClient.connected()==NULL){
     Serial.println("COnnecting to mqtt...");
     mqttClient.connect(clientID, mqttUserName, mqttPass);
     delay(1000);
  }
  mqttClient.loop();

    /* PIR CODE STARTS */
                    float temp = dht.readTemperature();
                float humidity = dht.readHumidity();

    val = digitalRead(inputPin); // read input value
    Serial.println(val);
//    if (val == HIGH)
//    { 
        pirState = HIGH;
        digitalWrite(trigpin1, LOW);

        delayMicroseconds(2);

        // Sets the trigpin1 on HIGH state for 10 micro seconds

        digitalWrite(trigpin1, HIGH);

        delayMicroseconds(10);

        digitalWrite(trigpin1, LOW);

        // Reads the echopin1, returns the sound wave travel time in microseconds
        duration1 = pulseIn(echopin1, HIGH);

        // Calculate the distance
        distance1 = duration1 * SOUND_SPEED / 2;

        digitalWrite(trigpin2, LOW);
        delayMicroseconds(2);
         digitalWrite(trigpin2, HIGH);
         delayMicroseconds(10);
         digitalWrite(trigpin2, LOW);
         duration2 = pulseIn(echopin2, HIGH);
         distance2 = duration2 * SOUND_SPEED / 2;
         
        // Prints the distance in the Serial Monitor

        Serial.print("Distance1 (cm): ");
        Serial.println(distance1);

        Serial.print("Distance2 (cm): ");
        Serial.println(distance2);
                        Serial.print("Temperature :");
                Serial.println(temp);
            
                Serial.print("Humidity :");
                Serial.println(humidity);

        if (distance1 < 350 && distance1 > 0 && distance2 > distance1)
        {
            Serial.println("Person Incoming!!!! ");
            count++;
            delay(5000);
//                float temp = dht.readTemperature();
//                float humidity = dht.readHumidity();
            
//                Serial.print("Temperature :");
//                Serial.println(temp);
//            
//                Serial.print("Humidity :");
//                Serial.println(humidity);
                delay(2000);
                if (temp<100)
                {
                  servo_obj.write(angle);
                  Serial.print("Constraint satisfied - moving to angle ");
                  Serial.println(angle);
                  angle += 20;
                  angle %= 180;
                }
                delay(1000);
        }
        else if(distance2 < 150 && distance2<distance1)
        {
            Serial.println("Person Outgoing!!!! ");
            if(count>0)
            {count--;}
            delay(5000);
        }
        delay(1000);
//    }
//    else
//    {
        //    digitalWrite(ledPin, HIGH); // turn LED OFF

        // we have just turned of
        Serial.println("Motion ended!");
        // We only want to print on the output change, not state
        pirState = LOW;
//    }
    Serial.println(count);
    String strtemp = String(temp);
    String strhumid = String(humidity);
    String strcount = String(count);
    CreateCI(strtemp);
    CreateCI2(strhumid);
    CreateCI3(strcount);
    delay(500);
    //**********************

  String dataString = "field1=" + String(temp);
  String topicString ="channels/" + String( writeChannelID ) + "/publish";
  mqttClient.publish( topicString.c_str(), dataString.c_str() );
  String dataString2 = "field2=" + String(humidity);
  String topicString2 ="channels/" + String( writeChannelID ) + "/publish";
  mqttClient.publish( topicString2.c_str(), dataString2.c_str() );
   String dataString3 = "field3=" + String(count);
  String topicString3 ="channels/" + String( writeChannelID ) + "/publish";
  mqttClient.publish( topicString3.c_str(), dataString3.c_str() );
//*********************
//delay(15000);
}
/* PIR CODE ENDS */


/* ULTRASONIC CODE STARTS*/

// Clears the trigpin1
