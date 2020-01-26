#include "widget.h"
#include "ui_widget.h"
#include "QRandomGenerator"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)



{

    ui->setupUi(this);

        ui->widget->move(0, 860);
        xCount[0] = ui->widget->x();
        xCount[1] = ui->widget->x();
        walk = new QTimer;
        connect(walk, SIGNAL(timeout()),this, SLOT(walkAnimation()));
        walk->start(100);
        ui->widget2->move(50, 860);
        xCount2[0] = ui->widget2->x();
        xCount2[1] = ui->widget2->x();
        walk2 = new QTimer;
        connect(walk2, SIGNAL(timeout()),this, SLOT(walkAnimation2()));
        walk2->start(100);

    this->installEventFilter(this);

}
Widget::~Widget()
{
    delete ui;
}

point e(0);
point mob1d(430);
point mob2d(740);
point mob3d(1120);

 QSet<int> pressedKeys;

 class mob{
 public:
   bool isalive;
   mob(){
   isalive=1;
   }
 };

 class hero
 {
 public:
     bool isalive;
     int hp;
     int exp;
     int lvl;
     int dmg;
     hero(){
     hp=3;
     isalive=1;
     exp=0;
     lvl=1;
     dmg=lvl;
     }

     void morexp(int k){
     exp+=k;
     if(exp>=100){
      lvl++;
      exp=0;
      hp=3;
     }
     }

     void hited(){
     hp--;
     if(hp==0){
     isalive=0;
     }
     }

     void revive(hero lol){
     lol.isalive=1;
     lol.hp=100;
     lol.lvl=1;
     lol.exp=0;
     lvl--;
     }



 };

hero h;
hero h1;
mob m1;
mob m2;
mob m3;
point p(0);       //grass
point p2(2048);


point gr(0);
point gr2(2048);

int l1;
int n=4;
int gmove=0;
int gmove2=0;

bool isUsingSword = 0;
bool isPunching = 0;
int punchPosition = 0;

bool isUsingSword2 = 0;
bool isPunching2 = 0;
int punchPosition2 = 0;

QRandomGenerator generator;



void Widget::punchAnimation()
{
    ui->head->setText("(•_•)");
    ui->body->setText(" /) )\"");
    ui->legs->setText("  | |");
    isPunching = 0;
    punchPosition--;
    timerpu->disconnect(timerpu, SIGNAL(timeout()), this, SLOT(punchAnimation()));
    delete timerpu;
    return;
}

void Widget::punchAnimation2()
{
    ui->head2->setText("(•_•)");
    ui->body2->setText(" /) )\"");
    ui->legs2->setText("  | |");
    isPunching2 = 0;
    punchPosition2--;
    timerpu2->disconnect(timerpu2, SIGNAL(timeout()), this, SLOT(punchAnimation2()));
    delete timerpu2;
    return;
}


void Widget::upAnimation()
{
    if (isMovingForward == 0) {
        if (upMoves >= 90) {
            widgetY += 2;
            if (widgetX < 1250) {
                widgetX += 1;
            }
            ui->widget->move(widgetX, widgetY);
            xCount[0] = ui->widget->x();
            xCount[1] = ui->widget->x();
            ui->body->setText(" /) )\\");
            ui->legs->setText("  | |");
            upMoves = 0;
            isMovingUp = 0;
            timer->stop();
            disconnect(timer, SIGNAL(timeout()),this, SLOT(upAnimation()));
            delete timer;
            qDebug() << "end";
            return;
        }
        if (upMoves < 50) {
            ui->body->setText("╰) )╯");
            widgetY -= 2;
            if (widgetX < 1250) {
                widgetX += 1;
            }
            ui->widget->move(widgetX, widgetY);
        }
        if (upMoves > 40) {
            ui->body->setText(" /) )\\");
            widgetY += 2;
            if (widgetX < 1250) {
                widgetX += 1;
            }
            ui->widget->move(widgetX, widgetY);
        }
        upMoves++;
    }
}

void Widget::upAnimation2()
{
    if (isMovingForward2 == 0) {
        if (upMoves2 == 90) {
            widgetY2 += 2;
            if (widgetX2 < 1250) {
                widgetX2 += 1;
            }
            ui->widget2->move(widgetX2, widgetY2);
            xCount2[0] = ui->widget2->x();
            xCount2[1] = ui->widget2->x();
            ui->body2->setText(" /) )\\");
            ui->legs2->setText("  | |");
            upMoves2 = 0;
            isMovingUp2 = 0;
            timer2->stop();
            disconnect(timer2, SIGNAL(timeout()),this, SLOT(upAnimation2()));
            delete timer2;
            qDebug() << "end";
            return;
        }
        if (upMoves2 < 50) {
            ui->body2->setText("╰) )╯");
            widgetY2 -= 2;
            if (widgetX2 < 1250) {
                widgetX2 += 1;
            }
            ui->widget2->move(widgetX2, widgetY2);
        }
        if (upMoves2 > 40) {
            ui->body2->setText(" /) )\\");
            widgetY2 += 2;
            if (widgetX2 < 1250) {
                widgetX2 += 1;
            }
            ui->widget2->move(widgetX2, widgetY2);
        }
        upMoves2++;
    }
}



void Widget::walkAnimation()
{
    qDebug() << xCount[0] << " " << xCount[1];
    if (xCount[1] == xCount[0] + 5 || xCount[1] == xCount[0] - 5) {
        xCount[0] = ui->widget->x();
        ui->head->setText("( @ )");

        if (isMovingJustForward == 1){
            if (walkPosition == 0) {
                ui->body->setText("  )\\) ");
                ui->legs->setText("  / |");
                walkPosition = 1;
                gmove=0;
                return;
            }
            if (walkPosition == 1  || gmove==1) {
                ui->body->setText("  )/) ");
                ui->legs->setText("  | \\");
                walkPosition = 0;
                gmove=0;
                return;
            }
            gmove=0;
        }

        if (isMovingJustBackward == 1) {
            qDebug() << "backward";
            if (walkPosition == 1) {
                ui->body->setText("  (\\( ");
                ui->legs->setText("  / |");
                walkPosition = 0;
                return;
            }
            if (walkPosition == 0) {
                ui->body->setText("  (/( ");
                ui->legs->setText("  | \\");
                walkPosition = 1;
                return;
            }
        }

    } else {
        xCount[0] = ui->widget->x();
        ui->legs->setText("  | |");
        ui->head->setText("(•_•)");
        ui->body->setText(" /) )\\");
        isMoving = 0;
        isMovingJustForward = 0;
        isMovingJustBackward = 0;
        return;
    }
}

void Widget::bullet1go(){
l1+=n;

}

void Widget::bullet2go(){
    l2+=n;

}

void Widget::bullet3go(){
    l3+=n;
}



void Widget::walkAnimation2()
{
    qDebug() << xCount2[0] << " " << xCount2[1];
    if (xCount2[1] == xCount2[0] + 5 || xCount2[1] == xCount2[0] - 5) {
        xCount2[0] = ui->widget2->x();
        ui->head2->setText("( @ )");

        if (isMovingJustForward2 == 1){
            if (walkPosition2 == 0) {
                ui->body2->setText("  )\\) ");
               ui->legs2->setText("  / |");
                walkPosition2 = 1;
                gmove2=0;
                return;
            }
            if (walkPosition2 == 1  || gmove2==1) {
                ui->body2->setText("  )/) ");
               ui->legs2->setText("  | \\");
                walkPosition2 = 0;
                gmove2=0;
                return;
            }
            gmove2=0;
        }

        if (isMovingJustBackward2 == 1) {
            qDebug() << "backward";
            if (walkPosition2 == 1) {
                ui->body2->setText("  (\\( ");
               ui->legs2->setText("  / |");
                walkPosition2 = 0;
                return;
            }
            if (walkPosition2 == 0) {
                ui->body2->setText("  (/( ");
                ui->legs2->setText("  | \\");
                walkPosition2 = 1;
                return;
            }
        }

    } else {
        xCount2[0] = ui->widget2->x();
        ui->legs2->setText("  | |");
        ui->head2->setText("(•_•)");
        ui->body2->setText(" /) )\\");
        isMoving2 = 0;
        isMovingJustForward2 = 0;
        isMovingJustBackward2 = 0;
        return;
    }
}

point sch(600);
point sch2(920);
point sch3(290);


bool m_bFirstRelease=0;

int Widget::random100()
{
    qint64 value = generator.generate() & std::numeric_limits<qint64>::max();
    return value%100+1;
}

bool Widget::eventFilter(QObject * obj, QEvent * event)
{

    if(event->type()==QEvent::KeyPress) {

        pressedKeys += ((QKeyEvent*)event)->key();

        if (isMoving == 0 && isMovingUp == 0 && isPunching == 0) {
            if (pressedKeys.contains(Qt::Key_T)) {
                isPunching = 1;
                ui->body->setText(" /) )----B");
                punchPosition++;
                timerpu = new QTimer;
                connect(timerpu, SIGNAL(timeout()),this, SLOT(punchAnimation()));
                timerpu->start(100);
            }
        }
        if (isMoving == 0 && isMovingUp == 0 && isPunching == 0) {
            if (pressedKeys.contains(Qt::Key_R)) {
                isPunching = 1;
                ui->body->setText("K----) )\"");
                ui->head->setText("   (•_•)");
                ui->legs->setText("     | |");
                punchPosition++;
                timerpu = new QTimer;
                connect(timerpu, SIGNAL(timeout()),this, SLOT(punchAnimation()));
                timerpu->start(100);
            }
        }
        if (isMoving == 0 && isMovingUp == 0 && isPunching == 0 && h.lvl>1) {
            if (pressedKeys.contains(Qt::Key_5)) {
                h.lvl-=1;
                isUsingSword = 1;
                isPunching = 1;
                ui->body->setText("/) )-|====>");
                punchPosition++;
                timerpu = new QTimer;
                connect(timerpu, SIGNAL(timeout()),this, SLOT(punchAnimation()));
                timerpu->start(100);
            }
        }
        if (isMoving == 0 && isMovingUp == 0 && isPunching == 0 && h.lvl>1) {
            if (pressedKeys.contains(Qt::Key_4)) {
                h.lvl -= 1;
                isUsingSword = 1;
                isPunching = 1;
                ui->head->setText("     (•_•)");
                ui->body->setText("<====|-) )\"");
                ui->legs->setText("      | |");
                punchPosition++;
                timerpu = new QTimer;
                connect(timerpu, SIGNAL(timeout()),this, SLOT(punchAnimation()));
                timerpu->start(100);
            }
        }



        if (isMoving2 == 0 && isMovingUp2 == 0 && isPunching2 == 0) {
            if (pressedKeys.contains(Qt::Key_U)) {
                isPunching2 = 1;
                ui->body2->setText(" /) )----B");
                punchPosition2++;
                timerpu2 = new QTimer;
                connect(timerpu2, SIGNAL(timeout()),this, SLOT(punchAnimation2()));
                timerpu2->start(100);
            }
        }
        if (isMoving2 == 0 && isMovingUp2 == 0 && isPunching2 == 0) {
            if (pressedKeys.contains(Qt::Key_Y)) {
                isPunching2 = 1;
                ui->body2->setText("K----) )\"");
                ui->head2->setText("   (•_•)");
                ui->legs2->setText("     | |");
                punchPosition2++;
                timerpu2 = new QTimer;
                connect(timerpu2, SIGNAL(timeout()),this, SLOT(punchAnimation2()));
                timerpu2->start(100);
            }
        }
        if (isMoving2 == 0 && isMovingUp2 == 0 && isPunching2 == 0 && h1.lvl>1) {
            if (pressedKeys.contains(Qt::Key_7)) {
                h1.lvl-=1;
                isUsingSword2 = 1;
                isPunching2 = 1;
                ui->body2->setText("/) )-|====>");
                punchPosition2++;
                timerpu2 = new QTimer;
                connect(timerpu2, SIGNAL(timeout()),this, SLOT(punchAnimation2()));
                timerpu2->start(100);
            }
        }
        if (isMoving2 == 0 && isMovingUp2 == 0 && isPunching2 == 0 && h1.lvl>1) {
            if (pressedKeys.contains(Qt::Key_6)) {
                h1.lvl -= 1;
                isUsingSword2 = 1;
                isPunching2 = 1;
                ui->head2->setText("     (•_•)");
                ui->body2->setText("<====|-) )\"");
                ui->legs2->setText("      | |");
                punchPosition2++;
                timerpu2 = new QTimer;
                connect(timerpu2, SIGNAL(timeout()),this, SLOT(punchAnimation2()));
                timerpu2->start(100);
            }
        }





        if(pressedKeys.contains(Qt::Key_D)&&pressedKeys.contains(Qt::Key_Right)&&h.isalive&&h1.isalive)
        {

            p.x-=n;                  //grass
            p2.x-=n;

            gr.x-=n;                  //earth
            gr2.x-=n;

            mob1d.x-=n;
            mob2d.x-=n;
            mob3d.x-=n;
            ui->ground->move(p.x,930);

            sch.x-=n;
            ui->ship->move(sch.x,920);

            if(sch.x<=0){
               //a=random100();
              ui->ship->move(1280,920);
             sch=1280;
            }

            sch2.x-=n;
            ui->ship2->move(sch2.x,920);

            if(sch2.x<=0){
                //a=random100();
              ui->ship2->move(1280,920);
             sch2=1280;
            }
            sch3.x-=n;
            ui->ship3->move(sch3.x,920);
            if(sch3.x<=0){
              // a=random100();
              ui->ship3->move(1280,920);
             sch3=1280;
            }
            ui->ground2->move(p2.x,930);
            gmove=1;
            gmove2=1;
            ui->lol->move(gr.x,943);     //earth
            ui->kek->move(gr2.x,943);
            xCount[0] = widgetX;
            xCount[1] = widgetX;
            xCount2[0] = widgetX2;
            xCount2[1] = widgetX2;


            ui->mob1->move(mob1d.x,920);
            ui->mob2->move(mob2d.x,920);
            ui->mob3->move(mob3d.x,920);

ui->bullet1->move(mob1d.x-l1,910);
ui->bullet2->move(mob2d.x-l2,910);
ui->bullet3->move(mob3d.x-l3,910);

            if(mob1d.x<=0){
                ui->mob1->hide();
                if(widgetX%2==0){
                ui->mob1->show();
                }
                m1.isalive=1;
                ui->mob1->setText("0-||-|||--||---|");
              ui->mob1->move(1280+30,920);
             mob1d=1280+30;
            }

            if(mob2d.x<=0){
                ui->mob2->hide();
                if(widgetX2%2==0){
                ui->mob2->show();
                }
               m2.isalive=1;
               ui->mob2->setText("0-||-|||--||---|");
              ui->mob2->move(1280+30,920);
             mob2d=1280+30;
            }

            if(mob3d.x<=0){
                ui->mob3->hide();
                if((widgetX+widgetX2)%2==0){
                ui->mob3->show();
                }
                m3.isalive=1;
                ui->mob3->setText("0-||-|||--||---|");
              ui->mob3->move(1280+30,920);
             mob3d=1280+30;
            }


            if(p.x==-2048){
                h.morexp(25);
                h1.morexp(25);
                ui->ur->display(h.lvl);
                ui->ur2->display(h1.lvl);
            ui->ground->move(2048,930);
            p.x=2048;
            } else{

            if(p2.x==-2048){
                h.morexp(25);
                h1.morexp(25);
                ui->ur->display(h.lvl);
                ui->ur2->display(h1.lvl);
            ui->ground2->move(2048,930);
            p2.x=2048;
           }
           }

            if(gr.x==-2048){                     //earth
            ui->lol->move(2048,943);
            gr.x=2048;
            } else{

            if(gr2.x==-2048){
            ui->kek->move(2048,943);
            gr2.x=2048;
           }
           }

        }



                if (pressedKeys.contains(Qt::Key_D) && !pressedKeys.contains(Qt::Key_Right)) {
                    if (isMovingUp == 0 && isMovingJustBackward == 0 && xCount[0] + 5 > xCount[1] && gmove==0 && h.isalive) {
                    if(widgetX+5<=1280){
                    widgetX += 5;
                    ui->widget->move(widgetX, widgetY);
                    isMovingJustForward = 1;
                    isMoving = 1;
                    xCount[1] = ui->widget->x();
                    gmove=0;
                }
                }
        }



            if (pressedKeys.contains(Qt::Key_Right) && !pressedKeys.contains(Qt::Key_D)) {
                 if (isMovingUp2 == 0 && isMovingJustBackward2 == 0 && xCount2[0] + 5 > xCount2[1] && gmove2==0 && h1.isalive) {
                 if(widgetX2+5<=1280){
                widgetX2 += 5;
                ui->widget2->move(widgetX2, widgetY2);
                isMovingJustForward2 = 1;
                isMoving2 = 1;
                xCount2[1] = ui->widget2->x();
                gmove2=0;
            }
            }
        }

        if(gmove==1){
            widgetX += 5;
            ui->widget->move(widgetX, widgetY);
            isMovingJustForward = 1;
            isMoving = 1;
            xCount[1] = ui->widget->x();
            gmove=0;
            widgetX -= 5;
        }

        if(gmove2==1){
            widgetX2 += 5;
            ui->widget2->move(widgetX2, widgetY2);
            isMovingJustForward2 = 1;
            isMoving2 = 1;
            xCount2[1] = ui->widget2->x();
            gmove2=0;
            widgetX2 -= 5;
        }


            if (pressedKeys.contains(Qt::Key_A)) {
                if (isMovingJustForward == 0 && isMovingUp == 0 && xCount[0] - 5 < xCount[1] && h.isalive) {
                if(widgetX-5>=0){
                widgetX -= 5;
                ui->widget->move(widgetX, widgetY);
                isMovingJustBackward = 1;
                isMoving = 1;
                xCount[1] = ui->widget->x();
                }

            }
        }

            if (pressedKeys.contains(Qt::Key_W)) {
                if (isMovingUp == 0 && isMoving == 0 && h.isalive) {
                if(widgetX+1<=1250){
                isMovingUp = 1;
                timer = new QTimer;
                connect(timer, SIGNAL(timeout()),this, SLOT(upAnimation()));
                timer->start(10);

            }

            }
        }



            if (pressedKeys.contains(Qt::Key_Left)) {
                if (isMovingJustForward2 == 0 && isMovingUp2 == 0 && xCount2[0] - 5 < xCount2[1]&& h1.isalive) {
                 if(widgetX2-5>=0){
                widgetX2 -= 5;
                ui->widget2->move(widgetX2, widgetY2);
                isMovingJustBackward2 = 1;
                isMoving2 = 1;
                xCount2[1] = ui->widget2->x();
                 }
            }

        }
        if (isMovingUp2 == 0 && isMoving2 == 0 && h1.isalive) {

            if (pressedKeys.contains(Qt::Key_Up)) {
                if(widgetX2+1<=1250){
                isMovingUp2 = 1;
                timer2 = new QTimer;
                connect(timer2, SIGNAL(timeout()),this, SLOT(upAnimation2()));
                timer2->start(10);

            }

            }
        }



            if (pressedKeys.contains(Qt::Key_L)) {
                if (!h1.isalive || !h.isalive) {
               if(!h1.isalive && h.lvl>1){
               h.revive(h1);
               //animation
               ui->widget2->move(0,widgetY2);
               }else{
               if(!h.isalive && h1.lvl>1){
               h1.revive(h);
               //animation
               ui->widget->move(0,widgetY);
               }
              }
            }
        }



    }
    else if(event->type()==QEvent::KeyRelease)
    {

        pressedKeys -= ((QKeyEvent*)event)->key();


    }





 if(((widgetX+60>=sch.x && widgetX-6<=sch.x) || (widgetX+60>=sch2.x && widgetX-6<=sch2.x )|| (widgetX+60>=sch3.x && widgetX-6<=sch3.x))&&(widgetY==860)){
  h.isalive=0;
  ui->head->setText("(X_X)");
  ui->body->setText("/)_)_");
  ui->legs->setText("");
  if(h1.isalive){
  ui->dia2->show();
  }
}


 if(((widgetX2+60>=sch.x && widgetX2-6<=sch.x) || (widgetX2+60>=sch2.x && widgetX2-6<=sch2.x) ||(widgetX2+60>=sch3.x && widgetX2-6<=sch3.x))&&(widgetY2==860)){
  h1.isalive=0;
  ui->head2->setText("(X_X)");
  ui->body2->setText("/)_)_");
  ui->legs2->setText("");
  if(h.isalive){
  ui->dia->show();
  }
}



 if (widgetX2+60==mob1d.x && m1.isalive && widgetY2==860){
     h1.isalive=0;
     ui->body2->setText("(X_X)");
     ui->legs2->setText("/)_)_");
     ui->head2->setText("");
     if(h.isalive){
     ui->dia->show();
     }
 }
 if (widgetX+60==mob1d.x && m1.isalive && widgetY==860){
     h1.isalive=0;
     ui->body->setText("(X_X)");
     ui->legs->setText("/)_)_");
     ui->head->setText("");
     if(h1.isalive){
     ui->dia2->show();
     }
 }

 if (widgetX2+60==mob2d.x && m1.isalive && widgetY2==860){
     h1.isalive=0;
     ui->body2->setText("(X_X)");
     ui->legs2->setText("/)_)_");
     ui->head2->setText("");
     if(h.isalive){
     ui->dia->show();
     }
 }
 if (widgetX+60==mob3d.x && m1.isalive && widgetY==860){
     h1.isalive=0;
     ui->body->setText("(X_X)");
     ui->legs->setText("/)_)_");
     ui->head->setText("");
     if(h1.isalive){
     ui->dia2->show();
     }
 }



 if (widgetX+60>mob1d.x && widgetX+60<mob1d.x+100 && m1.isalive && widgetY==860){
     m1.isalive=0;
     ui->mob1->setText("0--------");
     h.morexp(50);
     ui->ur->display(h.lvl);
     ui->ur2->display(h1.lvl);
 }

 if (widgetX2+60>mob1d.x && widgetX2+60<mob1d.x+100 && m1.isalive && widgetY2==860){
     m1.isalive=0;
     ui->mob1->setText("0--------");
     h1.morexp(50);
     ui->ur->display(h.lvl);
     ui->ur2->display(h1.lvl);
 }


 if (widgetX+60>mob2d.x && widgetX+60<mob2d.x+100 && m2.isalive && widgetY==860){
     m2.isalive=0;
     ui->mob2->setText("0--------");
     h.morexp(50);
     ui->ur->display(h.lvl);
     ui->ur2->display(h1.lvl);
 }

 if (widgetX2+60>mob2d.x && widgetX2+60<mob2d.x+100 && m2.isalive && widgetY2==860){
     m2.isalive=0;
     ui->mob2->setText("0--------");
     h1.morexp(50);
     ui->ur->display(h.lvl);
     ui->ur2->display(h1.lvl);
 }


 if (widgetX+60>mob3d.x && widgetX+60<mob3d.x+100 && m3.isalive && widgetY==860){
     m3.isalive=0;
     ui->mob3->setText("0--------");
     h.morexp(50);
     ui->ur->display(h.lvl);
     ui->ur2->display(h1.lvl);
 }

 if (widgetX2+60>mob3d.x && widgetX2+60<mob3d.x+100 && m3.isalive && widgetY2==860){
     m3.isalive=0;
     ui->mob3->setText("0--------");
     h1.morexp(50);
     ui->ur->display(h.lvl);
     ui->ur2->display(h1.lvl);
 }




  if(h.isalive){
  ui->dia2->hide();
  }

  if(h1.isalive){
  ui->dia->hide();
  }


    return false;
}





