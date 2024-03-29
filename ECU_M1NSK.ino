 unsigned long time = 0;
unsigned long time2 = 0;
int engineSpeed = 0;
const int buttonPin = 17;				// Номер пина для определения количества оборотов мотора в минуту
int IgnitionState = 0;					// Сохранение статуса пина buttonPin
float voltage = 0.0;
float r1 = 10000;						//сопротивление резистора r1
float r2 = 3330;						// сопротивление резистора r2
float OkrugEngineSpeed = 0.0;
float OkrugVoltage = 0.0;
float tmp = 0;

void setup(){
//  analogReference(DEFAULT);
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(13, OUTPUT);					// 13 пин – светодиод, объявляется как выход для тестов работы
  pinMode(buttonPin, INPUT);			// подкллючение пина для определение оборотов
}

int main0(){
	// Передача значения
	if ((millis() - time > 1000)){
		time = millis();
		Serial.println(String(abs(round(OkrugEngineSpeed * 2))) + ";" + String("0.0") + ";" + String(OkrugVoltage) + ";");	// Передача данных по serial в виде "обороты;температура;вольтаж;"
		//Serial.println(analogRead(A2));
		OkrugEngineSpeed = 0.0;
    OkrugVoltage = 0.0;
	} else {
    tmp = (analogRead(A1) * 5) / 1024.0;
		voltage = tmp / (r2/(r1+r2));		// Определение вольтажа
		if (voltage < 0.1){
			voltage=0.0;
		}
		if (voltage > 0){
			if (OkrugVoltage > 0){
				OkrugVoltage = (OkrugVoltage + voltage) / 2;		// Округление вольтажа
			} else {
				OkrugVoltage = voltage;
			}
		}
		
		if (engineSpeed > 0){
			if (OkrugEngineSpeed > 0){
				OkrugEngineSpeed = (OkrugEngineSpeed + engineSpeed) / 2;		// Округление оборотов двигателя
			} else {
				OkrugEngineSpeed = engineSpeed;
			}
		}
	}
}

void loop(){
  main0();
	if(analogRead(buttonPin)>800){								//  если показания датчика линии больше 400 (тёмное поле)
		if(time2<millis()){										//  если нет переполнения millis(), то ...
			engineSpeed = 60000/(millis()-time2);				//  записываем данные по оборотам
		}
		time2 = millis();										//  присваиваем переменной time2 текущее значение millis();
		while(analogRead(buttonPin)>600){						//  ждём пока датчик линии не выйдет из тёмного поля
			if((millis()-time2)>400){
				engineSpeed = 0.0;								//  если датчик находится на тёмном  поле дольше 0.4 секунды, то выводим 0.0
			}
			main0();
		}
	}
	if((millis()-time2)>400){
		engineSpeed = 0.0;										//  если датчик находится на светлом поле дольше 0.4 секунды, то выводим 0.0
	}
}
