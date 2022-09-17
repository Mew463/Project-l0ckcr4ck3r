
void crackLock() {
  estop = false;
  cracked = false;
  firstCheckStall = false;
  firstComboCheck = true;
  Serial.println(" ----- Start -----");
  printCombo(-1, -1, -1,1);
  lockTime = millis();
  findFirstNum();
  if (estop)
    return;
  printCombo(firstNum, -1, -1, 3);

  dial(39, CC); // Make sure all the disc packs dont interfere with finding the third num
  dial(0,CW); // Reset lock to 0 to prep for probing
  findThirdNum();

  if (estop)
    return;
  calcSecondNums();

  testAllCombos(0);
  if (!cracked)
    testAllCombos(2);

  
  double elapsedTime = (double)(millis() - lockTime)/ 1000;
  printLine("",3);
  printLine("Done in ",2);
  u8x8.setCursor(8,2);
  u8x8.print(elapsedTime);
  u8x8.drawString(14,2, "s");
  Serial.println(" ----- Done in " + String(elapsedTime) + " seconds -----");
  u8x8.drawString(0,4, "<");
  u8x8.drawString(2,4, "Back");
  while (!detectPress());

}