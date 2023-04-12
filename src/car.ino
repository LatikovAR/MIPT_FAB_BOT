#include <SPI.h>  // Подключаем библиотеку для работы с SPI-интерфейсом
#include <nRF24L01.h> // Подключаем файл конфигурации из библиотеки RF24
#include <RF24.h> // Подключаем библиотеку для работа для работы с модулем NRF24L01
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
RF24 radio(PIN_CE, PIN_CSN); // Создаём объект radio с указанием выводов CE и CSN

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
  Serial.begin(9600);
}

void loop() {
  if(radio.available()){
  radio.read(potValue, 12);
  Serial.print(potValue[0]);
  Serial.print("\t");
  Serial.print(potValue[1]);
  Serial.print("\t");
  Serial.print(potValue[2]);
  Serial.print("\n");
  if (potValue[2])
      digitalWrite(LED, 1);
  else 
      digitalWrite(LED, 0);
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
}
