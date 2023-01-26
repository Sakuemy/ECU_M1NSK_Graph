unsigned long time = 0;
unsigned long time2 = 0;
int engineSpeed = 0;
const int buttonPin = 17;				// Номер пина для определения количества оборотов мотора в минуту
int IgnitionState = 0;					// Сохранение статуса пина buttonPin
float voltage = 0.0;
float r1 = 10000.0;						//сопротивление резистора r1
float r2 = 3330.0;						// сопротивление резистора r2
float OkrugEngineSpeed = 0.0;

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(13, OUTPUT);					// 13 пин – светодиод, объявляется как выход для тестов работы
  pinMode(buttonPin, INPUT);			// подкллючение пина для определение оборотов
}

void main(){
	// Передача значения
	if ((millis() - time > 1000)){
		time = millis();
		voltage = ((analogRead(A2) * 5.0) / 1024.0) / (r2/(r1+r2));		// Определение вольтажа
		if (voltage < 0.1){
			voltage=0.0;
		}
		Serial.println(String(abs(round(OkrugEngineSpeed * 2))) + ";" + String("0.0") + ";" + String(voltage) + ";");	// Передача данных по serial в виде "обороты;температура;вольтаж;"
		OkrugEngineSpeed = 0.0;
	} else {
		if (EngineSpeed > 0){
			OkrugEngineSpeed = (OkrugEngineSpeed + EngineSpeed) / 2;		// Окуругление оборотов двигателя
		}
	}
}

void loop(){
	if(analogRead(buttonPin)>800){								//  если показания датчика линии больше 400 (тёмное поле)
		if(time2<millis()){										//  если нет переполнения millis(), то ...
			engineSpeed = 60000/(millis()-time2);				//  записываем данные по оборотам
		}
		time2 = millis();										//  присваиваем переменной time2 текущее значение millis();
		while(analogRead(buttonPin)>600){						//  ждём пока датчик линии не выйдет из тёмного поля
			if((millis()-time2)>400){
				engineSpeed = 0.0;								//  если датчик находится на тёмном  поле дольше 0.4 секунды, то выводим 0.0
			}
			main();
		}
	}
	if((millis()-time2)>400){
		engineSpeed = 0.0;										//  если датчик находится на светлом поле дольше 0.4 секунды, то выводим 0.0
		main();
	}
}
