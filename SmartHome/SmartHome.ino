 // CREATED BY MICE EFF https://youtu.be/5CnvRkqEsGU          
            #include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
            #include <SPI.h>  // https://github.com/PaulStoffregen/SPI
            #include <ESP8266WiFi.h> // ля, забыл сказать что пример Standalone появился, надо установить библиотеку Blynk https://github.com/blynkkk/blynk-library/releases/tag/v0.6.1
            #include <BlynkSimpleEsp8266.h>
            #include <SimpleTimer.h> //https://github.com/jfturcot/SimpleTimer
            #include <DHT.h> //https://github.com/adafruit/DHT-sensor-library
            #include <NewPing.h> // https://github.com/e-Gizmo/NewPing
#define f A0 // аналоговый вход
#define rele 4 // пин реле, мосфета,светодиода
#define BLYNK_PRINT Serial           
#define PIN_TRIG 12 // пин триг дальномера
#define PIN_ECHO 13// пин эхо дальномера
#define MAX_DISTANCE 200// макс расстояние измеряемое дальномером
char auth[] = "токен";// название токена
char ssid[] = "wi-fi";  //название wi-fi
char pass[] = "пароль";  //пароль от wi-fi
#define DHTPIN 2       // пин dh11
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321 
//#define DHTTYPE DHT21   // DHT 21, AM2301
#define PIN 14 // пин адресной ленты
#define NUMPIXELS 60 // кол-во светодиодов в ленте
#define BLYNK_PRINT Serial
   Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
   NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);
   DHT dht(DHTPIN, DHTTYPE);
 SimpleTimer timer;

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
     if (isnan(h) || isnan(t)) {
         Serial.println("Failed to read from DHT sensor!");
         }
               Blynk.virtualWrite(V5, h);  //на виртуальный пин 5 выводятся показания влажности 
               Blynk.virtualWrite(V6, t);  // на виртуальный пин 6 выводится показаниея температуры 
          
}



void setup(){
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  pinMode(f,OUTPUT);
    pinMode(PIN_TRIG, OUTPUT); 
    pinMode(PIN_ECHO, INPUT);
     
     pixels.begin();
       pinMode(rele, OUTPUT); 
       digitalWrite(rele, HIGH);
}
BLYNK_WRITE(V11)
{
 
int R = param[0].asInt();
int G = param[1].asInt();
int B = param[2].asInt();
Serial.println(R);
Serial.println(G);
Serial.println(B);
for(int i=0;i<NUMPIXELS;i++){
 
pixels.setPixelColor(i, pixels.Color(R,G,B));
 
pixels.show();
}
}

void loop(){
  
  Blynk.run(); 
  timer.run(); 

  
    
     int val =analogRead(f);
     Blynk.virtualWrite(V7, val);
     
     unsigned int distance = sonar.ping_cm();
     Blynk.virtualWrite(V8, distance);















     
}
