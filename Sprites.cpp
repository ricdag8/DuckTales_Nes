#include "Sprites.h"

#include <QBitmap>

#include <iostream>

#include <string>

#include <QPainter>

#include <QPixmap>


// utility function
QRect moveBy(QRect rect, int x, int y, int dx = 25, int dy = 30, int border_x = 1, int border_y = 1) {
    rect.moveTo(QPoint(rect.x() + x * dx, rect.y() + y * dy + y * border_y));
    return rect;
}

QRect moveScroogeBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1) {
    return moveBy(rect, x, y, dx, dy, 0, 0);
}

static QPixmap loadTextureTransparent(const std::string & file, QColor mask_color = Qt::white) {
    QPixmap pixmap(file.c_str());
    pixmap.setMask(pixmap.createMaskFromColor(mask_color));
    return pixmap;
}

// load texture from image file
// transparent pixel are identified with the given color
// if an image format not supporting transparency is used (e.g. like .bmp)
static QPixmap loadTexture(const std::string file, QColor mask_color = Qt::white) {
    //if(strends(file, ".bmp"))
    return loadTextureTransparent(file, mask_color);
    //else
    //return QPixmap(file.c_str());
}

// main object positions within sprites
static QRect scrooge_stand(1, 1, 24, 30);
static QRect scrooge_sitting(130, 259, 20, 20);
static QRect _pinkAlien(42, 5, 32, 35);
static QRect _octopus(4, 7, 16, 24);
static QRect _platform(79, 31, 33, 17);
static QRect _beagleBoy(113, 7, 25, 32);
static QRect _block(112, 32, 16, 16);
static QRect _sphere(16, 32, 16, 16);
static QRect _spawnable(0, 16, 16, 16);
static QRect _small_diamond(0, 8, 8, 8);
static QRect _chest(96, 1, 32, 30);
static QRect _launchpad(120, 6, 23, 40);
static QRect _launchpad_flying(3, 6, 53, 71);
static QRect _gizmoduck(122, 49, 32, 39);
static QRect _projectile(202, 66, 8, 8);
static QRect _hud(0, 0, 243, 39);
static QRect hud_letter(1, 130, 8, 7);
static QRect hud_number(1, 122, 8, 7);
static QRect hud_health(2, 138, 7, 7);
static QRect hud_dollar(226, 130, 7, 7);
static QRect hud_apostrophe(233, 130, 7, 7);
static QRect hud_dot(210, 130, 7, 7);
static QRect _greenGate(172, 360, 32, 80);
static QRect _titleScreen(0, 0, 256, 224);
static QRect _titleArrow(258, 111, 5, 8);
static QRect _level(0, 0, 256, 224);
static QRect _cheese(32, 48, 16, 16);
static QRect _nephews(25, 226, 17, 22);
static QRect _levelArrow(260, 3, 8, 8);
static QRect _winkingScrooge(260, 2, 34, 48);
static QRect _rat(141, 45, 39, 27);
static QRect _jumpingRat(139, 10, 44, 27);
static QRect _angryRat(94, 5, 38, 34);
static QRect _beakley(147, 14, 24, 31);
static QRect _scrooge_climbing(125, 60, 24, 32);
static QRect _scrooge_dying(125, 0, 24, 33);
static QRect _boxer_jumping(2, 50, 25, 30);
static QRect _boxer_punching(109, 50, 31, 30);
static QRect _boxer_standing(58, 51, 24, 30);

Sprites * Sprites::instance() {
    static Sprites uniqueInstance;
    return & uniqueInstance;
}

Sprites::Sprites() {
    scrooge = loadTexture(":/sprites/scroogeNew.png", QColor(0, 89, 255, 255));
    pinkAlien = loadTexture(":/sprites/enemies.png", QColor(255, 0, 255));
    octopus = loadTexture(":/sprites/enemies.png", QColor(255, 0, 255));
    beagleBoy = loadTexture(":/sprites/enemies.png", QColor(255, 0, 255));
    platform = loadTexture(":/sprites/itemsfinal.png", QColor(255, 0, 255));
    block = loadTexture(":/sprites/itemsfinal.png", QColor(255, 0, 255));
    spawnable = loadTexture(":/sprites/itemsfinal.png", QColor(255, 0, 255));
    chest = loadTexture(":/sprites/itemsfinal.png", QColor(255, 0, 255));
    gizmoduck = loadTexture(":/sprites/npcs.png", QColor(164, 224, 160));
    projectile = loadTexture(":/sprites/npcs.png", QColor(164, 224, 160));
    launchpad = loadTexture(":/sprites/npcs.png", QColor(164, 224, 160));
    greenGate = loadTexture(":/sprites/tileset.png", QColor(164, 224, 160));
    hud = loadTexture(":/sprites/hud.png", QColor(0, 89, 255));
    difficulty = loadTexture(":/sprites/difficulty.png");
    difficultyArrow = loadTexture(":/sprites/titlescreen.png", QColor(0, 210, 249));
    level = loadTexture(":/sprites/levelSelection.png", QColor(0, 210, 249));
    rat = loadTexture(":/sprites/bosses.png", QColor(164, 224, 160));
    beakley = loadTexture(":/sprites/npcs.png", QColor(164, 224, 160));
    cheese = loadTexture(":/sprites/itemsfinal.png", QColor(255, 0, 255));
}

QPixmap * Sprites::getSprite(const std::string & id) {
    if (id == "scrooge")
        return & scrooge;
    else if (id == "pinkAlien")
        return & pinkAlien;
    else if (id == "octopus")
        return & octopus;
    else if (id == "platform")
        return & platform;
    else if (id == "beagleBoy")
        return & beagleBoy;
    else if (id == "block")
        return & block;
    else if (id == "sphere")
        return & sphere;
    else if (id == "spawnable")
        return & spawnable;
    else if (id == "chest")
        return & chest;
    else if (id == "gizmoduck")
        return & gizmoduck;
    else if (id == "launchpad")
        return & launchpad;
    else if (id == "hud")
        return & hud;
    else if (id == "projectile")
        return & projectile;
    else if (id == "greenGate")
        return & greenGate;
    else if (id == "titleScreen")
        return & difficulty;
    else if (id == "titleArrow")
        return & difficultyArrow;
    else if (id == "level")
        return & level;
    else if (id == "rat")
        return & rat;
    else if (id == "beakley")
        return & beakley;
    else if (id == "cheese")
        return & cheese;

    else
        return 0;
}

void Sprites::get(const std::string & id, QRect animOutput[]) {
    if (id == "scrooge-stand") {
        //animOutput[0] = moveBy(scrooge_stand,0,0);
        animOutput[0] = moveBy(scrooge_stand, 0, 0);
    } else if (id == "scrooge-walk-0") {
        animOutput[0] = moveBy(scrooge_stand, 1, 0);
    } else if (id == "scrooge-walk-1") {
        animOutput[0] = moveBy(scrooge_stand, 2, 0);
    } else if (id == "scrooge-walk-2") {
        animOutput[0] = moveBy(scrooge_stand, 3, 0);
    } else if (id == "scrooge-jump-fall") {
        animOutput[0] = moveBy(scrooge_stand, 4, 0);
    } else if (id == "scrooge-dying") {
        animOutput[0] = moveBy(_scrooge_dying, 0, 0);
    } else if (id == "scrooge-bounce-0") {
        animOutput[0] = moveBy(scrooge_stand, 0, 2);
    } else if (id == "scrooge-bounce-1") {
        animOutput[0] = moveBy(scrooge_stand, 1, 2);
    } else if (id == "scrooge-crouch-0") {
        animOutput[0] = moveBy(scrooge_stand, 2, 2);
    } else if (id == "scrooge-crouch-1") {
        animOutput[0] = moveBy(scrooge_stand, 3, 2);
    } else if (id == "scrooge-stuck") {
        animOutput[0] = moveBy(scrooge_stand, 4, 2);
    } else if (id == "scrooge-climb-0") {
        animOutput[0] = moveBy(_scrooge_climbing, 0, 0);
    } else if (id == "scrooge-climb-1") {
        animOutput[0] = moveBy(_scrooge_climbing, -1, 1, 125, 62);
    } else if (id == "scrooge-putt-0") {
        animOutput[0] = moveBy(scrooge_stand, 1, 4);
    } else if (id == "scrooge-putt-1") {
        animOutput[0] = moveBy(scrooge_stand, 2, 4);
    } else if (id == "scrooge-putt-2") {
        animOutput[0] = moveBy(scrooge_stand, 3, 4);
    } else if (id == "scrooge-putt-3") {
        animOutput[0] = moveBy(scrooge_stand, 4, 4);
    } else if (id == "scrooge-putt-4") {
        animOutput[0] = moveBy(scrooge_stand, 5, 4);
    } else if (id == "scrooge-putt-5") {
        animOutput[0] = moveBy(scrooge_stand, 0, 6);
    } else if (id == "scrooge-putt-fail-0") {
        animOutput[0] = moveBy(scrooge_stand, 1, 6);
    } else if (id == "scrooge-putt-fail-1") {
        animOutput[0] = moveBy(scrooge_stand, 2, 6);
    } else if (id == "scrooge-sit") {
        animOutput[0] = moveBy(scrooge_sitting, 0, 0);
    } else if (id == "pink-alien-0") {
        animOutput[0] = moveBy(_pinkAlien, 0, 0);
    } else if (id == "pink-alien-1") {
        animOutput[0] = moveBy(_pinkAlien, 1, 1, 34, 1);
    } else if (id == "octopus-0") {
        animOutput[0] = moveBy(_octopus, 0, 0);
    } else if (id == "octopus-1") {
        animOutput[0] = moveBy(_octopus, 1, 0, 19);
    } else if (id == "beagleBoy-0") {
        animOutput[0] = moveBy(_beagleBoy, 0, 0);
    } else if (id == "beagleBoy-1") {
        animOutput[0] = moveBy(_beagleBoy, 1, 0, 26);
    } else if (id == "beagleBoy-2") {
        animOutput[0] = moveBy(_beagleBoy, 1, 0, 53);
    } else if (id == "platform") {
        animOutput[0] = moveBy(_platform, 0, 0);
    } else if (id == "block-0") {
        animOutput[0] = moveBy(_block, 0, 0);
    } else if (id == "sphere-0") {
        animOutput[0] = moveBy(_block, -1, 0, 96, 0);
    } else if (id == "block-1") {
        animOutput[0] = moveBy(_block, -1, 0, 112);
    } else if (id == "block-broken-0") {
        animOutput[0] = moveBy(_block, 0, 1, 16, 15);
    } else if (id == "block-hit-0") {
        animOutput[0] = moveBy(_block, -2, -1, 16, 16);
    } else if (id == "block-broken-1") {
        animOutput[0] = moveBy(_block, -1, 1, 16, 15);
    } else if (id == "ice-cream") {
        animOutput[0] = moveBy(_spawnable, 0, 0);
    } else if (id == "cake") {
        animOutput[0] = moveBy(_spawnable, 1, 0, 16);
    } else if (id == "diamond-small-0") {
        animOutput[0] = moveBy(_small_diamond, 0, 0);
    } else if (id == "diamond-small-1") {
        animOutput[0] = moveBy(_small_diamond, 1, 0, 8);
    } else if (id == "diamond-big-0") {
        animOutput[0] = moveBy(_spawnable, 1, -1, 16, 16);
    } else if (id == "diamond-big-1") {
        animOutput[0] = moveBy(_spawnable, 2, -1, 16, 16);
    } else if (id == "diamond-big-2") {
        animOutput[0] = moveBy(_spawnable, 3, -1, 16, 16);
    } else if (id == "diamond-big-3") {
        animOutput[0] = moveBy(_spawnable, 4, -1, 16, 16);
    } else if (id == "diamond-big-4") { // 4 è il red
        animOutput[0] = moveBy(_spawnable, 5, -1, 16, 16);
    } else if (id == "star-0") {
        animOutput[0] = moveBy(_spawnable, 2, 0, 16, 16);
    } else if (id == "star-1") {
        animOutput[0] = moveBy(_spawnable, 3, 0, 16, 16);
    } else if (id == "treasure") {
        animOutput[0] = moveBy(_spawnable, 1, 1, 64, 31);
    } else if (id == "key") {
        animOutput[0] = moveBy(_spawnable, 0, 1, 0, 79);
    } else if (id == "remote") {
        animOutput[0] = moveBy(_spawnable, 2, 1, 16, 79);
    } else if (id == "chest-small-0") {
        animOutput[0] = moveBy(_block, -1, 0, 64);
    } else if (id == "battery-0") {
        animOutput[0] = moveBy(_block, -1, 0, 80);
    } else if (id == "chest-big-0") {
        animOutput[0] = moveBy(_chest, 0, 0);
    } else if (id == "gizmoduck-0") {
        animOutput[0] = moveBy(_gizmoduck, 0, 0);
    } else if (id == "gizmoduck-1") {
        animOutput[0] = moveBy(_gizmoduck, 1, 0, 32);
    } else if (id == "launchpad-standing") {
        animOutput[0] = moveBy(_launchpad, 0, 0);
    } else if (id == "launchpad-flying-0") {
        animOutput[0] = moveBy(_launchpad_flying, 0, 0);
    } else if (id == "launchpad-flying-1") {
        animOutput[0] = moveBy(_launchpad_flying, 1, 0, 53);
    } else if (id == "projectile-0") {
        animOutput[0] = moveBy(_projectile, -1, 0, 8);
    } else if (id == "projectile-1") {
        animOutput[0] = moveBy(_projectile, 0, 0);
    } else if (id == "green-gate") {
        animOutput[0] = moveBy(_greenGate, 0, 0);
    } else if (id == "title-arrow") {
        animOutput[0] = moveBy(_titleArrow, 0, 0);
    } else if (id == "title-0") {
        animOutput[0] = moveBy(_titleScreen, 0, 0);
    } else if (id == "huey") {
        animOutput[0] = moveBy(_nephews, 0, 0);
    } else if (id == "dewey") {
        animOutput[0] = moveBy(_titleScreen, 1, 0, 17);
    } else if (id == "level-arrow-0") {
        animOutput[0] = moveBy(_levelArrow, 0, 0);
    } else if (id == "level-arrow-1") {
        animOutput[0] = moveBy(_levelArrow, 1, 0, 9);
    } else if (id == "scrooge-title-0") {
        animOutput[0] = moveBy(_winkingScrooge, 0, 0);
    } else if (id == "scrooge-title-1") {
        animOutput[0] = moveBy(_levelArrow, 0, 1, 0, 50);
    } else if (id == "rat-run-0") {
        animOutput[0] = moveBy(_rat, -1, 0, 49);
    } else if (id == "rat-run-1") {
        animOutput[0] = moveBy(_rat, 0, 0);
    } else if (id == "rat-jump-0") {
        animOutput[0] = moveBy(_jumpingRat, 0, 0);
    } else if (id == "rat-angry-0") {
        animOutput[0] = moveBy(_angryRat, 0, 0);
    } else if (id == "beakley-0") {
        animOutput[0] = moveBy(_beakley, 0, 0);
    } else if (id == "beakley-1") {
        animOutput[0] = moveBy(_beakley, 1, 0, 23, 0);
    } else if (id == "beakley-2") {
        animOutput[0] = moveBy(_beakley, 24, 0, 2, 0);
    } else if (id == "cheese") {
        animOutput[0] = moveBy(_cheese, 0, 0);
    } else if (id == "boxer-stand") {
        animOutput[0] = moveBy(_boxer_standing, 0, 0);
    } else if (id == "boxer-jump-0") {
        animOutput[0] = moveBy(_boxer_standing, -1, 0, 27);
    } else if (id == "boxer-jump-1") {
        animOutput[0] = moveBy(_boxer_jumping, 0, 0);
    } else if (id == "boxer-punch-0") {
        animOutput[0] = moveBy(_boxer_standing, 1, 26);
    } else if (id == "boxer-punch-1") {
        animOutput[0] = moveBy(_boxer_punching, 0, 0);
    } else {
        printf("warning: cannot get texture \"%s\"\n", id.c_str());
        //return QPixmap();
    }
}

QPixmap Sprites::getHUD(const std::string & id) {
    if (id.rfind("number-", 0) == 0)
        return hud.copy(moveBy(hud_number, id[7] - '0', 0, 8));

    else if (id.rfind("char-", 0) == 0)
        return hud.copy(moveBy(hud_letter, id[5] - 'A', 0, 8));
    else if (id == "$")
        return hud.copy(moveBy(hud_dollar, 0, 0));
    else if (id == "'")
        return hud.copy(moveBy(hud_apostrophe, 0, 0));
    else if (id == ".")
        return hud.copy(moveBy(hud_dot, 0, 0));
    else if (id == "health-0")
        return hud.copy(moveBy(hud_health, 0, 1, 0, 7));
    else if (id == "health-1")
        return hud.copy(moveBy(hud_health, 0, 0));
    else if (id == "hud-text")
        return hud.copy(moveBy(_hud, 0, 1, 0, 40));
    else return hud.copy(_hud);
}

QPixmap Sprites::getNumber(int n, int fill) {
    std::string text = std::to_string(n);

    // fill with 0s on the left
    if (fill)
        while (text.size() != fill)
            text = '0' + text;

    // create collage texture
    QPixmap collage(8 * int(text.size()), 7);
    QPainter painter( & collage);

    // add numbers
    for (int i = 0; i < text.size(); i++)
        painter.drawPixmap(8 * i, 0, Sprites::instance() -> getHUD(std::string("number-") + text[i]));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(0, 89, 255)));

    return collage;
}

QPixmap Sprites::getString(std::string text, int fill) {
    // fill with 0s on the left
    if (fill)
        while (text.size() != fill)
            text = ' ' + text;

    // create collage texture
    QPixmap collage(8 * int(text.size()), 7);
    QPainter painter( & collage);

    // add letters
    for (int i = 0; i < text.size(); i++)
        if (text[i] != ' ')
            painter.drawPixmap(8 * i, 0, Sprites::instance() -> getHUD(std::string("char-") + text[i]));

    // end painting (necessary for setMask)
    painter.end();

    // make background transparent
    collage.setMask(collage.createMaskFromColor(QColor(0, 89, 255)));

    return collage;
}
