#include <Wire.h>
#include <LiquidCrystal.h>

//lcd ekran
const int rs= 13, en= 12, d4= 11, d5= 10, d6= 9, d7= 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sicaklik;
int satir = 0;                    // İsim başlangıçta ilk satırda
int boslukEkle = 1;               // Başlangıçta string değere 16 boşluk ekler
String yazi;                      // Kayan yazı

void setup() {
  Wire.begin(1);                  // Haberleşme 1 adresinden başlatıldı
  Wire.onRequest(istekVeri);      // Veri istendiğinde
  Wire.onReceive(gelenVeri);      // Veri geldiğinde
  Serial.begin(9600);

  //lcd ayarları
  lcd.begin(16,2);
  lcd.setCursor(0,0);

  // 2. pine basılınca butonKesme fonksiyonu çalışır
  attachInterrupt(digitalPinToInterrupt(2), butonKesme, RISING);
}

// Kesme fonksiyonu
void butonKesme(){
  if(satir == 0)      satir= 1;
  else if(satir == 1) satir= 0;
}

// İsmin soldan sağa kaymasını sağlayan fonksiyon
void kayanYazi(String isim){
  
  // Kayacak yazıyı hazırlama
  if(boslukEkle == 1){
    yazi= String("                "+isim);
    boslukEkle=0;
  }
  else{  
    // Yazı yazdırılır
    yazi.remove(0,1);
    lcd.setCursor(0,satir);
    lcd.print(yazi);
    
    // Yazı bittiğinde sıfırlanması için değeri 1 yapar
    if(yazi.length() == 1) boslukEkle=1;
  }
}

// Sıcaklık değerlerini yazdıran fonksiyon
void sicaklikYazdir(){
  // Sıcaklık değerinin bulunacağı satır 
  int sicaklikSatir;
  if(satir == 0) sicaklikSatir= 1;
  else sicaklikSatir=0;

  // Sıcaklık değer ve durumu yazdırma
  lcd.setCursor(0, sicaklikSatir);
  if(sicaklik > 30) lcd.print("  " + String(sicaklik) + " COK SICAK");
  else if(sicaklik >= 25 && sicaklik <= 30) lcd.print("    " + String(sicaklik) + " SICAK");
  else if(sicaklik < 25) lcd.print("   " + String(sicaklik) + " NORMAL");
}

void loop() {
  kayanYazi("ABDULLAH TUNCER");
  sicaklikYazdir();
  delay(200);
  lcd.clear();
}

// Masterdan gelen veriler
void gelenVeri(int veri){
  while(Wire.available()){
    sicaklik= Wire.read();      // Gelen değeri atama
  }
}


void istekVeri(int veri){
}
