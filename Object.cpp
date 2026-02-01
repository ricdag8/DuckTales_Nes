#include <QPainter>

#include <QBrush>

#include <QPen>

#include "Object.h"

#include "Game.h"

#include <random>

using namespace DT;

static int created = 0;

Object::Object(QPointF pos, double width, double height) {
    _id = created++;
    _collidable = true;
    _compenetrable = false;
    _colliderVisible = false;
    _boundingRect = QRectF(0, 0, width, height);
    _collider = _boundingRect;

    _sprite = nullptr;
    _animRect = nullptr;

    Game::instance() -> world() -> addItem(this);
    setPos(pos);
}

QRectF Object::qsceneCollider() const {
    return mapRectToScene(_collider);
}

RectF Object::sceneCollider() const {
    QRectF coll = qsceneCollider();
    return RectF {
        {
            coll.x(), coll.y()
        }, {
            coll.width(),
            coll.height()
        }
    };
}

double Object::dist(Object * obj) const {
    QPointF p1 = qsceneCollider().center();
    QPointF p2 = obj -> qsceneCollider().center();
    return std::sqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) + (p2.y() - p1.y()) * (p2.y() - p1.y()));
}

void Object::toggleCollider() {
    if (_collidable)
        _colliderVisible = !_colliderVisible;
}

bool Object::chanceCalculator(double probability) {
    std::random_device rd; // Istanza della classe random_device, rd() restituisce un valore intero casuale-->seed del generatore (punto di partenza)
    std::mt19937 gen(rd()); // Generatore di numeri casuali basato sull'algoritmo Mersenne Twister
    std::uniform_real_distribution < double > dis(0.0, 1.0); // Distribuzione uniforme di numeri reali nell'intervallo 0-1

    double randomValue = dis(gen); // Genero un numero casuale usando la distribuzione dis e il generatore gen
    if (randomValue <= probability) {
        return true;
    } else {
        return false;
    }
}

void Object::schedule(const std::string & id, int delay, std:: function < void() > action, bool overwrite) {
    if (overwrite || _schedulers.find(id) == _schedulers.end())
        _schedulers[id] = Scheduler(delay, action);
}

void Object::updateSchedulers() {
    auto iter = _schedulers.begin();
    for (; iter != _schedulers.end();) {
        if (iter -> second.on()) {
            iter -> second++;
            ++iter;
        } else
            iter = _schedulers.erase(iter);
    }
}

void Object::paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option, QWidget * widget) {
    paint(painter);

    if (_colliderVisible) {
        painter -> setPen(QPen(QBrush(Qt::red), 0.5));
        painter -> setBrush(Qt::NoBrush);
        painter -> drawRect(_collider);
    }
}

void Object::paint(QPainter * painter) {
    if (_animRect && _sprite)
        painter -> drawPixmap(_boundingRect, * _sprite, * _animRect);
}
