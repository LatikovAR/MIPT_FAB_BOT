#include <SPI.h>  // Подключаем библиотеку для работы с SPI-интерфейсом
 #include <nRF24L01.h> // Подключаем файл конфигурации из библиотеки RF24
#include <RF24.h> // Подключаем библиотеку для работа для работы с модулем NRF24L01
#define PIN_CE  2  // Номер пина Arduino, к которому подключен вывод CE радиомодуля
#define PIN_CSN 3 // Номер пина Arduino, к которому подключен вывод CSN радиомодуля
#define LeftStick  A5
#define RightStick A4
#define RightButton 6
RF24 radio(PIN_CE, PIN_CSN); // Создаём объект radio с указанием выводов CE и CSN

int pultValues[3]; // Создаём массив для передачи значений потенциометра

void setup() {
  radio.begin();  // Инициализация модуля NRF24L01
  radio.setChannel(44); // Обмен данными будет вестись на пятом канале (2,405 ГГц)
  radio.setDataRate (RF24_1MBPS); // Скорость обмена данными 1 Мбит/сек
  radio.setPALevel(RF24_PA_HIGH); // Выбираем высокую мощность передатчика (-6dBm)
  radio.openWritingPipe(0x787); 
  Serial.begin(9600);
}

void loop() {
  pultValues[0] = analogRead(LeftStick);//Считываем показания левого стика
  pultValues[1] = analogRead(RightStick);//Считываем показания правого стика
  pultValues[2] = digitalRead(6); //Считываем показания правой кнопки 
  Serial.print(pultValues[0]);  
  Serial.print("\t");
  Serial.print(pultValues[1]);
  Serial.print("\t"); 
  Serial.print(pultValues[2]);
  Serial.print("\n");
  radio.write(pultValues, 12); // Отправляем считанные показания по радиоканалу
}
