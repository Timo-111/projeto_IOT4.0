#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10    
#define RST_PIN 9    
#define LED_PIN 5    
#define SERVO_PIN 2  

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servoMotor;

// UID autorizado (FF 1F C0 C4)
byte authorizedUID[] = {0xFF, 0x1F, 0xC0, 0xC4};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  servoMotor.attach(SERVO_PIN);
  servoMotor.write(0);

  Serial.println("Sistema iniciado. Aproxime um cartão...");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID detectado: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) Serial.print(" ");
  }
  Serial.println();

  // verificar
  if (checkUID(rfid.uid.uidByte)) {
    Serial.println("Cartão autorizado!");
    digitalWrite(LED_PIN, HIGH);  
    servoMotor.write(90);         
    delay(5000);                  // delay da porta 1000=1
    servoMotor.write(0);         
    digitalWrite(LED_PIN, LOW);   
  } else {
    Serial.println("Cartão não autorizado.");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// comparar UID lido com UID autorizado
bool checkUID(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID[i]) {
      return false;
    }
  }
  return true;
}