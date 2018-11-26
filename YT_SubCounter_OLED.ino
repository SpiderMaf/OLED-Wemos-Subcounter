/* 
Erics Wemos D1 Mini displaying YouTube Subscriber Count with MAX7219 LED Matrix Displays - Now modified by SpiderMaf to add extra details on the sub miniature OLED displays.

Original Library here https://github.com/squix78/MAX7219LedMatrix but contains no function to rotate for my displays
Brian Lough's library contains rotate: https://github.com/witnessmenow/MAX7219LedMatrix
Brians doesnt work with Wemos D1 mini unless you comment out this line https://github.com/witnessmenow/MAX7219LedMatrix/blob/master/LedMatrix.cpp#L34
Done in the cpp file contained with this sketch
Eric originally followed this tutorial here for the YouTube API info etc: http://www.joeybabcock.me/blog/projects/arduino-esp8266-live-subscriber-display/
Wiring for Wemos D1 Mini:
| Pin On 7219| Pin on Wemos D1 Mini |
| ------- |----------------|
| GND     | G |
| VCC     | 3V3 |
| DIN     | D7 |
| CS      | D4 |
| CLK     | D5 |

This code was modified by SpiderMaf from MKMe’s source code so credit to him and the other original authors above.
Support MKme’s original’s project by picking up the display/board here:
Wemos D1: https://amzn.to/2ACRWRA
LED Matrix: https://amzn.to/2McsuUl
MkMe Youtube Channel  : http://www.youtube.com/mkmeorg
MkMe website   : http://www.mkme.org

SpiderMaf’s Youtube Channel : http://www.youtube.com/SpiderMaf
SpiderMafs Website : https://mattnorman.co.uk

You will need to amend the code below with your Channel ID, your YouTube API key and the SSID and PW of the Wifi you want this to connect to.

*/
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h> // This Sketch doesn't technically need this, but the library does so it must be installed.
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <YoutubeApi.h>

//------- Replace the following! ------
char ssid[] = "Jarvis3";       // your network SSID (name)
char password[] = “XXX";  // your network key
#define API_KEY “YYY-YYY-YYY"  // your google apps API Token
#define CHANNEL_ID “ZZZZZZZZZ" // Channel URL text - get from YT advanced Dashboard
#define CS_PIN 2
int x = 0;

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);


unsigned long api_mtbs = 60000; //mean time between api requests
unsigned long api_lasttime;   //last time api request has been done
long subs = 0;
String txt = "Temp"; 
int subv,subc;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("SpiderMaf Stats”);  // Maybe include your channel name here - you don’t care about mine..
   display.println("");
  display.println("Locating AP: Jarvis3");
  display.println("This device name:\n\nMafSubOLED");

  display.display();
  Serial.begin(115200);
  WiFi.hostname("MafSubOLED"); //This changes the hostname of the ESP8266 to display neatly on the network router stats page
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
 
  display.print("WiFi IP:");

  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  display.println(ip);
    display.display();


}
void loop() {
  //ledMatrix.clear();
  //ledMatrix.scrollTextLeft();
  //ledMatrix.drawText();
  //ledMatrix.commit();
  delay(100);
   if(api.getChannelStatistics(CHANNEL_ID))
    {
   subc= api.channelStats.subscriberCount;
   subv = api.channelStats.viewCount;
    }
if (millis() - api_lasttime > api_mtbs)  {
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      Serial.println("---------Stats---------");
      Serial.print("Subscriber Count: ");
      Serial.println(api.channelStats.subscriberCount);

      Serial.print("View Count: ");
      Serial.println(api.channelStats.viewCount);
      Serial.print("Comment Count: ");
      Serial.println(api.channelStats.commentCount);
      Serial.print("Video Count: ");
      Serial.println(api.channelStats.videoCount);
      // Probably not needed :)
      //Serial.print("hiddenSubscriberCount: ");
      //Serial.println(api.channelStats.hiddenSubscriberCount);
      Serial.println("------------------------");
      txt = " Sub:" +String(api.channelStats.subscriberCount) + " V:" + String(api.channelStats.viewCount);

        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("MafSubOLED SpiderMaf");
        display.println(WiFi.localIP());
         display.println("");
      display.print("Subscriber Count: ");
      display.print(api.channelStats.subscriberCount);
       if (api.channelStats.subscriberCount > subc) {
        display.print(" **");
        }
      display.println("");
      display.print("View Count: ");
      display.print(api.channelStats.viewCount);
       if (api.channelStats.viewCount > subv) {
        display.print(" **");
        }
      display.println("");
      display.println("");
      display.print("Video Count: ");
      display.println(api.channelStats.videoCount);   
      display.println("");
      display.println("SPIDERMAF");
      display.display();
      //SaveStats(txt);
      //ledMatrix.setText(txt);
    }
    api_lasttime = millis();
  }
}

void SaveStats() {
  //ledMatrix.setText(“foo");
  }
