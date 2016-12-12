#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <QGraphicsScene>

#include "voronoi.h"
#include "vpoint.h"

#define POINT_SIZE 5.0

using namespace vor;

class Model
{
private:

    Voronoi *voronoi;
    Vertices *vertices;
    Edges *edges;

    double width;
    double height;

    double numOfPoints;

    double animationParameter;

    QGraphicsScene *scene;

    void DrawPoint(VPoint *point);

    void DrawLine(const VEdge *edge);

public:

    Model(int w, int h, int n);

    double Width() const;

    double Height() const;

    void SetNumOfPoints(int n);

    void SetAnimationParameter(double value);

    QGraphicsScene *Scene();

    void Clear();

    void Init();

    void Display();
};

#endif // MODEL_H
