#include <Arduino.h>
// Ultrasonic Sensor pins
const int TRIGGER_PIN = 2 ;
const int ECHO_PIN = 4;
// L293D pins
const int ENABLE_LEFT_MOTOR_PIN = 3;
const int ENABLE_RIGHT_MOTOR_PIN = 5;
const int INPUT_LEFT_MOTOR_1_PIN = 7;
const int INPUT_LEFT_MOTOR_2_PIN = 8;
const int INPUT_RIGHT_MOTOR_1_PIN = 12;
const int INPUT_RIGHT_MOTOR_2_PIN = 13;
// RGB pins
const int RED_LED_PIN = 6;
const int GREEN_LED_PIN = 9;
const int BLUE_LED_PIN = 10;

void setRGBColor(int red, int green, int blue){
    analogWrite(RED_LED_PIN, red);
    analogWrite(GREEN_LED_PIN, green);
    analogWrite(BLUE_LED_PIN, blue);
}

void initializeRGBLed(){
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
}

void initializeUltrasonicSensor(){
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIGGER_PIN, LOW);
}

long TrigerUltrasonicSensorPulse(){
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    unsigned long pulseTime = pulseIn(ECHO_PIN, HIGH);
    long distanceCM = pulseTime / 59;
    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.print(" cm");
    Serial.println();
    delay(100);
    return distanceCM;
}

void initializeMotors(){
    pinMode(ENABLE_LEFT_MOTOR_PIN, OUTPUT);
    pinMode(ENABLE_RIGHT_MOTOR_PIN, OUTPUT);
    pinMode(INPUT_LEFT_MOTOR_1_PIN, OUTPUT);
    pinMode(INPUT_LEFT_MOTOR_2_PIN, OUTPUT);
    pinMode(INPUT_RIGHT_MOTOR_1_PIN, OUTPUT);
    pinMode(INPUT_RIGHT_MOTOR_2_PIN, OUTPUT);

    digitalWrite(INPUT_LEFT_MOTOR_1_PIN, LOW);
    digitalWrite(INPUT_LEFT_MOTOR_2_PIN, LOW);
    digitalWrite(INPUT_RIGHT_MOTOR_1_PIN, LOW);
    digitalWrite(INPUT_RIGHT_MOTOR_2_PIN, LOW);
    analogWrite(ENABLE_LEFT_MOTOR_PIN, 0);
    analogWrite(ENABLE_RIGHT_MOTOR_PIN, 0);
}

void MoveMotors(int intLeftMotor1, int inputLeftMotor2, int inputRightMotor1, int inputRightMotor2, int speed = 255){
    digitalWrite(INPUT_LEFT_MOTOR_1_PIN, intLeftMotor1);
    digitalWrite(INPUT_LEFT_MOTOR_2_PIN, inputLeftMotor2);

    digitalWrite(INPUT_RIGHT_MOTOR_1_PIN, inputRightMotor1);
    digitalWrite(INPUT_RIGHT_MOTOR_2_PIN, inputRightMotor2);

    analogWrite(ENABLE_LEFT_MOTOR_PIN, speed);
    analogWrite(ENABLE_RIGHT_MOTOR_PIN, speed);
}
void selectMotorsMove(long distanceCMToObstacle){
    if(distanceCMToObstacle <= 20){
        setRGBColor(200, 0, 0);
        // Move backwards with one motor
        int motorSelected = random(0, 2);
        if(motorSelected == 0){
            MoveMotors(LOW, HIGH, LOW, LOW);
        }else{
            MoveMotors(LOW, LOW, LOW, HIGH);
        }
        delay(1000);
    }else{
        setRGBColor(0, 200, 0);
        // Move forward
        MoveMotors(HIGH, LOW, HIGH, LOW);
    }
}

void setup() {
    initializeRGBLed();
    initializeUltrasonicSensor();
    initializeMotors();
    Serial.begin(9600);
}

void loop() {
    long distanceCMToObstacle = TrigerUltrasonicSensorPulse();
    selectMotorsMove(distanceCMToObstacle);
}

