
int showmenuItems(String items[], int highlight = -1) {
  r.loop();

  // for (int i = 0; i < 5; i++) 
  //   Serial.print(items[i]);
  // Serial.println();

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
  
  if (encoderdiff != 0 || reset) {
    select -= encoderdiff; // Swap move direction cause it bugs the shit out of me
    
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
        if (curIndex == highlight)
          u8x8.drawString(13,curLine,"<");
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