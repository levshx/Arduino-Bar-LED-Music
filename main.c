#include <GyverWDT.h>
/*
  GyverWDT.h - применениe watchdog - сброс устройства при зависании
  Если не вызвать Watchdog.reset() вовремя - произойдет сброс
  Зависимость таймаутов от делителей см. в GyverWDT.h
*/

#include <DFPlayer_Mini_Mp3.h>
/*
  Библиотека плеера mp3-tf-16p
  По совместительству стала принадлежать компании DF-Robot 
  Можно запутаться в библиотеках
  Эта более старая
 */
 
#include <SoftwareSerial.h>
boolean oldStatusSensor = false;  

int sounds = 10;                   // Кол-во песен
int volume = 29;                   // Громкость

SoftwareSerial SerialMP3(7, 6);    // RX, TX

/*
  Герконовый датчик открытия двери ставица на A5/GND
  Резистор не нужен, используется аппаратный 10k
*/

void setup() {
  
  SerialMP3.begin (9600);
  mp3_set_serial (SerialMP3); 
  delay (100); 
  mp3_set_volume (volume);

  pinMode(A5, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);

  delay (2000);

  Watchdog.enable(RESET_MODE, WDT_PRESCALER_512); // Режим сторжевого сброса , таймаут ~4с
}

void loop() {

  // Герконовый датчик (открытия двери)
  boolean openSensor = digitalRead(A5);

  if (openSensor) {
    // Открыта дверь
    if (!oldStatusSensor) {
      mp3_play(random(1,sounds+1));      
    }    
    digitalWrite(13,1);
    digitalWrite(2,1);
    delay(500);
  }
  else
  {
    // Закрыта дверь
    if (oldStatusSensor) {
      mp3_stop();      
    }
    digitalWrite(13,0);
    digitalWrite(2,0);
    delay(500);
  }

  oldStatusSensor = openSensor;


  Watchdog.reset(); // Переодический сброс watchdog, означающий, что устройство не зависло
}
