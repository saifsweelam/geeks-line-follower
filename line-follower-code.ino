#define IR_RIGHT 12
#define IR_MIDDLE 13
#define IR_LEFT 11
#define MOTOR_SPEED 255

// Right motor
int enableRightMotor = 6;
int rightMotorPin1 = 9;
int rightMotorPin2 = 8;

// Left motor
int enableLeftMotor = 5;
int leftMotorPin1 = 7;
int leftMotorPin2 = 10;

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

    stopMotion();
}

void loop()
{
    int rightIRRead = digitalRead(IR_RIGHT);
    int middleIRRead = digitalRead(IR_MIDDLE);
    int leftIRRead = digitalRead(IR_LEFT);

    // if (rightIRRead == back && middleIRRead == back && leftIRRead == back)
    // {
    //     forward();
    // } else
    if (rightIRRead == back && middleIRRead == line && leftIRRead == back)
    {
        forward();
    }
    else if (rightIRRead == line && leftIRRead == back)
    {
        right();
    }
    else if (rightIRRead == back && leftIRRead == line)
    {
        left();
    }
    else if (rightIRRead == line && middleIRRead == line && leftIRRead == line && count < 2)
    {
        count += 1;
        forward();
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
    digitalWrite(leftMotorPin2, HIGH);
    analogWrite(enableRightMotor, MOTOR_SPEED);
    analogWrite(enableLeftMotor, MOTOR_SPEED);
}

void right()
{
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(enableRightMotor, MOTOR_SPEED);
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
