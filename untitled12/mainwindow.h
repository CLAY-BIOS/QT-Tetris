#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <time.h>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QStatusBar>
#include <QLabel>
#include <QDateTime>
#include <time.h>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QColorDialog>
#include <QColor>

const int BLOCK_SIZE=30; //方块边长
const int MARGIN=5; //场景边距
const int PLANK_Y=20; //场景行数
const int PLANK_X=10; //场景列数
const int PLANK_Yy=19; //场景行数(反向)
const int PLANK_Xx=9; //场景行数(反向)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Box
{
    int Sqare[2][4];
    int g_nSqareID;
    int g_nLine_Y;        //方块坐标Y
    int g_nList_X;        //方块坐标X
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
      Ui::MainWindow *ui;
      int game_area[PLANK_Y][PLANK_X];  //方块显示区域

      int temp[2][4];                 //随机方块
      int show_next_box[2][4];        //显示下一个方块

      int speed_ms;         //游戏刷新时间（速度）
      int speed_ms2;
      int speed_ms3;
      int speed_ms4;
      int speed_ms5;
      int speed_ms6;

      int refresh_ms;       //界面刷新时间

      int game_timer;       //开启游戏ID
      int game_timer2;
      int game_timer3;
      int game_timer4;
      int game_timer5;
      int game_timer6;

      int paint_timer;      //界面刷新ID

      int g_nLine_Y;        //方块坐标Y
      int g_nList_X;        //方块坐标X
      int g_nSqareID;       //方块ID
      int Next_g_nSqareID;  //下一个方块ID
      int fraction;         //分数
      bool game_state;      //游戏状态
      int game_difficulty;  //游戏难度

      QStatusBar *stbar;         //状态栏
      QMenuBar *mbar;            //菜单栏

      QMenu *game;              //游戏
      QMenu *difficulty;        //难度
      QMenu *setupcolour;       //设置颜色
      QMenu *auxiliary;         //辅助

      QAction *begin;           //开始游戏
      QAction *suspend;         //暂停游戏
      QAction *restart;         //重新开始

      QAction *simple;          //简单
      QAction *ordinary;        //普通
      QAction *difficulties;    //困难
      QAction *expert;          //专家
      QAction *nightmare;       //噩梦
      QAction *blackhole;       //黑洞

      QAction *color;               //方块颜色
      QAction *colordown;           //底部方块颜色
      QAction *backgroundcolor;     //背景颜色
      QAction *replytodefault;      //默认颜色

      QAction *auxiliarymodeopen;   //开启辅助线条
      QAction *auxiliarymodeclose;  //关闭辅助线条

      QLabel *lab;        //标签      时间
      QLabel *lab2;       //标签2     分数
      QLabel *lab3;       //标签3     难度

      QDateTime current_date_time;    //时间
      QString current_date;           //时间字符串

      QColor col1;       //方块颜色
      QColor col2;       //底部方块颜色
      QColor col3;       //背景颜色


      bool auxiliaryline;   //开启辅助线条

      Box power[2];      //power[0]为当前方块 power[1]为下一个
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);                //界面消息事件
    void timerEvent(QTimerEvent *event);                //时间消息事件
    void keyPressEvent(QKeyEvent *event);               //键盘消息事件

    void CurrentToNext(int a);   //当前方块和下一个方块

    void ChangeBlock();          //方块变形     (3x3)
    int BlockcanChange();        //方块能否变形    (3x3)

    void ChangeBlock2();         //方块2变形   (4x4)
    int BlockcanChange2();       //方块2能否变形   (4x4)

    int SubPlank();              //随机方块
    void InitGame();             //初始化游戏

    void PlankDown();            //方块下落
    void PlankLeft();            //方块左移
    void PlankRight();           //方块右移
    //方块能否下落
    int PlankNotDown();
    int PlankNotDown2();
    //方块能否左移
    int PlankNotLeft();
    int PlankNotLeft2();
    //方块能否右移
    int PlankNotRight();
    int PlankNotRight2();

    void NoeNotTow();         //改变方块颜色

    void BoxNextcopy();     //下一个方块复制
    void TempBoxcopy();     //方块复制
    void Eliminatebox();    //消除方块

    void GameBegin();       //开始游戏
    void GameSuspend();     //暂停游戏
    void GameRestart();     //重开游戏

    void SetColor();        //设置颜色
    void SetColorDown();    //设置底部颜色
    void SetBackgroundColor(); //设置背景颜色
    int GameOver();        //游戏结束
signals:

private slots:

};
#endif // MAINWINDOW_H
