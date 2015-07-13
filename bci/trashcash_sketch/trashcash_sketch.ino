// ---------------------------------------------------------------------------------------------//
// ThrashCash - Hardware Sheet 
// This sketch is made for public use. 
// With trashcash producst can be scanned by RFID. 
// A recognised product will give a *accepted bleep* and append 10 points.
// If a product is recognised it will append points (by RESTful webservices) to a database!
//--------------------------------------------------------------------------------------------//

//---------------------------------------------------//
//Used Hardware//                                   //
//-------------------------------------------------//
// *Arduino Uno Rev.3
// *Aruino Ethernetshield (with SD card slot)
// *RFID scanner - rdm6300
// *RFID tags
// *Ultrasonic Sensor - HC-sr04
// *Active Piezo speaker
// *5mm green and red led
// *16 x 2 LCD Display
// *Arduino Power Supply holder (for 9v. battery)


//---------------------------------------------------//
//Included Libraries                                //
//-------------------------------------------------//
#include <NewPing.h> 
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
#include "pitches.h" 
#include <SPI.h>
#include <Ethernet.h>

//---------------------------------------------------//
//Variables                                         //
//-------------------------------------------------//
SoftwareSerial RFID(2,3); //RX and TX
bool fullCan = false;
bool allreadyScanned = false;
bool noBrandAllreadyScanned = false;
bool loggedIn = false;

int time = 0;
int i;
int pointsReward = 0;
char server[] = ("192.168.1.101");
String data;

//---------------------------------------------------//
//Define Pins                                       //
//-------------------------------------------------//
#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     15 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define fullLed 6
#define emptyLed 7
#define productBrand 9
#define productNoBrand 1

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
LiquidCrystal lcd(17,18,5,4,3,8);
EthernetClient client;

//Initialize Tones for Piezo Speaker
int brandProduct[] = {
  NOTE_B3,NOTE_B3, NOTE_B3, NOTE_C4};
int noBrandProduct[] = {
  NOTE_C4,NOTE_C4, NOTE_C4, NOTE_G2};

//Note Durations 4 = 4th / 8 = 8th etc.
int noteDurations[] = {
  8, 8, 8, 4};

//Mac Adress for our Arduino Ethernet Shield (to allow acces to the router) 
byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0F, 0x0C, 0xA8 };

// If you don't specify the IP address, DHCP is used(only in Arduino 1.0 or later).

byte ip[] = {
  192, 168, 1, 101}; 
int data1 = 0;
int ok = -1;

//RFID tags Hex numbers
int tag1[14] = {
  2,49,48,48,48,52,69,54,54,67,54,70,69,3};
int tag2[14] = {
  2,48,67,48,48,51,49,55,57,49,65,53,69 };
int userTag[14] = {
  2,48,67,48,48,51,49,55,57,49,65,53,69,3
};
int newtag[14] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  RFID.begin(9600);
  Serial.begin(9600); // Open serial on 9600 bauds!

  pinMode(fullLed, OUTPUT);  
  pinMode(emptyLed, OUTPUT);  
  pinMode(productBrand, OUTPUT);
  pinMode(productNoBrand, OUTPUT);

  lcd.begin(16, 1);
  lcd.setCursor(0,1);
  lcd.clear();

  data = "points=";

  delay(1000);
  if (!Ethernet.begin(mac))  // Connect using DHCP
    Ethernet.begin(mac, ip); // Try to connect using a Static IP address.
  delay(100);
  Serial.print(F("Trashcan Ip : "));  // Print out the IP address.
  for (int i = 0; i < 4; i++)
  {
    Serial.print(Ethernet.localIP()[i], DEC);
    Serial.print("."); 
  }
}

//---------------------------------------------------//
//function to calculate HEX decimals for rfid       //
//-------------------------------------------------//
boolean comparetag(int aa[14], int bb[14])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 14 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 14)
  {
    ff = true;
  }
  return ff;
}

void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (comparetag(newtag, tag1) == true)
  {
    ok++;   
  }
  if (comparetag(newtag, tag2) == true)
  {
    ok++;
  }
}

void readTags()
{
  ok = -1;
  if (RFID.available() > 0)
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.
    for (int z = 0 ; z < 14 ; z++) // read the rest of the tag
    {
      data1 = RFID.read();
      newtag[z] = data1;
    }
    RFID.flush(); // stops multiple reads
    checkmytags();
  }

  //User Logged in?

  // now do something based on tag type
  if (ok > 0 && allreadyScanned == false) // if we had a match
  {
    allreadyScanned = true;
    Serial.println("Van hier");
    lcd.clear();
    lcd.print("Goed product!");
    lcd.println("+ 10");
    playBrandMelody();
    ok = -1;
    pointsReward = 0 +  10;
    appendPoints();
  }
  else if (ok == 0 && noBrandAllreadyScanned == false) // if we didn't have a match
  {
    noBrandAllreadyScanned = true;
    Serial.println("Niet van hier");
    lcd.clear();
    lcd.print("Ander merk");
    playNoBrandMelody();
    ok = -1;
    pointsReward = 0 +  2;
    appendPoints();
  }
}


//---------------------------------------------------//
//Functions//                                       //
//-------------------------------------------------//

void appendPoints()  //Restful Webservice
{  
  if(client.connect(server, 80))
  {
    client.println("GET /TrashCash_app/ajax/addpoints.php?"+ data+ pointsReward + "HTTP/1.1");
    client.println("Host: 192.168.1.101");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-length");
    client.println("Connection: close"); 
  }

}


void playBrandMelody() // Play tune via Piezo Speaker
{
  for (int thisNote = 0; thisNote < (sizeof(noteDurations)/2); thisNote++)
  {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(16, brandProduct[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(16); // Stop Tone
  }
}

void playNoBrandMelody() // Play tune via Piezo Speaker
{
  for (int thisNote = 0; thisNote < (sizeof(noteDurations)/2); thisNote++)
  {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(16, noBrandProduct[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(16); // stop the tone playing:
  }
}



void loop() {
  lcd.noBlink();
  readTags();
  Serial.println(pointsReward); //Read the points in serial (debugging purpose only!)

  delay(500);            // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  int range = uS / US_ROUNDTRIP_CM;
  Serial.print(range); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  if(range < 11){
    //Check if there is some trash in front of the ultrasonic sensor and start counting. 
    time++;
    if(time == 10){
      digitalWrite(fullLed, HIGH); // turns LED off 
      fullCan = true;

      if (fullCan == true)
      {
        // Led Indicator for Trashcan
        digitalWrite(emptyLed, LOW); // turns LED off 
        Serial.println("Volle bak "); //With a servo the trashcan can be closed! (Arduino Mega needed cause of more digital pins!)  
      }     
    }     
    Serial.println(time);
  }  
  else{
    // Led Indicator for Trashcan
    digitalWrite(fullLed, LOW);
    delay(10);
    digitalWrite(emptyLed, HIGH); // turns LED off
    time = 0;  //Reset time when Ultrasonic Sensor won't measure below 10!
    Serial.println("Vuilnisbak kan nog voller"); 
  }
}



