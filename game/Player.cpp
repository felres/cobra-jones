#include <QDebug>
#include <QKeyEvent>
#include <QSoundEffect>
#include <QApplication>
#include <QString>
#include <Tile.h>

#include "Player.h"

Player::Player(double tileWidth, double tileHeight, double spawnX, double spawnY)
{
    // Set the walking speed in each axis
    xWalkDistance = tileWidth;
    yWalkDistance = tileHeight;

    //change x and y
    setX(spawnX);
    setY(spawnY);

    // Pre-load the collision sound
    walkingSound = new QSoundEffect(qApp);
    walkingSound->setSource(QUrl("qrc:/assets/sfx_movement_footsteps1b.wav"));
    walkingSound->setVolume(0.98f);
}




void Player::setSkin(int skin)
{
    if(skin==1)
        setPixmap(QPixmap(":/assets/dawn sprite.png"));
}

bool Player::collisionLeft()
{
    if( x() <= 0 )
        return true;
    return false;
}

bool Player::collisionUp()
{
    if( y() <= 0 )
        return true;
    return false;
}


bool Player::collisionRight()
{
    double roomWidth = 800.0;
    if( x() >= roomWidth - xWalkDistance )
        return true;
    return false;
}

bool Player::collisionDown()
{
    double roomHeight = 600.0;
    if( y() >= roomHeight - yWalkDistance )
        return true;
    return false;
}

void Player::move(QString direction)
{
    if(direction == "left")
        setPos(x() - xWalkDistance, y());
    if(direction == "right")
        setPos(x() + xWalkDistance, y());
    if(direction == "up")
        setPos(x(), y() - yWalkDistance);
    if(direction == "down")
        setPos(x(), y() + yWalkDistance);
}

const QList<QGraphicsItem *> Player::getCollidingItems()
{
    const QList<QGraphicsItem*>& items = collidingItems();
    return items;
}
