
#include <WiFi.h>
#include <PubSubClient.h>

const int Relay1 = 15;
const int Relay2 = 2;
const int Relay3 = 4;
const int Relay4 = 22;

#define switch1 32
#define switch2 35
#define switch3 34
#define switch4 39
   

//WiFi Status LED
#define wifiLed1 26
#define wifiLed2 25
#define wifiLed3 27

int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag2_previous_I = 0;
int switch_ON_Flag3_previous_I = 0;
int switch_ON_Flag4_previous_I = 0;

// Update these with values suitable for your network.
//WIFI SETUP
const char* ssid = "HTC Portable Hotspot 7ABF"; //WiFI Name
const char* password = "1234567tc"; //WiFi Password
const char* mqtt_server = "iot.reyax.com";

//MQTT SETUP
const char* username = "mWwYrDpDhf"; //Reyax Useename
const char* pass = "4FsxEABSdE"; //Reyax Password
const char* topic = "api/request";
const char* clientID = "ESP8266Client-"; // client id
//String msgStr = "";      // MQTT message buffer

#define sub1 "switch1"
#define sub2 "switch2"
#define sub3 "switch3"
#define sub4 "switch4"

#define pub1 "switch1_state"
#define pub2 "switch2_state"
#define pub3 "switch3_state"
#define pub4 "switch4_state"

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (300)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(wifiLed1, HIGH);
    delay(250);
    Serial.print(".");
    digitalWrite(wifiLed1, LOW);
    delay(250);
  }
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  digitalWrite(wifiLed1, HIGH);
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID, username, pass)) {
      Serial.println("MQTT connected");
      digitalWrite(wifiLed2, HIGH);
      client.subscribe(sub1);
      client.subscribe(sub2);
      client.subscribe(sub3);
      client.subscribe(sub4);    
      //Serial.println(sub1);
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in few seconds");digitalWrite(wifiLed1, LOW);digitalWrite(wifiLed2, LOW);
      delay(200);
      digitalWrite(wifiLed1, HIGH);
      delay(200);// wait few sec and retry

//manual control when internet is not connected
    digitalWrite(Relay1, digitalRead(switch1));
    digitalWrite(Relay2, digitalRead(switch2));
    digitalWrite(Relay3, digitalRead(switch3));
    digitalWrite(Relay4, digitalRead(switch4));
   }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  digitalWrite(wifiLed3, HIGH);delay(100);
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i< length; i++) {
  Serial.print((char)payload[i]);
  }
  Serial.println();  
  Serial.print("Message size :");
  Serial.println(length);
  Serial.println();
  Serial.println("-----------------------");
  digitalWrite(wifiLed3, LOW);
  
  if (strstr(topic, sub1))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay1, LOW);   // Turn the LED on (Note that LOW is the voltage level
      Serial.print("Relay1 LOW");
    } else {
      digitalWrite(Relay1, HIGH);  // Turn the LED off by making the voltage HIGH
      Serial.print("Relay1 HIGH");
    }
  }

  else if ( strstr(topic, sub2))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay2, LOW);   // Turn the LED on (Note that LOW is the voltage level
      
    } else {
      digitalWrite(Relay2, HIGH);  // Turn the LED off by making the voltage HIGH
      
    }
  }
  else if ( strstr(topic, sub3))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay3, LOW);   // Turn the LED on (Note that LOW is the voltage level
      
    } else {
      digitalWrite(Relay3, HIGH);  // Turn the LED off by making the voltage HIGH
      
    }
  }
  else if ( strstr(topic, sub4))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(Relay4, LOW);   // Turn the LED on (Note that LOW is the voltage level
      
    } else {
      digitalWrite(Relay4, HIGH);  // Turn the LED off by making the voltage HIGH
     
    }
  }
  else
  {
    Serial.println("unsubscribed topic");
  }
}
void manual_control(){
         
 if (digitalRead(switch1) == LOW)
  {
    if (switch_ON_Flag1_previous_I == 0 )
    {
      digitalWrite(Relay1, LOW);
      client.publish(pub1, "0");
      Serial.println("Relay1- ON");
      switch_ON_Flag1_previous_I = 1;
    }
    }
  if (digitalRead(switch1) == HIGH )
  {
    if (switch_ON_Flag1_previous_I == 1)
    {
      digitalWrite(Relay1, HIGH);
      client.publish(pub1, "1");
      Serial.println("Relay1 OFF");
     switch_ON_Flag1_previous_I = 0;
    }
    }
 if (digitalRead(switch2) == LOW)
  {
    if (switch_ON_Flag2_previous_I == 0 )
    {
      digitalWrite(Relay2, LOW);
      client.publish(pub2, "0");
      Serial.println("Relay1- ON");
      switch_ON_Flag2_previous_I = 1;
    }
    }
  if (digitalRead(switch2) == HIGH)
  {
    if (switch_ON_Flag2_previous_I == 1)
    {
      digitalWrite(Relay2, HIGH);
      client.publish(pub2, "1");
      Serial.println("Relay1 OFF");
     switch_ON_Flag2_previous_I = 0;
    }
    }
   if (digitalRead(switch3) == LOW)
  {
    if (switch_ON_Flag3_previous_I == 0 )
    {
      digitalWrite(Relay3, LOW);
      client.publish(pub3, "0");
      Serial.println("Relay1- ON");
      switch_ON_Flag3_previous_I = 1;
    }
    }
  if (digitalRead(switch3) == HIGH )
  {
    if (switch_ON_Flag3_previous_I == 1)
    {
      digitalWrite(Relay3, HIGH);
      client.publish(pub3, "1");
      Serial.println("Relay1 OFF");
      switch_ON_Flag3_previous_I = 0;
    }
   }
 if (digitalRead(switch4) == LOW)
  {
    if (switch_ON_Flag4_previous_I == 0 )
    {
      digitalWrite(Relay4, LOW);
      client.publish(pub4, "0");
      Serial.println("Relay1- ON");
      switch_ON_Flag4_previous_I = 1;
    }
    }
  if (digitalRead(switch4) == HIGH )
  {
    if (switch_ON_Flag4_previous_I == 1)
    {
      digitalWrite(Relay4, HIGH);
      client.publish(pub4, "1");
      Serial.println("Relay1 OFF");
      switch_ON_Flag4_previous_I = 0;
    }
   }
    delay(100);
}


void setup() {
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);

  
  pinMode(wifiLed1, OUTPUT);
  pinMode(wifiLed2, OUTPUT);
  pinMode(wifiLed3, OUTPUT);

   digitalWrite(wifiLed1, HIGH);
   delay(100);
   digitalWrite(wifiLed2, HIGH);
   delay(100);
   digitalWrite(wifiLed3, HIGH);
   delay(100);

   digitalWrite(wifiLed1, LOW);
   digitalWrite(wifiLed2, LOW);
   digitalWrite(wifiLed3, LOW);
   delay(500);
   
   
  
  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
    
    }
    else{
    manual_control();
   }
  client.loop();
  delay(50);

 
}
