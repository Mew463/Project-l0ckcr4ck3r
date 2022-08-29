void findFirstNum() { // Spins the dial while slowly pulling up on the shackle, when the motor stalls add ~14 to the current number
  int curServoCom = servoNeutral - 60; // Start probing a little higher than Neutral to save time
  dial(0, CC, 2); // Clear lock and ensure all the dials are being spun

  servo.writeMicroseconds(curServoCom);

  while (true) {
    EVERY_N_SECONDS(1) 
      servo.writeMicroseconds(curServoCom-=2); // Slowly increase tension on the shackle

    double stallnum = returnStallNum(1500, 20);
    if (stallnum != -1) { // if stall detected
      stallnum -= .2;
      servo.writeMicroseconds(servoNeutral); 
      delay(100);
      gateHeight = curServoCom;
      Serial.println("Stalled at: " + String(stallnum));
      stallnum = (int)stallnum + 14; // Round down the number of interest and add 14
      if (stallnum > 40) // Wrap around case
        stallnum-=40;
      firstNum = stallnum;
      break;
    }
  }
  Serial.println("First number: " + String(firstNum) + " GateHeight : " + String(gateHeight));
}

void findThirdNum() {
  int lockedPos[3] = {-1, -1, -1};
  int posThirdNums[2];
  double gateSize[2];

  double gateDifferences[3];
  double NOI[3];


  int lcrossover;
  int rcrossover;
  int x = 0;

  dial(39.5, CLOSE); // Setup lock dial to intiate probing 
  firstNumRem = firstNum % 4;

  for (int i = 0; i < 3; i++) { // Never need to check more than the first 3 gates of the lock
      findBounds();

      if (gateBounds[0] > 20 && gateBounds[1] > 20) { // Did not cross over past 0 which can't be a number of interest
        dial(gateBounds[1] + 2, CLOSE); // Move onto the next gate, which is two numbers from the right edge of the previous gate 
        i = -1;
        Serial.println("Skipping as the number did not cross 0");
        continue;
      }
      
      lcrossover = int(gateBounds[0]) + 1; // lcrossover and rcross over should be the same 
      rcrossover = int(gateBounds[1]); 

      if (gateBounds[0] > 20) {
        lcrossover = 0;
        gateBounds[0] -= 40;
      }

      double diffl = abs(lcrossover - gateBounds[0]);
      double diffr = abs(rcrossover - gateBounds[1]); 

      if (lcrossover != rcrossover) {
        Serial.println("error!! crossovers are not equal");
        if (diffl > diffr)
          NOI[i] = lcrossover;
        else
          NOI[i] = rcrossover;
      }
      else
        NOI[i] = lcrossover;

      Serial.println("DiffL: " + String(diffl) + "\t DiffR: " + String(diffr) + " NOI : " + String(NOI[i]));

      if (diffl < diffr)
        gateDifferences[i] = diffl;
      else
        gateDifferences[i] = diffr;
      if (i != 2)
      dial(gateBounds[1] + 2.5, CLOSE); // Move onto the next gate, which is two numbers from the right edge of the previous gate 
    }

    // Serial.println(String(gateDifferences[0]) + " " + String(gateDifferences[1]) + " " + String(gateDifferences[2]));

    double greatest = 0;
    int ind;
    double tolCheck[2];
    bool stop = false;
    checkTwice = false;
    for (int z = 0; z < 3; z++) {

      if (z == 1) { // Tolerance check. If the second greatest gateDifferences are within a certain tolerance, calculate all possibilties
        int p = 0;
        for (int i = 0; i < 3; i++)
          if (gateDifferences[i] != -1)
            tolCheck[p++] = gateDifferences[i];
        if (abs(tolCheck[1] - tolCheck[0]) < 0.1) {
          Serial.println("Using 3 lockedPositions since Tolerance check actviated");
          checkTwice = true;
        }
      }

      for (int i = 0; i < 3; i++) {
        if (gateDifferences[i] > greatest) {
          greatest = gateDifferences[i];
          ind = i;
        }
      }
      lockedPos[z] = NOI[ind];
      gateDifferences[ind] = -1; // Reset it to make sure to not choose it again
      greatest = 0;
    }

    Serial.println("Locked Positions : " + String(lockedPos[0]) + " " + String(lockedPos[1]));
    if (checkTwice)
      Serial.println("Locked Positions : " + String(lockedPos[0]) + " " + String(lockedPos[2]));

  for (int a = 0; a < 2; a++) {
    x = 0;

    for (int i = 0; i < 4; i++) {  // Check all combinations to see if the modulus matures with the modules of the first Num 
      if (lockedPos[0] % 4 == firstNumRem)
        posThirdNums[x++] = lockedPos[0];
      if (lockedPos[a+1] % 4 == firstNumRem)
        posThirdNums[x++] = lockedPos[a+1];
      if (x > 1)
        break;

      lockedPos[0] += 10; lockedPos[a+1] += 10; //increment both numbers by 10 to check all combinations

    }

    for (int i = 0; i < 2; i++) { // Narrow it down from two numbers to one number by choosing the largest gate size
      dial(posThirdNums[i], CC); 
      findBounds();

      double diff = gateBounds[1] - gateBounds[0];
      if (diff < 0) // Handle wrap around
        diff += 40;
      gateSize[i] = diff;
    }

    if (gateSize[0] > gateSize[1]) {
      thirdNum[a] = posThirdNums[0];
      thirdNum[a+2] = posThirdNums[1]; // Keep track of the other one as well
    }
    else {
      thirdNum[a] = posThirdNums[1];
      thirdNum[a+2] = posThirdNums[0]; // Keep track of the other one as well
    }

    Serial.println("Third number: " + String(thirdNum[a]));  

    if (!checkTwice)
      break;

    dial(0, CW);
  }
}

void calcSecondNums() { // Calculates the possible second numbers and places them in the array
  firstNumRem = firstNum % 4;
  
  for (int d = 0; d < 4; d++) {
    int z = 0;
    int curCheck = firstNumRem + 2;
    // Serial.println(thirdNum[0]);
    for (int i = 0; i < 10; i++) { // If the number is 2 or less away from the first number, we can disregard it
      if (abs(curCheck - thirdNum[d]) > 3 && abs(curCheck - thirdNum[d]) < 38 && thirdNum[d] != -1) {
        secondNums[d][z++] = curCheck;
      }
      curCheck += 4;
      if (curCheck > 40) // Handles wrap around 
        curCheck -= 40;
    }
  }

  // Serial.println("secondNums array: ");
  // for (int i = 0; i < 8; i++) 
  //   Serial.print(String(secondNums[0][i]) + "\t");
  // Serial.println();

  
  
}

bool testAllCombos(int ind = 0) {
  int num = firstNum;
  int startIndex = -1;
  int curIndex;

  while (true) {
    for (int i = 0; i < 8; i++) {
      if (secondNums[ind][i] == num) {
        startIndex = i;
      }
    }
    if (startIndex != -1)
      break;
    num++;
    if (num >= 40) // wrap around!!
      num = 0;
  }

  for (int i = 0; i < 8; i++) {
    curIndex = startIndex + i;
    if (curIndex > 7) // Handle wrap around 
      curIndex -= 8; 
    
    Serial.println("trying " + String(firstNum) + "," + String(secondNums[ind][curIndex]) + "," + String(thirdNum[ind]));
    printCombo(firstNum, secondNums[ind][curIndex], thirdNum[ind]);

    dialcombo(firstNum, secondNums[ind][curIndex], thirdNum[ind]);
    if (testOpen()) {
      Serial.println("success!!!");
      cracked = true;
      return true;
    }
  }

  Serial.println("failed..");
  return false;
}

bool testOpen() {
  unsigned long curTime = millis();
  unsigned long lastTime = millis();

  double curPos = ringbufferAvg();
  double lastPos = curPos;
  
  int posThreshold = 25;
  int timeThreshold = 25;
  servo.writeMicroseconds(servoOpen);

  int nonfirst = 0;

  while (abs(curPos - servoFeedbackOpen) > posThreshold) { // while target position has not been hit yet
    curPos = ringbufferAvg();
    curTime = millis();

    if (abs(curPos - lastPos) > 5) { // Servo is still moving
      // Serial.println(String(curTime - lastTime));
      lastPos = curPos;
      lastTime = curTime;
      nonfirst++;
    }
    if (curTime - lastTime > timeThreshold && nonfirst != 0) { // Stalling!
      //Serial.println("stalling!!");
      servo.writeMicroseconds(servoNeutral);
      delay(350);
      return false;
    }
  }
  return true; // target position hit!!
}

void findBounds() { // Activate servo and find the right and left bounds of a gate
  gateBounds[0] = 0; gateBounds[1] = 0;
  int speed = 200;
  int threshold = 100;

  servo.writeMicroseconds(gateHeight-30);

  delay(150);

  double RstallNum = -1;
  while (RstallNum == -1) {
    RstallNum = returnStallNum(speed, threshold);
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
}

void crackLock() {
  cracked = false;
  Serial.println(" ----- Start -----");
  printCombo(-1, -1, -1);
  lockTime = millis();
  findFirstNum();
  printCombo(firstNum, -1, -1);

  dial(39, CC); // Make sure all the disc packs dont interfere with finding the third num
  dial(0,CW); // Reset lock to 0 to prep for probing
  findThirdNum();
  calcSecondNums();
  testAllCombos(0);
  if (!cracked)
    testAllCombos(2);

  if (checkTwice && !cracked)
    if (!testAllCombos(1)) // Test separate case if the previous test failed 
      testAllCombos(3);
  
  double elapsedTime = (double)(millis() - lockTime)/ 1000;
  u8x8.drawString(0,2, "Done in ");
  u8x8.setCursor(8,2);
  u8x8.print(elapsedTime);
  u8x8.drawString(14,2, "s");
  Serial.println(" ----- Done in " + String(elapsedTime) + " seconds -----");
}


