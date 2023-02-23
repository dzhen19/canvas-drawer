# canvas-drawer

Implements a simple drawing api

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake -G "Visual Studio 16 2019" ..
canvas-drawer/build $ start Draw-2D.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
canvas-drawer/build $ ../bin/Debug/draw_test
canvas-drawer/build $ ../bin/Debug/draw_art
```

*macOS*

Open terminal to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake ..
canvas-drawer/build $ make
```

To run each program from build, you would type

```
canvas-drawer/build $ ../bin/draw_test
canvas-drawer/build $ ../bin/draw_art
```

## Supported primitives

The following primitives are supported: 
```
enum PrimitiveType
{
   UNDEFINED,
   LINES,
   TRIANGLES,
   POINTS,
   CIRCLES,
   CONVEXPOLYGON,
};
```

In addition, rose curves can be drawn using many lines. 

## Results

### Image 1: Space

#### Set background gradient
```
Pixel color1 = {16, 0, 43};
Pixel color2 = {90, 24, 154};
drawer.background(color1, color2, VERTICAL);
```
![bg](https://user-images.githubusercontent.com/55254786/221039783-66689787-e075-4d67-b296-3dd15d69b995.png)

#### Generate Points 
```
drawer.begin(POINTS);
  for (int i = 0; i < 1000; i++)
  {
     Pixel randomColor = getRandomColor(true); // gets monochrome color
     drawer.color(randomColor.r, randomColor.g, randomColor.b);
     Vertex p = getRandomPoint(w, h);
     drawer.vertex(p.x, p.y);
  }
```
![space](https://user-images.githubusercontent.com/55254786/221040245-aa3004a4-0227-4a02-ba88-294722e75d88.png)


### Image 2: Circles
#### Draw circles and subcircles
```
drawer.begin(CIRCLES);
for (int i = 0; i < 100; i++)
{
   Vertex p = getRandomPoint(w, h);
   for (int j = 0; j < numSubCircles; j++)
   {
      randomColor = getRandomColor(false);
      drawer.color(randomColor.r, randomColor.g, randomColor.b);
      drawer.vertex(p.x, p.y);
      drawer.radius(circleRadius - pixDecrement * j);
   }
}
```
![circles](https://user-images.githubusercontent.com/55254786/221040755-244dcce0-4418-4777-adc8-8fb4d55151f9.png)

### Image 3: Convex Polygons
(Disclaimer) Each individual polygon was created by `draw_art.cpp`, but I put them together using google slides
```
void drawConvexPolygon(vector<Vertex> verticesToDraw, Image *canvas)
{
   int numVertices = verticesToDraw.size();
   int a = 0;
   int b = 1;
   int c = 2;
   // for n points, rasterize using n-2 triangles
   for (int i = 0; i < numVertices - 2; i++)
   {
      drawTriangle(verticesToDraw[a], verticesToDraw[b], verticesToDraw[c], canvas);
      b++;
      c++;
   }
}
```
![Untitled presentation (1)](https://user-images.githubusercontent.com/55254786/221042826-8e9c83d2-4154-4864-876e-3551dd31a229.png)

