#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "world.h"
#include "world_global.h"
#include <QQueue>
#include "node.h"
#include <QSet>
#include <math.h>
#include <QDebug>
#include <QStack>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "mainwindow.h"
#include "view.h"
#include <QObject>


class game: public QObject
{
    Q_OBJECT
public:
    game();
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthpacks;
    bool breadthFirst(int x,int y);
    bool bestFirst(int x,int y);
    bool dijkstra(int x,int y);
    void clearLists();
    QQueue<node> currentNodes;
    std::vector<node> availableNodes;
    std::vector<node> sptNodes;//shortest path tree
    int weight = 1;
    int ymax;
    int xmax;
    QSet<int> myIndexes;
    bool calcPath_BreadthFirst();
    bool calcPath_BestFirst();
    bool calcPath_AStar();
    QStack<std::shared_ptr<Tile>> route;
    void loadWorld(QString path,QGraphicsScene * scene);
    World *myWorld = new World();
    void setStart(int x, int y);
    int xDest;
    int yDest;
    void setDestination(int x, int y);
    int getWeight() const;
    void setWeight(int value);
    void setView(view* test);
    view* screen;
    std::shared_ptr<Tile> getTile(int x,int y);
    std::vector<std::unique_ptr<Enemy>>::iterator getClosestEnemy();
    bool isAllDefeated();
    Tile getClosestHealthpack();
    float moveCost = 0.0f;

    float getMoveCost() const;
    void setMoveCost(float value);

    void MoveProtagonist();
    int getProtagonistX();
    int getProtagonistY();
    void setEnergy(float passEnergy);
    void setHealth(float passHealth);
    float getEnergy();
    float getHealth();
    Protagonist *getProtagonist();

private:

    std::unique_ptr<Protagonist> protagonist;

    static bool node_compare(node a, node b)
    {
        return (a.getDistance() < b.getDistance());
    }
    node getNodeWithMinDistance();

signals:
    void changeStats(float energy, float health);
};

#endif // GAME_H
