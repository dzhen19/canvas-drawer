#include <iostream>
#include <math.h>
#include "canvas.h"
using namespace std;
using namespace agl;

Pixel getRandomColor(bool monochrome)
{
   Pixel randomColor;
   float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   float r3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

   randomColor = {static_cast<unsigned char>(r1 * 255),
                  static_cast<unsigned char>(r2 * 255),
                  static_cast<unsigned char>(r3 * 255)};

   if (monochrome)
   {
      randomColor = {static_cast<unsigned char>(r1 * 255),
                     static_cast<unsigned char>(r1 * 255),
                     static_cast<unsigned char>(r1 * 255)};
   }
   return randomColor;
}

Vertex getRandomPoint(int maxX, int maxY)
{
   Pixel white = {255, 255, 255};

   float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   Vertex randomPoint = {static_cast<int>(r1 * maxX),
                         static_cast<int>(r2 * maxY),
                         white};
   return randomPoint;
}

// get n points along the unit circle (for n-1 sided polygon)
void drawUnitCirclePoints(int n, int w, int h, Canvas *drawer)
{
   int radius = min(w, h) / 2 - 50;
   int xOffset = w / 2;
   int yOffset = h / 2;
   // counter is purely for coloring
   int counter = 0;
   float x;
   float y;

   drawer->begin(CONVEXPOLYGON);
   Pixel randomColor = getRandomColor(false);
   drawer->color(randomColor.r, randomColor.g, randomColor.b);
   for (int i = 0; i < n; i++)
   {
      x = (sin((float)i / (float)n * 2 * M_PI) * radius) + xOffset;
      y = (cos((float)i / (float)n * 2 * M_PI) * radius) + yOffset;
      // std::cout << "x: " << x << ", y: " << y << std::endl;
      if (counter == 2)
      {
         // set color so that every triangle is differently colored
         randomColor = getRandomColor(false);
         drawer->color(randomColor.r, randomColor.g, randomColor.b);
         counter = 0;
      }
      drawer->vertex(x, y);
      counter++;
   }
   drawer->end();
}

int main(int argc, char **argv)
{
   int w = 400;
   int h = 300;
   Canvas drawer(w, h);
   // your code here
   Pixel color1 = {16, 0, 43};
   Pixel color2 = {90, 24, 154};
   drawer.background(color1, color2, VERTICAL);
   drawer.save("bg.png");

   // draw points demo
   drawer.begin(POINTS);
   for (int i = 0; i < 1000; i++)
   {
      Pixel randomColor = getRandomColor(true);
      drawer.color(randomColor.r, randomColor.g, randomColor.b);
      Vertex p = getRandomPoint(w, h);
      drawer.vertex(p.x, p.y);
   }
   drawer.end();
   drawer.save("space.png");

   int circleRadius = 100;
   int numSubCircles = 5;
   int minSubCircleRadius = 1;
   int pixDecrement = (circleRadius - minSubCircleRadius) / numSubCircles;

   // draw circle demo
   drawer.begin(CIRCLES);
   for (int i = 0; i < 100; i++)
   {
      Pixel randomColor;
      Vertex p = getRandomPoint(w, h);

      for (int j = 0; j < numSubCircles; j++)
      {
         randomColor = getRandomColor(false);
         drawer.color(randomColor.r, randomColor.g, randomColor.b);
         drawer.vertex(p.x, p.y);
         drawer.radius(circleRadius - pixDecrement * j);
      }
   }
   drawer.end();
   drawer.save("circles.png");

   // draw convex polygon demo

   for (int i = 4; i < 13; i++)
   {
      // i'm going for a space theme here
      drawer.background(0, 0, 0);
      drawer.begin(POINTS);
      for (int i = 0; i < 1000; i++)
      {
         Pixel randomColor = getRandomColor(true);
         drawer.color(randomColor.r, randomColor.g, randomColor.b);
         Vertex p = getRandomPoint(w, h);
         drawer.vertex(p.x, p.y);
      }
      drawer.end();

      drawUnitCirclePoints(i, w, h, &drawer);
      // string name = std::format("{0}_lygon", i);
      drawer.save(std::to_string(i) + ".png");
   }

   // draw rose demo
   // drawer.drawRose();
}
