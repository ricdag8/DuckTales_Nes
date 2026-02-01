#include <QBrush>
#include "Menu.h"
#include "Scrooge.h"
#include "Loader.h"
#include "Game.h"
#include "GameConfig.h"
#include "StaticObject.h"
#include "PinkAlien.h"
#include "Octopus.h"
#include "DynamicPlatform.h"
#include "BBoy.h"
#include "Launchpad.h"
#include "Gizmoduck.h"
#include "Block.h"
#include "Spawnable.h"
#include "Menu.h"
#include "Rat.h"
#include "Beakley.h"


using namespace DT;

Scrooge* Loader::load(std::string levelName)
{
    if(levelName == "Title"){

        new Title();
        //new Arrow();
        return nullptr;
    }
    else if(levelName == "Level"){
        new Level();
        new StaticObject(QPointF(7*TILE,11.7*TILE),3*TILE,1*TILE);
        return new Scrooge(QPointF(7.35* TILE, 10.4*TILE));;
    }
    else if(levelName=="theMoon")
    {
        Game::instance()->world()->addPixmap(QPixmap(":/background/theMoon.png"));
        //primo livello

        new StaticObject(QPointF(0, 69*TILE), 54*TILE, 2.5*TILE); //primo rappresenta la posizione dall'alto verso il basso, il secondo rappresenta la lunghezza, il terzo invece lo spessore
        for (int i=0; i<5; i++)
        {
            new Block(QPointF((13+i)*TILE, 68*TILE), TILE, TILE,Block::Type::BRICK);
        }

        //in alternativa si puo fare un unico blocco di dimensione 4

        new Block(QPointF(16*TILE,67*TILE), TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(15*TILE,67*TILE), TILE,TILE,Block::Type::BRICK);
        for (int i=0; i<5; i++)
        {
            new Block(QPointF((42+i)*TILE, 68*TILE), TILE, TILE,Block::Type::BRICK);
        }
        for (int i=0; i<3; i++)
        {
            new Block(QPointF((43+i)*TILE, 67*TILE), TILE, TILE, Block::Type::BRICK);
        }

        new StaticObject(QPointF(0, 60*TILE), 0, 9*TILE);
        new Block(QPointF(19*TILE,67*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(19*TILE,68*TILE),TILE,TILE,Block::Type::BRICK);
        new StaticObject(QPointF(58*TILE,69*TILE),4*TILE,2.5*TILE);
        new StaticObject(QPointF(64*TILE,69*TILE),18*TILE,2.5*TILE);
        new StaticObject(QPointF(48*TILE, 68*TILE), 2*TILE, TILE);
        for(int i=0;i<4;i++){
            new Block(QPointF((66+i)*TILE, 68*TILE), TILE, TILE,Block::Type::BRICK);
        }
        new Block(QPointF(67*TILE, 67*TILE), TILE, TILE,Block::Type::BRICK);
        new Block(QPointF(67*TILE, 66*TILE), TILE, TILE,Block::Type::BRICK);
        new Block(QPointF(67*TILE, 65*TILE), TILE, TILE,Block::Type::BRICK);
        new Block(QPointF(69*TILE, 67*TILE), TILE, TILE,Block::Type::BRICK);
        new Block(QPointF(69*TILE, 66*TILE), TILE, TILE,Block::Type::BRICK);
        new StaticObject(QPointF(93*TILE,65*TILE),3*TILE,6.5*TILE); //sistema questo
        new StaticObject(QPointF(98*TILE,69*TILE),8*TILE,2.5*TILE);
        new StaticObject(QPointF(100*TILE,68*TILE),2*TILE,TILE); // ultimo tronco in fondo
        new StaticObject(QPointF(108*TILE,69*TILE),11*TILE,2.5*TILE);


        new StaticObject(QPointF(119*TILE,64*TILE),2*TILE,TILE);
        new StaticObject(QPointF(119*TILE,65*TILE),2*TILE,TILE*7, StaticObject::Type::GREEN_GATE);


        new StaticObject(QPointF(0,56.5*TILE),16*TILE,3.5*TILE);
        new StaticObject(QPointF(54*TILE,49*TILE),4*TILE,TILE);//FINE LIANA
        new StaticObject(QPointF(22*TILE,47*TILE),4*TILE,TILE);//FINE LIANA

        //blocchi finali primo livello a destra
        new StaticObject(QPointF(123*TILE,68*TILE),TILE,8*TILE);
        new StaticObject(QPointF(121*TILE,69*TILE),2*TILE,7*TILE);
        new StaticObject(QPointF(124*TILE,66*TILE),TILE,10*TILE); // potrebbe essere necessario diminuire di uno l'altezza
        new StaticObject(QPointF(125*TILE,63*TILE),TILE,13*TILE);
        new StaticObject(QPointF(126*TILE,60*TILE),2*TILE,24*TILE);


        //blocchi tra il primo livello ed il secondo livello
        new StaticObject(QPointF(4*TILE,45*TILE),2*TILE,2*TILE);
        new StaticObject(QPointF(6*TILE,46*TILE),2*TILE,3*TILE);
        new StaticObject(QPointF(8*TILE,48*TILE),4*TILE,3*TILE);
        new StaticObject(QPointF(12*TILE,50*TILE),6*TILE,4*TILE);
        new StaticObject(QPointF(18*TILE,52*TILE),4*TILE,2*TILE);
        new StaticObject(QPointF(22*TILE,52*TILE),TILE,4*TILE);
        new StaticObject(QPointF(25*TILE,52*TILE),TILE,4*TILE);
        new StaticObject(QPointF(26*TILE,52*TILE),2*TILE,2*TILE);
        new StaticObject(QPointF(28*TILE,52*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(30*TILE,54*TILE),24*TILE,7*TILE);
        new StaticObject(QPointF(54*TILE,54*TILE),TILE,9*TILE);
        new StaticObject(QPointF(57*TILE,54*TILE),TILE,9*TILE);
        new StaticObject(QPointF(58*TILE,54*TILE),24*TILE,7*TILE); //384*11
        new StaticObject(QPointF(70*TILE,53*TILE),6*TILE,TILE); //35*16
        new StaticObject(QPointF(82*TILE,52*TILE),2*TILE,4.5*TILE); //32*72
        new StaticObject(QPointF(84*TILE,52*TILE),10*TILE,2*TILE); //160*32
        new StaticObject(QPointF(94*TILE,50*TILE),4*TILE,4*TILE); //64*64
        new StaticObject(QPointF(100*TILE,48*TILE),4*TILE,4*TILE); //
        new StaticObject(QPointF(104*TILE,46*TILE),2*TILE,4*TILE); //
        new StaticObject(QPointF(106*TILE,44*TILE),2*TILE,2*TILE);
        new StaticObject(QPointF(82*TILE,56.5*TILE),46*TILE,3.5*TILE); //grande blocco dopo 384*11
        new StaticObject(QPointF(0,50*TILE),0,19*TILE);






        //oggetti livello 1, spine
        new StaticObject(QPointF(12*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(13*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(14*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(15*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(16*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(17*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(18*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(19*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(20*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(21*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(90*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(91*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(92*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(93*TILE,50*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(94*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(95*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(96*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(97*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(98*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(99*TILE,48*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(32*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(33*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(34*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(35*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(36*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(37*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(38*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(39*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(60*TILE,44*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(61*TILE,44*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(64*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(65*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(68*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(69*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(76*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(77*TILE,45*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(84*TILE,44*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(85*TILE,44*TILE),TILE,2*TILE, StaticObject::Type::SPIKE);

        //rocce primo livello
        new Block(QPointF(60*TILE,52*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(61*TILE,52*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(60*TILE,53*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(61*TILE,53*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(84*TILE,51*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(85*TILE,51*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(86*TILE,51*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(87*TILE,51*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(88*TILE,51*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(85*TILE,50*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(86*TILE,50*TILE),TILE,TILE,Block::Type::BRICK);
        //rocce sui funghi
        new Block(QPointF(71*TILE,48*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(74*TILE,48*TILE),TILE,TILE,Block::Type::SPHERE);




        //funghi giganti
        new StaticObject(QPointF(32*TILE,49*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(42*TILE,49*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(48*TILE,49*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(62*TILE,49*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(70*TILE,49*TILE),2*TILE,4*TILE);
        new StaticObject(QPointF(74*TILE,49*TILE),2*TILE,4*TILE);








        new StaticObject(QPointF(0,41.5*TILE),48*TILE,2.5*TILE);
        new StaticObject(QPointF(2*TILE,39*TILE),53*TILE,2.5*TILE);
        new StaticObject(QPointF(10*TILE,30*TILE),9*TILE,9*TILE);
        new StaticObject(QPointF(19*TILE,36*TILE),2*TILE,3*TILE);
        //new StaticObject(QPointF(62*TILE,30*TILE),4*TILE,9*TILE);
        new StaticObject(QPointF(21*TILE,38*TILE),2*TILE,1*TILE);
        new StaticObject(QPointF(10*TILE,30*TILE),9*TILE,9*TILE);
        new StaticObject(QPointF(57*TILE,39*TILE),30*TILE,5*TILE);
        new StaticObject(QPointF(48*TILE,41.5*TILE),7*TILE,2.5*TILE);
        new StaticObject(QPointF(89*TILE,39*TILE),7*TILE,5*TILE);
        new StaticObject(QPointF(96*TILE,39*TILE),10*TILE,5*TILE); //forse bisogna farlo di un tile in più

        new StaticObject(QPointF(64*TILE,31*TILE),6*TILE,8*TILE);
        new StaticObject(QPointF(6*TILE,34*TILE),TILE,TILE);
        new StaticObject(QPointF(9*TILE,32*TILE),TILE,TILE);
        new StaticObject(QPointF(9*TILE,36*TILE),TILE,TILE);
        new StaticObject(QPointF(94*TILE,32*TILE),5*TILE,4*TILE);
        new StaticObject(QPointF(94*TILE,30*TILE),3*TILE,2*TILE);
        //new StaticObject(QPointF(101*TILE,3*TILE),TILE,3*TILE);
        new StaticObject(QPointF(102*TILE,39*TILE),2*TILE,TILE);
        new StaticObject(QPointF(104*TILE,35*TILE),2*TILE,3*TILE);
        new StaticObject(QPointF(106*TILE,30*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(2*TILE,30*TILE),4*TILE,9*TILE);


        //blocchi tra primo e secondo verde
        new StaticObject(QPointF(26*TILE,24*TILE),44*TILE,7*TILE);
        new StaticObject(QPointF(70*TILE,24*TILE),16*TILE,6*TILE);
        new StaticObject(QPointF(90*TILE,24*TILE),20*TILE,6*TILE); //estremità liana, l'altra è inclusa nel blocco 58*39
        //new StaticObject(QPointF(68*TILE,49*TILE),2*TILE,5*TILE);
        new StaticObject(QPointF(89*TILE,24*TILE),TILE,5*TILE);

        //oggetti secondo livello
        new StaticObject(QPointF(30*TILE,35*TILE),2*TILE,4*TILE);
        new StaticObject(QPointF(32*TILE,35*TILE),2*TILE,4*TILE);
        new StaticObject(QPointF(42*TILE,35*TILE),2*TILE,4*TILE);
        new StaticObject(QPointF(44*TILE,35*TILE),2*TILE,4*TILE); //funghi

        new Block(QPointF(21*TILE,36*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(21*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(22*TILE,36*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(22*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(23*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(23*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(24*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(58*TILE,38*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(61*TILE,38*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(63*TILE,38*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(63*TILE,37*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(63*TILE,36*TILE),TILE,TILE,Block::Type::SPHERE);

        new Block(QPointF(70*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(70*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(70*TILE,36*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(71*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(71*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(71*TILE,36*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(72*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(72*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(92*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(93*TILE,38*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(94*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(96*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(98*TILE,37*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(102*TILE,35*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(103*TILE,35*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(97*TILE,30*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(97*TILE,31*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(98*TILE,30*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(98*TILE,31*TILE),TILE,TILE,Block::Type::BRICK);

        new StaticObject(QPointF(31*TILE,31*TILE), 2*TILE, TILE);
        new StaticObject(QPointF(31*TILE,32*TILE),2*TILE, TILE, StaticObject::Type::SPIKE);

        new StaticObject(QPointF(43*TILE,31*TILE),2*TILE, TILE);
        new StaticObject(QPointF(43*TILE,32*TILE),2*TILE, TILE, StaticObject::Type::SPIKE);



        //new StaticObject(QPointF(89*TILE,36*TILE),TILE,TILE);
    // new StaticObject(QPointF(63*TILE,36*TILE),TILE,TILE);
       // new StaticObject(QPointF(63*TILE,36*TILE),TILE,TILE);
        new StaticObject(QPointF(86*TILE,24*TILE),TILE,5*TILE);

        //piattaforma
        new StaticObject(QPointF(86*TILE,34*TILE),4*TILE,TILE);

      //  new StaticObject(QPointF(0,40*TILE),48*TILE,2*TILE); //grande blocco bianco primo livello a sx confine con il secondo livello


        //terzo livello
        new StaticObject(QPointF(4*TILE,21*TILE),2*TILE,5.5*TILE);
        new StaticObject(QPointF(4*TILE,25.5*TILE),2*TILE,5.5*TILE);
        new StaticObject(QPointF(6*TILE,19*TILE),2*TILE,7.5*TILE);
        new StaticObject(QPointF(8*TILE,24*TILE),4*TILE,2.5*TILE);
        new StaticObject(QPointF(12*TILE,23*TILE),4*TILE,3.5*TILE);
        new StaticObject(QPointF(16*TILE,23*TILE),5*TILE,4*TILE);
        new StaticObject(QPointF(8*TILE,17*TILE),4*TILE,3*TILE);
        //new StaticObject(QPointF(10*TILE,17*TILE),2*TILE,3*TILE);
        new StaticObject(QPointF(12*TILE,15*TILE),6*TILE,3*TILE);
        new StaticObject(QPointF(18*TILE,15*TILE),28*TILE,TILE);
        new StaticObject(QPointF(46*TILE,15*TILE),8*TILE,9*TILE);
        new StaticObject(QPointF(64*TILE,22*TILE),TILE,2*TILE, StaticObject::Type::GATE);
        new StaticObject(QPointF(64*TILE,15*TILE),2*TILE,7*TILE);
        new StaticObject(QPointF(66*TILE,19*TILE),2*TILE,TILE);
        new StaticObject(QPointF(66*TILE,15*TILE),18*TILE,TILE);
        new StaticObject(QPointF(80*TILE,0),4*TILE,15*TILE);
        new StaticObject(QPointF(84*TILE,0),2*TILE,15*TILE);
        new StaticObject(QPointF(86*TILE,0),TILE,14*TILE);
        new StaticObject(QPointF(87*TILE,3*TILE),3*TILE,TILE);
        new StaticObject(QPointF(101*TILE,38*TILE),TILE,TILE);
        new StaticObject(QPointF(101*TILE,35*TILE),TILE,3*TILE);

        new StaticObject(QPointF(89*TILE,9*TILE),1*TILE,5*TILE);
        new StaticObject(QPointF(90*TILE,9*TILE),2*TILE,6*TILE);
        new StaticObject(QPointF(92*TILE,7*TILE),2*TILE,9*TILE);
        new StaticObject(QPointF(94*TILE,7*TILE),2*TILE,11*TILE);
        new StaticObject(QPointF(96*TILE,7*TILE),2*TILE,4.5*TILE);
        new StaticObject(QPointF(96*TILE,15*TILE),2*TILE,3*TILE);
        new StaticObject(QPointF(98*TILE,16*TILE),2*TILE,2*TILE);
        new StaticObject(QPointF(100*TILE,17*TILE),2*TILE,3*TILE);
        new StaticObject(QPointF(102*TILE,18*TILE),2*TILE,2*TILE);
        new StaticObject(QPointF(104*TILE,19*TILE),2*TILE,3*TILE);
        new StaticObject(QPointF(106*TILE,21*TILE),2*TILE,3*TILE);

        new StaticObject(QPointF(109*TILE,6*TILE),TILE,TILE);
        new StaticObject(QPointF(111*TILE,5*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(111*TILE,4*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(114*TILE,8*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(114*TILE,7*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(116*TILE,4*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(116*TILE,5*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(118*TILE,6*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(118*TILE,7*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(119*TILE,3*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(119*TILE,4*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(122*TILE,7*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(122*TILE,8*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(122*TILE,7*TILE),TILE,TILE, StaticObject::Type::SPIKE);
        new StaticObject(QPointF(124*TILE,8*TILE),4*TILE,TILE);
        new StaticObject(QPointF(26*TILE, 68*TILE), 2*TILE, TILE);


        new Block(QPointF(11*TILE,23*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(12*TILE,22*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(13*TILE,22*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(14*TILE,22*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(14*TILE,21*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(15*TILE,22*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(19*TILE,22*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(19*TILE,21*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(20*TILE,22*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(28*TILE,23*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(36*TILE,23*TILE),TILE,TILE,Block::Type::SPHERE);
        new Block(QPointF(37*TILE,23*TILE),TILE,TILE,Block::Type::SPHERE);

        new Block(QPointF(31*TILE,23*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(32*TILE,23*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(39*TILE,23*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(40*TILE,23*TILE),TILE,TILE,Block::Type::BRICK);





        new StaticObject(QPointF(87*TILE,3*TILE),3*TILE,TILE);
        //piattaforma



        //livello sotteraneo


        new StaticObject(QPointF(64*TILE,75*TILE),TILE,9*TILE);
        new StaticObject(QPointF(65*TILE,81*TILE),3*TILE,TILE);
        new StaticObject(QPointF(76*TILE,81*TILE),3*TILE,TILE);
        new StaticObject(QPointF(79*TILE,75*TILE),TILE,7*TILE);
        new StaticObject(QPointF(80*TILE,75*TILE),32*TILE,TILE);
        new StaticObject(QPointF(112*TILE,71.5*TILE),7*TILE,4.5*TILE);
        new StaticObject(QPointF(64*TILE,84*TILE),64*TILE,2.5*TILE);
        new StaticObject(QPointF(88*TILE,83*TILE),9*TILE,TILE);
        new StaticObject(QPointF(90*TILE,82*TILE),4*TILE,TILE);
        new StaticObject(QPointF(90*TILE,81*TILE),2*TILE,TILE);
        new StaticObject(QPointF(99*TILE,83*TILE),8*TILE,TILE);
        new StaticObject(QPointF(99*TILE,82*TILE),8*TILE,TILE);
        new StaticObject(QPointF(99*TILE,81*TILE),3*TILE,TILE);
        new StaticObject(QPointF(105*TILE,81*TILE),2*TILE,TILE);
        new StaticObject(QPointF(109*TILE,82*TILE),2*TILE,TILE);
        new StaticObject(QPointF(113*TILE,82*TILE),2*TILE,TILE);
        new StaticObject(QPointF(109*TILE,83*TILE),9*TILE,TILE);
        new StaticObject(QPointF(86*TILE,0),20*TILE,0);



        new Block(QPointF(86*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(87*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(97*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(98*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(108*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(107*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(123*TILE,83*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(89*TILE,82*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(98*TILE,82*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(111*TILE,82*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(112*TILE,82*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(123*TILE,82*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(102*TILE,81*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(112*TILE,81*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(123*TILE,81*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(90*TILE,80*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(102*TILE,80*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(112*TILE,80*TILE),TILE,TILE,Block::Type::BRICK);
        new Block(QPointF(123*TILE,80*TILE),TILE,TILE,Block::Type::BRICK);

        new StaticObject(QPointF(21*TILE,24*TILE),TILE,7*TILE);
        new StaticObject(QPointF(102*TILE,38*TILE),2*TILE,TILE);
        new StaticObject(QPointF(22*TILE,26*TILE),TILE,3*TILE);
        new StaticObject(QPointF(25*TILE,26*TILE),TILE,3*TILE);
        new StaticObject(QPointF(44*TILE,19*TILE),2*TILE,TILE);
        new StaticObject(QPointF(54*TILE,21*TILE),6*TILE,TILE);
        new StaticObject(QPointF(65*TILE,74*TILE),14*TILE, TILE); // Rat Pit ceiling





        //LIANE
        new StaticObject(QPointF(24*TILE, 48*TILE), 0, 9*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(56*TILE, 31*TILE), 0,15*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(56*TILE, 50*TILE), 0, 15*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(24*TILE, 16*TILE), 0, 18*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(24*TILE, 49*TILE), 0, 8*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(88*TILE, 35*TILE), 0, 13*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(88*TILE, 4*TILE), 0, 28*TILE, StaticObject::Type::ROPE);
        new StaticObject(QPointF(56*TILE, 5.7*TILE), 0, 10.3*TILE, StaticObject::Type::ROPE);

        new StaticObject(QPointF(24 * TILE - TILE/4, 59.5 * TILE), TILE/2,  TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(56 * TILE - TILE/4, 47.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(56 * TILE - TILE/4, 66.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(24 * TILE - TILE/4, 35.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(88 * TILE - TILE/4, 49.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(88 * TILE - TILE/4, 33.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(56 * TILE - TILE/4, 17.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);
        new StaticObject(QPointF(119.5 * TILE - TILE/4, 75.5 * TILE), TILE/2, TILE/2, StaticObject::Activator::CLIMBING);



        //TEMPORARY StaticObjectS-->SENZA QUESTI GLI ALIENI NON HANNO IL RIFERIMENTO SU COSA SBATTERE PER CAMBIARE DIREZIONE
        new StaticObject(QPointF(55*TILE, 53*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(25.0 *TILE, 51*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(30.0 *TILE, 51*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(30.0 *TILE, 51*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(92.0 *TILE, 6*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(98.0 *TILE, 6*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);

        new PinkAlien(QPointF(50.0 * TILE, 51.8*TILE));
        new PinkAlien(QPointF(34.0 * TILE, 51.8*TILE));
        new PinkAlien(QPointF(25.0 * TILE, 49.8*TILE));
        new PinkAlien(QPointF(64.0 * TILE, 51.8*TILE));
        new PinkAlien(QPointF(76.0 * TILE, 51.8*TILE));
        new PinkAlien(QPointF(92.0 * TILE, 4.8*TILE));


        new StaticObject(QPointF(10 *TILE, 65*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(73 *TILE, 46.2*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(73 *TILE, 50.2*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(87 *TILE, 48.5*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(89.5 *TILE, 48.5*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(83 *TILE, 34*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(77.5 *TILE, 35.5*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(25.5 *TILE, 35.5*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(19.5 *TILE, 18.5*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(17 *TILE, 18.5*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(31.5 *TILE, 23*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(39.5 *TILE, 23*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(22 *TILE, 36*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(31.5 *TILE, 18.5*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(39.5 *TILE, 18.5*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(101.5 *TILE, 5.5*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(101.5 *TILE, 9*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(105.5 *TILE, 5.5*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(105.5 *TILE, 9*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(54 *TILE, 17.3*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(57.8 *TILE, 17.3*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(55 *TILE, 16.5*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(87.5 *TILE, 66*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(87.5 *TILE, 62*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(102.5 *TILE, 65*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(101.5 *TILE, 61*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(101.5 *TILE, 65*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);


        new Octopus(QPointF(10.0 * TILE, 65*TILE), Direction::UP);
        new Octopus(QPointF(72.5 * TILE, 48.5*TILE), Direction::UP);
        new Octopus(QPointF(87 * TILE, 48.5*TILE), Direction::RIGHT);
        new Octopus(QPointF(85 * TILE, 34*TILE), Direction::RIGHT);
        new Octopus(QPointF(77.5 * TILE, 35*TILE), Direction::UP);
        new Octopus(QPointF(25.5 * TILE, 31*TILE), Direction::UP);
        new Octopus(QPointF(21.5 * TILE, 33*TILE), Direction::UP);
        new Octopus(QPointF(18.5 * TILE, 18.5*TILE), Direction::RIGHT);
        new Octopus(QPointF(31.5 * TILE, 21.5*TILE), Direction::UP);
        new Octopus(QPointF(39.5 * TILE, 21.5*TILE), Direction::UP);
        new Octopus(QPointF(101.5 * TILE, 6*TILE), Direction::UP);
        new Octopus(QPointF(105.5 * TILE, 6*TILE), Direction::UP);
        new Octopus(QPointF(54 * TILE, 17*TILE), Direction::UP);
        new Octopus(QPointF(55 * TILE, 16.5*TILE), Direction::RIGHT);
        new Octopus(QPointF(57 * TILE, 19*TILE), Direction::UP);
        new Octopus(QPointF(87.5 * TILE, 63*TILE), Direction::UP);
        new Octopus(QPointF(101.5 * TILE, 63*TILE), Direction::UP);
        new Octopus(QPointF(102.5 * TILE, 65*TILE), Direction::UP);

        //DynamicPlatform
        new DynamicPlatform(QPointF(91*TILE,66*TILE));
        new StaticObject(QPointF(105.5 *TILE, 9*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(105.5 *TILE, 9*TILE), 0.5*TILE, 0*TILE, StaticObject::Type::BUMPER);


        new StaticObject(QPointF(92* TILE, 66*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        new StaticObject(QPointF(83* TILE, 66*TILE), 0*TILE, 0.5*TILE, StaticObject::Type::BUMPER);
        //new StaticObject(QPointF(3* TILE, 62*TILE), TILE, 6*TILE, StaticObject::Type::ROPE); ROPE nello Spawn per testing



        //DEATH LINE

        new StaticObject(QPointF(53*TILE, 71.5*TILE), 56*TILE, 0, StaticObject::Type::DEATHLINE);
        new StaticObject(QPointF(98*TILE, 11.5*TILE), 30*TILE, 0, StaticObject::Type::DEATHLINE);


        // BEAGLE BOY

        new BBoy(QPointF(102 * TILE, 80* TILE));

        // CHESTS

       


        // BATTERY

        new Block(QPointF(19*TILE, 35*TILE), TILE, TILE,Block::Type::BATTERY);
         new Block(QPointF(19*TILE, 34*TILE), TILE, TILE,Block::Type::BATTERY);
       

        
    


        // TELECOMANDO PER ATTIVARE GIZMODUCK

        new Spawnable(QPointF(55.5*TILE, 19*TILE), TILE, TILE, Spawnable::Type::REMOTE);
        new Launchpad(QPointF(44.5*TILE, 16*TILE), 23, 40);
        new Gizmoduck(QPointF(107* TILE, 65.5*TILE), 32, 39);
        //new StaticObject(QPointF(117*TILE, 60*TILE), TILE, 9*TILE, StaticObject::Type::ACTIVATOR); Cosa è?
        new StaticObject(QPointF(117*TILE, 60*TILE), TILE, 9*TILE, StaticObject::Activator::GIZMO);
        new StaticObject(QPointF(79*TILE, 82*TILE), TILE/2, 2*TILE, StaticObject::Activator::BOSS);
        new StaticObject(QPointF(57*TILE,10.1*TILE),6*TILE,4.9*TILE);
        new StaticObject(QPointF(48*TILE,10.1*TILE),7*TILE,4.9*TILE);
        new StaticObject(QPointF(128*TILE,0*TILE),0.1*TILE,20*TILE);
        new StaticObject(QPointF(48*TILE,0*TILE),4*TILE,10.1*TILE);
        new StaticObject(QPointF(60*TILE,0*TILE),4*TILE,10.1*TILE);
        new StaticObject(QPointF(54*TILE,5.7*TILE),4*TILE,TILE);

        //new StaticObject(QPointF(55*TILE, 60*TILE), 2*TILE, TILE, StaticObject::Activator::CAMERA);
        new Beakley(QPointF(55.3*TILE,2.7*TILE),24,31);
        new StaticObject(QPointF(55*TILE, 11*TILE), 2*TILE, 1*TILE, StaticObject::Activator::BEAKLEY);
        new StaticObject(QPointF(55*TILE, 57*TILE), 2*TILE, 0.5*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(23*TILE, 55*TILE), 2*TILE, 0.5*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(55*TILE, 42*TILE), 2*TILE, 1*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(23*TILE, 27*TILE), 2*TILE, 0.5*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(87*TILE, 26*TILE), 2*TILE, 0.5*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(87*TILE, 42*TILE), 2*TILE, 1*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(87*TILE, 14*TILE), 2*TILE, 1*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(119*TILE, 72*TILE), 2*TILE, 1*TILE, StaticObject::Activator::CAMERA);
        new StaticObject(QPointF(55*TILE, 12*TILE), 2*TILE, 1*TILE, StaticObject::Activator::CAMERA);


                //posizione di tutti gli spawnables
        new Spawnable(QPointF(16*TILE, 63*TILE), TILE, TILE, Spawnable::Type::STAR, 1);
        new Spawnable(QPointF(43*TILE, 63*TILE), TILE, TILE, Spawnable::Type::ICE_CREAM, 1);
        new Spawnable(QPointF(45*TILE, 63*TILE), TILE, TILE, Spawnable::Type::ICE_CREAM, 1);
        new Spawnable(QPointF(124*TILE, 78*TILE), TILE, TILE, Spawnable::Type::ICE_CREAM, 1);
        new Spawnable(QPointF(125*TILE, 78*TILE), TILE, TILE, Spawnable::Type::ICE_CREAM, 1);

        new Spawnable(QPointF(6*TILE, 35*TILE), TILE, TILE, Spawnable::Type::CAKE, 1);
        new Spawnable(QPointF(61*TILE, 34*TILE), 0.5*TILE, 0.5*TILE, Spawnable::Type::DIAMOND_YELLOW_SMALL, 1);
        new Spawnable(QPointF(71*TILE, 34*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(73*TILE, 34*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(95*TILE, 21*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(97*TILE, 21*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(99*TILE, 21*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(73*TILE, 18*TILE), TILE, TILE, Spawnable::Type::ICE_CREAM, 1);
        new Spawnable(QPointF(77*TILE, 18*TILE), TILE, TILE, Spawnable::Type::ICE_CREAM, 1);
        new Spawnable(QPointF(28*TILE, 33*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(60*TILE, 33*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        new Spawnable(QPointF(95*TILE, 45*TILE), TILE, TILE, Spawnable::Type::DIAMOND_YELLOW_BIG, 1);
        










        new Block(QPointF(6*TILE, 33*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(9*TILE, 47*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(10*TILE, 47*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::CAKE);
        new Block(QPointF(23.5*TILE, 46*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_YELLOW_BIG);
        new Block(QPointF(101*TILE, 47*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(102*TILE, 47*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_YELLOW_BIG);
        new Block(QPointF(102*TILE, 37*TILE), TILE, TILE, Block::Type::CHEST_SMALL, true, Spawnable::Type::CAKE);
        new Block(QPointF(103*TILE, 37*TILE), TILE, TILE, Block::Type::CHEST_SMALL, true, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(99*TILE, 32*TILE), TILE, TILE, Block::Type::CHEST_SMALL, true, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(100*TILE, 32*TILE), TILE, TILE, Block::Type::CHEST_SMALL, true, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(9*TILE, 23*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::KEY);
        new Block(QPointF(2*TILE, 88*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_RED_BIG);
        new Block(QPointF(23*TILE, 62*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_YELLOW_BIG);
        new Block(QPointF(24*TILE, 62*TILE), TILE, TILE, Block::Type::CHEST_SMALL, false, Spawnable::Type::DIAMOND_YELLOW_BIG);
        new Block(QPointF(125*TILE, 6*TILE), 2*TILE, 2*TILE,Block::Type::CHEST_BIG,true, Spawnable::Type::TREASURE);

        new Rat(QPointF(72 * TILE - 39/2, 80* TILE));

        new StaticObject(QPointF(7*TILE, 83.3*TILE), 2*TILE, TILE); // Final Menu

        new StaticObject(QPointF(66.5*TILE, 18*TILE), TILE, TILE, StaticObject::Activator::EVY);

        return new Scrooge(QPointF(3* TILE, 67*TILE));


        /*
         Spawning Point 3 67
         Gizmoduck    105 67
         Launchpad     40 17
         */
    }
    else{
        return nullptr;
    }
}
