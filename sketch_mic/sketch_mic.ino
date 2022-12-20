int sensorPin1 = A0;
int sensorPin2 = A1;
int micValue = 0;
int period = 100;


void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin1, INPUT);
  //pinMode(sensorPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //micValue = analogRead(sensorPin);
  int sum1 = 0, sumPrev1 = 0;
  //int sum2 = 0;
  for(int i = 0; i < period; i++){
      sum1 += analogRead(sensorPin1);
      //sum2 += analogRead(sensorPin2);
  }

  sum1 /= period;
  Serial.print(sum1);
  //Serial.print(",");
  //Serial.println(sum2 / period);    
  
  if(sum1 > sumPrev1 + 50){
    while(sum1 > sumPrev1){
      sumPrev1 = sum1;
      sum1 = 0;
      for(int i = 0; i < period; i++){
          sum1 += analogRead(sensorPin1);
          //sum2 += analogRead(sensorPin2);
      }
      sum1 /= period;
    }    
  }
  
  Serial.print(",");
  Serial.print(sumPrev1);  
  Serial.println("");
  delay(10);

  sumPrev1 = sum1;
}
