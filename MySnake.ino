/*
  MySnake.pde
  
 ######  ##    ##    ###    ##    ## ######## 
##    ## ###   ##   ## ##   ##   ##  ##       
##       ####  ##  ##   ##  ##  ##   ##       
 ######  ## ## ## ##     ## #####    ######   
      ## ##  #### ######### ##  ##   ##       
##    ## ##   ### ##     ## ##   ##  ##       
 ######  ##    ## ##     ## ##    ## ######## 

   _________         _________
  /         \       /         \   Brennan
 /  /~~~~~\  \     /  /~~~~~\  \ (bbrown17)
 |  |     |  |     |  |     |  |
 |  |     |  |     |  |     |  |
 |  |     |  |     |  |     |  |         /
 |  |     |  |     |  |     |  |       //
(o  o)    \  \_____/  /     \  \_____/ /
 \__/      \         /       \        /
  |         ~~~~~~~~~         ~~~~~~~~
  ^ 
  
 
  A simple Snake game.

*/
   
// Arrays Tutorial: http://arduino.cc/en/Reference/Array


#include <MeggyJrSimple.h>    // Required code, line 1 of 2.

// global variables go here
int xplayer = 3;  // coordinates of player dot
int yplayer = 4; 
int dir = 0;  // top of compass, possible values are 0, 90, 180, 270
int xapple = random(8);
int yapple = random(8);
int marker = 3;

struct Point
{
  int x;
  int y;
};

Point p1 = {3,4}; // address by saying p1.x or p1.y, ex: p1.x = 3
Point p2 = {4,4};
Point p3 = {5,4};

Point snakeArray[64] = {p1,p2,p3}; // just keep adding points to array to lengthen snake


/*
IN THE LOOP:
  1. Draw Player (coordinates), call drawSnake();
  2. Display Slate, delay 100
  3. Check Buttons
  4. Update Direction if button is pressed
  5. Update Player based on direction
  6. Correct for Wrapping
  7. Change from xplayer yplayer to Array to have same function
*/

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code
  Serial.begin(9600);       // helpful code
  
}

void loop()  // run over and over again
{
 // see variable data 
  
 Serial.print("x is");  // things in quotes show up literally
 Serial.println(xplayer);  // println is print line
 Serial.print("y is ");
 Serial.println(yplayer);
 Serial.println();
 
 
 DrawPx(xplayer,yplayer,Red);
 DrawPx (xapple,yapple,Green);
 DisplaySlate();
 delay(250);
 ClearSlate(); 
 
CheckButtonsDown();
 if (xapple == xplayer) // collision detection (checks if snake hit apple)
 {
    if (yapple == yplayer) // xapple == xplayer must be true as well
    { 
      Tone_Start(ToneA4, 100); delay(125); // apple eaten music
      Tone_Start(ToneCs5, 100); delay(125);
      Tone_Start(ToneE5, 100); delay(125);
      
      xapple = random(8); // generate new apple
      yapple = random(8);    
    }  
 }
 
 if (Button_Right)
 {
   dir = 90;
 }
 
 if (Button_Left)
 {
   dir = 270;
 }
 
 if (Button_Up)
 {
   dir = 0;
 }
 
 if (Button_Down)
 {
   dir = 180;
 }
 
 if (dir == 90)
 {
   xplayer++;
 }
 
 if (dir == 270)
 {
   xplayer--;
 }
 
 if (dir == 0)
 {
   yplayer++;
 }
 
 if (dir == 180)
 {
   yplayer--;
 }
 
 if (xplayer > 7)
 {
   xplayer = 0;
 }
 
 if (yplayer > 7)
 {
   yplayer = 0;
 }
 
 if (xplayer < 0)
 {
   xplayer = 7;
 }
 
 if (yplayer < 0)
 {
   yplayer = 7;
 }
 
}  

void drawSnake()
{
  for (int i = 0; i < marker; i++)
  {
    DrawPx(snakeArray[i].x,snakeArray[i].y,Red);  
  }
}
