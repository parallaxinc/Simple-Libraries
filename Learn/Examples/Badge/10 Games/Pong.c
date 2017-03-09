/*
   Box and Lines.c
   Box and line functions have parameters of xi, yi, xf, yf, color.  
   Valid x ranges are 0 to 127, and valid y ranges are 0 to 63.  These
   pixel counts are measured from the top-left.  The color is just one 
   bit, with 1 indicating white and 0 black.  Pixel counts are measured 
   from the top-left.   
*/

#include "simpletools.h"                     // Include simpletools library
#include "badgetools.h"                      // Include badgetools library


// Function declarations, so the compiler knows these are coming
void Init(void);
void GameLoop(void);
void Play(void);
void Draw(void);
void Reset(void);

//Constant values for various things about the game
const int PadLen = 3;
const int Height = 26;
const int Width = 63;

const int VCenter = 27;
const int HCenter = 63;
const int PadRow = 59;

const int PadStep = 2;


// Variables
int Paddle[2] = {0,0};        // Positions of the two paddles
int Score[2]  = {0,0};        // Scores for the two players

int BallX = 0, BallY = 0;     // Location of the ball
int BallDx = 2, BallDy = 1;   // Speed / direction of the ball
int GameMode = 0;             // 0 = playing, 1 = resetting
int AutoMode = 1;


void main()                   // Main function (standard C entry point)
{
  badge_setup();              // Call badge setup
  Init();                     // Initialize the game board
  GameLoop();                 // Run the game loop
}


// Set up some global things
void Init(void)
{
  screen_auto(0);     // Set the screen not to auto-update (we want to control it)
  text_size(SMALL);   // Set the text size
}


// Main game loop
void GameLoop(void)
{
   while(1)     // Repeat forever
   {
    switch( GameMode )
    {
    case 0:     // Mode 0 is normal gameplay
      Play();   // Update the game state
      Draw();   // Draw the game board
      break;

    case 1:
      Reset();  // Reset the game (score, paddles, ball, etc)
      break;
    }

    pause(20);  // Slow the frame rate down a little
  }
}


void Play(void)
{
  // Cache the value of all pad buttons in one call.  This is less readable than checking
  // the Button(x) function per button, but it's also MUCH faster.  The Button(x) function
  // does some work internally, and doing it for all buttons at once instead of per-button
  // makes the frame rate much faster.  The (1<<x) notation you'll see after this is testing
  // for individual bits in the But variable, each corresponding to a single button state.
  int But = buttons();

  // switch modes between two player and self-playing if the OSH (center) button is pressed
  if( But & (1<<6) ) {
    AutoMode ^= 1;
    GameMode = 1;
    pause(50);
    return;
  }

  // If in two-player mode...
  if( AutoMode == 0 )
  {
    // Turn off the two middle LEDs - off indicates two player mode
    led(1,0);
    led(4,0);

    if( But & (1<<3) )
    {
      led(3,1);
      if( (Paddle[0] + PadStep) < Height )
        Paddle[0] += PadStep;
    }
    else
    {
      led(3,0);
    }    
    
    if( But & (1<<5) )
    {
      led(5,1);
      if( (Paddle[0] - PadStep) > -Height )
        Paddle[0] -= PadStep;
    }
    else
    {
      led(5,0);
    }    
  
  
    if( But & (1<<2) )
    {
      led(2,1);
      if( (Paddle[1] + PadStep) < Height )
        Paddle[1] += PadStep;
    }
    else
    {
      led(2,0);
    }    
  
    if( But & (1<<0) )
    {
      led(0,1);
      if( (Paddle[1] - PadStep) > -Height )
        Paddle[1] -= PadStep;
    }
    else
    {
      led(0,0);
    }
  }

  // If in self-playing mode...
  if( AutoMode == 1 )
  {
    // Turn on the two middle LEDs - on indicates self-playing mode
    led(1,1);
    led(4,1);

    if( BallDx < 0 ) {  // moving toward player 0
      if( BallY < Paddle[0] )
        Paddle[0] -= PadStep;
      if( BallY > Paddle[0] )
        Paddle[0] += PadStep;
    }

    if( BallDx > 0 ) {  // moving toward player 1
      if( BallY < Paddle[1] )
        Paddle[1] -= PadStep;
      if( BallY > Paddle[1] )
        Paddle[1] += PadStep;
    }
  }


  // Check to see if the ball is going to cross the left player paddle (Player 0)
  if( BallX > -PadRow && (BallX+BallDx) <= -PadRow )
  {
    if( BallY >= (Paddle[0]-PadLen) &&
        BallY <= (Paddle[0]+PadLen) &&
       (BallY+BallDy) >= (Paddle[0]-PadLen) &&
       (BallY+BallDy) <= (Paddle[0]+PadLen) )
     {
       BallDx = -BallDx;
     }         
  }


  // Check to see if the ball is going to cross the right player paddle (Player 1)
  if( BallX < PadRow && (BallX+BallDx) >= PadRow )
  {
    if( BallY >= (Paddle[1]-PadLen) &&
        BallY <= (Paddle[1]+PadLen) &&
       (BallY+BallDy) >= (Paddle[1]-PadLen) &&
       (BallY+BallDy) <= (Paddle[1]+PadLen) )
     {
       BallDx = -BallDx;
     }         
  }

  // Check for collisions against the side walls
  if( BallY <= -Height )
  {
    BallDy = -BallDy;
  }
  else if( BallY >= Height )
  {
    BallDy = -BallDy;
  }

  BallX += BallDx;
  BallY += BallDy;

  // Check to see if Player 0 has scored (ball has gone off the right)
  if( BallX > Width )
  {
    // Score player 0
    rgb(R,RED);
    Score[0]++;
    BallX = BallY = 0;
    pause(100);
    rgb(R,OFF);

    if( Score[0] == 10 )
    {
      AutoMode = 1;
      GameMode = 1;
    }      
  }
  // Check to see if Player 1 has scored (ball has gone off the left)
  else if( BallX < -Width )
  {
    // Score player 1
    rgb(L,RED);
    Score[1]++;
    BallX = BallY = 0;
    pause(100);
    rgb(L,OFF);

    if( Score[1] == 10 )
    {
      AutoMode = 1;
      GameMode = 1;
    }      
  }
}


void Draw(void)
{
  clear();

  cursor(6, 7);
  string("Score");

  cursor(0, 7);
  letter( '0' + Score[0] );

  cursor(15, 7);
  letter( '0' + Score[1] );

  box(0, 1, Width*2, Height*2+1, 1);
  point(BallX + HCenter, BallY + VCenter, 1);
  line( HCenter-PadRow, VCenter + Paddle[0] - PadLen,  HCenter-PadRow, VCenter + Paddle[0] + PadLen, 1 );
  line( HCenter+PadRow, VCenter + Paddle[1] - PadLen,  HCenter+PadRow, VCenter + Paddle[1] + PadLen, 1 );

  screen_update();
}


void Reset(void)
{
  GameMode = 0;
  Score[0]  = Score[1] = 0;
  Paddle[0] = Paddle[1] = 0;
}
