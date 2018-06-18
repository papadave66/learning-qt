#include "widget.h"
#include <QButtonGroup>
#include <QVBoxLayout>
//#include <QHBoxlayout>
//#include <QGridlayout>
#include <QTimerEvent>
#include <QMessageBox>
#include <QTime>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(500,600);
    this->move(200,100);
    this->setFont(QFont("times",20,QFont::Bold));

    this->levelComboBox = new QComboBox(this);
    levelComboBox->addItem("Easy");
    levelComboBox->addItem("Normal");
    levelComboBox->addItem("Hard");

    this->timeLabel = new QLabel(this);
    this->scoreLabel = new QLabel("Score:0");
    this->startBtn = new QPushButton("Start");
    for(int i = 0;i < 9;i++)
    {
        btn[i] = new QPushButton(this);
        btn[i]->setSizePolicy(QSizePolicy::Ignored,
                              QSizePolicy::Ignored);
        btn[i]->setIconSize(QSize(80,80));
    }
    QButtonGroup *grp = new QButtonGroup(this);
    for(int i = 0;i < 9;i++)
    {
        grp->addButton(btn[i]);
    }
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(levelComboBox);
    hlayout->addWidget(timeLabel);
    hlayout->addWidget(scoreLabel);
    hlayout->addWidget(startBtn);

    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(btn[0],0,0);
    glayout->addWidget(btn[1],0,1);
    glayout->addWidget(btn[2],0,2);
    glayout->addWidget(btn[3],1,0);
    glayout->addWidget(btn[4],1,1);
    glayout->addWidget(btn[5],1,2);
    glayout->addWidget(btn[6],2,0);
    glayout->addWidget(btn[7],2,1);
    glayout->addWidget(btn[8],2,2);

    QVBoxLayout  *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addLayout(glayout);
    this->setLayout(vlayout);

    initGame();
    connect(levelComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(setGameLevel(int)));
    connect(startBtn,SIGNAL(pressed()),this,SLOT(startGameSlot()));
    connect(grp,SIGNAL(buttonPressed(QAbstractButton*)),
            this,SLOT(getGameScore(QAbstractButton*)));
    connect(grp,SIGNAL(buttonClicked(QAbstractButton*)),
            this,SLOT(mouseRelease(QAbstractButton*)));

    this->setCursor(QCursor(QPixmap(":DD.png")));
    qsrand(time(NULL));
}
void Widget::initGame()
{
    this->currentLevel = EASY;
    this->currentScore = 0;
    this->currentTime = GAMETIME;
    this->timerLabelId = 0;
    this->changeIconId = 0;
    timeLabel->setText(tr("Time:%1").arg(GAMETIME));

    this->scoreLabel->setText("Score:0");

    currentIconBtn = btn[4];
    currentIconBtn->setIcon(QIcon(":MOUSE.GIF"));
    this->levelComboBox->setEnabled(true);
    this->startBtn->setEnabled(true);
}

void Widget::mouseRelease(QAbstractButton*)
{
    this->setCursor(QCursor(QPixmap(":DD.png")));
}
void  Widget::startGameSlot()
{
     if(timerLabelId != 0)
         killTimer(timerLabelId);
     if(changeIconId != 0)
         killTimer(changeIconId);

     timerLabelId = startTimer(1000);
     changeIconId = startTimer(3000/currentLevel);
     levelComboBox->setEnabled(false);
     startBtn->setEnabled(false);
}

void  Widget::setGameLevel(int index)
{
     if(index == 0)
         this->currentLevel = EASY;
     else if(index == 1)
         this->currentLevel = NORMAL;
     else if(index == 2)
         this->currentLevel = HARD;
}

void  Widget::getGameScore(QAbstractButton *button)
{
    this->setCursor(QCursor(QPixmap(":D.png")));
    if(currentTime == GAMETIME)
        return;
    if((QPushButton*)button == currentIconBtn)
    {
        this->currentScore++;
        this->scoreLabel->setText(tr("Score:%1").arg(currentScore));
    }
}

void  Widget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timerLabelId)
    {
        if(currentTime > 0)
        {
            this->currentTime--;
            this->timeLabel->setText(tr("Time:%1").arg(currentTime));
        }
        else
        {
            killTimer(timerLabelId);
            killTimer(changeIconId);
            if(QMessageBox::information(this,"Infomation",
                                    "Game Over!try angin?",
                                    QMessageBox::Ok|QMessageBox::Cancel,
                                       QMessageBox::Ok)
                    == QMessageBox::Ok)
            {
                currentIconBtn->setIcon(QIcon(""));
                initGame();
            }
            else
              exit(1);
        }
    }
    else if(e->timerId() == changeIconId)
        changIcon();
}

void  Widget::changIcon()
{
    int i = qrand()%9;
    currentIconBtn->setIcon(QIcon(""));
    currentIconBtn = btn[i];
    currentIconBtn->setIcon(QIcon(":resources/MOUSE.GIF"));
}

Widget::~Widget()
{

}
