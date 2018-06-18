#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>


#define   EASY      3
#define   NORMAL    6
#define   HARD      9
#define   GAMETIME  20

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected slots:
    void  startGameSlot();
    void  setGameLevel(int );
    void  getGameScore(QAbstractButton *);//判读有没有点中
    void  mouseRelease(QAbstractButton*);
protected:
    void timerEvent(QTimerEvent *);
    void changIcon();
    void initGame();
private:
    QPushButton  *startBtn;
    QPushButton  *btn[9];
    QComboBox    *levelComboBox;
    QLabel       *timeLabel;
    QLabel       *scoreLabel;

    int    currentTime;
    int    currentScore;
    int    currentLevel;

    QPushButton  *currentIconBtn;

    int    timerLabelId;
    int    changeIconId;
};

#endif // WIDGET_H
