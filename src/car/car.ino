#include <SPI.h>  // Подключаем библиотеку для работы с SPI-интерфейсом
#include <nRF24L01.h> // Подключаем файл конфигурации из библиотеки RF24
#include <RF24.h> // Подключаем библиотеку для работа для работы с модулем NRF24L01
#include <microLED.h>

#define PIN_CE  2  // Номер пина Arduino, к которому подключен вывод CE радиомодуля
#define PIN_CSN 3 // Номер пина Arduino, к которому подключен вывод CSN радиомодуля
#define DIRM1 4 // Направление M1
#define  SPEEDM1 5
#define DIRM2 7
#define SPEEDM2 6
#define MUX 1
#define HIGH_LEVEL_LEFT 512
#define LOW_LEVEL_LEFT 465
#define HIGH_LEVEL_RIGHT 550
#define LOW_LEVEL_RIGHT 500
#define LED 10
#define NUMLEDS 5     // кол-во светодиодов

RF24 radio(PIN_CE, PIN_CSN); // Создаём объект radio с указанием выводов CE и CSN

microLED <NUMLEDS, LED, -1, LED_WS2813, ORDER_GRB> leds;

int potValue[3]; // Создаём массив для приёма значений потенциометра

void setup() {
  pinMode(DIRM1, OUTPUT);
  pinMode(DIRM2, OUTPUT);
  pinMode(SPEEDM1, OUTPUT);
  pinMode(SPEEDM2, OUTPUT);
  radio.begin();  // Инициализация модуля NRF24L01
  radio.setChannel(44); // Обмен данными будет вестись на пятом канале (2,405 ГГц)
  radio.setDataRate (RF24_1MBPS); // Скорость обмена данными 1 Мбит/сек
  radio.setPALevel(RF24_PA_HIGH); // Выбираем высокую мощность передатчика (-6dBm)
  radio.openReadingPipe(1, 0x787); // Открываем трубу ID передатчика
  radio.startListening(); // Начинаем прослушивать открываемую труб
  leds.setBrightness(255);  // яркость
  Serial.begin(9600);
}

void loop() {
  static volatile unsigned long millis_off_prev = 0;
  if(radio.available()){
    millis_off_prev = millis();
    leds.set (0, mRGB(255, 255, 255));
    leds.set (NUMLEDS-1, mRGB(255, 255, 255));
    radio.read(potValue, 6);
    Serial.print(potValue[0]);
    Serial.print("\t");
    Serial.print(potValue[1]);
    Serial.print("\t");
    Serial.print(potValue[2]);
    Serial.print("\n");
    if (potValue[2]) {
      for (byte i = 1; i < NUMLEDS - 1; i++) {
        leds.set (i, mRGB(255, 200, 0));
      }
    }
    else {
      for (byte i = 1; i < NUMLEDS - 1; i++) {
        leds.set (i, mRGB(0, 0, 0));
      }
    }
    // Если в буфер приёмника поступили данные
    if (((potValue[0] < LOW_LEVEL_LEFT) | (potValue[0] > HIGH_LEVEL_LEFT))){
      if (potValue[0] < LOW_LEVEL_LEFT){
        digitalWrite(DIRM1, HIGH);
        analogWrite(SPEEDM1, (LOW_LEVEL_LEFT - potValue[0])/2);
      }
       else{
            digitalWrite(DIRM1, LOW);
         analogWrite(SPEEDM1, (potValue[0] - HIGH_LEVEL_LEFT)/2);
      }
    }
    else{
      analogWrite(SPEEDM1,0);
    }
    if (((potValue[1] < LOW_LEVEL_RIGHT) | (potValue[1] > HIGH_LEVEL_RIGHT))){
      if (potValue[1] < 500){
        digitalWrite(DIRM2, HIGH);
       analogWrite(SPEEDM2, (LOW_LEVEL_RIGHT - potValue[1])/2);
      }
      else{ 
        digitalWrite(DIRM2, LOW);
        analogWrite(SPEEDM2, (potValue[1] - HIGH_LEVEL_RIGHT)/2);
      }
    }
    else{
      analogWrite(SPEEDM2,0);
    }
  }
  else {
    Serial.println ("radio not avail");
    if (millis () - millis_off_prev > 1000) {
      for (byte i = 0; i < NUMLEDS; i++) {
        leds.set (i, mRGB(0, 0, 0));
      }
      millis_off_prev = millis();
    }
  }
  static volatile unsigned long millis_prev = 0;
  if (millis () - millis_prev > 1) { // if 1ms passed
      leds.show();
      millis_prev = millis();
    }
}
