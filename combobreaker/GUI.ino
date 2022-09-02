
int showmenuItems(String items[], bool forcereset = false) {  
  r.loop();
  static int select = 0;
  static int lastposencoder = 0;
  static String lastItem;
  static bool reset = true;
  String curItem = items[1];
  int encoderdiff = positionencoder - lastposencoder;

  if (curItem != lastItem ) // Reset select index if page changes
    select = 0;

  if (reset) { // Reset if the page changes
    u8x8.clearDisplay();
  }
  
  if (encoderdiff != 0 || reset || forcereset) {
    select -= encoderdiff; // Swap move direction cause it bugs the shit out of me
    if (forcereset)
      select = 0;
    int arrayLeng = 0;
    while (items[arrayLeng] != "end")
      arrayLeng++;
    arrayLeng -= 1; // Deal with the word "end" it is from 0, 1, 2
    if (select > arrayLeng) 
      select = arrayLeng;
    else if (select < 0) 
      select = 0;
    else { // Only update display if neccessary
      for (int i = 0; i < 4; i++)
        u8x8.clearLine(2+ i*2);
      
      u8x8.setCursor(0,0);
      u8x8.print(items[arrayLeng + 2]);
      
      int curIndex = select; 

      if (select == arrayLeng) {
        curIndex = select - 2;
        u8x8.drawString(0,6,">");
      }
      else if (select == arrayLeng - 1) {
        curIndex = select - 1;
        u8x8.drawString(0,4,">");
      }
      else if (select == 0) {
        if (items[0] == "Back")
          u8x8.drawString(0,2,"<");
        else
          u8x8.drawString(0,2,">");
      }
      else {
        curIndex = select - 1;
        u8x8.drawString(0,4,">");
      }
      
      int curLine = 2;
      
      for (int i = 0; i < 3; i++) {
        u8x8.setCursor(2,curLine);
        u8x8.print(items[curIndex]);
        curIndex++;
        curLine += 2;
      }
    }

    reset = false;
  }

  lastposencoder = positionencoder;
  lastItem = curItem;
  if (detectPress()) {
    reset = true;
    Serial.println("Pressed!!");
    return select;
  }
  else
    return -1;
}

void showError(String message, String message2) {
  u8x8.clear();
  u8x8.drawString(0,0, "Error");
  u8x8.drawString(0,7, "> Continue");
  u8x8.setCursor(0,3);
  u8x8.print(message);
  u8x8.setCursor(0,4);
  u8x8.print(message2);
  while (!detectPress()) ;
  u8x8.clear();
  return;
}

void printLine(String message, int line) {
  u8x8.clearLine(line);
  u8x8.setCursor(0,line);
  u8x8.print(message);
}

bool detectPress() {
  bool curState = digitalRead(BUTTON_PIN);
  static bool prevState = 1;

  if (curState - prevState == 1) {
    prevState = curState;
    return true;
  }
  else {
    prevState = curState;
    return false;
  }
}

void rotate(ESPRotary& r) {
  positionencoder = r.getPosition();
}


void showDirection(ESPRotary& r) {

}

void printCombo(int num1, int num2, int num3, int highLight = -1) {
  int line = 6;
  int digCount = 0;
  int beg;
  int nums[] = {num1, num2, num3};
  u8x8.clearLine(line);
  u8x8.clearLine(line+1);

  for (int i = 0; i < 3; i++)
    if (detSingleDig(nums[i]))
      digCount++;
    else
      digCount+=2;
  beg = 7 - (digCount+2)/2 ;

  for (int i = 0; i < 3; i++) {
    if (nums[i] != -1){
      u8x8.setCursor(beg,line);
      u8x8.print(nums[i]);
    }
    else {
      if (i == highLight-1) {
        u8x8.drawString(beg,line+1, "^");
      }
      u8x8.drawString(beg,line, "?");
    }
    if (detSingleDig(nums[i]))
      beg+=1;
    else
      beg+=2;

    if (i != 2)
      u8x8.drawString(beg,line, "-");
    beg += 1;
    }
}

bool detSingleDig(int num) {
  if (num - 10 < 0)
    return true;
  else
    return false;
}