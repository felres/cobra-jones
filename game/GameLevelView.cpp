#include "GameLevelView.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <QtMath>
#include <QDebug>
#include <QKeyEvent>

#include "Player.h"
#include "tile.h"
#include "level.h"

#define NEWLINE "\n"

void GameLevelView::loadLevelView()
{
    // Add the level items
    displayLevel();

    // Calculate the place in the center where the player should spawn
    double spawnX = floor((screenWidth/2)/tileWidth) * tileWidth;
    double spawnY = floor((screenHeight/2)/tileHeight) * tileHeight;
    qDebug() << "Width: "<< screenWidth << ". Height: " << screenHeight << NEWLINE
            << "spawnX: " << spawnX << ". spawnY: " << spawnY;

    //add the player caracter
    player = new Player(tileWidth, tileHeight, spawnX, spawnY);
    player->setSkin(1);
    scene->addItem(player);

    // make player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Set a color background
    this->view->setBackgroundBrush(QBrush(QColor(231,180,155), Qt::SolidPattern));

    // The scene has infinite size, but we want it has the same size than the view
    this->scene->setSceneRect( this->view->rect() );

    // Disable scrollbars because they are not longer needed
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Show the view and enter in application's event loop
    this->view->show();
}

GameLevelView::GameLevelView(Level *currentLevel, QWidget *parent)
  : QWidget(parent)
  , currentLevel(currentLevel)
    {
        // An invisible object that manages all the items
        this->scene = new QGraphicsScene();
        this->scene->setSceneRect(0, 0, screenWidth, screenHeight);
        // A visible rectangle of the scene
        this->view = new QGraphicsView(this->scene);
        view->setFixedSize(screenWidth, screenHeight);
        loadLevelView();
    }

GameLevelView::~GameLevelView()
{
    delete view;
    delete scene;
}

/*void GameLevelView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_P)
        emit goMenu();
}*/

/*void GameLevelView::goToMenuRequested()
{
    // Signal for go to menu
    emit goMenu();
}*/

void GameLevelView::displayLevel()
{
    rows = static_cast<double>(currentLevel->rows);
    cols = static_cast<double>(currentLevel->cols);
    imgSide = 32.0;
    tileWidth = screenWidth / cols;
    tileHeight = screenHeight / rows;
    qreal growthFactor = tileWidth / imgSide;

    qDebug() << rows << "\n" << cols << "\n" << tileWidth << "\n" << tileHeight << "\n";

    for(int row = 0; row < currentLevel->rows; ++row)
    {
        for(int col = 0; col < currentLevel->cols; ++col)
        {
            qreal posX = tileWidth * static_cast<double>(col);
            qreal posY = tileHeight * static_cast<double>(row);
            qDebug() << posX << posY;

            Tile *currentTile = new Tile();
            currentTile->setType(currentLevel->matrix[row][col]);
            //change x and y
            currentTile->setPos( QPoint(posX, posY) );
            //transform
            currentTile->setScale( growthFactor );

            qDebug() << "rect created";
            this->scene->addItem(currentTile);
            qDebug() << "rect added to scene\n";
            tiles.append(currentTile);
        }
    }
}
