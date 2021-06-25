// Fingerprint system by Rahul Thumma

#include <Adafruit_Fingerprint.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


SoftwareSerial mySerial(2, 3);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

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
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");
  lcd.clear();
      lcd.print("Fingerprint sensor enrollment");
      delay(2000);

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
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
}

uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()                     // run over and over again
{

  Serial.println("Ready to enroll a fingerprint!");
  lcd.clear();
      lcd.print("Ready to enroll a fingerprint!");
      delay(2000);
  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
  lcd.clear();
      lcd.print("Please type in the ID #");
      delay(2000);
  id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);
  lcd.clear();
      lcd.print("Please type in the ID #");
       lcd.print(id);
      delay(2000);
  
  while (!  getFingerprintEnroll() );
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); 

  Serial.println(id);
  lcd.clear();
      lcd.print("Waiting for valid finger to enroll as #");
      lcd.print(id);
      delay(2000);
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
       lcd.clear();
      lcd.print("Image Taken");
      delay(2000);
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
       lcd.clear();
      lcd.print("Communication error");
      delay(2000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
       lcd.clear();
      lcd.print("Imaging error");
      delay(2000);
      break;
    default:
      Serial.println("Unknown error");
       lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted"); lcd.clear();
      lcd.print("Image Converted");
      delay(2000);
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
       lcd.clear();
      lcd.print("Image too Messy");
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
  
  Serial.println("Remove finger");
   lcd.clear();
      lcd.print("Remove finger");
      delay(2000);
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  lcd.clear();
      lcd.print(" ID ");
      lcd.print(id);
     
      delay(2000);
  delay(2000);
  p = -1;
  Serial.println("Place same finger again");
  lcd.clear();
      lcd.print("Place same finger again");
      delay(2000);
  delay(2000);
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      lcd.clear();
      lcd.print("Image taken");
      delay(2000);
  delay(2000);
  
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Communication error");
      delay(2000);
  delay(2000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      lcd.clear();
      lcd.print("Imaging error");
      delay(2000);
  delay(2000);
      break;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
  delay(2000);
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
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
  Serial.print("Creating model for #");  Serial.println(id);
  lcd.clear();
  lcd.print("Creating for #");
      lcd.print(id);
      delay(2000);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
    lcd.clear();
      lcd.print("Prints matched!");
      delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.clear();
      lcd.print("Communication error");
      delay(2000);
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    lcd.clear();
      lcd.print("Fingerprints did not match");
      delay(2000);
    return p;
  } else {
    Serial.println("Unknown error");
    lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  lcd.clear();
      lcd.print("ID ");
       lcd.print(id);
      delay(2000);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
      lcd.print("Stored");
      delay(2000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.clear();
      lcd.print("Communication error");
      delay(2000);
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    lcd.clear();
      lcd.print("Could not store in that location");
      delay(2000);
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    lcd.clear();
      lcd.print("Error writing to flash");
      delay(2000);
    return p;
  } else {
    Serial.println("Unknown error");
    lcd.clear();
      lcd.print("Unknown error");
      delay(2000);
    return p;
  }   
}
