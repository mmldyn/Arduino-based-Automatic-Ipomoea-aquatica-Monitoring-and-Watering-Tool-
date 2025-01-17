#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <Servo.h>

#define TRIG_PIN 6
#define ECHO_PIN 5
#define DHT_PIN 3
#define DHTTYPE DHT11 
#define LDR_PIN 2 
#define SOIL_PIN A2
#define BUZZER_PIN 7
#define GREEN_PIN 9
#define YELLOW_PIN 10
#define RED_PIN 11

#define DHT_REFRESH_INTERVAL 43200000 
#define LDR_THRESHOLD 500 

#define LCD_ADDRESS 0x27  
#define LCD_COLUMNS 16
#define LCD_ROWS 2

#define wet 210
#define dry 510

#define RELAY_PIN 12

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHTTYPE); 
Servo servo;
unsigned long previousServoMoveTime = 0;
unsigned long previousKondisiTime = 0;
const unsigned long kondisiInterval = 60000;

float readTemperature();
float calculatePlantHeight();
void kondisi();
float HitungTita();
float readDistance();
void paneldua();
void animasiteks();

void setup() {
  Serial.begin(9600);
  Wire.begin(); 
  lcd.init();
  lcd.backlight();

  lcd.clear();
  animasiteks();
  delay(500);

  pinMode(SOIL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  float temperature = readTemperature();
  if (isnan(temperature)) {
    temperature = 0.0;
  } else {
    temperature += 13;
  }
  
  float Tita = HitungTita(); 
  float Waktu = analogRead(LDR_PIN);

  Serial.println("=========AGRISHIELD=========");
  Serial.print("Suhu              : ");
  Serial.print(temperature);
  Serial.println("°C");

  Serial.print("Tinggi Tanaman    : ");
  if (Tita < 0) {
    Serial.println("-");
  } else {
    Serial.print(Tita);
    Serial.println(" cm");
  }

  Serial.print("Waktu             : ");
  Serial.println(Waktu);
  Serial.print("Kondisi           : ");

  if (Waktu >= 555) {
    Serial.println("M");
  } else {
    Serial.println("S");
  }

  int value = analogRead(SOIL_PIN);
  Serial.print("Kelembapan Tanah  : ");
  Serial.println(value);

  int pre = map(value, wet, dry, 100, 0);
  Serial.print("Kondisi Tanah     : ");
  
  if (value <= 500) {
    Serial.println("Basah");
  } else {
    Serial.println("Kering");
  }

  Serial.println("============================");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(temperature);
  lcd.write(223); 
  lcd.print("C     "); 
  lcd.setCursor(0, 1);
  lcd.print("Tita: ");

  if (Tita < 0) {
    lcd.print("-");
  } else {
    lcd.print(Tita);
    lcd.print(" cm");
  }

  if (Tita > 48) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(RED_PIN, HIGH);
    noTone(BUZZER_PIN);
    digitalWrite(RED_PIN, LOW);
    delay(500);  
  }

  if (temperature > 30 && temperature < 35) {
    for (int x = 0; x < 10; x++) {
      tone(BUZZER_PIN, 1000);
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      noTone(BUZZER_PIN);           
      digitalWrite(YELLOW_PIN, LOW);
      delay(500);                   
    }
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    delay (500);
  } 

  if (temperature > 35) { 
    for (int x = 0; x < 10; x++) {
      tone(BUZZER_PIN, 1000);
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      noTone(BUZZER_PIN);           
      digitalWrite(RED_PIN, LOW);
      delay(500);    
    }
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousKondisiTime >= kondisiInterval) {
    previousKondisiTime = currentMillis;
    kondisi();
    paneldua();  
  }

  delay(200); 

  if (value < 500) {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(RELAY_PIN, HIGH); 
    }
    
  if (value > 500) {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(RELAY_PIN, HIGH); 
    } 
}

float readTemperature() {
  delay(50); 
  float temperature_C = dht.readTemperature(); 
  return temperature_C;
}

float HitungTita() {
  float distance_cm = readDistance();
  float tinggi_ruangan = 38.5; 
  float tinggi_benda = tinggi_ruangan - distance_cm;
  return tinggi_benda;
}

float readDistance() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  pinMode(ECHO_PIN, INPUT); 
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  
  float distance_cm = duration * 0.034 / 2; 
  return distance_cm;
}

void kondisi() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("KONDISI");
  lcd.setCursor(4, 1);
  lcd.print("TANAMAN");

  delay(2000); 
}

void paneldua() {
  float Waktu = analogRead(LDR_PIN);
  int value = analogRead(SOIL_PIN);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waktu: ");

  if (Waktu > 555) {
    lcd.setCursor(6, 0);
    lcd.print(" Malam");
  } else {
    lcd.setCursor(6, 0);
    lcd.print(" Siang");
  }

  lcd.setCursor(0, 1);
  lcd.print("Ketan: ");
  int pre = map(value, wet, dry, 100, 0);
  lcd.setCursor(6, 1);

  if (value <= 500) {
    lcd.println("Basah");
  } else {
    lcd.println("Kering");
  }

  delay(15000);  
}

void animasiteks() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 7000);
    digitalWrite(RED_PIN, HIGH);
    delay(200);
    noTone(BUZZER_PIN);
    digitalWrite(RED_PIN, LOW);
    delay(200);

    tone(BUZZER_PIN, 5000);
    digitalWrite(GREEN_PIN, HIGH);
    delay(200);
    noTone(BUZZER_PIN);
    digitalWrite(GREEN_PIN, LOW);
    delay(200);

    tone(BUZZER_PIN, 4000);
    digitalWrite(YELLOW_PIN, HIGH);
    delay(200);
    noTone(BUZZER_PIN);
    digitalWrite(YELLOW_PIN, LOW);
    delay(200);
  }

  String agrishield = "AGRISHIELD";
  for (int i = 0; i <= agrishield.length(); i++) {
    lcd.setCursor(8 - i, 0);
    lcd.print(agrishield.substring(0, i));
    delay(200);
    tone(BUZZER_PIN, 2000);
    digitalWrite(RED_PIN, HIGH);
    delay(100); 
    noTone(BUZZER_PIN);
    digitalWrite(RED_PIN, LOW);
  }

  String starting = "GNITRATS";
  for (int i = 0; i <= starting.length(); i++) {
    lcd.setCursor(15 - starting.length() + i, 1);
    lcd.print(starting.substring(starting.length() - i));
    delay(200);
    tone(BUZZER_PIN, 2000);
    digitalWrite(GREEN_PIN, HIGH);
    delay(100); 
    noTone(BUZZER_PIN);
    digitalWrite(GREEN_PIN, LOW);
  }
}

//GROUP TUJUH - ARSITEKTUR DAN ORGANISASI KOMPUTERx
//ADI - AURORA - HISMA - SAFITRI - ZIDAN

