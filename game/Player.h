#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
class QSoundEffect;

class Player: public QGraphicsPixmapItem
{

  public:
    ///constructor
    Player(double tileWidth, double tileHeight, double spawnX, double spawnY);
    /// Called if this object has the focus and a key is pressed by user
    void keyPressEvent(QKeyEvent* event);
    /// ???
    void drill();
    void setSkin(int skin);
  protected:
    QSoundEffect* walkingSound=nullptr;
    double xWalkDistance = 0.0;
    double yWalkDistance = 0.0;
    double walk_speed = 10.0;
    bool collisionLeft();
    bool collisionRight();
    bool collisionUp();
    bool collisionDown();
};

#endif // PLAYER_H
