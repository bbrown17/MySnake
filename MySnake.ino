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

// DID YOU KNOW THAT YOU CAN SELECT A BUNCH OF CODE AND INDENT IT ALL AT ONCE??

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.

// global variables go here
int dir = 0;  // top of compass, possible values are 0, 90, 180, 270
int xapple = random(8);
int yapple = random(8);
int marker = 4; // same number as points in array
boolean gameOver= false;

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
  1. Draw Snake (coordinates), call drawSnake(); then draw Head
  2. Display Slate, delay
  3. Clear Slate
  4. Check Buttons 
  5. Update Snake based on direction (copy values backwards through arrays)
  6. Check if apple is eaten, if true, spawn new apple, increase marker by one
  7. Repeat from Step 1
*/

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code
  Serial.begin(9600);       // helpful code
  
}

void loop()  // run over and over again
{
  if (gameOver == false)
  {
    
   // see variable data 
   updateSnake(); // must be at top of loop so 0,0 glitch doesn't happen
   Serial.print("x is");  // things in quotes show up literally
   Serial.println(p1.x);  // println is print line
   Serial.print("y is ");
   Serial.println(p1.y);
   Serial.println();
 
 
   drawSnake();
   DisplaySlate();
   delay(250);
   ClearSlate(); 
 
 
  CheckButtonsPress();
 
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
     snakeArray[0].x++;
   }
 
   if (dir == 270)
   {
     snakeArray[0].x--;
   }
 
   if (dir == 0)
   {
     snakeArray[0].y++;
   }
 
   if (dir == 180)
   {
     snakeArray[0].y--;
   }
 
   if (snakeArray[0].x > 7)
   {
     snakeArray[0].x = 0;
   }
 
   if (snakeArray[0].y > 7)
   {
     snakeArray[0].y = 0;
   }
 
   if (snakeArray[0].x < 0)
   {
     snakeArray[0].x = 7;
   }
 
   if (snakeArray[0].y < 0)
   {
     snakeArray[0].y = 7;
   }
 
   DrawPx (xapple,yapple,DimRed);
 
   if (xapple == snakeArray[0].x) // collision detection (checks if snake hit apple)
   {
      if (yapple == snakeArray[0].y) // xapple == snakeArray[0].x must be true as well
      { 
      
        Tone_Start(ToneA4, 100); delay(125); // apple eaten music
        Tone_Start(ToneCs5, 100); delay(125);
        Tone_Start(ToneE5, 100); delay(125);
        
        xapple = random(8); // generate new apple
        yapple = random(8);
      
        marker++;    
      }  
   } 
 
  if (snakeCollide())
  {
    gameOver = true;
  }
  }
  
  else // gameOver content in here
  {
    ClearSlate(); // gets rid of any game apples
    Tone_Start(ToneA3, 250); // beeping noise with blinking X
    
    DrawPx(5,5,Red); DrawPx(6,6,Red); // blinking red X
    DrawPx(2,5,Red); DrawPx(1,6,Red);
    
    DrawPx(3,4,Red); DrawPx(4,4,Red); 
    DrawPx(3,3,Red); DrawPx(4,3,Red);
    
    DrawPx(5,2,Red); DrawPx(6,1,Red);
    DrawPx(2,2,Red); DrawPx(1,1,Red);
     
    DisplaySlate();
    delay(250);
    
    ClearSlate(); // creates blinking effect
    DisplaySlate();
    delay(250);
  }
    
 
}  

void drawSnake()
{
  for (int i = 0; i < marker; i++) // i++ means i plus one
  {
    DrawPx(snakeArray[i].x,snakeArray[i].y,Green);  
  }
  
}

void updateSnake()
{
  for (int i = marker -1; i > 0; i--) // -1 makes marker 4 change to 3 at game start
  {
    snakeArray[i] = snakeArray [i-1];
  }
}

boolean snakeCollide()
{
  for (int i = 1; i < marker; i++) // ends game if snake hits itself
  {
    if (snakeArray[0].x == snakeArray[i].x &&
      snakeArray[0].y == snakeArray[i].y)
   
    return true;
  }
    return false;
}
