#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("俄罗斯方块"));
    this->setWindowIcon(QIcon(":/icon/WindowIcon.png"));
    this->resize(480,655);
    this->setMaximumSize(480,655);
    this->setMinimumSize(480,655);
    setFocusPolicy(Qt::StrongFocus);           //设置消息接收对象（焦点）

    /* 设置状态栏 */
    stbar = statusBar(); //获取QStatusBar对象
    lab = new QLabel;
    lab2 = new QLabel;
    lab3 = new QLabel;

    //lab3->setText("Ctrl+d开始游戏");

    stbar->addWidget(lab);  //把标签放入状态栏
    stbar->addWidget(lab2);
    stbar->addWidget(lab3);

    mbar = menuBar(); //获取QMenuBar对象

    game = new QMenu("游戏");
    difficulty = new QMenu("难度");
    setupcolour = new QMenu("设置颜色");
    auxiliary =  new QMenu("辅助");

    begin = new QAction("开始游戏");
    suspend = new QAction("暂停游戏");
    restart = new QAction("重新开始");

    simple = new QAction("简单(最低)");
    ordinary = new QAction("普通(默认)");
    difficulties = new QAction("困难");
    expert = new QAction("专家");
    nightmare = new QAction("噩梦");
    blackhole = new QAction("黑洞(最高)");
    simple->setCheckable(true);
    ordinary->setCheckable(true);
    difficulties->setCheckable(true);
    expert->setCheckable(true);
    nightmare->setCheckable(true);
    blackhole->setCheckable(true);

    color = new QAction("方块颜色");
    colordown = new QAction("底部方块颜色");
    backgroundcolor = new QAction("背景颜色");
    replytodefault = new QAction("恢复默认");

    auxiliarymodeopen = new QAction("开启辅助线条");
    auxiliarymodeclose = new QAction("关闭辅助线条");
    auxiliarymodeopen->setCheckable(true);
    auxiliarymodeclose->setCheckable(true);

    mbar->addMenu(game);        //向QMenuBar添加menu 
    mbar->addMenu(difficulty);
    mbar->addMenu(setupcolour);
    mbar->addMenu(auxiliary);

    game->addAction(begin);
    game->addAction(suspend);
    game->addAction(restart);

    difficulty->addAction(simple);
    difficulty->addAction(ordinary);
    difficulty->addAction(difficulties);
    difficulty->addAction(expert);
    difficulty->addAction(nightmare);
    difficulty->addAction(blackhole);

    setupcolour->addAction(color);
    setupcolour->addAction(colordown);
    setupcolour->addAction(backgroundcolor);
    setupcolour->addAction(replytodefault);

    auxiliary->addAction(auxiliarymodeopen);
    auxiliary->addAction(auxiliarymodeclose);

    connect(begin,&QAction::triggered,this,&MainWindow::GameBegin);
    connect(suspend,&QAction::triggered,this,&MainWindow::GameSuspend);
    connect(restart,&QAction::triggered,this,&MainWindow::GameRestart);

    connect(color,&QAction::triggered,this,&MainWindow::SetColor);
    connect(colordown,&QAction::triggered,this,&MainWindow::SetColorDown);
    connect(backgroundcolor,&QAction::triggered,this,&MainWindow::SetBackgroundColor);
    connect(replytodefault,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        col1 = Qt::cyan;
        col2 = Qt::green;
        col3 = Qt::lightGray;
    });

    connect(simple,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        simple->setChecked(true);
        ordinary->setChecked(false);
        difficulties->setChecked(false);
        expert->setChecked(false);
        nightmare->setChecked(false);
        blackhole->setChecked(false);
        game_difficulty = 1;
        qDebug() <<"game_difficulty = "<< game_difficulty;
    });
    connect(ordinary,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        simple->setChecked(false);
        ordinary->setChecked(true);
        difficulties->setChecked(false);
        expert->setChecked(false);
        nightmare->setChecked(false);
        blackhole->setChecked(false);
        game_difficulty = 2;
        qDebug() <<"game_difficulty = "<< game_difficulty;
    });
    connect(difficulties,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        simple->setChecked(false);
        ordinary->setChecked(false);
        difficulties->setChecked(true);
        expert->setChecked(false);
        nightmare->setChecked(false);
        blackhole->setChecked(false);
        game_difficulty = 3;
        qDebug() <<"game_difficulty = "<< game_difficulty;
    });
    connect(expert,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        game_difficulty = 4;
        simple->setChecked(false);
        ordinary->setChecked(false);
        difficulties->setChecked(false);
        expert->setChecked(true);
        nightmare->setChecked(false);
        blackhole->setChecked(false);
        qDebug() <<"game_difficulty = "<< game_difficulty;
    });
    connect(nightmare,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        game_difficulty = 5;
        simple->setChecked(false);
        ordinary->setChecked(false);
        difficulties->setChecked(false);
        expert->setChecked(false);
        nightmare->setChecked(true);
        blackhole->setChecked(false);
        qDebug() <<"game_difficulty = "<< game_difficulty;
    });
    connect(blackhole,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        game_difficulty = 6;
        simple->setChecked(false);
        ordinary->setChecked(false);
        difficulties->setChecked(false);
        expert->setChecked(false);
        nightmare->setChecked(false);
        blackhole->setChecked(true);
        qDebug() <<"game_difficulty = "<< game_difficulty;
    });

    connect(auxiliarymodeopen,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        auxiliarymodeopen->setChecked(true);
        auxiliarymodeclose->setChecked(false);
        auxiliaryline = true;
        qDebug() <<"auxiliaryline = "<< auxiliaryline;
    });
    connect(auxiliarymodeclose,&QAction::triggered,this,[=](bool ok)
    {
        qDebug() << ok;
        auxiliarymodeopen->setChecked(false);
        auxiliarymodeclose->setChecked(true);
        auxiliaryline = false;
        qDebug() <<"auxiliarymodeclose = "<< auxiliarymodeclose;
    });

    //快捷键
    begin->setShortcut(QKeySequence(QLatin1String("Ctrl+d"))); //开始游戏
    suspend->setShortcut(QKeySequence(QLatin1String("Ctrl+f"))); //暂停游戏
    restart->setShortcut(QKeySequence(QLatin1String("Ctrl+s"))); //重开游戏
    //初始化游戏难度
    game_difficulty = 2;
    //初始化默认颜色
    col1 = Qt::cyan;
    col2 = Qt::green;
    col3 = Qt::lightGray;
    //初始化游戏
    auxiliaryline = false;
    InitGame();

    simple->setChecked(false);
    ordinary->setChecked(true);
    difficulties->setChecked(false);
    expert->setChecked(false);
    nightmare->setChecked(false);
    blackhole->setChecked(false);

    auxiliarymodeopen->setChecked(false);
    auxiliarymodeclose->setChecked(true);

}

void MainWindow::InitGame()
{
    for(int i=0;i<PLANK_Y;i++)
    {
        for(int j=0;j<PLANK_X;j++)
        {
            game_area[i][j]=0;
        }
    }
    speed_ms = 275;
    speed_ms2 = 225;
    speed_ms3 = 175;
    speed_ms4 = 150;
    speed_ms5 = 125;
    speed_ms6 = 100;

    refresh_ms = 1;
    //初始化随机数种子
    qsrand((unsigned int)(time(NULL)));
    //初始化游戏状态
    game_state =false;

    game_timer = startTimer(speed_ms); //游戏timerID
    game_timer2 = startTimer(speed_ms2);
    game_timer3 = startTimer(speed_ms3);
    game_timer4 = startTimer(speed_ms4);
    game_timer5 = startTimer(speed_ms5);
    game_timer6 = startTimer(speed_ms6);

    paint_timer = startTimer(refresh_ms); //界面刷新timerID

    fraction = 0;         //分数
    //随机方块
    for(int i = 0;i < 2;i++)//初始化时，随机两次方块，分别给当前方块和下一个方块。
    {
        SubPlank();
        CurrentToNext(i);
    } 
    TempBoxcopy();
}

void MainWindow::CurrentToNext(int a)
{
    for (int i = 0;i < 2 ;i++ ) {
        for (int j = 0;j < 4 ;j++ ) {
            power[a].Sqare[i][j] = temp[i][j];
        }
    }
    power[a].g_nSqareID = g_nSqareID;
    if(power[a].g_nSqareID == 0)
    {
        power[a].g_nLine_Y = 0;
        power[a].g_nList_X = 2;
    }
    if(power[a].g_nSqareID == 1 || power[a].g_nSqareID == 2 || power[a].g_nSqareID == 3 || power[a].g_nSqareID == 4 || power[a].g_nSqareID == 5)
    {
        power[a].g_nLine_Y = 0;
        power[a].g_nList_X = 3;
    }
    if(power[a].g_nSqareID == 6 || power[a].g_nSqareID == 7)
    {
        power[a].g_nLine_Y = 0;
        power[a].g_nList_X = 4;
    }
}

int MainWindow::GameOver()
{
    for(int i = 0;i < 10;i++)
    {
        if(game_area[0][i] == 2)
        {
            game_state = false;
        }
    }
    if(game_state == false)
    {
        char temp[128];
        sprintf(temp,"得分:%d,是否继续？",fraction * 100);
        QMessageBox::StandardButton result = QMessageBox::warning(this,"游戏结束",
                                                                   tr(temp),QMessageBox::Yes|QMessageBox::No);
        switch(result)
        {
        case QMessageBox::Yes:
            qDebug()<<"Yes";
            InitGame();
            game_state =false;
            break;
        case QMessageBox::No:
            qDebug()<<"NO";
            this->close();
            break;
        default:
            break;
        }
    }
    return 0;
}


void MainWindow::SetColor()
{
    qDebug()<<"color ";
    QColor temp;
    temp = QColorDialog::getColor();
    bool demo = temp.isValid();         //判断颜色是否无效
    if(demo != false)
    {
         col1 = temp;
    }
    qDebug()<<col1;

}

void MainWindow::SetColorDown()
{
    qDebug()<<"colordown ";
    QColor temp;
    temp = QColorDialog::getColor();
    bool demo = temp.isValid();         //判断颜色是否无效
    if(demo != false)
    {
         col2 = temp;
    }
    qDebug()<<col2;
}

void MainWindow::SetBackgroundColor()
{
    qDebug()<<"backgroundcolor ";
    QColor temp;
    temp = QColorDialog::getColor();
    bool demo = temp.isValid();         //判断颜色是否无效
    if(demo != false)
    {
         col3 = temp;
    }
    qDebug()<<col3;
}

void MainWindow::GameBegin()       //开始游戏
{
    game_state = true;
}


void MainWindow::GameSuspend()     //暂停游戏
{
    game_state = false;
}

void MainWindow::GameRestart()
{
    game_state =false;
    InitGame();
    game_state =true;
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(game_state == true)
    {
        switch(event->key())
        {
        case Qt::Key_Up:
            qDebug()<< Qt::Key_Up;
            if(power[0].g_nSqareID == 0)
            {
                qDebug()<<"power[0].g_nSqareID = "<< power[0].g_nSqareID;
            }
            if(power[0].g_nSqareID == 1 || power[0].g_nSqareID == 2 || power[0].g_nSqareID == 3 || power[0].g_nSqareID == 4 || power[0].g_nSqareID == 5)
            {
                qDebug()<<"power[0].g_nSqareID = "<< power[0].g_nSqareID;
                if(BlockcanChange() == 1)
                {
                     ChangeBlock();
                }
            }
            if(power[0].g_nSqareID == 6 || power[0].g_nSqareID == 7)
            {
                qDebug()<<"power[0].g_nSqareID = "<< power[0].g_nSqareID;
                if(BlockcanChange2() == 1)
                {
                     ChangeBlock2();
                }
            }

            break;
        case Qt::Key_Down:
            qDebug()<< Qt::Key_Down;
            if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
            {
                PlankDown();
                power[0].g_nLine_Y++;
                //g_nLine_Y++;
                qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                qDebug()<<"g_nList_X = "<< power[0].g_nList_X;

            }
            break;
        case Qt::Key_Left:
             qDebug()<< Qt::Key_Left;
            if(PlankNotLeft() == 1 && PlankNotLeft2() == 1)
            {
                 PlankLeft();
                 power[0].g_nList_X--;
            }
            break;
        case Qt::Key_Right:
            qDebug()<< Qt::Key_Right;
            if(PlankNotRight() == 1 && PlankNotRight2() == 1)
            {
                 PlankRight();
                  power[0].g_nList_X ++;
            }
            break;
        default:
            break;
        }
    }
    switch (event->key())
    {
    case Qt::Key_B:
        qDebug()<< 'B';
        game_difficulty ++;
        if(game_difficulty > 6)
        {
            game_difficulty = 6;
        }
        if(game_difficulty == 1)
        {
                simple->setChecked(true);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 2)
        {
               simple->setChecked(false);
                ordinary->setChecked(true);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 3)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(true);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 4)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(true);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 5)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(true);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 6)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(true);
        }
        break;
    case Qt::Key_V:
        qDebug()<< 'V';
        game_difficulty --;
        if(game_difficulty < 1)
        {
            game_difficulty = 1;
        }
        if(game_difficulty == 1)
        {
                simple->setChecked(true);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 2)
        {
               simple->setChecked(false);
                ordinary->setChecked(true);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 3)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(true);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 4)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(true);
                nightmare->setChecked(false);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 5)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(true);
                blackhole->setChecked(false);
        }
        if(game_difficulty == 6)
        {
               simple->setChecked(false);
                ordinary->setChecked(false);
                difficulties->setChecked(false);
                expert->setChecked(false);
                nightmare->setChecked(false);
                blackhole->setChecked(true);
        }
        break;
    case Qt::Key_I:     //方块颜色
        qDebug()<< 'I';
        SetColor();
        break;
    case Qt::Key_O:     //底部方块颜色
        qDebug()<< 'O';
        SetColorDown();
        break;
    case Qt::Key_P:     //底部方块颜色
        qDebug()<< 'P';
        SetBackgroundColor();
        break;
    case Qt::Key_U:     //默认颜色
        qDebug()<< 'U';
        col1 = Qt::cyan;
        col2 = Qt::green;
        col3 = Qt::lightGray;
        break;
    case Qt::Key_E:     //开启辅助线条
        qDebug()<< 'I';
        auxiliaryline = true;
        auxiliarymodeopen->setChecked(true);
        auxiliarymodeclose->setChecked(false);
        break;
    case Qt::Key_R:     //关闭辅助线条
        qDebug()<< 'I';
        auxiliaryline = false;
        auxiliarymodeopen->setChecked(false);
        auxiliarymodeclose->setChecked(true);
        break;
    default:
        break;
    }

}

int MainWindow::PlankNotLeft()
{
    for (int i = 0;i < PLANK_Y ;i++ )
    {
            if(game_area[i][0]== 1)
            {
                return 0;
            }

    }

    return 1;
}

int MainWindow::PlankNotRight(){

    for (int i = 0;i < PLANK_Y ;i++ )
    {
            if(game_area[i][9]== 1)
            {
                return 0;
            }

    }

    return 1;
}


int MainWindow::PlankNotLeft2(){

    for (int i = 0;i < PLANK_Y ;i++ )
    {
        for (int j = 0;j < PLANK_X ;j++ )
        {

            if(game_area[i][j]== 1)
            {
               if(game_area[i][j-1] == 2)
               {
                   return 0;
               }
            }

        }

    }
    return 1;
}
int MainWindow::PlankNotRight2(){

    for (int i = 0;i < PLANK_Y ;i++ )
    {
        for (int j = PLANK_Xx;j >= 0 ;j-- )
        {

            if(game_area[i][j]== 1)
            {
                if(game_area[i][j+1]==2)
                {
                    return 0 ;
                }
            }

        }

    }
    return 1;
}


void MainWindow::PlankLeft()
{
    for (int i = 0;i < PLANK_Y ;i++ )
    {
        for (int j = 0;j < PLANK_X ;j++ )
        {
            if(game_area[i][j]== 1)
            {
                game_area[i][j-1] = game_area[i][j];
                game_area[i][j] = 0;
            }
        }
    }
}

void MainWindow::PlankRight()
{
    for (int i = 0;i < PLANK_Y ;i++ )
    {
        for (int j = PLANK_Xx;j >= 0 ;j-- )
        {
            if(game_area[i][j]== 1)
            {
                game_area[i][j+1] = game_area[i][j];
                game_area[i][j] = 0;
            }
        }
    }
}
void MainWindow::ChangeBlock()
{
    int arrSqare[3][3];
    int i = 0;
    int j = 0;
    int nTemp = 2;
    //背景方块复制出来
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            arrSqare[i][j] = game_area[i +  power[0].g_nLine_Y][j +  power[0].g_nList_X];
        }
    }
    //变形后复制回去
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            game_area[i +  power[0].g_nLine_Y][j +  power[0].g_nList_X] = arrSqare[nTemp][i];
            nTemp--;
        }
        nTemp = 2;
    }
}

int MainWindow::BlockcanChange()
{
    for (int i = 0; i < 3; i++)
        {
            for(int j = 0 ; j < 3; j++)
            {
                if(game_area[ power[0].g_nLine_Y+i][ power[0].g_nList_X+j]==2)
                {
                    return 0;
                }
            }
        }
        if( power[0].g_nList_X<0)
        {
             power[0].g_nList_X = 0;
        }
        if ( power[0].g_nList_X + 2 > 9)
        {
             power[0].g_nList_X = 7;
        }
        return 1;
}


void MainWindow::ChangeBlock2()          //方块2变形   (4x4)
{
    if(game_area[ power[0].g_nLine_Y][ power[0].g_nList_X-1]==1)
        {
            game_area[ power[0].g_nLine_Y][ power[0].g_nList_X-1] = 0;
            game_area[ power[0].g_nLine_Y][ power[0].g_nList_X+1] = 0;
            game_area[ power[0].g_nLine_Y][ power[0].g_nList_X+2] = 0;
            if (game_area[ power[0].g_nLine_Y + 1][ power[0].g_nList_X] == 2)
            {
                game_area[ power[0].g_nLine_Y - 1][ power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y - 2][ power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y - 3][ power[0].g_nList_X] = 1;
            }
            else if (game_area[ power[0].g_nLine_Y + 2][ power[0].g_nList_X] == 2)
            {
                game_area[ power[0].g_nLine_Y + 1][power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y + 2][power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y - 1][power[0].g_nList_X] = 1;
            }
            else if (power[0].g_nLine_Y == 0)
            {
                game_area[ power[0].g_nLine_Y + 1][ power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y + 2][ power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y + 3][ power[0].g_nList_X] = 1;
                power[0].g_nLine_Y = power[0].g_nLine_Y + 1;
            }
            else
            {
                game_area[ power[0].g_nLine_Y - 1][ power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y + 1][ power[0].g_nList_X] = 1;
                game_area[ power[0].g_nLine_Y + 2][ power[0].g_nList_X] = 1;
            }
        }
        else
        {
            game_area[ power[0].g_nLine_Y - 1][power[0].g_nList_X] = 0;
            game_area[ power[0].g_nLine_Y + 1][power[0].g_nList_X] = 0;
            game_area[ power[0].g_nLine_Y + 2][power[0].g_nList_X] = 0;
            if (game_area[ power[0].g_nLine_Y][power[0].g_nList_X + 1] == 2 || power[0].g_nList_X == 9)
            {

                game_area[power[0].g_nLine_Y ][power[0].g_nList_X- 1] = 1;
                game_area[power[0].g_nLine_Y ][power[0].g_nList_X- 2] = 1;
                game_area[power[0].g_nLine_Y ][power[0].g_nList_X- 3] = 1;
                power[0].g_nList_X = power[0].g_nList_X - 2;
            }
            else if (game_area[power[0].g_nLine_Y][power[0].g_nList_X + 2] == 2 || power[0].g_nList_X == 8)
            {
                game_area[power[0].g_nLine_Y][power[0].g_nList_X+1] = 1;
                game_area[power[0].g_nLine_Y][power[0].g_nList_X-1] = 1;
                game_area[power[0].g_nLine_Y][power[0].g_nList_X-2] = 1;
                power[0].g_nList_X = power[0].g_nList_X - 1;
            }
            else if (game_area[power[0].g_nLine_Y][power[0].g_nList_X - 1] == 2 || power[0].g_nList_X == 0)
            {
                game_area[power[0].g_nLine_Y][power[0].g_nList_X + 1] = 1;
                game_area[power[0].g_nLine_Y][power[0].g_nList_X + 2] = 1;
                game_area[power[0].g_nLine_Y][power[0].g_nList_X + 3] = 1;
                power[0].g_nList_X = power[0].g_nList_X + 1;
            }
            else
            {
                game_area[power[0].g_nLine_Y][power[0].g_nList_X-1] = 1;
                game_area[power[0].g_nLine_Y][power[0].g_nList_X+1] = 1;
                game_area[power[0].g_nLine_Y][power[0].g_nList_X+2] = 1;
            }

        }
}
int MainWindow::BlockcanChange2()      //方块2能否变形   (4x4)
{
        int i=0;
        int j=0;
        for (i = 1; i < 4; i++)
        {
            if (game_area[power[0].g_nLine_Y][power[0].g_nList_X + i] == 2 || power[0].g_nList_X + i > 9)
            {
                break;
            }
        }
        for (j = 1; j < 4; j++)
        {
            if (game_area[power[0].g_nLine_Y][power[0].g_nList_X - j] == 2 || power[0].g_nList_X - j < 0)
            {
                break;
            }
        }
        if ((i - 1 + j - 1) < 3)
        {
            return 0;
        }
        return 1;
}

void MainWindow::Eliminatebox()
{
    int nSum = 0;
        for (int i = 19; i >= 0; i--)
        {
            for (int j = 0; j < 10; j++)
            {
                    nSum += game_area[i][j];
            }
            if(nSum==20)        //当nSum == 20 时执行消除
            {
                for (int x = i-1 ; x >= 0; x--)
                {
                    for (int y = 0; y < 10; y++)
                    {
                        game_area[x+1][y] = game_area[x][y];
                    }
                }
                fraction++;
                i = 20;
            }
            nSum = 0;
        }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(game_state == true)
    {
        if(game_difficulty == 1)
        {
            if(event->timerId()==game_timer)
            {
                if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
                {
                       PlankDown();
                       power[0].g_nLine_Y++;
                       qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                       qDebug()<<"g_nList_X = "<< power[0].g_nList_X;
                }
                else
                {
                    NoeNotTow();
                    Eliminatebox();
                    GameOver();
                    power[0] = power[1];    //将下一个方块给当前方块
                    SubPlank();             //随机方块
                    BoxNextcopy();          //赋值给下一个
                    TempBoxcopy();          //将当前方块复制到游戏界面
                }
                update();
            }
        }
        if(game_difficulty == 2)
        {
            if(event->timerId()==game_timer2)
            {
                if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
                {
                       PlankDown();
                       power[0].g_nLine_Y++;
                       qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                       qDebug()<<"g_nList_X = "<< power[0].g_nList_X;
                }
                else
                {
                    NoeNotTow();
                    Eliminatebox();
                    GameOver();
                    power[0] = power[1];    //将下一个方块给当前方块
                    SubPlank();             //随机方块
                    BoxNextcopy();          //赋值给下一个
                    TempBoxcopy();          //将当前方块复制到游戏界面
                }
                update();
            }
        }
        if(game_difficulty == 3)
        {
            if(event->timerId()==game_timer3)
            {
                if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
                {
                       PlankDown();
                       power[0].g_nLine_Y++;
                       qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                       qDebug()<<"g_nList_X = "<< power[0].g_nList_X;
                }
                else
                {
                    NoeNotTow();
                    Eliminatebox();
                    GameOver();
                    power[0] = power[1];    //将下一个方块给当前方块
                    SubPlank();             //随机方块
                    BoxNextcopy();          //赋值给下一个
                    TempBoxcopy();          //将当前方块复制到游戏界面
                }
                update();
            }
        }
        if(game_difficulty == 4)
        {
            if(event->timerId()==game_timer4)
            {
                if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
                {
                       PlankDown();
                       power[0].g_nLine_Y++;
                       qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                       qDebug()<<"g_nList_X = "<< power[0].g_nList_X;
                }
                else
                {
                    NoeNotTow();
                    Eliminatebox();
                    GameOver();
                    power[0] = power[1];    //将下一个方块给当前方块
                    SubPlank();             //随机方块
                    BoxNextcopy();          //赋值给下一个
                    TempBoxcopy();          //将当前方块复制到游戏界面
                }
                update();
            }
        }
        if(game_difficulty == 5)
        {
            if(event->timerId()==game_timer5)
            {
                if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
                {
                       PlankDown();
                       power[0].g_nLine_Y++;
                       qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                       qDebug()<<"g_nList_X = "<< power[0].g_nList_X;
                }
                else
                {
                    NoeNotTow();
                    Eliminatebox();
                    GameOver();
                    power[0] = power[1];    //将下一个方块给当前方块
                    SubPlank();             //随机方块
                    BoxNextcopy();          //赋值给下一个
                    TempBoxcopy();          //将当前方块复制到游戏界面
                }
                update();
            }
        }
        if(game_difficulty == 6)
        {
            if(event->timerId()==game_timer6)
            {
                if(PlankNotDown() == 1 && PlankNotDown2() == 1)//方块下落
                {
                       PlankDown();
                       power[0].g_nLine_Y++;
                       qDebug()<<"g_nLine_Y = "<< power[0].g_nLine_Y;
                       qDebug()<<"g_nList_X = "<< power[0].g_nList_X;
                }
                else
                {
                    NoeNotTow();
                    Eliminatebox();
                    GameOver();
                    power[0] = power[1];    //将下一个方块给当前方块
                    SubPlank();             //随机方块
                    BoxNextcopy();          //赋值给下一个
                    TempBoxcopy();          //将当前方块复制到游戏界面
                }
                update();
            }
        }
    }
    //刷新画面
   if(event->timerId()==paint_timer)
   {
       //时间
       current_date_time =QDateTime::currentDateTime();
       //current_date =current_date_time.toString(" ddd hh:mm:ss");
       current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
       lab->setText(current_date);

       //分数
       char temp[128];
       sprintf(temp,"得分:%d",fraction * 100);
       QPalette pe;
       pe.setColor(QPalette::WindowText,Qt::red);
       lab2->setPalette(pe);
       lab2->setText(temp);
       memset(temp,0,sizeof (temp));

       //难度
       if(game_difficulty == 1)
       {
           sprintf(temp,"当前难度:%s","简单(最低)");
       }
       if(game_difficulty == 2)
       {
           sprintf(temp,"当前难度:%s","普通(默认)");
       }
       if(game_difficulty == 3)
       {
           sprintf(temp,"当前难度:%s","困难");
       }
       if(game_difficulty == 4)
       {
           sprintf(temp,"当前难度:%s","专家");
       }
       if(game_difficulty == 5)
       {
           sprintf(temp,"当前难度:%s","噩梦");
       }
       if(game_difficulty == 6)
       {
           sprintf(temp,"当前难度:%s","黑洞(最高)");
       }
       lab3->setText(temp);
       memset(temp,0,sizeof (temp));
       update();
   }

}

void MainWindow::NoeNotTow()
{
    for (int i = 0;i<PLANK_Y ;i++ )
    {
        for (int j = 0;j<PLANK_X ;j++ )
        {
            if(game_area[i][j]==1)
            {
                game_area[i][j] = 2;
            }
        }
    }
}



void MainWindow::PlankDown()
{
    for (int i = 19;i >= 0 ;i-- )
    {
        for (int j = 0;j<PLANK_X ;j++ )
        {

            if(game_area[i][j]== 1)
            {
                game_area[i+1][j] = game_area[i][j];
                game_area[i][j] = 0;

            }

        }

    }
}

int MainWindow::PlankNotDown()
{
    for (int i = 0 ;i < 10 ;i++ ) {
        if(game_area[19][i] == 1)
        {

            return 0;
        }
    }
    return 1;
}

int MainWindow::PlankNotDown2()
{
    for (int i = 0;i<PLANK_Y ;i++ )
    {
        for (int j = 0;j<PLANK_X ;j++ )
        {
            if(game_area[i][j] == 1)
            {
                if(game_area[i+1][j] == 2)
                {
                    return 0 ;
                }
            }
        }
    }
    return 1;
}


void MainWindow::BoxNextcopy()
{
    for (int i = 0;i < 2 ;i++ )
    {
        for (int j = 0;j < 4 ;j++ )
        {
            power[1].Sqare[i][j] = temp[i][j];
        }
    }
    power[1].g_nSqareID = g_nSqareID;
}

void MainWindow::TempBoxcopy()
{
    for (int i = 0;i < 2 ;i++ )
    {
        for (int j = 0;j < 4 ;j++ )
        {
            game_area[i][j+3] = power[0].Sqare[i][j];

        }
    }

}

int MainWindow::SubPlank()
{
    int nIndex = qrand()%8;
    switch(nIndex)
    {
        case 0:
                temp[0][0] = 0;temp[0][1] = 1;temp[0][2] = 1;temp[0][3] = 0;
                temp[1][0] = 0;temp[1][1] = 1;temp[1][2] = 1;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 3;
        break;
        case 1:
                temp[0][0] = 1;temp[0][1] = 0;temp[0][2] = 0;temp[0][3] = 0;
                temp[1][0] = 1;temp[1][1] = 1;temp[1][2] = 1;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 3;
        break;
        case 2:
                temp[0][0] = 0;temp[0][1] = 0;temp[0][2] = 1;temp[0][3] = 0;
                temp[1][0] = 1;temp[1][1] = 1;temp[1][2] = 1;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 3;
        break;
        case 3:
                temp[0][0] = 1;temp[0][1] = 1;temp[0][2] = 0;temp[0][3] = 0;
                temp[1][0] = 0;temp[1][1] = 1;temp[1][2] = 1;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 3;
        break;
        case 4:
                temp[0][0] = 0;temp[0][1] = 1;temp[0][2] = 1;temp[0][3] = 0;
                temp[1][0] = 1;temp[1][1] = 1;temp[1][2] = 0;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 3;
        break;
        case 5:
                temp[0][0] = 0;temp[0][1] = 1;temp[0][2] = 0;temp[0][3] = 0;
                temp[1][0] = 1;temp[1][1] = 1;temp[1][2] = 1;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 3;
        break;
        case 6:
                temp[0][0] = 1;temp[0][1] = 1;temp[0][2] = 1;temp[0][3] = 1;
                temp[1][0] = 0;temp[1][1] = 0;temp[1][2] = 0;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 4;
        break;
        case 7:
                temp[0][0] = 1;temp[0][1] = 1;temp[0][2] = 1;temp[0][3] = 1;
                temp[1][0] = 0;temp[1][1] = 0;temp[1][2] = 0;temp[1][3] = 0;
                power[1].g_nLine_Y = 0;
                power[1].g_nList_X = 4;
        break;
    }
    g_nSqareID = nIndex;
    return g_nSqareID;
}

void MainWindow::paintEvent(QPaintEvent *event)
{          
         QPainter painter(this);
         //画边框
         painter.setBrush(QBrush(QColor(col3),Qt::SolidPattern));
         painter.drawRect(MARGIN,30,PLANK_X*30,PLANK_Y*BLOCK_SIZE);
         //画下一个方块
         painter.setBrush(QBrush(QColor(col1),Qt::SolidPattern));
         for(int i=0;i<2;i++)
         {
            for(int j=0;j<4;j++)
            {
                if(power[1].Sqare[i][j]==1)
                {
                 painter.drawRect(j*BLOCK_SIZE+MARGIN+330,i*BLOCK_SIZE+MARGIN+85,BLOCK_SIZE,BLOCK_SIZE);
                }
            }
         }
        //画方块
        for (int i = 0;i<PLANK_Y ;i++ )
        {
            for (int j = 0;j<PLANK_X ;j++ )
            {
                if(game_area[i][j]==1)
                {
                    painter.setBrush(QBrush(QColor(col1),Qt::SolidPattern));

                    painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+30,BLOCK_SIZE,BLOCK_SIZE);

                }
                if(game_area[i][j]==2)
                {
                    painter.setBrush(QBrush(QColor(col2),Qt::SolidPattern));
                    painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+30,BLOCK_SIZE,BLOCK_SIZE);
                }
                if(auxiliaryline == true)
                {
                    if(game_area[i][j]==0)
                    {
                        if(col3 == Qt::black)
                        {
                            painter.setBrush(QBrush(QColor(col3),Qt::SolidPattern));
                            painter.setPen(Qt::white);
                            painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+30,BLOCK_SIZE,BLOCK_SIZE);
                        }
                        else
                        {
                            painter.setBrush(QBrush(QColor(col3),Qt::SolidPattern));
                            painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+30,BLOCK_SIZE,BLOCK_SIZE);
                        }
                    }
                }
            }

        }
        update();

}


MainWindow::~MainWindow()
{
    delete ui;
}


