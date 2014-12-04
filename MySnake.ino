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
Point p4 = {6,4};

Point snakeArray[64] = {p1,p2,p3,p4}; // just keep adding points to array to lengthen snake
// 64 because that is max number of dots snake could be, 64 dots in Meggy

/*
IN THE LOOP:
  1. Draw Snake (coordinates), call drawSnake();
  2. Display Slate, delay 100
  3. Delay (longer delay is easier)
  4. Check Buttons 
  5. Update Snake based on direction (copy values backwards through arrays)
  6. Add segment to snake after apple is eaten, have success action
  7. Repeat from Step 1
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
 Serial.println(p1.x);  // println is print line
 Serial.print("y is ");
 Serial.println(p1.y);
 Serial.println();
 
 
 DrawPx (p1.x,p1.y,Red);
 DrawPx (xapple,yapple,Green);
 DisplaySlate();
 delay(250);
 ClearSlate(); 
 
CheckButtonsDown();
 if (xapple == p1.x) // collision detection (checks if snake hit apple)
 {
    if (yapple == p1.y) // xapple == p1.x must be true as well
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
   p1.x++;
 }
 
 if (dir == 270)
 {
   p1.x--;
 }
 
 if (dir == 0)
 {
   p1.y++;
 }
 
 if (dir == 180)
 {
   p1.y--;
 }
 
 if (p1.x > 7)
 {
   p1.x = 0;
 }
 
 if (p1.y > 7)
 {
   p1.y = 0;
 }
 
 if (p1.x < 0)
 {
   p1.x = 7;
 }
 
 if (p1.y < 0)
 {
   p1.y = 7;
 }
 
}  

void drawSnake()
{
  for (int i = 0; i < marker; i++) // i++ means i plus one
  {
    DrawPx(snakeArray[i].x,snakeArray[i].y,Red);  
  }
}
