# Arduino-Bar-LED-Music

Структурная схема, отличается расположением датчика открытия двери

Питание (максимальные амперы/мощность) подбирать исходя от потребления светодиодной ленты, контроллера (12В/~150mA) и модуля mp3 (5В/~1А)

Использование старажевого таймера `GyverWDT` может быть осуществимо только на загрузчике `optiboot`.
Не работает на (`OldBootloader`). Можно испортить Arduino и вызвать бесконечную перезагрузку.

![Иллюстрация к проекту](https://sun9-80.userapi.com/impg/3vggisbSHnAF85Tl3Br_mDVv7E08xsAy3yab6g/K_JSEgGCaLw.jpg?size=1280x640&quality=96&sign=e3ab287664105f5c29f94ae00e45b31a&type=album)

https://alexgyver.ru/gyverwdt/
Для проверки GyverWDT:
``` c
#include "GyverWDT.h"
/*
  Пример тестирующий поддержку всех функций watchdog на вышем устройстве
  > После 10 секунд отсчета программа стартует заного -> поддерживаются все функции
  > После таймаута устройство зависает, светодиод на D13 начинает мигать -> подерживается только INTERRUPT_MODE
  В случае bootloop у вас будет 10 секунд на перепрошивку устройства после подачи питания
  Для добавления поддержки всего функционала watchdog загрузите optiboot или откажитесь от загрузчика
*/
void setup() {
  Serial.begin(9600);
  Serial.println("Program started , wait 10 seconds");
  delay(10000);                                             // 10 секунд на перепрошивку в случае bootloop
  Watchdog.enable(RESET_MODE, WDT_PRESCALER_1024);          // Режим сторжевого сброса , таймаут ~8с
  Serial.println("watchdog enabled");
  while (1) {                                               // Бесконечный цикл , эмуляция "зависания"
    if (!(millis() % 1000)) {                               // Каждую секунду
      Serial.println((uint16_t)((millis() / 1000) - 10));   // Вывести время после включения watchdog в секундах
      delay(10);
    }
  }
}
void loop() {}
```


