#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>

#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

float hum;  //Stores humidity value
float temp; //Stores temperature value

RTC_DS1307 RTC;
const int chipSelect = 10;  // Set the chip select pin for your SD card module


File dataFile;  // File object to handle the data file


void  setup()
{
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
   RTC.begin();

    if (! RTC.isrunning()) {
   Serial.println("RTC is NOT running!");
   // following line sets the RTC to the date & time this sketch was compiled
   RTC.adjust(DateTime(__DATE__, __TIME__));
 }

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");
}

void loop(){

   DateTime now;
   dataFile = SD.open("datab.txt", FILE_WRITE);

  if (dataFile) {
    // Write the sensor value to the file
    // fetch the time
  now = RTC.now();
  // log time
  
hum = dht.readHumidity();
temp= dht.readTemperature();

  dataFile.println(now.unixtime()); // seconds since 1/1/1970
  dataFile.print(now.year(), DEC);
  dataFile.print("/");
  dataFile.print(now.month(), DEC);
  dataFile.print("/");
  dataFile.print(now.day(), DEC);
  dataFile.print(" ");
  dataFile.print(now.hour(), DEC);
  dataFile.print(":");
  dataFile.print(now.minute(), DEC);
  dataFile.print(":");
  dataFile.print(now.second(), DEC);
  dataFile.print (" ");
    dataFile.print(temp);
     dataFile.print (",");
  dataFile.print(hum);
   dataFile.print (",--");
 


Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    dataFile.close();
    Serial.println("Data written to the file.");
}
   
  else {
    Serial.println("Error opening the file.");
  }
//delay (2000);
const unsigned long SECOND = 1000;
const unsigned long HOUR = 3600*SECOND;
delay(1*HOUR);

  }
