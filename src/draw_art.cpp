#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char **argv)
{
   Canvas drawer(640, 380);
   // your code here
   Pixel color1 = {0, 0, 0};
   Pixel color2 = {255, 255, 255};
   drawer.background(color1, color2, VERTICAL);
   drawer.save("line-color-interpolation.png");

   // void Canvas::background(Pixel color1, Pixel color2, DirectionType direction)
}
