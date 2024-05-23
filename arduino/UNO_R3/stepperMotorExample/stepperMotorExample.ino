#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

#define LED_GREEN 3
#define LED_RED 2

#define FULL_ROTATION_STEPS 4096 // 28BYJ-48 stepper motor has 4096 steps per full rotation

int step_number = 0;

void setup() {
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void singleStep(bool dir){
  if(dir){
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }
  else{
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  }
  
  int step_sequence[8] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001};
  int index = dir ? step_number : (7 - step_number);
  
  for(int pin = 0; pin < 4; pin++){
    digitalWrite(STEPPER_PIN_1 + pin, bitRead(step_sequence[index], pin));
  }
  
  step_number = (step_number + 1) % 8;
}

void loop() {
  for(int i = 0; i < FULL_ROTATION_STEPS; i++){
    singleStep(true);
    delay(2);
  }
  
  //delay(1000); // pause for a second
  
  for(int i = 0; i < FULL_ROTATION_STEPS; i++){
    singleStep(false);
    delay(2);
  }
  
  //delay(1000); // pause for a second
}