#include <Adafruit_Fingerprint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
LiquidCrystal_I2C lcd(0x27, 21, 22);

void setup()
{
  // LCD
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  //  LCD
  lcd.setCursor(0, 0);
  lcd.print("Lock The Door");

  pinMode(14, OUTPUT);
  Serial.begin(57600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nการทดสอบการตรวจหานิ้วของ Adafruit");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("ตรวจพบเซ็นเซอร์!");
  } else {
    Serial.println("ตรวจไม่พบเซ็นเซอร์ :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("ข้อมูลภายในเซ็นเซอร์ "); Serial.print(finger.templateCount); Serial.println(" รูปแบบ");
  Serial.println("กำลังรอนิ้วมือ...");
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("ภาพลายนิ้วมือ");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("ไม่พบลายนิ้วมือ");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("พบข้อผิดพลาดของการเชื่อมต่อ");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("พบข้อผิดพลาดของภาพลายนิ้วมือ");
      return p;
    default:
      Serial.println("พบข้อผิดพลาดที่ไม่รู้จัก");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("แปลงรูปภาพ");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("รูปภาพไม่ชัดเจน");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("พบข้อผิดพลาดของการเชื่อมต่อ");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("ไม่พบคุณสมบัติลายนิ้วมือ");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("ไม่พบคุณสมบัติลายนิ้วมือ");
      return p;
    default:
      Serial.println("พบข้อผิดพลาดที่ไม่รู้จัก");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("พบลายนิ้วมือที่บันทึกไว้!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("พบข้อผิดพลาดของการเชื่อมต่อ");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("ลายนิ้วมือไม่ตรงกับข้อมูลใดๆ");
    return p;
  } else {
    Serial.println("พบข้อผิดพลาดที่ไม่รู้จัก");
    return p;
  }

  // found a match!
  Serial.print("พบลายนิ้วมือ ID #"); Serial.print(finger.fingerID);
  Serial.print(" ซึ่งมีความใกล้เคียงกัน "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("พบลายนิ้วมือ ID #"); Serial.print(finger.fingerID);
  Serial.print(" ซึ่งมีความใกล้เคียงกัน "); Serial.println(finger.confidence);
  if (finger.fingerID == 1) {
    digitalWrite(14, HIGH);
    Serial.println("ปลดล็อค 10 ");
    lcd.clear();
    lcd.setCursor(0, 0); // ไปที่ตัวอักษรที่ 0 แถวที่ 1
    lcd.print("Unlock The Door");
    delay(3000);
    digitalWrite(14, LOW);
    lcd.clear();
    lcd.setCursor(0, 0); // ไปที่ตัวอักษรที่ 7 แถวที่ 2
    lcd.print("Lock The Door");
  }

  return finger.fingerID;
}
