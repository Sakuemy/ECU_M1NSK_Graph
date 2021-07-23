unsigned long time = 0;
unsigned long time2 = 0;
int engineSpeed = 0;
bool b;
char val;
char valSave;
const int buttonPin = 5;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(50); // установить таймаут
  pinMode(13, OUTPUT); // 13 пин – светодиод, объявляется как выход
  pinMode(buttonPin, INPUT);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if ((buttonState == HIGH) and (b == false)) {
    if (engineSpeed != 0){
        engineSpeed = round(((60000 / (millis() - time2)) + engineSpeed) / 2);
    } else {
      engineSpeed = round(60000 / (millis() - time2));
    }
    time2 = millis();
    b = true;
  }
  if (buttonState == LOW) {
    b = false;
  }


  if ((millis() - time > 1000)){ // and (valSave == '2')
      time = millis();
      Serial.println(String(engineSpeed) + ";" + String(analogRead(A4)) + ";" + String(analogRead(A3)) + ";");
      engineSpeed = 0;
  }
/*
  if ((Serial.available() > 0)) {
    val = Serial.read();
    switch (val) {
      case '1':
        Serial.print(engineSpeed);
        engineSpeed = 0;
        break;
      case '2':
        Serial.print(analogRead(A4));
        break;
      case '3':
        Serial.print(analogRead(A2));
        break;
      case '0':
        Serial.print(0);
        break;
    }
  }
*/
}
