float readLockNum(int num = -1) { // Returns the current number dialed in based on the AS5600
  int adjustedangle;
  if (num == -1)
    adjustedangle = as5600.readAngle() - offset;
  else  
    adjustedangle = num - offset;
     
  if (adjustedangle < 0)
    adjustedangle = adjustedangle + 4096;

  return adjustedangle/102.4;
}

long multiTurnAngle() { // Multiturn angle
  static int lastAngle = 0;
  static long multiTurn = 0;
  int threshold = 50;
  int curAngle = 0;
  int deltaAngle = 0;

  curAngle = as5600.readAngle();

  deltaAngle = curAngle - lastAngle;
  if (deltaAngle < -4096 + threshold)
    deltaAngle+=4096;
  if (deltaAngle > 4096 - threshold)
    deltaAngle-=4096;

  multiTurn+=deltaAngle;

  lastAngle = curAngle;

  return multiTurn;
}

double returnStallNum(int speed, int ms_threshold) { // Runs the motor at certain speed and returns the lock number it stopped at
  static unsigned long lastTime;
  static long peakAngle = 0;
  long curMultiTurn;

  digitalWrite(enablePin, LOW);
  stepper.setSpeed(speed);
  stepper.runSpeed();

  curMultiTurn = multiTurnAngle();

  if (!digitalRead(BUTTON_PIN) || estop) {
    estop = 1;
    return;
  }

  if (!firstCheckStall) {
    firstCheckStall = true;
    peakAngle = curMultiTurn;
    lastTime = millis();
  }

  if (speed > 0) {
    if (curMultiTurn > peakAngle) {
      peakAngle = curMultiTurn;
      lastTime = millis();
    }
  }
  else
    if (curMultiTurn < peakAngle) {
      peakAngle = curMultiTurn;
      lastTime = millis();
    }

  if (millis() - lastTime > ms_threshold) {
    firstCheckStall = false;
    return readLockNum(peakAngle % 4096);
  }

  return -1;
}

void dial(float num, DIR _dir = CLOSE, int extraRot = 0) { // Inputs number into lock
  int stepval;
  float deltanum;
  float CCdelta;
  float CWdelta;
  digitalWrite(enablePin, LOW);

  extraRot = abs(extraRot);

  if (readLockNum() > num)
    CCdelta = 40 + num - readLockNum();
  else
    CCdelta = num - readLockNum();

  if (readLockNum() < num)
    CWdelta = -40 + num - readLockNum();
  else
    CWdelta = num - readLockNum();

  if (_dir == CC) {
    deltanum = CCdelta;
  }
  else if (_dir == CW){
    extraRot = -extraRot;
    deltanum = CWdelta;
  }
  else if (_dir == CLOSE) {
    if (abs((int)CCdelta) < abs((int)CWdelta))
      deltanum = CCdelta;
    else
      deltanum = CWdelta;
  }
  
  stepval = int(extraRot * stepsperRev + deltanum * (stepsperRev/40));

  stepper.moveTo(stepper.currentPosition() + stepval);
  stepper.runToPosition();
}

void dialcombo(int num1, int num2, int num3) { // Inputs 3 number combination, will use least amount of moves during brute forcing
  static int lastnum1 = -1;
  static int lastnum2 = -1;
  static int lastnum3 = -1; 
  int CCdelta;

  if ((lastnum1 == num1 && lastnum3 == num3) && !firstComboCheck) { 
    if (lastnum2 > num2)
      CCdelta = 40 + num2 - lastnum2;
    else
      CCdelta = num2 - lastnum2;

    if (CCdelta != 4)
      dial(num2, CC, 1);
    else
      dial(num2, CC);
    
    dial(num3, CW);
  }
  else {
    dial(num1, CW, 2);
    dial(num2, CC, 1);
    dial(num3, CW);
    firstComboCheck = false;
  }

  lastnum1 = num1;
  lastnum2 = num2;
  lastnum3 = num3;
}

int arraysize = 25;
int nums[25] = {0};

double ringbufferAvg() {
  static int z = -1;
  if (z = -1) 
    for (int i = 0; i < arraysize; i++)
      nums[i] = analogRead(servofeedback);

  nums[z] = analogRead(servofeedback);
  int sum = 0;
  z++;
  if (z > arraysize-1)
    z = 0;

  for (int i = 0; i < arraysize; i++) 
    sum += nums[i];
  return (double)sum/arraysize;
}

bool testOpen() {
  unsigned long curTime = millis();
  unsigned long lastTime = millis();

  double curPos = ringbufferAvg();
  double lastPos = curPos;
  
  int posThreshold = 35;
  int timeThreshold = 45;
  servo.writeMicroseconds(servoOpen);

  int nonfirst = 0;

  while (abs(curPos - servoFeedbackOpen) > posThreshold) { // while target position has not been hit yet
    curPos = ringbufferAvg();
    curTime = millis();

    if (abs(curPos - lastPos) > 5) { // Servo is still moving
      lastPos = curPos;
      lastTime = curTime;
      nonfirst++;
    }
    if (curTime - lastTime > timeThreshold && nonfirst != 0) { // Stalling!
      servo.writeMicroseconds(servoNeutral);
      delay(350);
      return false;
    }
  }
  return true; // target position hit!!
}

bool findBounds(bool checkSkip = 0) { // Activate servo and find the right and left bounds of a gate
  gateBounds[0] = 0; gateBounds[1] = 0;
  int speed = 200;
  int threshold = 100;
  double initialStart = readLockNum();
  double distanceMoved;

  servo.writeMicroseconds(gateHeight-50);

  delay(150);
  
  double RstallNum = -1;
  while (RstallNum == -1) {
    RstallNum = returnStallNum(speed, threshold);
    distanceMoved = readLockNum() - initialStart;
    if (checkSkip) {
      if (distanceMoved < -20)
        distanceMoved += 40;
      if (distanceMoved > 4) {
        servo.writeMicroseconds(servoNeutral);
        delay(200);
        return 0;
      }
    }
  }
  
  gateBounds[1] = RstallNum;
  
  delay(50);

  double LstallNum = -1;
  while (LstallNum == -1) {
    LstallNum = returnStallNum(-speed, threshold);
  }

  gateBounds[0] = LstallNum;

  servo.writeMicroseconds(servoNeutral);

  // Serial.println("LBound : " + String(LstallNum) + " RBound : " + String(RstallNum));
  
  delay(200);
  return 1;
}

