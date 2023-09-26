#include "haro.h"
#include "resources.h"
#include "ui_haro.h"
#include <iostream>
#include <QApplication>

Haro::Haro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Haro)
{

    this->ui->setupUi(this);

    // make background translucent
    this->setAttribute(Qt::WA_TranslucentBackground);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, QColor(0x00, 0xFF, 0x00, 0x00));
    this->setPalette(palette);

    // make window stay on top and hide window frame based on system
    #ifdef _WIN32
        // On Windows we need to set Qt::Tool so this app won't show in Windows' taskbar
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    #else
        // On Linux we need to set Qt::X11BypassWindowManagerHint so this app won't show in taskbar
        // Note if you want to use this app on wayland, you need to install x11-wayland and set env QT_QPA_PLATFORM="xcb" to force qt use X11 backend
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    #endif

    // read settings
    this->settings = new QSettings("Haro", "Haro");
    // restore window size, default is 400
    this->size = this->settings->value("WindowSize", 400).toInt();
    this->haroSizeChangeSlots(this->size);
    // restore Haro body and ear
    this->bodyDressIndex = this->settings->value("Body", 0).toInt();
    this->earDressIndex = this->settings->value("Ear", 0).toInt();
    // init windows
    this->initWindow();

    // bind slots to signals
    this->bindSlots();
    // init timer
    this->timer = new QTimer(this);
    this->bindTimerSlots();
    this->timer->start(10);

    // restore window coordinates
    int X = this->settings->value("Coordinates/X", 100).toInt();
    int Y = this->settings->value("Coordinates/Y", 100).toInt();
    this->move(X, Y);
}

Haro::~Haro()
{
    delete ui;
}

void Haro::initWindow()
{
    // reload Haro so it will looks better
    this->ui->bodyImage->setPixmap(QPixmap(QString(Body::getBody((Body::BodyName)(this->bodyDressIndex)))).scaled(this->ui->bodyImage->size()));
    this->ui->earImage->setPixmap(QPixmap(QString(Ear::getEar((Ear::EarName)(this->earDressIndex)))).scaled(this->ui->earImage->size()));
    this->ui->eyeImage->setPixmap(QPixmap(QString(Eye::getEye(Eye::Eye))).scaled(this->ui->eyeImage->size()));
    this->ui->stripeImage->setPixmap(QPixmap(QString(Stripe::getStripe(Stripe::Stripe))).scaled(this->ui->stripeImage->size()));

    // init all other windows
    // dresss window
    this->dressWindow = new DressWin;
    // music window
    this->musicWindow = new MusicWin;
    // setting window
    this->setWindow = new SetWin;
    this->setWindow->setSize(this->size);
    // calendar window
    this->calenWindow = new QCalendarWidget;
    this->calenWindow->resize(600,400);
    #ifdef _WIN32
        // On Windows we need to set Qt::Tool so this app won't show in Windows' taskbar
        this->calenWindow->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    #else
        // On Linux we need to set Qt::X11BypassWindowManagerHint so this app won't show in taskbar
        // Note if you want to use this app on wayland, you need to install x11-wayland and set env QT_QPA_PLATFORM="xcb" to force qt use X11 backend
        this->calenWindow->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    #endif

    // hide button
    this->hideOrShowButton();
}

void Haro::bindSlots()
{
    QObject::connect(this->ui->musicButton, &QPushButton::clicked, this, &Haro::onMusicButtonClicked);
    QObject::connect(this->setWindow, &SetWin::sliderValueChanged, this, &Haro::haroSizeChangeSlots);
    QObject::connect(this->ui->settingButton, &QPushButton::clicked, this, &Haro::onSettingButtonClicked);
    QObject::connect(this->ui->minButton, &QPushButton::clicked, this, &Haro::onMinButtonClicked);
    QObject::connect(this->ui->calendarButton, &QPushButton::clicked, this, &Haro::onCalendarButtonClicked);
    QObject::connect(this->ui->moreButton, &QPushButton::clicked, this, &Haro::onMoreButtonClicked);
    QObject::connect(this->ui->dressButton, &QPushButton::clicked, this, &Haro::onDressButtonClicked);
    QObject::connect(this->ui->closeButton, &QPushButton::clicked, this, &Haro::onCloseButtonClicked);
    QObject::connect(this->dressWindow, &DressWin::bodyChangeSignal, this, &Haro::bodyChangeSlots);
    QObject::connect(this->dressWindow, &DressWin::earChangeSignal, this, &Haro::earChangeSlots);
    QObject::connect(this->musicWindow, &MusicWin::hideHaro, this, &Haro::hideHaroSlots);
    QObject::connect(this->musicWindow, &MusicWin::showHaro, this, &Haro::showHaroSlots);
}

void Haro::bindTimerSlots()
{
    QObject::connect(this->timer, &QTimer::timeout, this, &Haro::timerSlots);
    QObject::connect(this->timer, &QTimer::timeout, this, &Haro::earsMovement);
    QObject::connect(this->timer, &QTimer::timeout, this, &Haro::eyesMovement);
}

void Haro::bodyChangeSlots(int index)
{
    this->bodyDressIndex = index;
    this->ui->bodyImage->setPixmap(QPixmap(QString(Body::getBody((enum Body::BodyName)index))).scaled(this->ui->bodyImage->size()));
}

void Haro::earChangeSlots(int index)
{
    this->earDressIndex = index;
    this->earChangeFlag = 1;
}

void Haro::timerSlots()
{
    // every call means one 10 ms has elapsed
    // we want "Bye" show 10xSHOW_BYE_MAX_COUNT ms
    if (this->exitSwitch >= SHOW_BYE_MAX_COUNT)
    {
        // call close so it will trigger close event
        this->close();
        emit this->exitSignal();
    }
    else if (this->exitSwitch >= 0)
    {
        this->exitSwitch ++;
    }
}

void Haro::earsMovement()
{
    if (this->earSwitchInterval >= EAR_SWITCH_MAX_COUNT)
    {
        if (this->earMoveIndex == 0)
        {
            this->ui->earImage->setPixmap(QPixmap(QString(
                Ear::getEar((enum Ear::EarName)this->earDressIndex)
            )).scaled(this->ui->earImage->size()));
        }
        else
        {
            this->ui->earImage->setPixmap(QPixmap(QString(
                Ear::getEar2((enum Ear::EarName2)this->earDressIndex)
            )).scaled(this->ui->earImage->size()));
        }
        this->earMoveIndex = (this->earMoveIndex + 1) % 2;
        this->earSwitchInterval = 0;
    }
    else if (this->earChangeFlag)
    {
        // user has changed ear, we need to change immediately
        this->ui->earImage->setPixmap(QPixmap(QString(
            Ear::getEar((enum Ear::EarName)this->earDressIndex)
        )).scaled(this->ui->earImage->size()));
        // reset switch interval count and move index
        this->earSwitchInterval = 0;
        this->earMoveIndex = 1;
        this->earChangeFlag = 0;
    }
    else
    {   
        this->earSwitchInterval ++;
    }
}

void Haro::haroSizeChangeSlots(int size)
{
    // check if size >= 400, because we want window's size is larger than 400
    if (size >= 400)
    {
        this->resize(145 + size, size);
    }
    this->ui->bodyImage->resize(size, size);
    this->ui->earImage->resize(size, size);
    this->ui->eyeImage->resize(size, size);
    this->ui->stripeImage->resize(size, size);
    // reset image except eyeImage and earImage
    this->ui->bodyImage->setPixmap(QPixmap(QString(
        Body::getBody((Body::BodyName)(this->bodyDressIndex))
    )).scaled(this->ui->bodyImage->size()));
    // haro doesn't need stripe when its size is less than 300
    if (size <= 300)
    {
        this->ui->stripeImage->setVisible(false);
    }
    else
    {
        this->ui->stripeImage->setVisible(true);
        this->ui->stripeImage->setPixmap(QPixmap(QString(
            Stripe::getStripe(Stripe::Stripe)
        )).scaled(this->ui->stripeImage->size()));
    }
}

void Haro::hideHaroSlots()
{
    // hide music window and haro
    this->musicWindow->hide();
    this->hide();
}

void Haro::showHaroSlots()
{
    // show music window and haro
    this->show();
    this->musicWindow->show();
}

void Haro::hideOrShowButton()
{
    this->ui->closeButton->setVisible(this->basicButtonSwitch);
    this->ui->dressButton->setVisible(this->basicButtonSwitch);
    this->ui->moreButton->setVisible(this->basicButtonSwitch);
    this->ui->minButton->setVisible(this->basicButtonSwitch);

    this->ui->settingButton->setVisible(this->moreButtonSwith);
    this->ui->musicButton->setVisible(this->moreButtonSwith);
    this->ui->gameButton->setVisible(this->moreButtonSwith);
    this->ui->calendarButton->setVisible(this->moreButtonSwith);
}

void Haro::onCloseButtonClicked()
{

    if (this->exitSwitch < 0)
    {
        this->exitSwitch = 0;
    }
    this->ui->eyeImage->setPixmap(QPixmap(QString(Eye::getEye(Eye::ByeEye))).scaled(this->ui->eyeImage->size()));
}

void Haro::onDressButtonClicked()
{
    if(this->dressWindow->isHidden())
    {
        this->dressWindow->move(this->x() - this->dressWindow->width() + 100, this->y());
        
        this->dressWindow->show();
        this->calenWindow->hide();
        this->setWindow->hide();
        this->musicWindow->hide();
    }
    else
    {
        this->dressWindow->hide();
    }
}

void Haro::onMoreButtonClicked()
{
    if (this->moreButtonSwith == 0)
    {
        // show more button
        this->moreButtonSwith = 1;
        this->hideOrShowButton();
        // move other window
        this->dressWindow->move(this->x() - this->dressWindow->width(), this->y());
        this->calenWindow->move(this->x() - this->calenWindow->width(), this->y());
        this->setWindow->move(this->x() - this->setWindow->width(), this->y());
        this->musicWindow->move(this->x() - this->musicWindow->width(), this->y());
    }
    else
    {
        // hide more button
        this->moreButtonSwith = 0;
        this->hideOrShowButton();
        // moveother window
        this->dressWindow->move(this->x() - this->dressWindow->width() + 100, this->y());
        this->calenWindow->move(this->x() - this->calenWindow->width() + 100, this->y());
        this->setWindow->move(this->x() - this->setWindow->width() + 100, this->y());
        this->musicWindow->move(this->x() - this->musicWindow->width() + 100, this->y());
    }
}

void Haro::onMinButtonClicked()
{
    this->hide();
    this->dressWindow->hide();
    this->calenWindow->hide();
    this->setWindow->hide();
    this->musicWindow->hide();
    // hide button too
    this->basicButtonSwitch = 0;
    this->moreButtonSwith = 0;
    this->hideOrShowButton();
}

void Haro::onSettingButtonClicked()
{
    if(setWindow->isHidden())
    {
        //移动窗口坐标↓
        this->setWindow->move(this->x() - this->setWindow->width(), this->y());
        this->setWindow->show();
        // hide other window
        this->calenWindow->hide();
        this->dressWindow->hide();
        this->musicWindow->hide();
    }
    else
    {
        setWindow->hide();
    }
}

void Haro::onMusicButtonClicked()
{
    if(this->musicWindow->isHidden()){
        //移动窗口坐标↓
        this->musicWindow->move(this->x() - this->setWindow->width(), this->y());

        this->musicWindow->show();
        this->calenWindow->hide();
        this->setWindow->hide();
        this->dressWindow->hide();
    }
    else
    {
        this->musicWindow->hide();
    }
}

void Haro::gameBtnPush()
{
    //隐藏所有窗口
    this->hide();
    setWindow->hide();
    calenWindow->hide();
    musicWindow->hide();
    QDir dir( "./game/Sky_island/Release/Sky_island.exe.lnk");//获取相对路径
    QString temDir = dir.absolutePath();//通过相对路径获取绝对路径
    system(temDir.toLatin1());

    //↑通过cmd启动游戏，toLatin1()将QString类型转为char*类型
    //阻塞式启动，关闭后游戏窗口后才运行下面语段↓
    //隐藏按钮↓
    btnSwitch_1=0;
    btnSwitch_2=0;
    // btnSwitchRole();

    this->show();
}

void Haro::onCalendarButtonClicked()
{
    if (calenWindow->isHidden())
    {
        this->calenWindow->move(this->x() - 600, this->y());

        this->calenWindow->show();
        this->dressWindow->hide();
        // musicWindow->hide();
        this->setWindow->hide();
    }
    else
    {
        this->calenWindow->hide();
    }
}

void Haro::onSystemTrayIconActivate()
{
    if (this->isHidden())
    {
        this->show();
    }
    else
    {
        this->hide();
    }
    

}

void Haro::mouseMoveEvent(QMouseEvent *event)
{
    // move window
    if (event->buttons() & Qt::LeftButton)
    {
        this->move(event->globalPos() - this->mousePosition);
        // just a move, no need to show error ^_^
        this->errorMovemntTriggerCount = 0;
        // move other window simultaneously
        this->dressWindow->move(this->x() - 470 + 180, this->y());
        this->calenWindow->move(this->x() - 600 + 180, this->y());
        this->setWindow->move(this->x() - this->setWindow->width() + 180, this->y());
        this->musicWindow->move(this->x() - this->musicWindow->width() + 180, this->y());
    }
}

void Haro::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // mouse left button event
        this->mousePosition = event->pos();
        // hide button
        this->basicButtonSwitch = 0;
        this->moreButtonSwith = 0;
        this->hideOrShowButton();
        // hide other window
        this->errorMovemntTriggerCount ++;
        if (this->errorMovemntTriggerCount >= ERROR_MOVEMENT_TRIGGER_COUNT)
        {
            // ohhhh, you destroy Haro T_T
            this->eyeMoveKind = (int)Movement::Error;
            this->eyeMoveIndex = 1;
            this->errorMovemntTriggerCount = 0;
            // add more interval so error can show longger.
            this->customEyeSwitchInterval = 45;
        }
        // show random movement
        if (this->eyeMoveKind < 0)
        {
            this->eyeMoveKind = rand() % Movement::movementNum;
            this->eyeMoveIndex = 1;
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        // hide or show basic button
        if (this->basicButtonSwitch == 0)
        {
            // show basic button
            this->basicButtonSwitch = 1;
            this->hideOrShowButton();
            // we need to move other window to left side of basic button
            this->dressWindow->move(this->x() - this->dressWindow->width() + 100, this->y());
            this->calenWindow->move(this->x() - this->calenWindow->width() + 100, this->y());
            this->setWindow->move(this->x() - this->setWindow->width() + 100, this->y());
            this->musicWindow->move(this->x() - this->musicWindow->width() + 100, this->y());
        }
        else
        {
            // hide all button
            this->basicButtonSwitch = 0;
            this->moreButtonSwith = 0;
            this->hideOrShowButton();
            // move other window to Haro's left side
            this->dressWindow->move(this->x() - this->dressWindow->width() + 180, this->y());
            this->calenWindow->move(this->x() - this->calenWindow->width() + 180, this->y());
            this->setWindow->move(this->x() - this->setWindow->width() + 180, this->y());
            this->musicWindow->move(this->x() - this->musicWindow->width() + 180, this->y());
        }
    }
}

void Haro::closeEvent(QCloseEvent *event)
{
    // store settings before closing
    // window size
    this->settings->setValue("WindowSize", this->setWindow->getSize());
    // body and ear
    this->settings->setValue("Body", this->bodyDressIndex);
    this->settings->setValue("Ear", this->earDressIndex);
    // coordinates
    this->settings->setValue("Coordinates/X", this->x());
    this->settings->setValue("Coordinates/Y", this->y());
    // sync
    this->settings->sync();
    
    event->accept();
}

void Haro::eyesMovement()
{
    if (this->exitSwitch < 0 and this->eyeSwitchInterval >= (EYE_MOVE_MAX_COUNT + this->customEyeSwitchInterval))
    {
        if (this->eyeMoveKind >= 0)
        {
            int maxNumberOfMove = Movement::getMovementNum((Movement::MovementKind)(this->eyeMoveKind));
            // change eye picture
            char* moveName = Movement::getMovementName((Movement::MovementKind)(this->eyeMoveKind));
            this->ui->eyeImage->setPixmap(QPixmap(QString(":/%1/res/images/movement/%2/%3.png"
                                                         ).arg(moveName).arg(moveName).arg(this->eyeMoveIndex)
                                                 ).scaled(this->ui->eyeImage->size()));
            // if Haro wants to fly, we help it (seriously)
            if (this->eyeMoveKind == Movement::Fly)
            {
                this->move(this->x(), this->y() - 5);
            }
            // check if we have displayed all picture
            this->eyeMoveIndex ++;
            if (this->eyeMoveIndex > maxNumberOfMove)
            {
                // reset move kind and move index
                this->eyeMoveKind = -1;
                this->eyeMoveIndex = 1;
                // reset custom eye switch interval
                this->customEyeSwitchInterval = 0;
            }
        }
        else
        {
            // there is no eye movment currently, so we throw a dice and see if Haro need to blink its cute eyes
            if ((rand() % 40) < 1)
            {
                this->eyeMoveKind = (int)Movement::Blink;
            }
            else
            {
                // no, and we're not going to shut down, so we change eye picture to default
                this->ui->eyeImage->setPixmap(QPixmap(
                    Eye::getEye(Eye::Eye)
                ).scaled(this->ui->eyeImage->size()));
            }
            
        }
        this->eyeSwitchInterval = 0;
    }
    else
    {
        this->eyeSwitchInterval ++;
    }
}