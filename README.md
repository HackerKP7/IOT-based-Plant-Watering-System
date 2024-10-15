# IOT-based-Plant-Watering-System
IOT based watering system using ESP32 board. Read Readme.txt for description
In this project i have used Blynk which is a low-code Internet of Things (IoT) software platform that helps users build, manage, and scale connected hardware. It can be used for a variety of purposes. It is an open source iot cloud platform. To connect esp32 with your Blynk cloud platform, you must first set up your project on the Blynk app, design the interface however you see fit, and copy the auth token. In the project the components used were-


Soil moisture sensor: To detect moisture of the soil.

Link to buy- https://www.amazon.in/Electron-Moisture-Output-Soil-Hygrometer-Soil-Sensor-Soil/dp/B0D2BMSXQ8/ref=asc_df_B0D2BMSXQ8/?tag=googleshopdes-21&linkCode=df0&hvadid=709962222620&hvpos=&hvnetw=g&hvrand=12945044259044600812&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9198122&hvtargid=pla-2355942178481&psc=1&mcid=aa537acaf2a2353ea011ba701a9222c9&gad_source=1


Water pump with L293D motor driver: To pump water into the plant pot. 

Link to buy- https://www.amazon.in/Adafruit-4546-Submersible-Water-Pump/dp/B085KYZCDV


OLED display for displaying data.

Link to buy - https://robu.in/product/0-96-inch-i2c-iic-oled-lcd-module-4pin-with-vcc-gnd-white/?gad_source=1&gclid=CjwKCAjwpbi4BhByEiwAMC8JnZATNEO4AVNTmUeejm0iekjHP94b-AHN-8fKWOQ1kM8mfD1_6q5X0BoCzQcQAvD_BwE


ESP32 board as the main Microcontroller


Connections-
                                                                                       OLED display
                                                                                            |
                                                                                            |
                                                                                         (4 pins)
                                                                                            |
                                                                                            |
Soil moisture sensor ---(2 pins)----> LM393 comparator module ---(3 pins[A0,GND,VCC])---->ESP32<------Motor driver[L293D] (2 pins) <---(2 pins)---- Water pump
                                                                                                                  |
                                                                                                                  |
                                                                                                                  |
                                                                                                        (external power supply 12v)
                                                                                                            
We are using NTP server to extract real world time 
