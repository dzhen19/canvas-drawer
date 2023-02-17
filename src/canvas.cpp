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

Pixel interpolateLineColor(Pixel startColor, Pixel endColor, float t)
{
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
      float drawnDist = sqrt(pow((x - a.x), 2) + pow((y - a.y), 2));
      float t = drawnDist / dist;

      canvas->set(y, x, interpolateLineColor(a.color, b.color, t));
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

      canvas->set(y, x, interpolateLineColor(a.color, b.color, t));
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

void drawTriangle(Vertex a, Vertex b, Vertex c, Image *canvas)
{
   int minX = std::min({a.x, b.x, c.x});
   int maxX = std::max({a.x, b.x, c.x});
   int minY = std::min({a.y, b.y, c.y});
   int maxY = std::max({a.y, b.y, c.y});

   for (int x = minX; x <= maxX; x++)
   {
      for (int y = minY; y <= maxY; y++)
      {
         float alpha = float((b.y - c.y) * x + (c.x - b.x) * y + b.x * c.y - c.x * b.y) /
                       float((b.y - c.y) * a.x + (c.x - b.x) * a.y + b.x * c.y - c.x * b.y);

         float gamma = float((a.y - b.y) * x + (b.x - a.x) * y + a.x * b.y - b.x * a.y) /
                       float((a.y - b.y) * c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y);

         float beta = 1 - alpha - gamma;

         if (alpha > 0 && beta > 0 && gamma > 0)
         {
            Pixel color = {static_cast<unsigned char>(alpha * a.color.r + beta * b.color.r + gamma * c.color.r),
                           static_cast<unsigned char>(alpha * a.color.g + beta * b.color.g + gamma * c.color.g),
                           static_cast<unsigned char>(alpha * a.color.b + beta * b.color.b + gamma * c.color.b)};

            canvas->set(y, x, color);
         }
      }
   }
}

void Canvas::end()
{
   int numVertices = verticesToDraw.size();

   if (numVertices == 0)
   {
      return;
   }

   if (currentType == LINES)
   {
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
   }

   if (currentType == TRIANGLES)
   {
      if (numVertices % 3 != 0)
      {
         std::cout << "#vertices for triangle drawing not divisible by 3" << std::endl;
         return;
      }

      for (int i = 0; i < numVertices / 3; i++)
      {
         Vertex a = verticesToDraw[3 * i];
         Vertex b = verticesToDraw[(3 * i) + 1];
         Vertex c = verticesToDraw[(3 * i) + 2];
         drawTriangle(a, b, c, &_canvas);
      }
   }

   verticesToDraw.clear();
}

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
