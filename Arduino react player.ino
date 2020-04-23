
#include <ESP8266WiFi.h>            //included to allow fuctionality of Wemos D1 Wifi Board
#define PubNub_BASE_CLIENT WiFiClient  //included to access pubnub
#include <PubNub.h> //included to access pubnub

const char* ssid = "VM6377135"; //constant variable to wifi SSID to connect to
const char* password = "g4tzQbqMgk3z"; //constant variable for security key for wifi
const static char pubkey[]  = "pub-c-eac6bd24-e961-4566-b70d-1fedde56b792"; //publish key for pubnub
const static char subkey[]  = "sub-c-ec64027a-81ab-11ea-b498-86721831d398"; // subscriber key for pubnub
const static char channel[] = "VIDEOSELECTION";  // variable storing pubnub channel name
String message; 


const int ledPin =  14;      // the number of the LED pin on the D1 board to be used as a test indicator
int ledState = LOW; // sets the initial state of the LED 


//below function to flash the LED depending of the amount
//of times required , amount of times passed to function using
//amt variable (e.g. flashpin(10) will make amt=10 therfore loops 10 times
void Flashpin14(int amt) {
  for (int i=0; i<amt; i++){   //sets up loop
      digitalWrite(ledPin, HIGH); //turns on LED
      delay (300); // waits 300 milliseconds
      digitalWrite(ledPin, LOW); //turns off LED
      delay (300); // waitis 300 milliseconds
  
  }
}


void setup() {
  pinMode(ledPin, OUTPUT);   //setup the pin to be used for LED
  Serial.begin(9600);   //tells arduino what baud rate to talk to the board at
  delay(10);  
  Serial.println("starting");   //echo starting to console so I know the code is starting
  Serial.print("Connecting to WiFi -  "); // echos connecting to wifi
  Serial.println(ssid); // adds the wifi SSID to the above line
  WiFi.hostname("Name");
  WiFi.begin(ssid, password); //starts the wifi connection process

 //loop to display connecting message whilst connection is made as a visual feedback test
 //once the wifi status is connected the loop ends
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //echo the connected message and displays the IP address so a ping test can be done if needed
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
 //initalises the pubnub process and echos for user to press 1,2 or 3
  PubNub.begin(pubkey, subkey); // Start PubNub.
  Serial.println("PubNub is initalised.");
  Serial.println("Please press 1,2 or 3");
  pinMode(ledPin, OUTPUT);
 
}

//function to publish the required value to pubnub 
void publishtopubnub(char msg[]){

        WiFiClient* client = PubNub.publish(channel, msg); // Publish message.
        if (0 == client) {
            Serial.println("Error publishing message.");
            delay(1000);
            return;
        }
        client->stop();
        
     }

//main code to loop for constant input and to send value to publishtopubnub function when correct key is pressed. 
void loop() {
  int inputByte = Serial.read(); //waits for keypress and assigns value to inputbyte variable
  
  switch (inputByte) { //checks the varibale value for each case
      case '1': //if keypress is 1 
        Serial.println ("1 pressed playing Antartica Video"); //send message to console 
        publishtopubnub ("\"VIDEO1\""); //call publishtopubnub function and send "VIDEO1" to pubnub channel
        Flashpin14(1); //call flashpin14 function with a value of 1 to flash LED once
        break; //finish case statement
      case '2':
         Serial.println ("2 pressed playing Austraila Video");
         publishtopubnub ("\"VIDEO2\"");
         Flashpin14(2);
         break;
      case '3':
          Serial.println ("3 pressed playing Europe Video");
          publishtopubnub ("\"VIDEO3\"");
          Flashpin14(3);
          break;
          
     
     
     
  }
  
}
