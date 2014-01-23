#define SENSOR_1 A0
#define SENSOR_2 A1
#define SENSOR_3 A2
#define SENSOR_4 A3

#define ON_LINE_AVERAGE 890
#define OFF_LINE_AVERAGE 970

#define NUM_SENSORS 4
#define DATA_ARRAY_SIZE 20

#define LEFT_MOTOR 10
#define RIGHT_MOTOR 11

#define PW_AVERAGE 50
#define PW_SMALL_ADJUST 100
#define PW_LARGE_ADJUST 200

int sensor_1_avg;
int sensor_2_avg;
int sensor_3_avg;
int sensor_4_avg;

int SENSOR_1_DATA[DATA_ARRAY_SIZE];
int SENSOR_2_DATA[DATA_ARRAY_SIZE];
int SENSOR_3_DATA[DATA_ARRAY_SIZE];
int SENSOR_4_DATA[DATA_ARRAY_SIZE];

char left_motor_pw;
char right_motor_pw;

void readSensors(void);
void arrayShift(int * data_arr);
int dataAverages(int * data_arr);
void determineDirection(void);
void driveMotors(void);

void setup() {
  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
}

void loop() {
  readSensors();
  
  sensor_1_avg = dataAverages(SENSOR_1_DATA);
  sensor_2_avg = dataAverages(SENSOR_2_DATA);
  sensor_3_avg = dataAverages(SENSOR_3_DATA);
  sensor_4_avg = dataAverages(SENSOR_4_DATA);
  
  determineDirection();
  
  driveMotors();
}

void readSensors(void) {
  arrayShift(SENSOR_1_DATA);
  arrayShift(SENSOR_2_DATA);
  arrayShift(SENSOR_3_DATA);
  arrayShift(SENSOR_4_DATA);
  
  SENSOR_1_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_1);
  SENSOR_2_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_2);
  SENSOR_3_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_3);
  SENSOR_4_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_4);
}

void arrayShift(int * data_arr) {
  for(int i = 0; i < DATA_ARRAY_SIZE; i++) {
    data_arr[i] = data_arr[i+1];
  }
}

int dataAverages(int * data_arr) {
  int sum = 0;
  
  for(int i = 0; i <= DATA_ARRAY_SIZE; i++) {
    sum += data_arr[i];
  }
  
  return sum/DATA_ARRAY_SIZE;
}

void determineDirection(void) {
  if (abs(ON_LINE_AVERAGE - sensor_1_avg) > abs(OFF_LINE_AVERAGE - sensor_1_avg)) {
    left_motor_pw = PW_AVERAGE;
    right_motor_pw = PW_LARGE_ADJUST;
    Serial.println("Hard Left");
  }
  else if (abs(ON_LINE_AVERAGE - sensor_2_avg) > abs(OFF_LINE_AVERAGE - sensor_2_avg)) {
    left_motor_pw = PW_AVERAGE;
    right_motor_pw = PW_SMALL_ADJUST;
    Serial.println("Soft Left");
  }
  else if (abs(ON_LINE_AVERAGE - sensor_3_avg) > abs(OFF_LINE_AVERAGE - sensor_3_avg)) {
    left_motor_pw = PW_SMALL_ADJUST;
    right_motor_pw = PW_AVERAGE;
    Serial.println("Soft Right");
  }
  else if (abs(ON_LINE_AVERAGE - sensor_4_avg) > abs(OFF_LINE_AVERAGE - sensor_4_avg)) {
    left_motor_pw = PW_LARGE_ADJUST;
    right_motor_pw = PW_AVERAGE;
    Serial.println("Hard Right");
  }
}

void driveMotors(void) {
  analogWrite(LEFT_MOTOR, left_motor_pw);
  analogWrite(RIGHT_MOTOR, right_motor_pw);
}
