#define SENSOR_1 A0
#define SENSOR_2 A1
#define SENSOR_3 A2
#define SENSOR_4 A3

#define ON_LINE_AVERAGE XXXX
#define OFF_LINE_AVERAGE XXXX

#define NUM_SENSORS 4
#define DATA_ARRAY_SIZE 20

int sensor_1_avg;
int sensor_2_avg;
int sensor_3_avg;
int sensor_4_avg;

int SENSOR_1_DATA[DATA_ARRAY_SIZE];
int SENSOR_2_DATA[DATA_ARRAY_SIZE];
int SENSOR_3_DATA[DATA_ARRAY_SIZE];
int SENSOR_4_DATA[DATA_ARRAY_SIZE];

void readSensors(void);
void arrayShift(int * data_arr);
int dataAverages(int * data_arr);

void setup() {

}

void loop() {
  readSensors();
  dataAverages(SENSOR_1_DATA);
  dataAverages(SENSOR_2_DATA);
  dataAverages(SENSOR_3_DATA);
  dataAverages(SENSOR_4_DATA);

}

void readSensors(void) {
  arrayShift(SENSOR_1_DATA);
  arrayShift(SENSOR_2_DATA);
  arrayShift(SENSOR_3_DATA);
  arrayShift(SENSOR_4_DATA);
  
  sensor_1_avg = SENSOR_1_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_1);
  sensor_2_avg = SENSOR_2_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_2);
  sensor_3_avg = SENSOR_3_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_3);
  sensor_4_avg = SENSOR_4_DATA[DATA_ARRAY_SIZE] = analogRead(SENSOR_4);
  
  
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
