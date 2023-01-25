unsigned long time = 0;
unsigned long time2 = 0;
int engineSpeed = 0;
bool b;
const int buttonPin = 17;			// Номер пина для определения количества оборотов мотора в минуту
int IgnitionState = 0;				// Сохранение статуса пина buttonPin
float voltage = 0.0;
float temp=0.0;						// Переменная для преобразования напряжения
float r1=10000.0; //сопротивление резистора r1
float r2=3330.0; // сопротивление резистора r2

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(13, OUTPUT); // 13 пин – светодиод, объявляется как выход для тестов работы
  pinMode(buttonPin, INPUT); // подкллючение пина для определение оборотов
}

void loop(){
/*  IgnitionState = digitalRead(buttonPin);
  
  // Определение количества оборотов мотора в минуту
  if ((IgnitionState == HIGH) and (b == false)) {
    if (engineSpeed != 0){
        engineSpeed = round(((60000 / (millis() - time2)) + engineSpeed) / 2);
    } else {
      engineSpeed = round(60000 / (millis() - time2));
    }
    engineSpeed = abs(engineSpeed);
    time2 = millis();
    b = true;
  }
  if (IgnitionState == LOW) {
    b = false;
  }
*/

  if(analogRead(buttonPin)>400){                             //  если показания датчика линии больше 400 (тёмное поле)
    if(time2<millis()){                                  //  если нет переполнения millis(), то ...
      engineSpeed = 60000/(millis()-time2);             //  записываем данные по оборотам
    }
    time2 = millis();                                  //  присваиваем переменной time2 текущее значение millis();
    while(analogRead(buttonPin)>350){                        //  ждём пока датчик линии не выйдет из тёмного поля
      if((millis()-time2)>1000){
		  engineSpeed = 0.0;
	  }  //  если датчик находится на тёмном  поле дольше 6 секунд, то выводим 0.0
    }
  }   if((millis()-time2)>1000){
		  engineSpeed = 0.0;
	  }	  //  если датчик находится на светлом поле дольше 6 секунд, то выводим 0.0
  
  // Определение вольтажа
  temp = (analogRead(A2) * 5.0) / 1024.0; // формула для конвертирования значения напряжения
  voltage = temp / (r2/(r1+r2)); // определение напряжения
  if (voltage < 0.1)
  {
    voltage=0.0;
  }

  // Передача значения
  if ((millis() - time > 1000)){
      time = millis();
      
      Serial.println(String(abs(round(engineSpeed / 2))) + ";" + String("0.0") + ";" + String(voltage) + ";");  // Передача данных по serial в виде "обороты;температура;вольтаж;"
  }
}
