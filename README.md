# Introduction to Robotics
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

# Homework 1
  Use a separat potentiometer in controlling each of the color of the RGB led (*R*ed, *G*reen and *B*lue).  The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connectedto the led.
  
## Setup

  <img src="https://user-images.githubusercontent.com/79380914/197886843-1d80908d-0ce9-43b8-aeb9-123c700270a8.jpeg" width="570" height="426" />

## Video
  [Watch the video](https://youtu.be/uTKtmfkYtcI)
  
# Homework 2
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

# Homework 3
  TBA
