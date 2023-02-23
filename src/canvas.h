/*-----------------------------------------------
 * Author: Derrick Zhen
 * Date: 2/16/23
 * Description: This is the header file for the Canvas class and Vertex struct
 ----------------------------------------------*/

#ifndef canvas_H_
#define canvas_H_

#include <string>
#include <vector>
#include "image.h"

namespace agl
{
   enum PrimitiveType
   {
      UNDEFINED,
      LINES,
      TRIANGLES,
      POINTS,
      CIRCLES,
      CONVEXPOLYGON,
   };

   enum DirectionType
   {
      HORIZONTAL,
      VERTICAL
   };

   struct Vertex
   {
      int x;
      int y;
      Pixel color;
   };

   class Canvas
   {
   public:
      Canvas(int w, int h);
      virtual ~Canvas();

      // Save to file
      void save(const std::string &filename);

      // Draw primitives with a given type (either LINES or TRIANGLES)
      // For example, the following draws a red line followed by a green line
      // begin(LINES);
      //    color(255,0,0);
      //    vertex(0,0);
      //    vertex(100,0);
      //    color(0,255,0);
      //    vertex(0, 0);
      //    vertex(0,100);
      // end();
      void begin(PrimitiveType type);
      void end();

      // Specifiy a vertex at raster position (x,y)
      // x corresponds to the column; y to the row
      void vertex(int x, int y);

      void radius(int r);

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with gradient
      void background(Pixel color1, Pixel color2, DirectionType direction);

      void drawRose();

   private:
      Image _canvas;
      std::vector<Vertex> verticesToDraw;
      std::vector<int> radiiToDraw;
      Pixel currentColor;
      PrimitiveType currentType;
   };
}

#endif
