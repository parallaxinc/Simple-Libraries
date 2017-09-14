/*
  Shooter.c

  A simple asteroids-like demonstration
  
*/

#include "simpletools.h"                     // Include simpletools library

#include "badgetools.h"                      // Include badgetools library
#include "Shooter.h"


// Function declarations, so the compiler knows these are coming
void Init(void);
void GameLoop(void);
void Play(void);
void Draw(void);


//Constant values for various things about the game
const int Height = 26;      // Height of half the play area
const int Width = 63;       // Width of half the play area
const int VCenter = 27;     // Vertical center of the play area
const int HCenter = 63;     // Horizontal center of the play area
const int RotSpeed = 128;   // Rotation step for the ship when turning

#define  MaxShots  6        // maximum number of shots in flight at once
#define  ShotLen   4        // length in pixels of the shot
#define  ShotDelay 3        // updates before you can shoot again


int ShipAng = 0;            // Current direction of the ship

SHOT Shots[MaxShots];       // Array of SHOT structs, hold information about shots in-flight
char FreeShots = MaxShots;  // How many shots there are in the Shots array
char UsedShots = 0;         // How many we've used
char ShotTimer = 0;         // How many are left (this didn't have to be two variables, but it's easier to read this way)


void main()                   // Main function (standard C entry point)
{
  badge_setup();              // Call badge setup

  Init();                     // Initialize the game board
  GameLoop();                 // Run the game loop
}


// Set up some global things
void Init(void)
{
  screen_auto(0);       // Set the screen not to auto-update (we want to control it)
  text_size(SMALL);     // Set the text size

  UsedShots = 0;        // No shots currently active
  FreeShots = MaxShots;
}


void GameLoop(void)
{
   while(1)     // Repeat forever
   {
    Play();     // Update the game state
    Draw();     // Draw the game board

    pause(20);  // Slow the frame rate a little
  }
}


// Use the built-in SINE table in the Propeller to return a Sin value from -0xffff to +0xffff
// for angle values in the range of 0x0000 to 0x1fff being 0 to 360 degrees.  Values outside of
// this range are allowed, and will just wrap around.
int Sin(int a)
{
  if( a & 0x800 ) {
    a = 0x1000 - a;
  }
  int s = ((unsigned short *)0xe000)[a & 0xfff];
  if( a & 0x1000 ) {
    s = -s;
  }
  return s;    
}

// Return a cosine value in the same way (and same ranges) as Sin() above
int Cos(int a)
{
  return Sin( a + 0x800 );
}

// Rotate an input vector (coordinate) around the origin by the angle (a)
// stores the result in the variables pointed to by nx and ny
// The angle (a) has a range of 0 to 0x1fff (8191).  Values outside this
// range are allowed, but will simply wrap around.  All inputs are integers
// and the math is done using fixed-point multiplication with rounding.

void Rotate(int x, int y, int a, int * nx, int * ny)
{
  int cs = Cos(a), sn = Sin(a);
  *nx = ((cs * x) - (sn * y) + 32768) / 65536;
  *ny = ((sn * x) + (cs * y) + 32768) / 65536;
}


// Draw a Ship (ok, it's really just a triangle)

void DrawShip(void)
{
  // These are the coordinates of the ship
  int xc[] = { 0,  4,  0, -4};
  int yc[] = {-5,  5,  3,  5};

  int x[4], y[4];
  for( int i=0; i<4; i++ )
  {
    // rotate the input coordinates of the ship to the correct orienation
    Rotate( xc[i], yc[i], ShipAng, &x[i], &y[i] );

    // add the offset for the center of the screen to position it in the middle of the display
    x[i] += HCenter;
    y[i] += VCenter;
  }

  // Draw the lines connecting the rotated result points
  line( x[0], y[0], x[1], y[1], 1 );
  line( x[1], y[1], x[2], y[2], 1 );
  line( x[2], y[2], x[3], y[3], 1 );
  line( x[3], y[3], x[0], y[0], 1 );
}


void Shoot(void)
{
  // Make sure we have a free slot to store the shot info in, and we're allowed to shoot (timer is zero)
  if( FreeShots == 0 || ShotTimer != 0 ) return;

  // This shot starts at the center of the screen
  Shots[UsedShots].dist = 0;

  // Since the ship doesn't use all the precision for what angle it's at, we don't need to
  // store that for the shots, either.  I chop off the bottom 7 bits so I can fit it into a char
  Shots[UsedShots].ang = ShipAng >> 7;

  // Keep track of how many shots are active, and how many free ones are available
  UsedShots++;
  FreeShots--;

  // Set a timer so we can't shoot again immediately
  ShotTimer = ShotDelay;
}


// This is probably the most complicated thing in the code.  In order to simplify storing the shots,
// and make their movement reasonably accurate, I just store how far from the center they are (dist)
// and what angle they were fired at.  The only thing to "move" is the distance, but it makes checking
// to see if the shot has gone off the playfield a little harder, because we have to rotate each shot
// by the angle and figure out if the result is off the display.

void MoveShot( int i )
{
  // We're going to test if the far end of the shot is off the screen yet (that's why we add ShotLen)
  int dist = Shots[i].dist + ShotLen + 1;

  int a = Shots[i].ang << 7;  // scale the angle value back up from when we stored it

  // Compute the rotated location of the shot
  int x = ( Sin(a) * dist + 32768) / 65536;
  int y = (-Cos(a) * dist + 32768) / 65536;

  // If the rotated x or y are outside the range of the display, the shot has gone off the screen
  if( abs(x) >= Width || abs(y) >= Height )
  {
    // out of bounds - remove this shot from the active list
    UsedShots--;
    FreeShots++;

    // Do we still have any shots that are active?
    if( UsedShots )
    {
      // Copy the data for the LAST active shot into this spot in the shots array
      // This compacts the list.
      memcpy( Shots + i, Shots + UsedShots, sizeof(SHOT) );

      // Because we just moved the LAST shot in the list to this spot in the Shots array,
      // the moved entry would get skipped by the updating code, because it has no idea
      // that we changed the list order.  We call MoveShot AGAIN, on the updated entry, so it doesn't get missed.
      // This is overkill for a simple demo, but it's good to know that this kind of thing happens.  :)
      MoveShot( i );
    }
  }
  else
  {
    Shots[i].dist = dist;
  }
}

// Iterate through the list of currently active shots and move them
void MoveShots(void)
{
  for( int i=0; i<UsedShots; i++ ) {
    MoveShot(i);
  }
}

// Iterate through the list of active shots and draw them
void DrawShots(void)
{
  for( int i=0; i<UsedShots; i++ )
  {
    int x0, y0, x1, y1;
    int d0 = Shots[i].dist;
    int d1 = d0 + ShotLen;

    int a = Shots[i].ang << 7;
    int cs = -Cos(a), sn = Sin(a);

    x0 = ((sn * d0) + 32768) / 65536 + HCenter;
    y0 = ((cs * d0) + 32768) / 65536 + VCenter;
    x1 = ((sn * d1) + 32768) / 65536 + HCenter;
    y1 = ((cs * d1) + 32768) / 65536 + VCenter;

    line( x0, y0, x1, y1, 1 );
  }
}


// Get player input, rotate the ship, fire shots, move active shots
void Play(void)
{
  int But = buttons();
  
  if( But & (1<<2) )
  {
    led(2,1);
    ShipAng = (ShipAng + RotSpeed) & 0x1fff;
  }
  else
    led(2,0);

  if( But & (1<<0) )
  {
    led(0,1);
    ShipAng = (ShipAng - RotSpeed) & 0x1fff;
  }
  else
    led(0,0);


  if( ShotTimer > 0 ) {
    ShotTimer--;
  }    

  if( But & ((1<<1) | (1<<4)) ) {
    Shoot();
  }

  MoveShots();
}

// Draw our little universe
void Draw(void)
{
  clear();

  DrawShip();
  DrawShots();

  screen_update();
}

