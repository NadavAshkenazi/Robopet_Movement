***************************************************************
 _______  _______  ______   _______  _______  _______ _________
(  ____ )(  ___  )(  ___ \ (  ___  )(  ____ )(  ____ \\__   __/
| (    )|| (   ) || (   ) )| (   ) || (    )|| (    \/   ) (   
| (____)|| |   | || (__/ / | |   | || (____)|| (__       | |   
|     __)| |   | ||  __ (  | |   | ||  _____)|  __)      | |   
| (\ (   | |   | || (  \ \ | |   | || (      | (         | |   
| ) \ \__| (___) || )___) )| (___) || )      | (____/\   | |   
|/   \__/(_______)|/ \___/ (_______)|/       (_______/   )_(   
                                                               
***************************************************************
#Arduino commands

* "stop" - stop the movement
* "left" - hardcoded turn to max left (60 degrees)
* "right" - hardcoded turn to max right (120 degrees)
* "straight" - hardcoded turn straight (90 degrees)
* "forward" - activate motors to run forward spin on current speed
* "backward" - activate motors to run backward spin on current speed
* "scan" - activate scanning sequence of the camera stand
* "speed {int a}" - set motors speed to a
* "turn {int a}" - turn axis to to a
* "cam_setX {int a}" - turn camera stand X axis to to a
* "cam_setY {int a}" - turn camera stand Y axis to to a
* "dist (--front)/(--back)" - get the distance of the nearest object to front/back
* "spin (--left)/(--right) (--front)/(--back) {int x}" - preform a spin of x quarters to the given direction in a given orientation 

#PINS

## Arduino UNO PINS:

###  Analog pins:

* A0 - Empty
* A1 - Empty
* A2 - Empty
* A3 - Empty
* A4 - SCA of PAC99685
* A5 - SCL of PAC99685


### Digital pins:

* 0 -- Empty
* 1 -- Empty
* 2 -- IN1 of L298
* 3 -- IN2 of L298
* 4 -- IN3 of L298
* 5 -- IN4 of L298
* 6 -- Empty
* 7 -- Echo of Ultrasonic Distance Sensor (Front)
* 8 -- Trig of Ultrasonic Distance Sensor (Front) 
* 9 -- ENA of L298
* 10 - ENB of L298
* 11 - Empty
* 12 - Echo of Ultrasonic Distance Sensor (Back)
* 13 - Trig of Ultrasonic Distance Sensor (Back)

## pca9685 PINS:

* 0 -- Axis servo
* 1 -- tailStart servo
* 2 -- tailEnd servo 
* 3 -- Empty 
* 4 -- Empty 
* 5 -- Empty 
* 6 -- Empty 
* 7 -- Empty 
* 8 -- Empty 
* 9 -- Empty 
* 10 - Empty 
* 11 - Empty 
* 12 - Empty 
* 13 - Empty 
* 14 - Camera X-axis Servo
* 15 - Camera Y-axis Servo 