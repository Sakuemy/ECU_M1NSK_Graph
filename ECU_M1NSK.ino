unsigned long time = 0;
unsigned long time2 = 0;
int engineSpeed = 0;
bool b;
const int buttonPin = 5;			// Номер пина для определения количества оборотов мотора в минуту
int IgnitionState = 0;				// Сохранение статуса пина buttonPin
float voltage = 0.0;
float temp=0.0;						// Переменная для преобразования напряжения

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(13, OUTPUT); // 13 пин – светодиод, объявляется как выход для тестов работы
  pinMode(buttonPin, INPUT); // подкллючение пина для определение оборотов
  float r1=100000.0; //сопротивление резистора r1
  float r2=10000.0; // сопротивление резистора r2
}

void loop(){
  IgnitionState = digitalRead(buttonPin);
  
  // Определение количества оборотов мотора в минуту
  if ((IgnitionState == HIGH) and (b == false)) {
    if (engineSpeed != 0){
        engineSpeed = round(((60000 / (millis() - time2)) + engineSpeed) / 2);
    } else {
      engineSpeed = round(60000 / (millis() - time2));
    }
    time2 = millis();
    b = true;
  }
  if (IgnitionState == LOW) {
    b = false;
  }
  
  // Определение вольтажа
  temp = (analogRead(A3) * 5.0) / 1024.0; // формула для конвертирования значения напряжения
  voltage = temp / (r2/(r1+r2)); // определение напряжения
  if (voltage < 0.1)
  {
    voltage=0.0;
  }

  // Передача значения
  if ((millis() - time > 1000)){
      time = millis();
      Serial.println(String(engineSpeed) + ";" + String(analogRead(A4)) + ";" + String(voltage) + ";");  // Передача данных по serial в виде "обороты;температура;вольтаж;"
      engineSpeed = 0;
  }
}
