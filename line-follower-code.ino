#include <LiquidCrystal.h>

#define IR_RIGHT A0
#define IR_MIDDLE A1
#define IR_LEFT A2
#define MOTOR_SPEED 255

// Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 9;
int rightMotorPin2 = 8;

// Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 7;
int leftMotorPin2 = 10;

// LCD
int rs = 0, en = 1, p4 = 2, p5 = 3, p6 = 4, p7 = 11;
LiquidCrystal lcd(rs, en, p4, p5, p6, p7);

int back = LOW;
int line = HIGH;

int count = 0;

void setup()
{
    count = 0;
    // put your setup code here, to run once:
    TCCR0B = TCCR0B & B11111000 | B00000010;

    pinMode(enableRightMotor, OUTPUT);
    pinMode(rightMotorPin1, OUTPUT);
    pinMode(rightMotorPin2, OUTPUT);

    pinMode(enableLeftMotor, OUTPUT);
    pinMode(leftMotorPin1, OUTPUT);
    pinMode(leftMotorPin2, OUTPUT);

    pinMode(IR_RIGHT, INPUT);
    pinMode(IR_MIDDLE, INPUT);
    pinMode(IR_LEFT, INPUT);

    lcd.begin(16, 2);

    stopMotion();
}

void loop()
{
    int rightIRRead = digitalRead(IR_RIGHT);
    int middleIRRead = digitalRead(IR_MIDDLE);
    int leftIRRead = digitalRead(IR_LEFT);

    lcd.clear();

    lcd.setCursor(4, 0);
    lcd.print("G e e k s");

    if (rightIRRead == line && leftIRRead == line)
    {
        forward();
        lcd.setCursor(5, 1);
        lcd.print("FORWARD");
    }
    else if (rightIRRead == back && leftIRRead == line)
    {
        right();
        lcd.setCursor(5, 1);
        lcd.print("RIGHT");
    }
    else if (rightIRRead == line && leftIRRead == back)
    {
        left();
        lcd.setCursor(5, 1);
        lcd.print("LEFT");
    }
    else if (rightIRRead == back && middleIRRead == back && leftIRRead == back)
    {
        // count += 1;
        forward();
        // delay(2500);
        lcd.setCursor(5, 1);
        lcd.print("FORWARD");
    }
    else
    {
        stopMotion();
    }
}

void forward()
{
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(enableRightMotor, MOTOR_SPEED);
    analogWrite(enableLeftMotor, MOTOR_SPEED);
}

void left()
{
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(enableRightMotor, MOTOR_SPEED);
    analogWrite(enableLeftMotor, 0);
}

void right()
{
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(enableRightMotor, 0);
    analogWrite(enableLeftMotor, MOTOR_SPEED);
}

void stopMotion()
{
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(enableRightMotor, 0);
    analogWrite(enableLeftMotor, 0);
}
