#ifndef HARO_H
#define HARO_H
#define EAR_SWITCH_MAX_COUNT 50
#define SHOW_BYE_MAX_COUNT 50
#define EYE_MOVE_MAX_COUNT 5
#define ERROR_MOVEMENT_TRIGGER_COUNT 10

#include <QMainWindow>
#include <QMouseEvent>
#include <QtGlobal>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <QPushButton>
#include <QCalendarWidget>
#include <QFile>
#include <QDataStream>

#include <QSystemTrayIcon>

#include "dresswin.h"
#include "setwin.h"
#include "musicwin.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Haro; }
QT_END_NAMESPACE

class Haro : public QMainWindow
{
    Q_OBJECT
private:
    Ui::Haro *ui;

    DressWin *dressWindow;//换装窗口指针

    SetWin *setWindow;//设置窗口指针

    MusicWin *musicWindow;//音乐窗口页面指针

    QCalendarWidget *calenWindow;//日历窗口指针
    // record mouse position
    QPoint mousePosition;

    vector<QPixmap> movement;//表情图片容器

    vector<QPixmap> spMovement;//特殊动作图片容器

    vector<int>faceNum;//每个表情对应帧数与起始位置

    vector<QPixmap> body,ears1,ears2;//各部件对应图片容器

    QPixmap eyes,stripe;//眼睛和眼部遮罩

    // QTimer *timer;//定时器

    int size;//体型大小

    int btnSize;//按钮大小

    int bodyNum,earsNum;//身体和耳朵对应装扮序号

    int face;//表情序号

    int faceSum;//表情数量

    int spMove;//特殊动作序号

    int btnSwitch_1,btnSwitch_2;//菜单按钮显示开关
    // flag to hide or show button
    int basicButtonSwitch = 0, moreButtonSwith = 0;
    // flag to exit
    int exitSwitch = -1;
    // remember ear dress index
    int earDressIndex = 0;
    // remember ear movement index
    int earMoveIndex = 0;
    // ear switch interval count, because timer emit signal every 10ms, and we change ear every 10xEAR_SWITCH_MAX_COUNT ms
    int earSwitchInterval = 0;
    // ear change flag
    int earChangeFlag = 0;
    // eye move index
    int eyeMoveIndex = 1;
    // eye move kind
    int eyeMoveKind = -1;
    // eye switch interval count
    int eyeSwitchInterval = 0;
    // error movement trigger count
    int errorMovemntTriggerCount = 0;
    // custom count add to eye switch interval count.
    // for example, if you set it to 50, then the inverval between eye movement picture will be (50 + EYE_MOVE_MAX_COUNT)x10 ms.
    // but please note that it will be reset to 0 after a movemnt finish.
    int customEyeSwitchInterval = 0;

    QSystemTrayIcon* pSystemTray;//系统托盘
public:
    Haro(QWidget *parent = nullptr);
    ~Haro();
    // init window
    void initWindow();
    // bind slots
    void bindSlots();
    // bind timer slots
    void bindTimerSlots();
    // hide or show button
    void hideOrShowButton();
    // timer
    QTimer* timer;
    // ear movement
    void earsMovement();

    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件-虚函数

    void mousePressEvent(QMouseEvent *event);//鼠标点击事件-虚函数

    void eyesMovementLoad();//眼部动作载入

    void eyesMovement();//眼部动作表情

    inline void imageSet(QLabel *image,QPixmap map);//设置各部位图片

    void imageLoad();//各部位图片载入

    void initBtn();//初始化按钮

    void reInitBtn();//修改大小时再次初始化按钮

    // void initSystemTray();//初始化系统托盘

    void onCloseButtonClicked();//点击关闭按钮事件

    void onDressButtonClicked();//点击装扮按钮事件

    void onMoreButtonClicked();//点击最展开更多按钮事件

    void onMinButtonClicked();//点击最小化按钮事件

    void setBtnPush();//点击设置按钮事件

    void musicBtnPush();//点击设置按钮事件

    void gameBtnPush();//点击游戏按钮事件

    void calenBtnPush();//点击日历按钮事件

    void onSystemTrayIconActivate();//点击系统托盘事件

    void btnSwitchRole();//根据btnSwitch切换按钮状态

    void specialMovementLoad();//特殊动作载入

    void specialMovement();//特殊动作事件

    void saveData();//存储数据

public slots:
    void bodyChangeSlots(int);
    void earChangeSlots(int);
    void timerSlots();

signals:
    void exitSignal();
};




#endif // HARO_H

