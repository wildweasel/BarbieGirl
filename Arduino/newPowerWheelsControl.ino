
// Output pin definitions
#define FORWARD_PWM 9   // PWM for forward
#define REVERSE_PWM 10  // PWM for reverse

// Enable pin definitions
#define FORWARD_ENABLE 5   // PWM for forward
#define REVERSE_ENABLE 6
// PWM for reverse

// values for maximum commanded motor speed (maximum is 255 for forward directions, and -255 for reverse)
#define FWD_MAX  100
#define REV_MAX  -100

int currentSpeed = 0;

enum MotorDirection {
  FORWARD,
  REVERSE
};

int i;

void setup() {
    
  // set up the pins to the h-bridge as outputs
  pinMode(FORWARD_PWM, OUTPUT);
  pinMode(REVERSE_PWM, OUTPUT);
  pinMode(FORWARD_ENABLE, OUTPUT);
  pinMode(REVERSE_ENABLE, OUTPUT);


  digitalWrite(FORWARD_PWM, LOW);
  digitalWrite(REVERSE_PWM, LOW);
  digitalWrite(FORWARD_ENABLE, LOW);
  digitalWrite(REVERSE_ENABLE, LOW);
  
  int i = 0;
    
  Serial.begin(9600);
  Serial.print("ready"); 
}

void loop() {

  digitalWrite(FORWARD_ENABLE,HIGH);
  digitalWrite(REVERSE_ENABLE,HIGH);

  commandMotor(i++%2);
  
  delay(2000);

}

void commandMotor(MotorDirection motorDirection){

  switch(motorDirection){
  case FORWARD:     
     goForward();
     break;
  case REVERSE:
     goBackward();
     break;
  default:     
     digitalWrite(FORWARD_PWM,0);Serial.println("Stop");
     digitalWrite(REVERSE_PWM,0);
  };
}

void goForward(){
  while(currentSpeed < FWD_MAX){
    accelerateForward();
    delay(500);
  }
}

void goBackward(){
  while(currentSpeed > REV_MAX){
    accelerateBackwards();
    delay(500);
  }
}

void accelerateForward(){
  currentSpeed = min(currentSpeed+10, FWD_MAX);
  Serial.print("Accelerating to ");
  Serial.println(currentSpeed);
  move();
}

void accelerateBackwards(){
  currentSpeed = max(currentSpeed-10, REV_MAX);
  Serial.print("Decelerating to ");
  Serial.println(currentSpeed);
  move();
}

void move(){
  // Forward
  if(currentSpeed > 0){    
    analogWrite(FORWARD_PWM,currentSpeed);
    analogWrite(REVERSE_PWM,0);
  }
  // Reverse
  else{
    analogWrite(REVERSE_PWM,-currentSpeed);
    analogWrite(FORWARD_PWM,0);
  }
}




