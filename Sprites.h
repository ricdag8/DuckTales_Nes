#ifndef SPRITES_H
#define SPRITES_H
#include <QPixmap>


// Singleton class
class Sprites {
private:

    // sprites
    QPixmap hud;
    QPixmap pinkAlien;
    QPixmap octopus;
    QPixmap beagleBoy;
    QPixmap scrooge;
    QPixmap title_screen;
    QPixmap platform;
    QPixmap block;
    QPixmap sphere;
    QPixmap spawnable;
    QPixmap chest;
    QPixmap gizmoduck;
    QPixmap projectile;
    QPixmap launchpad;
    QPixmap greenGate;
    QPixmap difficulty;
    QPixmap difficultyArrow;
    QPixmap level;
    QPixmap rat;
    QPixmap beakley;
    QPixmap cheese;

    Sprites();

public:

    // singleton
    static Sprites * instance();

    // extract texture from sprites using the given id
    QPixmap * getSprite(const std::string & id);
    void get(const std::string & id, QRect animOutput[]);
    QPixmap getHUD(const std::string & id);
    // score composite from sprite single score pieces
    QPixmap getScore(int);

    // number composite from sprite single characters
    QPixmap getNumber(int n, int fill = 0);

    // string composite from sprite single characters
    QPixmap getString(std::string text, int fill = 0);
};
#endif
