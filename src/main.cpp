#include <FastLED.h>
#include "snake.h"
#include "tail.h"

#define LED_TYPE    WS2812B
#define NUM_LEDS    512
#define DATA_PIN    3

#define LEFT_BTN 1
#define UP_BTN 2
#define RIGHT_BTN 4
#define DOWN_BTN 5

CRGB leds[NUM_LEDS];

Snake snake;
Tail tail(8, 8);

volatile int Dir = 4;

void controlLED(int y, int x, CRGB color) 
{
  int ledIndex = x + y * 16;
  leds[ledIndex] = color;
}

void AddApple(int x, int y){
  snake.SetApplePos(x, y);
  controlLED(x, y, CRGB::Yellow);
}

void AddBlockedArea(int x, int y){
  snake.SetArea(x, y);
  controlLED(x, y, CRGB::Blue);
}

void GG()
{
  for(int i = 0; i < 256; i++)
        leds[i] = CRGB::Red;
      
      FastLED.show();
      delay(500);
      for(int i = 0; i < 256; i++)
        leds[i] = CRGB::Black;

      FastLED.show();
      controlLED(8, 8, CRGB::Red);
      AddApple(rand() % 16, rand() % 16);
      AddBlockedArea(rand() % 16, rand() % 16);
      FastLED.show();

      snake.X = 8;
      snake.Y = 8;
      tail.reset();
}

void RemoveColoredLED(){
  controlLED(tail.end_X, tail.end_Y, CRGB::Black);
}

void MoveSnek(int dir){

    // int temp_size = 1;
    // while (temp_size > 0)
    // {
    //   controlLED(snake.X, snake.Y, CRGB::Black);
    //   FastLED.show();
    //   temp_size--;
    // }

    // if (tail.size > 0){
    //   tail.begin_X = snake.X;
    //   tail.begin_Y = snake.Y;
    //   controlLED(tail.begin_X, tail.begin_Y, CRGB::Red);
    // }

    switch(dir){
      case(1):      // Left
        snake.X--;
        break;
      case(2):      // Right
        snake.X++;
        break;
      case(3):      // Up
        snake.Y++;
        break;
      case(4):
        snake.Y--;
        break;      // Down
    }

    if(snake.X < 0 || snake.Y < 0 || snake.X > 15 || snake.Y > 15)
    {
      GG();
    }
}

void ChangeDirU(){
  Dir = 3;
}


ISR (PCINT2_vect) {
  if (!digitalRead(1)) {
    Dir = 1;
  }
  else if (!digitalRead(4)) {
    Dir = 2;
  }
  else if (!digitalRead(5)) {
    Dir = 4;
  }
}


void CheckApple(){
  if(snake.X == snake.GetApplePosX() && snake.Y == snake.GetApplePosY())
  {
    tail.Expand(snake.X, snake.Y);
    AddApple(rand() % 16, rand() % 16);
  }
}

void CheckArea(){
  if(snake.X == snake.GetAreaPosX() && snake.Y == snake.GetAreaPosY())
  {
    GG();
  }
}

// void CheckCollission(){
//   auto tmpTail = tail.GetHistory();
//   if(tmpTail.size() != 0)
//   {
//     for (auto val = 0; val < tmpTail.size() - 1; val++)
//     {
//       if(tmpTail[val].first == snake.X || tmpTail[val].second == snake.Y)
//         GG();
//     }
//   }
// }

void setup() 
{
  srand(0);
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);

  pinMode (LEFT_BTN, INPUT_PULLUP);
  pinMode (UP_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(UP_BTN), ChangeDirU, FALLING);
  pinMode (RIGHT_BTN, INPUT_PULLUP);
  pinMode (DOWN_BTN, INPUT_PULLUP);

  PCICR |= B00000100;
  PCMSK2 |= B00110010;

  controlLED(8, 8, CRGB::Red);
  AddApple(rand() % 16, rand() % 16);
  AddBlockedArea(rand() % 16, rand() % 16);
  FastLED.show();

  snake.X = 8;
  snake.Y = 8;
  
}

void loop() 
{
  tail.Update(snake.X, snake.Y);
  MoveSnek(Dir);
  CheckApple();
  CheckArea();
  // CheckCollission();
  controlLED(snake.X, snake.Y, CRGB::Red);
  RemoveColoredLED();
  auto tmpTail = tail.GetHistory();
  if(tmpTail.size() != 0)
  {
    for (auto val : tmpTail)
    {
      controlLED(val.first, val.second, CRGB::Red);
    }
  }
  FastLED.show();
  delay(500);
}

