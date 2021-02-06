#include <Wire.h>

int lm35Pin = A15;
float lm35Deger;
int sicaklik;

void setup() {
  pinMode(lm35Pin, INPUT);
  Wire.begin();                   // I2C Haberleşme başlatıldı
  Serial.begin(9600);

}

void loop() {
  lm35Deger=analogRead(lm35Pin);  // Değer okuma
  
  // Sıcaklığa dönüşüm işlemi
  lm35Deger=(lm35Deger/1023)*5000;
  sicaklik=lm35Deger/10;

  // Sıcaklık değerinin gönderir
  Wire.beginTransmission(1);
  Wire.write(sicaklik);
  Wire.endTransmission();
  
  delay(1000);
}
