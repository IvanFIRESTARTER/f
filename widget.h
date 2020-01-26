#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QTimer * timer;
    QTimer * walk;
    QTimer * walkWGround;
    int xCount[4]; // 0 - старый X, 1 - новый X
    int widgetX = 0;
    int widgetY = 860;
    int a;
    int l=15;
     int l2=15;
      int l3=15;
    int upMoves = 0; //когда идёт вверх
    bool isMovingUp = 0; //имеется ввиду вверх
    bool isMoving = 0; //имеется ввиду идёт вперёд/нвзад
    bool isMovingForward = 0;
    bool isMovingJustBackward = 0;
    bool isMovingDown = 0;
    bool isMovingJustForward = 0;
    bool walkPosition = 0; //0 - не сделал шаг, 1 - сделал шаг. прилагается к isMoving и isMovingJustForward.

    QTimer * timer2;
    QTimer * walk2;
    QTimer * walkWGround2;

    QTimer * timerpu2;
    QTimer * timerpu;

    QTimer * timerbull1;
    QTimer * timerbull2;
    QTimer * timerbull3;

    int xCount2[4]; // 0 - старый X, 1 - новый X
    int widgetX2 = 50;
    int widgetY2 = 860;
    int upMoves2 = 0; //когда идёт вверх
    bool isMovingUp2 = 0; //имеется ввиду вверх
    bool isMoving2 = 0; //имеется ввиду идёт вперёд/нвзад
    bool isMovingForward2 = 0;
    bool isMovingJustBackward2 = 0;
    bool isMovingDown2 = 0;
    bool isMovingJustForward2 = 0;

    bool walkPosition2 = 0; //0 - не сделал шаг, 1 - сделал шаг. прилагается к isMoving и isMovingJustForward.
protected:
   bool eventFilter(QObject * obj, QEvent * event);
   void fly1();
   void fly2();
   void fly3();
   int random100();
private:
    Ui::Widget *ui;
public slots:
    void upAnimation();
    void walkAnimation();

    void upAnimation2();
    void walkAnimation2();

    void punchAnimation2();
    void punchAnimation();

    void bullet1go();
    void bullet2go();
    void bullet3go();


};
class point
{
public: int x;
    point(int a=0){
    x=a;
    }
};







#endif // WIDGET_H
