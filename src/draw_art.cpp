#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

Pixel getRandomColor()
{
   float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   float r3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
   Pixel randomColor = {static_cast<unsigned char>(r1 * 255),
                        static_cast<unsigned char>(r2 * 255),
                        static_cast<unsigned char>(r3 * 255)};
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

int main(int argc, char **argv)
{
   int w = 640;
   int h = 380;
   Canvas drawer(w, h);
   // your code here
   Pixel color1 = {0, 0, 0};
   Pixel color2 = {0, 0, 0};
   drawer.background(color1, color2, VERTICAL);

   drawer.begin(POINTS);
   for (int i = 0; i < 100; i++)
   {
      Pixel randomColor = getRandomColor();
      drawer.color(randomColor.r, randomColor.g, randomColor.b);
      Vertex p = getRandomPoint(w, h);
      drawer.vertex(p.x, p.y);
   }
   drawer.end();
   drawer.save("art.png");
}
