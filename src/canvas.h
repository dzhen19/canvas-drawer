/*-----------------------------------------------
 * Author:
 * Date:
 * Description:
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
      TRIANGLES
   };

   struct Vertex
   {
      int x;
      int y;
      Pixel color;
   };

   // struct Line
   // {
   //    Vertex p1;
   //    Vertex p2;
   // };

   // struct Triangle
   // {
   //    Vertex p1;
   //    Vertex p2;
   //    Vertex p3;
   // };

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

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b);

   private:
      Image _canvas;
      std::vector<Vertex> verticesToDraw;
      Pixel currentColor;
      PrimitiveType currentType;
   };
}

#endif
