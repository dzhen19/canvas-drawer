#include <iostream>
#include "canvas.h"
#include <cassert>
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

// draw everything to canvas
void Canvas::end()
{
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
