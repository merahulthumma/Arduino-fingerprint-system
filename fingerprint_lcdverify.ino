
// Fingerprint system by Rahul Thumma

#include <Adafruit_Fingerprint.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


SoftwareSerial mySerial(2, 3);
LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, Mates'!");
  lcd.setCursor(2,1);
  lcd.print("G'day");
  
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  lcd.clear();
      lcd.print("Fingerprint sensor enrollment");
      delay(2000);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.clear();
      lcd.print("Found fingerprint sensor");
      delay(2000);
  } else {
    Serial.println("Did not find fingerprint sensor :(");
     lcd.clear();
      lcd.print("Did not find fingerprint sensor :(");
      delay(2000);
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); 
  lcd.clear();
      lcd.print("Sensor contains");
      delay(2000);
      Serial.print(finger.templateCount);
      lcd.clear();
      lcd.print(finger.templateCount);
      delay(2000);
      Serial.println(" templates");
      lcd.clear();
      lcd.print("templates");
      delay(2000);
  Serial.println("Waiting for valid finger...");
  lcd.clear();
      lcd.print("Waiting for valid finger...");
      delay(2000);
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);            //don't need to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.clear();
      lcd.print("Image taken");
      delay(2000);
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      lcd.clear();
      lcd.print("No finger detected");
      delay(2000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Communication error");
      delay(2000);
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.clear();
      lcd.print("Imaging error");
      delay(2000);
      return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.clear();
      lcd.print("Image converted");
      delay(2000);
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.clear();
      lcd.print("Image too messy");
      delay(2000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Communication error");
      delay(2000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Could not find fingerprint features");
      delay(2000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Could not find fingerprint features");
      delay(2000);
      return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    lcd.clear();
      lcd.print("Found a print match!");
      delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.clear();
      lcd.print("Communication error");
      delay(2000);
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    lcd.clear();
      lcd.print("Did not find a match");
      delay(2000);
    return p;
  } else {
    Serial.println("Unknown error");
    lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  lcd.clear();
      lcd.print("Found ID #");
      lcd.print(finger.fingerID);
      delay(2000);
  Serial.print(" with % of "); 
  Serial.println(finger.confidence); 
  lcd.clear();
       lcd.print("with % of  ");
      lcd.print(finger.confidence);
      delay(2000);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

 

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_NOTFOUND)  {
   lcd.clear();
   Serial.print("Finger Not Found "); 
   lcd.print("Finger Not Found");
   delay(1000);
   lcd.clear();
   Serial.print("Try Later ");    
   lcd.print("Try Later");
   delay(2000);
  return -1;
  }

  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  
  lcd.clear();
      lcd.print("Found ID #");
      lcd.print(finger.fingerID);
      delay(2000);
  Serial.print(" with % of ");
  Serial.println(finger.confidence);
  lcd.clear();
      lcd.print("with % of ");
      lcd.print(finger.confidence);
      delay(2000);
  return finger.fingerID; 
} 
