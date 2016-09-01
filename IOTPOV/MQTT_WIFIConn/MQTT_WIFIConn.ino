#include <Adafruit_DotStar.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h> 
const char* ssid = "free";
const char* password = "133133133";
const char* mqtt_server = "121.201.68.252";

#define MaxStripNum 20
#define switchPin 2 
 
uint32_t contentA[360][MaxStripNum];
uint32_t contentB[360][MaxStripNum];
//uint32_t contentC[360][MaxStripNum];
char showX='0';

Adafruit_DotStar strip = Adafruit_DotStar(MaxStripNum, 4, 5, DOTSTAR_BRG);



void callback(char *topic, byte* payload, unsigned int length) {

  String sTopic = topic;
 
  if(sTopic=="Content")
  {
     Serial.print("changeImage");
     Serial.print((char)payload[0]);
  }
  if(sTopic == "ContentA")
  {
    
    String readRString ;
    readRString= readRString +(char)payload[0] ;
    readRString= readRString +(char)payload[1];//+ (char)payload[2];
    readRString= readRString +(char)payload[2];
  
    int x=readRString.toInt();
    Serial.println(x);
    //Serial.println(length);
    for(int i=0;i<(length-3)/6;i++){
      char color[6];
      color[0]=payload[i*6+3] ;
      color[1]=payload[i*6+4] ;
      color[2]=payload[i*6+5] ;
      color[3]=payload[i*6+6] ;
      color[4]=payload[i*6+7] ;
      color[5]=payload[i*6+8] ;
      uint32_t c = strtoul(color, 0, 16);
      contentA[x][i]=c;
    }
  }
}

WiFiClient espClient;
PubSubClient client(mqtt_server,1883,callback,espClient);


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient","iotpov_chengdu/test0001","Khb78JCWUy2Lqj3miH8bSR45WbC32qM577rHsuDjbYg=")) {
      Serial.println("connected");
      client.subscribe("Content");
      client.subscribe("ContentA");
      client.subscribe("ContentB");
      client.subscribe("ContentC");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  strip.setBrightness(15); 
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP

  pinMode(switchPin,INPUT);
}
int location=0;
int tag =0;
void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  tag = digitalRead(switchPin);
  if(LOW==tag)
  {
    location=0;
  }

  for(int a=location;a<360;a++){
     strip.setPixelColor(0, contentA[a][0]);
     strip.setPixelColor(1, contentA[a][1]); 
     strip.setPixelColor(2, contentA[a][2]);
     strip.setPixelColor(3, contentA[a][3]);
     strip.setPixelColor(4, contentA[a][4]);
     strip.setPixelColor(5, contentA[a][5]);
     strip.setPixelColor(6, contentA[a][6]);
     strip.setPixelColor(7, contentA[a][7]);
     strip.setPixelColor(8, contentA[a][8]);
     strip.setPixelColor(9, contentA[a][9]);
     strip.setPixelColor(10, contentA[a][10]);
     strip.setPixelColor(11, contentA[a][11]);
     strip.setPixelColor(12, contentA[a][12]);  
     strip.setPixelColor(13, contentA[a][13]);  
     strip.setPixelColor(14, contentA[a][14]);  
     strip.setPixelColor(15, contentA[a][15]);  
     strip.setPixelColor(16, contentA[a][16]);  
     strip.setPixelColor(17, contentA[a][17]);  
     strip.setPixelColor(18, contentA[a][18]);  
     strip.setPixelColor(19, contentA[a][19]);  
  }

 
       
  strip.show();
  if(location>360) {
    location=0;
  }
  client.loop();
    
}
