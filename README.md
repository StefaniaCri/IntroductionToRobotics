# Introduction to Robotics
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.
<details>
<summary>RGB led with potentiometers</summary>
<br>
  Use a separat potentiometer in controlling each of the color of the RGB led (*R*ed, *G*reen and *B*lue).  The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connectedto the led.
  
## Setup

  <img src="https://user-images.githubusercontent.com/79380914/197886843-1d80908d-0ce9-43b8-aeb9-123c700270a8.jpeg" width="570" height="426" />

## Video
  [Watch the video](https://youtu.be/uTKtmfkYtcI)
</details> 
<details>
<summary>Traffic  lights  for  a  crosswalk</summary>
  Building  the  traffic  lights  for  a  crosswalk.   
  Use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).
  
  The system has the following states:
  1. State 1(default, reinstated after state 4 ends):  
    - green light for cars;
    - red  light  for  people;  
    - no  sounds.   
    
 Duration:  indefinite,  changed  by pressing the button.
 
 2. State 2 (initiated by counting down 8 seconds after a button press):
   - yellow  for  cars;  
   - red  for  people;
   - no  sounds.
    
 Duration:  3 seconds.
 
 3. State 3 (initiated after state 2 ends):  
   - red for cars;
   - green for people
   - a beeping sound from the buzzer at a constant interval. 
   
 Duration: 8 seconds.
 
 4. State 4 (initiated after state 3 ends):  
  - red for cars;
  - blinking green for people;
  - a beeping sound from the buzzer,  at a constant interval,  faster than the beeping in state 3.  
 Duration: 4 seconds.
 
 Pressing  the  button  in  any  state  other  than  state  1  should NOT yield any actions.
  ## Setup
  <img src="https://user-images.githubusercontent.com/79380914/199465955-e7b0dc0a-a068-47c9-a034-cab50a9b211d.png" width="600" height="500" />
  
  <img src="https://user-images.githubusercontent.com/79380914/199466150-86fa17a2-51e8-4a5e-b7f8-f2869b8b23fb.jpg" width="397" height="530" />
  
  ## Video
   [Showing functionality](https://youtu.be/qx-ZBx0JzNs)
   
   [Showing what happens if the button is pressed in different states](https://youtu.be/tTEfWM5sgps)
</details>
<details>
<summary>Draw on a 7-segment display</summary>

  Use the joystick to control the position ofthe segment and ”draw” on the display.  
  The movement between segments should be natural (meaning they should jump from the current position only to neighbors, but without passing through ”walls”.
  The system has the following states:
  
    1.State  1 (default,  but  also  initiated  after  a  button  press  in  State2):  Current  position  blinking.   Can  use  the  joystick  to  move  from one  position  to  neighbors.   Short  pressing  the  button  toggles  state2.  Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
    2.State  2 (initiated  after  a  button  press  in  State  1):   The  current segment  stops  blinking,  adopting  the  state  of  the  segment  before selection (ON or OFF). Toggling the Y axis should change  the  segment  state  from  ON  to  OFF  or  from  OFF  to  ON. Clicking the joystick should save the segment state and exit back to state 1.
  ## Posible moves: 
   ![image](https://user-images.githubusercontent.com/79380914/200834753-d0f3eac0-14b7-4f52-9a8a-b8801fd50b20.png)

  ## Setup
  <img src="https://user-images.githubusercontent.com/79380914/200825583-429c980b-2c96-414d-9c85-016e471f2647.jpg" width="397" height="530" />
  
  ## Video
  [Watch the video](https://youtu.be/n4lp0E6eDjI)
   
</details>
<details>
<summary>Move through a 4 digit display</summary>
Use the joystick to move through the 4 digit 7 segment displays digits, press the button to lock in on the current digit and use the other axis to increment or decrement the number.  
Keep the button pressed to reset all the digit values and the current position to the first digit in the first state.
The system has the following states:

  1.  First state: you can use a joystick axis to cycle through the 4 digits; using the other axis does nothing.  A blinking decimal point shows the current digit position.  When pressing the button, you lock in on the selected digit and enter the second state.
  
  2.  Second state: in this state, the decimal point stays always on, no longer blinking and you can no longer use the axis to cycle through the 4 digits. Instead,  using  the  other  axis, can  increment  or decrement  the  number  on  the  current  digit  IN  HEX  (aka  from  0 to F, as in the lab).  Pressing the button again returns you to the previous state.
  
  3.  Reset:  toggled by long pressing the button only in the first state. When resetting, all the digits go back to 0 and the current positionis set to the first (rightmost) digit, in the first state.
  
  ## Setup
  <img src="https://user-images.githubusercontent.com/79380914/202043012-6ef68322-6f5a-4483-bfa1-ca08b170aaa9.jpeg" width="500" height="300" />
  
  ## Video
  [Watch the video](https://www.youtube.com/watch?v=iYw0XJoFlxs)
</details>
