#include <iostream>
#include "canvas.h"
#include <cassert>
#include <math.h>
#include <vector>

using namespace std;
using namespace agl;

Canvas::Canvas(int w, int h) : _canvas(w, h)
{
   Pixel white = {255, 255, 255};
   currentColor = white;
}

Canvas::~Canvas()
{
}

void Canvas::save(const std::string &filename)
{
   _canvas.save(filename);
}

void Canvas::begin(PrimitiveType type)
{
   currentType = type;
}

Pixel interpolateColor(Pixel startColor, Pixel endColor, float t)
{
   // std::cout << t << std::endl;
   Pixel newColor = {
       static_cast<unsigned char>(startColor.r * (1 - t) + endColor.r * (t)),
       static_cast<unsigned char>(startColor.g * (1 - t) + endColor.g * (t)),
       static_cast<unsigned char>(startColor.b * (1 - t) + endColor.b * (t)),
   };
   return newColor;
}

void drawLineLow(Vertex a, Vertex b, Image *canvas)
{
   float dist = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));

   int y = a.y;
   int w = b.x - a.x;
   int h = b.y - a.y;
   int dy = 1;
   if (h < 0)
   {
      dy = -1;
      h = -h;
   }
   int f = 2 * h - w;
   for (int x = a.x; x <= b.x; x++)
   {
      // color interpolation
      float drawnDist = sqrt(pow((x - a.x), 2) + pow((y - a.y), 2));
      float t = drawnDist / dist;

      canvas->set(y, x, interpolateColor(a.color, b.color, t));
      if (f > 0)
      {
         y += dy;
         f += 2 * (h - w);
      }
      else
      {
         f += 2 * h;
      }
   }
}

void drawLineHigh(Vertex a, Vertex b, Image *canvas)
{
   float dist = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));

   int x = a.x;
   int w = b.x - a.x;
   int h = b.y - a.y;
   int dx = 1;
   if (w < 0)
   {
      dx = -1;
      w = -w;
   }
   int f = 2 * w - h;
   for (int y = a.y; y <= b.y; y++)
   {
      float drawnDist = sqrt(pow((x - a.x), 2) + pow((y - a.y), 2));
      float t = drawnDist / dist;

      // std::cout << "dist: " << dist << " drawn: " << drawnDist << std::endl;
      // std::cout << "set r: " << y << "c: " << x << std::endl;
      // std::cout << "r: " << newColor.r << "g: " << newColor.g << "b: " << newColor.b << std::endl;
      canvas->set(y, x, interpolateColor(a.color, b.color, t));
      if (f > 0)
      {
         x += dx;
         f += 2 * (w - h);
      }
      f += 2 * w;
   }
}

void drawLine(Vertex a, Vertex b, Image *canvas)
{
   // std::cout << "drawLine" << std::endl;
   // std::cout << "ax " << a.x << " ay: " << a.y << std::endl;
   // std::cout << "bx " << b.x << " by: " << b.y << std::endl;
   Vertex temp;

   int w = b.x - a.x;
   int h = b.y - a.y;
   if (abs(h) < abs(w))
   {
      if (a.x > b.x)
      {
         temp = a;
         a = b;
         b = temp;
      }
      drawLineLow(a, b, canvas);
   }
   else
   {
      if (a.y > b.y)
      {
         temp = a;
         a = b;
         b = temp;
      }
      drawLineHigh(a, b, canvas);
   }
}

// draw everything to canvas
void Canvas::end()
{
   if (verticesToDraw.empty())
   {
      return;
   }

   if (currentType == LINES)
   {
      int numVertices = verticesToDraw.size();
      if (numVertices % 2 != 0)
      {
         std::cout << "#vertices for line drawing not divisible by 2" << std::endl;
         return;
      }

      for (int i = 0; i < numVertices / 2; i++)
      {
         Vertex a = verticesToDraw[2 * i];
         Vertex b = verticesToDraw[(2 * i) + 1];
         drawLine(a, b, &_canvas);
      }

      verticesToDraw.clear();
   }
}

// add vertex onto verticesToDraw
void Canvas::vertex(int x, int y)
{
   Vertex vertex = {x, y, currentColor};
   verticesToDraw.push_back(vertex);
}

void Canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
   Pixel color = {r, g, b};
   currentColor = color;
}

void Canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
   Pixel color = {r, g, b};
   _canvas.fill(color);
}
