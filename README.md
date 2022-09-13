# Project-l0ckcr4ck3r
A fully Autonomous Lock Cracking Robot which uses Samy Kamkar's algorithm to crack locks in ~40 seconds

![MVIMG_20220913_114445](https://user-images.githubusercontent.com/72902803/189985666-f4c0db4e-e7cb-4d15-8908-caf322dbd3b7.jpg)
[Video](https://cad.onshape.com/documents/2b977856993104d0f24f1470/w/e2828f2601c6a316a05788e0/e/a76e54aa91df89bb32ae0012)

# how it works. 
## Cracking a lock 
First number: Turn dial Counter Clockwise while incrementally adding more and more force to the shackle until it suddenly stops. Round down to the nearest whole number and add 14. That is the first number in the combo

Third number: Find the gates between numbers 0 - 10 digits. Perform some math for the gates that correspond to a whole number. Do some more math and math and then check the two numbers that will be spit out. The number with the biggest gate is the third number.

Second number: Guess and check till the lock opens, though it follows a pattern of being a constant + a multiple of 4.

I found that this [video](https://www.youtube.com/watch?v=27rE5ZvWLU0&ab_channel=HelpfulLockPicker) really helped me when trying to program to algorithm.

## This robot 
A stepper motor / Encoder drives the dial and can regain it's positioning even if steps are lost.
![L0ckcr4ck3r (4)](https://user-images.githubusercontent.com/72902803/189998683-6a05d873-729a-4aa7-8828-fad94feb1225.png)
[Accurate Positioning](https://photos.app.goo.gl/EqdcLpkwjZUhWpmp6)


Whilst a servo with an analogFeedback wire can pull up on the shackle and check whether the lock has been opened or not. 




# 3D Model
![L0ckcr4ck3r](https://user-images.githubusercontent.com/72902803/189988396-6efb5e2c-a33e-4650-aaaa-6274c8dd3277.png)
[CAD Files](https://cad.onshape.com/documents/2b977856993104d0f24f1470/w/e2828f2601c6a316a05788e0/e/a76e54aa91df89bb32ae0012)

# Electronics 
Custom PCB powered by a USB C input.
![MVIMG_20220823_125722](https://user-images.githubusercontent.com/72902803/189993917-e4d566d9-a710-4d93-b4f6-112b091685c3.jpg)
![l0ckcr4ck3r](https://user-images.githubusercontent.com/72902803/189994125-900fee2f-7ecb-45a0-b1cc-69ece87774d7.jpg)

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

