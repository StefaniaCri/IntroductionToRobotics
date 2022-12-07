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

<summary>Menu for a 8x8 matrix game</summary>
<br>
Create a menu for your game, emphasis on the game.  The player should scroll on the LCD with the joystick.    The menu should include the following functionality:
1.  When powering up a game, a greeting message should be shown fora few moments.2.  Should contain roughly the following categories:
  <br>
  (a)Start game, starts the initial level of your game [done]
  <br>
(b)Highscore: [not done, TO DO list]
–Initially, we have 0. <br>
–Update  it  when  the  game  is  done. <br>   
Highest  possible  score should be achieved by starting at a higher level. <br>
–Save the top 5+ values in EEPROM with name and score. <br>
<br>
(c)Settings:<br>

–Enter name. The name should be shown in highscore. [Buggy right now]<br>
–Starting  level:  Set  the  starting  level  value.   The  idea  is  to be able to start from a higher level as well.  Can be replaced with difficulty.<br>
–LCD contrast control (optional, it replaces the potentiometer).  Save it to eeprom.<br>
–LCD brightness control (mandatory, must change LED wirethat’s directly connected to 5v).Save it to eeprom.<br>
[Both lcd contrast need an setup change => TO DO] <br>

–Matrix brightness control (see function setIntesnity from the ledControl library).  Save it to eeprom.[done]<br>
–Sounds on or off.Save it to eeprom.[done]  <br>
  

(d)About: should include details about the creator(s) of the game.At least game name, author and github link or user (use scrollingtext?)(e)How to play:short and informative description [done]

3.While playing the game:display all relevant info
  –Lives [done]
  –Level [done]
  –Score [done]
  –Time? [partially done]
  –Player name?–etc [todo]

4.Upon game ending:<br>
  (a)  Screen 1: a message such as ”Congratulations on reaching level/scoreX”.  ”You did better than y people.”.  etc.<br>
  Switches to screen 2upon interaction (button press) or after a few moments.<br>
  (b)  Screen 2:  display relevant game info:  score, time, lives left etc.Must  inform  player  if  he/she  beat  the  highscore.<br>
  This menu should only be closed by the player, pressing a button. [not yet implemented]
  
  ## Setup
  <img src="https://user-images.githubusercontent.com/79380914/206221101-3e52766d-0f9c-401c-8838-2542f8d69169.jpg" width="397" height="530" />
   A mess I know. Need to be improved.
  
  ## Video
  [Watch the video](https://youtu.be/JZQMg5Ia4RE)

</details>


