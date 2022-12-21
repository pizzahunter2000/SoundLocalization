int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorPin4 = A3;
int micValue = 0;
int period = 30;
int LED1 = 10;
int LED2 = 11;
int LED3 = 12;
int LED4 = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

char* leds(int par1, int par2, int par3, int par4) {
  if (par1 > par2 && par1 > par3 && par1 > par4) {
    return "1000";
  }
  else if (par2 > par1 && par2 > par3 && par2 > par4) {
    return "0100";
  }
  else if (par3 > par1 && par3 > par2 && par3 > par4) {
    return "0010";
  }
  else if (par4 > par1 && par4 > par2 && par4 > par3) {
    return "0001";
  }
  else {
    return "0000";
  }
}

void handleLeds(char ledsArray[4]) {
  if (ledsArray == "1000") {
    digitalWrite(LED1, HIGH);
  }
  else if (ledsArray == "0100") {
    digitalWrite(LED2, HIGH);
  }
  else if (ledsArray == "0010") {
    digitalWrite(LED3, HIGH);
  }
  else if (ledsArray == "0001") {
    digitalWrite(LED4, HIGH);
  }

  delay(10);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //micValue = analogRead(sensorPin);
  int sum1 = 0, sumPrev1 = 0;
  int sum2 = 0, sumPrev2 = 0;
  int sum3 = 0, sumPrev3 = 0;
  int sum4 = 0, sumPrev4 = 0;
  for(int i = 0; i < period; i++){
      sum1 += analogRead(sensorPin1);
      sum2 += analogRead(sensorPin2);
      sum3 += analogRead(sensorPin3);
      sum4 += analogRead(sensorPin4);
  }

  sum1 /= period;
  sum2 /= period;
  sum3 /= period;
  sum4 /= period;

  Serial.print(sum1);
  Serial.print(",");
  Serial.print(sum2);
  Serial.print(",");
  Serial.print(sum3);
  Serial.print(",");
  Serial.print(sum4);
  Serial.print(",");
  
  if(sum1 > sumPrev1 + 50 || sum2 > sumPrev2 + 50 || sum3 > sumPrev3 + 50 || sum4 > sumPrev4 + 50){
    while(sum1 > sumPrev1){
      sumPrev1 = sum1;
      sumPrev2 = sum2;
      sumPrev3 = sum3;
      sumPrev4 = sum4;
      sum1 = 0;
      sum2 = 0;
      sum3 = 0;
      sum4 = 0;
      for(int i = 0; i < period; i++){
          sum1 += analogRead(sensorPin1);
          sum2 += analogRead(sensorPin2);
          sum3 += analogRead(sensorPin3);
          sum4 += analogRead(sensorPin4);
      }
      sum1 /= period;
      sum2 /= period;
      sum3 /= period;
      sum4 /= period;
    }    
  }

  char* ledsArray = leds(sumPrev1, sumPrev2, sumPrev3, sumPrev4);
  handleLeds(ledsArray);
  
  /*Serial.print(",");
  Serial.print(sumPrev1);
  Serial.print(",");
  Serial.print(sumPrev2);
  Serial.print(",");
  Serial.print(sumPrev3);
  Serial.print(",");
  Serial.print(sumPrev4);*/

  Serial.print(",");
  Serial.print(ledsArray[0]);
  Serial.print(",");
  Serial.print(ledsArray[1]);
  Serial.print(",");
  Serial.print(ledsArray[2]);
  Serial.print(",");
  Serial.print(ledsArray[3]);

  Serial.println("");
  //delay(10);

  sumPrev1 = sum1;
  sumPrev2 = sum2;
  sumPrev3 = sum3;
  sumPrev4 = sum4;
}
