# Project-l0ckcr4ck3r
This robot is a true creation of the idea many years ago brought on by [Samy Kamkar's robot](https://samy.pl/combobreaker/) that "utilized" his algorithm for cracking combination locks. Samy Kamkar never demonstrated his robot actually performing the algorithm, though he implied multiple times that it does do it.

![Untitled-1](https://user-images.githubusercontent.com/72902803/190844818-697106ac-0b5a-423b-b87c-c39876b1ba75.png)

I've always wanted to build a robot that actually decodes locks while maintaining a cool desk toy vibe! I am quite happy with the user-oriented design and doubles as a nice fidgety-toy-thing to play with.  

This robot is able to decode the majority of locks that don't have much wear and tear on it and usually takes ~40 seconds.

![MVIMG_20220913_114445](https://user-images.githubusercontent.com/72902803/189985666-f4c0db4e-e7cb-4d15-8908-caf322dbd3b7.jpg)

## Video
[![3 Locks in a Row](https://img.youtube.com/vi/nw5f3ZPQd-o/0.jpg)](https://www.youtube.com/watch?v=nw5f3ZPQd-o)


# How it works. 
## Cracking lock Algorithm 
First number: Turn dial Counter Clockwise while incrementally adding more and more force to the shackle until it suddenly stops. Round down to the nearest whole number and add 14. That is the first number in the combo. 

Third number: 
1) Find the gates between digits 0 - 10 . 
2) Take the two gates that correspond to a whole number and see whether each of those numbers %(modulo) 4 = firstNum % 4. 
3) If the equation is satisfied, store that number somewhere. Now add 10 to each number and perform the same operation as the previous step until you have **two** numbers that satisfy the equation
4) Now check the gate size of the two numbers which satisfy the equation. The number with the biggest gate is the third number. 

Second number: Guess and check until the lock opens, though it follows a pattern of being (FirstNum % 4) + a multiple of 4.

I found that this [video](https://www.youtube.com/watch?v=27rE5ZvWLU0&ab_channel=HelpfulLockPicker) really helped me when trying to program the algorithm.

## This robot 
A TMC2208 Trinamic driver drives a stepper motor & magnetic encoder. These components turn the dial and can detect when the stepper motor stalls. 
![L0ckcr4ck3r (6)](https://user-images.githubusercontent.com/72902803/190066424-c39b0e46-af7e-4335-b26d-acb7b4b06bff.png)

With this method, any desired number can easily be input into the lock and the lock can be "felt" for it's geometries.
![ezgif com-gif-maker (4)](https://user-images.githubusercontent.com/72902803/190001685-2d0fac5a-8186-4610-8ea3-449809643d41.gif)


Meanwhile a servo powers a rack and pinion gear which allows precise control of the shackle.
![ezgif com-gif-maker](https://user-images.githubusercontent.com/72902803/190001057-069cf706-c8b1-4324-ace1-77e981bfb805.gif)


Since I modified the servo with an [analog Feedback wire](https://www.youtube.com/watch?v=XfZLtkr6dgU&ab_channel=CuriousMotor), we can pull up on the shackle and use this to check whether the lock has been opened or not. 

![ezgif com-gif-maker (6)](https://user-images.githubusercontent.com/72902803/190021674-d77ea7ec-cc6f-4fd7-95ee-f4dc7078bf53.gif)


# 3D Model
![L0ckcr4ck3r](https://user-images.githubusercontent.com/72902803/189988396-6efb5e2c-a33e-4650-aaaa-6274c8dd3277.png)
[CAD Files](https://cad.onshape.com/documents/2b977856993104d0f24f1470/w/e2828f2601c6a316a05788e0/e/a76e54aa91df89bb32ae0012)

# Electronics 
Custom PCB powered by a 12V USB C input. An Arduino Nano is the brain and a 5V regulator gives the neccessary voltage for the servo. 
![MVIMG_20220823_125722](https://user-images.githubusercontent.com/72902803/189993917-e4d566d9-a710-4d93-b4f6-112b091685c3.jpg)
![l0ckcr4ck3r](https://user-images.githubusercontent.com/72902803/189994125-900fee2f-7ecb-45a0-b1cc-69ece87774d7.jpg)
![Electronics](https://user-images.githubusercontent.com/72902803/190002726-54b034f9-83e8-422e-8b92-fd85a2464a27.png)

KiCAD files are included in the github. 


# Materials

## Mechanical
* [TMC2208 Stepper Driver](https://www.amazon.com/Printer-TMC2208-Screwdriver-Controller-Ramps1-4/dp/B082LSQWZF/ref=sr_1_3?crid=2DM8J6G3IDA8J&keywords=tmc2208&qid=1661839331&sprefix=tmc2208%2Caps%2C133&sr=8-3)
* [High torque servos](https://www.amazon.com/Youleke-Torque-Digital-Servo%EF%BC%8CWaterproof-Horn%EF%BC%88270%C2%B0%EF%BC%89/dp/B08739MGPL/ref=sr_1_11?crid=81HZZ5JLGLML&keywords=servo&qid=1661839358&sprefix=servo+%2Caps%2C248&sr=8-11)
* [Stepper motor](https://www.amazon.com/STEPPERONLINE-Bipolar-Stepper-22-6oz-Extruder/dp/B00PNEQ79Q/ref=sr_1_6?crid=1U1NH4LQTF0ZK&keywords=stepper+motor&qid=1661839383&sprefix=stepper+motor+%2Caps%2C139&sr=8-6)
* [AS5600 Magnetic Encoder](https://www.amazon.com/Magnetic-Encoder-Induction-Measurement-Precision/dp/B094F8H591/ref=sr_1_4?crid=M8OANSRLFX5C&keywords=as5600+encoder&qid=1661839450&sprefix=as5600+encod%2Caps%2C130&sr=8-4)
* Assorted M3 Bolts

## Electrical
* Arduino Nano
* 10uF Capacitor x2
* Diode 
* [5V Regulator](https://www.digikey.com/en/products/detail/stmicroelectronics/LD1085V50/669220?s=N4IgTCBcDaIDIBECMAGAHAVgGoZSAugL5A)
* [OLED Display](https://www.amazon.com/Self-Luminous-Display-Compatible-Arduino-Raspberry/dp/B09JWN8K99/ref=sr_1_2_sspa?crid=DM9HX86FS3Q5&keywords=oled+arduino&qid=1661839948&sprefix=oledarduino%2Caps%2C143&sr=8-2-spons&psc=1)
* [Rotary Encoder](https://www.amazon.com/Taiss-KY-040-Encoder-15%C3%9716-5-Arduino/dp/B07F26CT6B/ref=sr_1_4?keywords=rotary+encoder&qid=1661839976&sprefix=roataray%2Caps%2C139&sr=8-4)
* [Blower Fan](https://www.amazon.com/WINSINN-Bearings-Brushless-Cooling-40mm20mm/dp/B08R9JJZ5Z/ref=sr_1_8?crid=1UCHGY2B410VX&keywords=blower+fan+12v+40mm&qid=1661839541&sprefix=blower+fan+12v+40m%2Caps%2C119&sr=8-8)
* [USB C 12V ](https://www.amazon.com/MELIFE-Type-C-Voltage-Trigger-Module/dp/B0953G14Q2/ref=sr_1_3?crid=12XVP47XQI63X&keywords=usb+c+12v+trigger&qid=1662871099&sprefix=usb+c+12v+trigge%2Caps%2C227&sr=8-3)
* [Power Supply](https://www.amazon.com/ZMI-zPower-Turbo-Power-Adapter/dp/B07D64QLQ1/ref=sr_1_5?crid=3I0WTX44C53G1&keywords=usb+c+charger+pd&qid=1662871140&sprefix=usb+c+charger+%2Caps%2C244&sr=8-5)

