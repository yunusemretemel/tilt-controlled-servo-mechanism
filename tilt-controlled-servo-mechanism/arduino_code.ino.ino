#include <Servo.h>

Servo takipServosu;

// Pin tanımlamaları
const int solSensorPin = 2;
const int sagSensorPin = 3;
const int servoPin = 9;

void setup() {
  // Servo motoru 9. pine bağlıyoruz
  takipServosu.attach(servoPin);
  
  // Sensör pinlerini dahili pull-up ile giriş olarak ayarlıyoruz
  pinMode(solSensorPin, INPUT_PULLUP);
  pinMode(sagSensorPin, INPUT_PULLUP);
  
  // Başlangıçta servoyu merkez (90 derece) konumuna al
  takipServosu.write(90);
}

void loop() {
  // Pull-up mantığında sensör tetiklendiğinde (iletken olduğunda) LOW okunur
  bool solYatik = (digitalRead(solSensorPin) == LOW);
  bool sagYatik = (digitalRead(sagSensorPin) == LOW);

  // Sola yatırılma durumu
  if (solYatik && !sagYatik) {
    takipServosu.write(45); // Servoyu sola çevir (Açıyı mekaniğinize göre ayarlayabilirsiniz)
  }
  // Sağa yatırılma durumu
  else if (sagYatik && !solYatik) {
    takipServosu.write(135); // Servoyu sağa çevir
  }
  // Platform düz veya her iki sensör de bir şekilde tetiklenmiş (hatalı durum)
  else {
    takipServosu.write(90);  // Servoyu merkeze al
  }

  // Mekanik bilye sıçramalarını (contact bounce) ve servonun titremesini 
  // yazılımsal olarak filtrelemek için kısa bir bekleme (debouncing)
  delay(100); 
}