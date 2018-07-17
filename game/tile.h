#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>

class Tile
{
  protected:
    double x;
    double y;
    char type;
  public:
    Tile(double x, double y, char type);
};

#endif // TILE_H
