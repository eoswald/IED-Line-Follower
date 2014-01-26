#define SENSOR_1 A0
#define SENSOR_2 A1
#define SENSOR_3 A2
#define SENSOR_4 A3

#define ON_LINE_AVERAGE 500
#define OFF_LINE_AVERAGE 1000

#define LEFT_MOTOR 10
#define RIGHT_MOTOR 11

#define PW_AVERAGE 50
#define PW_SMALL_ADJUST 100
#define PW_LARGE_ADJUST 200

/*#define LED_1 3
#define LED_2 5
#define LED_3 6
#define LED_4 9*/

#define LED 9

#define PW_LED 4

int sensor_1_avg = 500;
int sensor_2_avg = 500;
int sensor_3_avg = 500;
int sensor_4_avg = 500;

char left_motor_pw;
char right_motor_pw;

void lightLEDs(void);
void readSensors(void);
void determineDirection(void);
void driveMotors(void);

void setup() {
  analogReference(EXTERNAL);
  
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  
  /*pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);*/
  
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  lightLEDs();
  
  readSensors();
  
  determineDirection();
  
  driveMotors();
}

void lightLEDs(void) {
  /*analogWrite(LED_1, PW_LED);
  analogWrite(LED_2, PW_LED);
  analogWrite(LED_3, PW_LED);
  analogWrite(LED_4, PW_LED);*/
  
  analogWrite(LED, PW_LED);
}

void readSensors(void) {
  sensor_1_avg = (.5*analogRead(SENSOR_1)) + (.5*sensor_1_avg);
  sensor_2_avg = (.5*analogRead(SENSOR_2)) + (.5*sensor_2_avg);
  sensor_3_avg = (.5*analogRead(SENSOR_3)) + (.5*sensor_4_avg);
  sensor_4_avg = (.5*analogRead(SENSOR_4)) + (.5*sensor_4_avg);
}

void determineDirection(void) {
  if (200 > abs(OFF_LINE_AVERAGE - sensor_1_avg)) {
    left_motor_pw = PW_AVERAGE;
    right_motor_pw = PW_LARGE_ADJUST;
    Serial.println("Hard Left");
  }
  else if (200 > abs(OFF_LINE_AVERAGE - sensor_2_avg)) {
    left_motor_pw = PW_AVERAGE;
    right_motor_pw = PW_SMALL_ADJUST;
    Serial.println("Soft Left");
  }
  else if (200 > abs(OFF_LINE_AVERAGE - sensor_3_avg)) {
    left_motor_pw = PW_SMALL_ADJUST;
    right_motor_pw = PW_AVERAGE;
    Serial.println("Soft Right");
  }
  else if (200 > abs(OFF_LINE_AVERAGE - sensor_4_avg)) {
    left_motor_pw = PW_LARGE_ADJUST;
    right_motor_pw = PW_AVERAGE;
    Serial.println("Hard Right");
  }
  else {
    left_motor_pw = PW_AVERAGE;
    right_motor_pw = PW_AVERAGE;
    //Serial.println("On Line");
  }
}

void driveMotors(void) {
  analogWrite(LEFT_MOTOR, left_motor_pw);
  analogWrite(RIGHT_MOTOR, right_motor_pw);
}
