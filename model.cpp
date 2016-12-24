#include "model.h"

Model::Model(int w, int h) :
    width(w),
    height(h),
    numOfPoints(50)
{
    voronoi = new Voronoi();
    vertices = new Vertices();
    scene = new QGraphicsScene(0, 0, w, h);

    animationParameter = ModelToDisplayY(0);

    timer.setInterval(1.0 / ANIMATION_FPS);
    connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));

    srand((unsigned)time(NULL));
}

double Model::Width() const
{
    return width;
}

double Model::Height() const
{
    return height;
}

double Model::GetYFromAP(double ap)
{
    double maxHeight = qMax(ModelToDisplayY(eventsData.back().ly),
            ModelToDisplayY(-height));

    return ModelToDisplayY(ap * maxHeight);
}

double Model::ModelToDisplayX(double x)
{
    return x;
}

double Model::ModelToDisplayY(double y)
{
    return height - y;
}

void Model::SetNumOfPoints(int n)
{
    numOfPoints = n;
}

void Model::SetAnimationParameter(double value)
{
    animationParameter = value;
}

double Model::AnimationParameter() const
{
    return animationParameter;
}

QGraphicsScene *Model::Scene()
{
    return scene;
}

QTimer *Model::Timer()
{
    return &timer;
}

void Model::Clear()
{
    for (VPoint *point : *vertices)
    {
        delete point;
    }

    vertices->clear();

    eventsData.clear();
}

void Model::Init()
{
    vertices->clear();

    for (EventData ed : eventsData)
    {
        ed.root->DeepDelete();
    }

    eventsData.clear();

    for (int i = 0; i < numOfPoints; i++)
    {
        vertices->push_back(new VPoint(width * (double)rand() /
            (double)RAND_MAX,
            height * (double)rand() / (double)RAND_MAX));
    }

    edges = voronoi->GetEdges(vertices, (int)width, (int)height, eventsData);
    std::cout << "Voronoi diagram done!" << std::endl;

#ifdef DEBUG
    for (EventData ed : eventsData)
    {
        std::cout << ed.ly << " ";
    }
    std::cout << std::endl;
#endif
}

void Model::DrawPoint(VPoint *point, bool isSpecial)
{
    double x = ModelToDisplayX(point->x);
    double y = ModelToDisplayY(point->y);

    QBrush brush(Qt::black);

    if (isSpecial)
    {
        brush.setColor(Qt::yellow);
        brush.setStyle(Qt::BrushStyle::SolidPattern);
    }

    scene->addRect(x - POINT_SIZE / 2,
        y - POINT_SIZE / 2,
        POINT_SIZE,
        POINT_SIZE,
        QPen(),
        brush);
}

void Model::DrawLine(const VEdge *edge)
{
    DrawLine(edge->start->x, edge->start->y, edge->end->x, edge->end->y);
}

void Model::DrawLine(double startX,
    double					startY,
    double					endX,
    double					endY,
    bool					isBeachLine)
{
    startX = ModelToDisplayX(startX);
    startY = ModelToDisplayY(startY);
    endX = ModelToDisplayX(endX);
    endY = ModelToDisplayY(endY);

    scene->addLine(startX, startY, endX, endY,
        QPen(isBeachLine ? Qt::red : Qt::black));
}

EventData &Model::FindEventData()
{
    if (true)
    {
        auto eventData = std::lower_bound(eventsData.begin(), eventsData.end(),
                EventData(animationParameter),
                [](const EventData &ed1, const EventData &ed2)
        {
            return !(ed1 < ed2);
        }
                );

        if (eventData == eventsData.end())
        {
            return *(eventData - 1);
        }
        else
        {
            return *eventData;
        }
    }
}

void Model::Display()
{
    scene->clear();

    // Draw points
    for (VPoint *point : *vertices)
    {
        DrawPoint(point, false /* isSpecial */);
    }

    // Draw Edges
    for (VEdge *edge: *edges)
    {
        DrawLine(edge);

        if (edge->start->x < 0 || edge->start->x > width ||
            edge->start->y < 0 || edge->start->y > height)
        {
            if (edge->end->x < 0 || edge->end->x > width ||
                edge->end->y < 0 || edge->end->y > height)
            {
                //std::cout << "Invalid line" << std::endl;
            }
        }
    }

    const EventData &eventData = FindEventData();

    eventData.root->Display(this);

    double sweepingLineY = ModelToDisplayY(animationParameter);

    // Draw sweeping line
    scene->addLine(ModelToDisplayX(0), sweepingLineY, ModelToDisplayX(
            width), sweepingLineY);

#ifdef DEBUG
    std::cout << "Sweeping line: " << FindEventData().ly << std::endl;
#endif
}

void Model::animate()
{
    animationParameter -= ANIMATION_SPEED;
    Display();
}
