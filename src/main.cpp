// /*
//   Basic ESP8266 MQTT PIR sketch
// */
// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include "Adafruit_MQTT.h"
// #include "Adafruit_MQTT_Client.h"

// // Update these with values suitable for your network.

// #include "secrets.h"

// // Start a counter for serial logging and set the initial value to no motion
// int counter = 0;
// int previousReading = LOW;

// WiFiClientSecure client;
// // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
// Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// // Setup publish feeds - define topic name in parenthesis
// Adafruit_MQTT_Publish status = Adafruit_MQTT_Publish(&mqtt, AIO_CID "/feeds/motion");
// Adafruit_MQTT_Publish motion_topic = Adafruit_MQTT_Publish(&mqtt, AIO_CID "/feeds/motion");

// long lastMsg = 0;
// char msg[50];
// int value = 0;

// /////////////////////////////
// //VARS
// //the time we give the sensor to calibrate (10-60 secs according to the datasheet)
// int calibrationTime = 15;

// //the time when the sensor outputs a low impulse
// long unsigned int lowIn;

// //the amount of milliseconds the sensor has to be low
// //before we assume all motion has stopped
// long unsigned int pause = 5000;

// boolean lockLow = true;
// boolean takeLowTime;

// int pirPin = D7; // the digital pin connected to the PIR sensor's output
// int ledPin = D0; // the digital pin connected to built-in LED

// void MQTT_connect();

// void setup_wifi()
// {

//   delay(10);
//   // We start by connecting to a WiFi network
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(WLAN_SSID);

//   WiFi.begin(WLAN_SSID, WLAN_PASS);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }

// // Setup a MQTT subscription
// void callback(char *topic, byte *payload, unsigned int length)
// {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//   for (int i = 0; i < length; i++)
//   {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();

//   // Switch on the LED if an 1 was received as first character
//   if ((char)payload[0] == '1')
//   {
//     digitalWrite(BUILTIN_LED, HIGH); // Turn the LED on (Note that LOW is the voltage level
//     // but actually the LED is on; this is because
//     // it is active low on the ESP-01)
//   }
//   else
//   {
//     digitalWrite(BUILTIN_LED, LOW); // Turn the LED off by making the voltage HIGH
//   }
// }

// void MQTT_connect()
// {
//   int8_t ret;

//   // Stop if already connected.
//   if (mqtt.connected())
//   {
//     return;
//   }

//   Serial.print("Connecting to MQTT... ");

//   uint8_t retries = 3;
//   while ((ret = mqtt.connect()) != 0)
//   { // connect will return 0 for connected
//     Serial.println(mqtt.connectErrorString(ret));
//     Serial.println("Retrying MQTT connection in 5 seconds...");
//     mqtt.disconnect();
//     delay(5000); // wait 5 seconds
//     retries--;
//     if (retries == 0)
//     {
//       // basically die and wait for WDT to reset me
//       while (1)
//         ;
//     }
//   }
//   Serial.println("MQTT Connected!");
//   status.publish("online");
// }

// void setup()
// {
//   pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
//   // Serial.begin(115200);
//   Serial.begin(9600);
//   setup_wifi();
//   pinMode(pirPin, INPUT);
//   pinMode(ledPin, OUTPUT);
//   digitalWrite(pirPin, HIGH);

//   //give the sensor some time to calibrate
//   Serial.print("calibrating sensor ");
//   for (int i = 0; i < calibrationTime; i++)
//   {
//     Serial.print(".");
//     delay(500);
//   }
//   Serial.println(" done");
//   Serial.println("SENSOR ACTIVE");
//   delay(50);
// }

// void loop()
// {
//   // Ensure the connection to the MQTT server is alive (this will make the first
//   // connection and automatically reconnect when disconnected).  See the MQTT_connect
//   // function definition further below.
//   MQTT_connect();

//   if (digitalRead(pirPin) == HIGH)
//   {
//     digitalWrite(ledPin, LOW); //the led visualizes the sensors output pin state
//     if (lockLow)
//     {
//       motion_topic.publish("ON");
//       //makes sure we wait for a transition to LOW before any further output is made:
//       lockLow = false;
//       Serial.println("---");
//       Serial.print("motion detected at ");
//       Serial.print(millis() / 1000);
//       Serial.println(" sec");
//       delay(50);
//     }
//     takeLowTime = true;
//   }

//   if (digitalRead(pirPin) == LOW)
//   {
//     digitalWrite(ledPin, HIGH); //the led visualizes the sensors output pin state

//     if (takeLowTime)
//     {
//       lowIn = millis();    //save the time of the transition from high to LOW
//       takeLowTime = false; //make sure this is only done at the start of a LOW phase
//     }
//     //if the sensor is low for more than the given pause,
//     //we assume that no more motion is going to happen
//     if (!lockLow && millis() - lowIn > pause)
//     {
//       motion_topic.publish("OFF");
//       //makes sure this block of code is only executed again after
//       //a new motion sequence has been detected
//       lockLow = true;
//       Serial.print("motion ended at "); //output
//       Serial.print((millis() - pause) / 1000);
//       Serial.println(" sec");
//       delay(50);
//     }
//   }
// }
