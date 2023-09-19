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
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
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
    // Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    // setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);//保持窗口置顶2

    // int coordX,coordY;//桌面坐标
    // QFile file("/home/syize/Documents/C++/coursework-a-table-pet-Haro/res/file/file.dat");
    // file.open(QIODevice::ReadOnly);
    // QDataStream in(&file);
    // if(file.isOpen())//读取体型、装扮编号参数、相对桌面坐标
    //     in>>size>>bodyNum>>earsNum>>coordX>>coordY;
    // else{
    //     size = 400;
    //     bodyNum = 0;
    //     earsNum = 0;
    //     coordX = x();
    //     coordY = y();
    // }
    // file.close();
    // move(coordX,coordY);

    // timer = new QTimer;
    // timer->start(40);//动画速度
    // connect(timer,&QTimer::timeout,this,&Haro::eyesMovement);//关联眼部动作

    // this->size = 400;
    this->bodyNum = 0;
    this->earsNum = 0;
    imageLoad();//载入部位图片
    // eyesMovementLoad();//载入表情图片
    // specialMovementLoad();//载入特殊动作图片

    // bodyImage = new QLabel(this);//身体图片指针
    // eyesImage = new QLabel(this);//眼部图片指针
    // stripeImage = new QLabel(this);//屏幕遮盖条纹图片指针
    // earsImage = new QLabel(this);//耳朵图片指针

    // imageSet(bodyImage,body[bodyNum]);

    // imageSet(eyesImage,eyes);

    // if(size>140){
    //     imageSet(stripeImage,stripe);
    //     stripeImage->show();
    // }
    // else
    //     stripeImage->hide();

    // imageSet(earsImage,ears1[earsNum]);

    initBtn();//初始化按钮
    this->initWindow();

    // bind slots to signals
    this->bindSlots();
    // init timer
    this->timer = new Timer();
    this->timer->setSleepTime(1);
    QObject::connect(this->timer, &Timer::atTime, this, &Haro::timerSlots);
    this->timer->start();
    // initSystemTray();//初始化系统托盘
}

Haro::~Haro()
{
    //清理各类指针申请的空间
    delete ui;

    delete dressWindow;
    delete setWindow;
    delete calenWindow;
    delete musicWindow;
}

void Haro::imageSet(QLabel *image,QPixmap map)
{
    //根据size设定各图片大小和坐标
    image->setPixmap(map.scaled(size,size));//使用scaled修改图片大小，能避免图片因缩放模糊
    image->setScaledContents(true);
    image->resize(size,size);
    image->move(this->frameGeometry().width()/2 - size/2,
                this->frameGeometry().height()/2 - size/2);
}

void Haro::imageLoad()
{
    //载入装扮图片
    body.push_back(QPixmap(QString(Body::getBody(Body::Body))));
    body.push_back(QPixmap(QString(Body::getBody(Body::BlueBody))));
    body.push_back(QPixmap(QString(Body::getBody(Body::PinkBody))));
    body.push_back(QPixmap(QString(Body::getBody(Body::IceFireBody))));
    body.push_back(QPixmap(QString(Body::getBody(Body::CatBody))));
    body.push_back(QPixmap(QString(Body::getBody(Body::GundamBody))));
    body.push_back(QPixmap(QString(Body::getBody(Body::DrillBody))));
    body.push_back(QPixmap(QString(Body::getBody(Body::AngelBody))));

    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::Ear))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::BlueEar))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::PinkEar))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::IceFireEar))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::CatEar))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::GundamEar))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::DrillEar))));
    ears1.push_back(QPixmap(QString(Ear::getEar(Ear::AngelEar))));

    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::Ear2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::BlueEar2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::PinkEar2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::IceFireEar2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::CatEar2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::GundamEar2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::DrillEar2))));
    ears2.push_back(QPixmap(QString(Ear::getEar(Ear::AngelEar2))));

    eyes.load(Eye::getEye(Eye::Eye));
    stripe.load(Stripe::getStripe(Stripe::Stripe));
}

void Haro::initWindow()
{
    // reload Haro so it will looks better
    this->ui->bodyImage->setPixmap(QPixmap(QString(Body::getBody(Body::Body))).scaled(this->ui->bodyImage->size()));
    this->ui->earImage->setPixmap(QPixmap(QString(Ear::getEar(Ear::Ear))).scaled(this->ui->earImage->size()));
    this->ui->eyeImage->setPixmap(QPixmap(QString(Eye::getEye(Eye::Eye))).scaled(this->ui->eyeImage->size()));
    this->ui->stripeImage->setPixmap(QPixmap(QString(Stripe::getStripe(Stripe::Stripe))).scaled(this->ui->stripeImage->size()));

    // init all other windows
    this->dressWindow = new DressWin;

    // hide button
    this->hideOrShowButton();
}

void Haro::bindSlots()
{
    QObject::connect(this->ui->moreButton, &QPushButton::clicked, this, &Haro::onMoreButtonClicked);
    QObject::connect(this->ui->dressButton, &QPushButton::clicked, this, &Haro::onDressButtonClicked);
    QObject::connect(this->ui->closeButton, &QPushButton::clicked, this, &Haro::onCloseButtonClicked);
    QObject::connect(this->dressWindow, &DressWin::bodyChangeSignal, this, &Haro::bodyChangeSlots);
    QObject::connect(this->dressWindow, &DressWin::earChangeSignal, this, &Haro::earChangeSlots);
}

void Haro::bodyChangeSlots(int index)
{
    this->ui->bodyImage->setPixmap(QPixmap(QString(Body::getBody((enum Body::BodyName)index))).scaled(this->ui->bodyImage->size()));
}

void Haro::earChangeSlots(int index)
{
    this->ui->earImage->setPixmap(QPixmap(QString(Ear::getEar((enum Ear::EarName)index))).scaled(this->ui->earImage->size()));
}

void Haro::timerSlots()
{
    // every call means one second has elapsed
    if (this->exitSwitch >= 1)
    {
       emit this->exitSignal();
    }
    else if (this->exitSwitch >= 0)
    {
        this->exitSwitch ++;
    }
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

void Haro::initBtn()
{
    // closeBtn = new QPushButton(this);//关闭按钮
    // dressBtn = new QPushButton(this);//换装按钮
    // moreBtn = new QPushButton(this);//展开更多按钮
    // minBtn = new QPushButton(this);//最小化按钮
    // setBtn = new QPushButton(this);//设置按钮
    // musicBtn = new QPushButton(this);//音乐按钮
    // gameBtn = new QPushButton(this);//游戏按钮
    // calenBtn = new QPushButton(this);//日历按钮

    // closeBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Close))));
    // dressBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Dress))));
    // moreBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::More))));
    // minBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Min))));
    // setBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Setting))));
    // musicBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Music))));
    // gameBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Game))));
    // calenBtn->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Calendar))));

    // reInitBtn();

    // //设置按钮样式
    // setStyleSheet("QPushButton{border:4px solid black;"
    //               "background-color:rgb(200,210,255);border-radius: 10px;}"
    //               "QPushButton::hover{background-color:rgb(170,200,255);}"
    //               "QPushButton:pressed{background-color:rgb(60,70,200);}");

    // dressWindow = new DressWin;//换装窗口
    // dressWindow->accept(body,ears1,bodyNum,earsNum);

    // setWindow =  new SetWin;//设置窗口
    // setWindow->setSize(size);//为设置窗口传入size参数

    // musicWindow = new MusicWin;//音乐窗口

    // calenWindow = new QCalendarWidget;//日历窗口
    // calenWindow->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    // calenWindow->setWindowIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Calendar)))); //设置窗口图标
    // calenWindow->resize(600,400);


    // //连接按钮信号与对应槽函数
    // connect(closeBtn,&QPushButton::clicked,this,&Haro::closeBtnPush);
    // connect(this->ui->dressButton,&QPushButton::clicked,this,&Haro::dressBtnPush);
    // connect(moreBtn,&QPushButton::clicked,this,&Haro::moreBtnPush);
    // connect(minBtn,&QPushButton::clicked,this,&Haro::minBtnPush);
    // connect(setBtn,&QPushButton::clicked,this,&Haro::setBtnPush);
    // connect(musicBtn,&QPushButton::clicked,this,&Haro::musicBtnPush);
    // // connect(gameBtn,&QPushButton::clicked,this,&Haro::gameBtnPush);
    // connect(calenBtn,&QPushButton::clicked,this,&Haro::calenBtnPush);

    // btnSwitch_1 = 0;//初始化按钮显示
    // btnSwitch_2 = 0;
    // btnSwitchRole();
}

void Haro::reInitBtn()
{
    btnSize = size;

   // if(btnSize > 650)//限制按钮大小
    //    btnSize = 650;
    if(btnSize < 300)//限制按钮大小
         btnSize = 300;
    //按钮的坐标和大小参数
    int btnX = this->frameGeometry().width()/2 - btnSize*3/5-5;
    int btnY = this->frameGeometry().height()/2 - btnSize/4;
    int btnWidth = btnSize/5;
    int btnHeight = btnSize/8;

    this->ui->closeButton->setGeometry(btnX,btnY,btnWidth,btnHeight);
    // std::cout << "close button: " << btnX << ", " << btnY << ", " << btnWidth << ", " << btnHeight << std::endl;
    this->ui->dressButton->setGeometry(btnX,btnY + btnSize/6,btnWidth,btnHeight);
    // std::cout << "dress button: " << btnX << ", " << btnY + btnSize / 6 << ", " << btnWidth << ", " << btnHeight << std::endl;
    this->ui->moreButton->setGeometry(btnX,btnY + 2*btnSize/6,btnWidth,btnHeight);
    // std::cout << "more button: " << btnX << ", " << btnY+2*btnSize/6 << ", " << btnWidth << ", " << btnHeight << std::endl;
    this->ui->minButton->setGeometry(btnX,btnY + 3*btnSize/6,btnWidth,btnHeight);
    // std::cout << "min button: " << btnX << ", " << btnY+3*btnSize/6 << ", " << btnWidth << ", " << btnHeight << std::endl;

    this->ui->settingButton->setGeometry(btnX - btnWidth*1.2,btnY,btnWidth,btnHeight);
    // std::cout << "setting button: " << btnX-btnWidth*1.2 << ", " << btnY << ", " << btnWidth << ", " << btnHeight << std::endl;
    this->ui->musicButton->setGeometry(btnX - btnWidth*1.2,btnY + btnSize/6,btnWidth,btnHeight);
    // std::cout << "music button: " << btnX-btnWidth*1.2 << ", " << btnY+btnSize/6 << ", " << btnWidth << ", " << btnHeight << std::endl;
    this->ui->gameButton->setGeometry(btnX - btnWidth*1.2,btnY + 2*btnSize/6,btnWidth,btnHeight);
    // std::cout << "game button: " << btnX-btnWidth*1.2 << ", " << btnY+2*btnSize/6 << ", " << btnWidth << ", " << btnHeight << std::endl;
    this->ui->calendarButton->setGeometry(btnX - btnWidth*1.2,btnY + 3*btnSize/6,btnWidth,btnHeight);
    // std::cout << "calendar button: " << btnX-btnWidth*1.2 << ", " << btnY+3*btnSize/6 << ", " << btnWidth << ", " << btnHeight << std::endl;
    //图标大小
    // QSize temp(btnSize/8,btnSize/8);
    // std::cout << "Icon size: " << btnSize/8 << ", " << btnSize/8 << std::endl;
    // this->ui->closeButton->setIconSize(temp);
    // dressBtn->setIconSize(temp);
    // moreBtn->setIconSize(temp);
    // minBtn->setIconSize(temp);
    // setBtn->setIconSize(temp);
    // musicBtn->setIconSize(temp);
    // gameBtn->setIconSize(temp);
    // calenBtn->setIconSize(temp);

}

// void Haro::initSystemTray()
// {

//     pSystemTray = new QSystemTrayIcon(this);
//     pSystemTray->setIcon(QIcon(":/images/icon/haro_icon.ico"));
//     pSystemTray->setToolTip("Hello, I'm Haro.");
//     pSystemTray->show();
//     connect(pSystemTray,&QSystemTrayIcon::activated,this,&Haro::onSystemTrayIconActivate);

// }

void Haro::onCloseButtonClicked()
{

//    this->dressWindow->close();
//    this->setWindow->close();
//    this->musicWindow->close();
//    this->calenWindow->close();
    this->ui->eyeImage->setPixmap(QPixmap(QString(Eye::getEye(Eye::ByeEye))).scaled(this->ui->eyeImage->size()));
    if (this->exitSwitch < 0)
    {
        this->exitSwitch = 0;
    }
}

void Haro::onDressButtonClicked()
{
    if(dressWindow->isHidden()){
        dressWindow->move(x()+frameGeometry().width()/2-10
                          -btnSize*0.6-dressWindow->frameGeometry().width(),
                          y()+frameGeometry().height()/2-150
                          -dressWindow->frameGeometry().height()/2);
        dressWindow->show();
        // calenWindow->hide();
        // setWindow->hide();
        // musicWindow->hide();
        btnSwitch_2=0;
        // btnSwitchRole();
    }
    else
        dressWindow->hide();
}

void Haro::onMoreButtonClicked()
{
    if (this->moreButtonSwith == 0)
    {
        // show more button
        this->moreButtonSwith = 1;
        this->hideOrShowButton();
    }
    else
    {
        // hide more button
        this->moreButtonSwith = 0;
        this->hideOrShowButton();
    }
}

void Haro::onMinButtonClicked()
{
    //this->setWindowState(Qt::WindowMinimized);//最小化窗口（已弃用）
    this->hide();
    dressWindow->hide();
    calenWindow->hide();
    setWindow->hide();
    musicWindow->hide();

    btnSwitch_1=0;
    btnSwitch_2=0;
    btnSwitchRole();

}

void Haro::setBtnPush()
{
    if(setWindow->isHidden()){
        //移动窗口坐标↓
        setWindow->move(x()+frameGeometry().width()/2
        -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-setWindow->frameGeometry().width(),
        y()+frameGeometry().height()/2-size/5
        -setWindow->frameGeometry().height()/2);

        setWindow->show();
        calenWindow->hide();
        musicWindow->hide();
    }
    else
        setWindow->hide();
}

void Haro::musicBtnPush()
{
    if(musicWindow->isHidden()){
        //移动窗口坐标↓
        musicWindow->move(x()+frameGeometry().width()/2
        -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-musicWindow->frameGeometry().width(),
        y()+frameGeometry().height()/2-size/5
        -musicWindow->frameGeometry().height()/2);

        musicWindow->show();
        calenWindow->hide();
        setWindow->hide();
    }
    else
        musicWindow->hide();
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
    btnSwitchRole();

    this->show();
}

void Haro::calenBtnPush()
{
    if(calenWindow->isHidden()){
        //移动窗口坐标↓
        calenWindow->move(x()+frameGeometry().width()/2
        -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-calenWindow->frameGeometry().width(),
        y()+frameGeometry().height()/2-size/5
        -calenWindow->frameGeometry().height()/2);

        calenWindow->show();
        musicWindow->hide();
        setWindow->hide();
    }
    else
        calenWindow->hide();
}

void Haro::onSystemTrayIconActivate()
{
    if(this->isHidden())
    {
        this->show();
    }
    else
    {
        this->hide();
    }
    

}

void Haro::btnSwitchRole()
{
    //根据btnSwitch调整按钮是否显示
    this->ui->closeButton->setVisible(btnSwitch_1);
    this->ui->dressButton->setVisible(btnSwitch_1);
    this->ui->moreButton->setVisible(btnSwitch_1);
    this->ui->minButton->setVisible(btnSwitch_1);
    this->ui->settingButton->setVisible(btnSwitch_2);
    this->ui->musicButton->setVisible(btnSwitch_2);
    this->ui->gameButton->setVisible(btnSwitch_2);
    this->ui->calendarButton->setVisible(btnSwitch_2); 
    //移动窗口坐标↓
    // musicWindow->move(x()+frameGeometry().width()/2
    // -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-musicWindow->frameGeometry().width(),
    // y()+frameGeometry().height()/2-size/5
    // -musicWindow->frameGeometry().height()/2);
    // //移动窗口坐标↓
    // calenWindow->move(x()+frameGeometry().width()/2
    // -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-calenWindow->frameGeometry().width(),
    // y()+frameGeometry().height()/2-size/5
    // -calenWindow->frameGeometry().height()/2);


}

void Haro::mouseMoveEvent(QMouseEvent *event)
{
    // move window
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(event->globalPos() - this->mousePosition);
        // dressWindow->move(x()+frameGeometry().width()/2-10
        //                   -btnSize*0.6-dressWindow->frameGeometry().width(),
        //                   y()+frameGeometry().height()/2-150
        //                   -dressWindow->frameGeometry().height()/2);

        // musicWindow->move(x()+frameGeometry().width()/2
        // -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-musicWindow->frameGeometry().width(),
        // y()+frameGeometry().height()/2-size/5
        // -musicWindow->frameGeometry().height()/2);

        // calenWindow->move(x()+frameGeometry().width()/2
        // -btnSize*(btnSwitch_1+btnSwitch_2+1.5)/4-calenWindow->frameGeometry().width(),
        // y()+frameGeometry().height()/2-size/5
        // -calenWindow->frameGeometry().height()/2);
        // saveData();
    }
}

void Haro::mousePressEvent(QMouseEvent *event)
{
    // static int flag = 0;//触发特殊动作的计数变量
    if(event->button() == Qt::LeftButton)
    {
        // mouse left button event
        this->mousePosition = event->pos();
        // hide button
        this->basicButtonSwitch = 0;
        this->moreButtonSwith = 0;
        this->hideOrShowButton();
    // if(face<0&&spMove<0){//随机播放表情
    //     face = qrand()%(faceSum-1)+1;
    //     flag++;
    //     if(flag==10){//触发蓝屏
    //         flag = 0;
    //         spMove = 0;
    //         face = -1;
    //     }
    // }
    }
    else if(event->button() == Qt::RightButton)
    {
        // hide or show basic button
        if (this->basicButtonSwitch == 0)
        {
            this->basicButtonSwitch = 1;
            this->hideOrShowButton();
        }
        else
        {
            this->basicButtonSwitch = 0;
            this->moreButtonSwith = 0;
            this->hideOrShowButton();
        }
    }
}

void Haro::eyesMovementLoad()
{
    faceNum.push_back(9);//帧数-例：9代表9帧
    faceNum.push_back(0);//起始位置-例：0代表该表情第一张图片下标
    for(int i = 1; i<=faceNum[0]; i++)//表情1-眨眼
        movement.push_back(QPixmap(QString(":/images/movement/blink/%1.png").arg(i)));
    faceNum.push_back(12);
    faceNum.push_back(9);
    for(int i = 1; i<=faceNum[2]; i++)//表情2-心动
        movement.push_back(QPixmap(QString(":/images/movement/heart/%1.png").arg(i)));
    faceNum.push_back(16);
    faceNum.push_back(21);
    for(int i = 1; i<=faceNum[4]; i++)//表情3-疑惑
        movement.push_back(QPixmap(QString(":/images/movement/question/%1.png").arg(i)));
    faceNum.push_back(15);
    faceNum.push_back(37);
    for(int i = 1; i<=faceNum[6]; i++)//表情4-闭眼
        movement.push_back(QPixmap(QString(":/images/movement/closeEyes/%1.png").arg(i)));
    faceNum.push_back(9);
    faceNum.push_back(52);
    for(int i = 1; i<=faceNum[8]; i++)//表情5-单眨眼
        movement.push_back(QPixmap(QString(":/images/movement/wink/%1.png").arg(i)));

    face = -1;//表情序号初始化为-1，不生效
    faceSum = 5;//表情数量
}

void Haro::eyesMovement()
{
    //各种静态变量，用于计数、记录状态等↓
    static int flag = 0,second1 = 0,second2 = 0,earSwitch = 1;
    int valve = qrand()%200;
    if(face<0 && spMove<0){//控制眨眼动作
        second1++;
        if(second1>=valve && valve>100){
            face = 0;
            second1 = 0;
        }
    }

    second2++;//控制耳朵的动画
    if(second2>40 && earSwitch){
        this->ui->earImage->setPixmap(ears2[earsNum].scaled(size,size));
        earSwitch = 0;
        second2 = 0;
    }
    else if(second2>10 && !earSwitch){
        this->ui->earImage->setPixmap(ears1[earsNum].scaled(size,size));
        earSwitch = 1;
        second2 = 0;
    }

    if(face!=-1){//控制表情变化
    int num = faceNum[face*2],start = faceNum[face*2+1];
        flag++;
        if(flag<num)
            this->ui->eyeImage->setPixmap(
                        movement[start+flag].scaled(size,size));
        else
            this->ui->eyeImage->setPixmap(
                        movement[start-flag+(num-1)*2].scaled(size,size));

        if(flag>=(num-1)*2){
            flag = 0;
            face = -1;
            this->ui->eyeImage->setPixmap(eyes.scaled(size,size));
        }
    }
    // if(!dressWindow->isHidden()){//从换装窗口中获取bodyNum、earsNum参数
    //     if(bodyNum!=dressWindow->getBodyNum()){
    //         bodyNum = dressWindow->getBodyNum();
    //         this->ui->bodyImage->setPixmap(body[bodyNum].scaled(size,size));
    //         saveData();
    //     }
    //     if(earsNum!=dressWindow->getEarsNum()){
    //         earsNum = dressWindow->getEarsNum();
    //         this->ui->bodyImage->setPixmap(ears1[earsNum].scaled(size,size));
    //         saveData();
    //     }
    // }

    if(!setWindow->isHidden()){//从设置窗口中获取size参数
        if(size!=setWindow->getSize()){
            size = setWindow->getSize();

            imageSet(this->ui->bodyImage,body[bodyNum]);
            imageSet(this->ui->eyeImage,eyes);
            if(size>140){
                imageSet(this->ui->stripeImage,stripe);
                this->ui->stripeImage->show();
            }
            else
                this->ui->stripeImage->hide();
            imageSet(this->ui->earImage,ears1[earsNum]);

            saveData();
            reInitBtn();
        }
    }
    if(spMove>-1)//特殊动作
        specialMovement();
}


void Haro::specialMovementLoad()
{
    for(int i = 1;i<=11;i++)
        spMovement.push_back(QPixmap(QString(":/images/movement/error/%1.png").arg(i)));
    for(int i = 1;i<=22;i++)
        spMovement.push_back(QPixmap(QString(":/images/movement/fly/%1.png").arg(i)));

    spMove = -1;
}

void Haro::specialMovement(){
    static int flag = 0;

    if(spMove == 0){//动作-error
        if(flag%20==0 && flag<=200)
            this->ui->eyeImage->setPixmap(spMovement[flag/20].scaled(size,size));
        else if(flag>300){
            this->ui->eyeImage->setPixmap(eyes.scaled(size,size));
            flag=0;
            spMove=-1;
            return ;
        }

    }


    flag++;
}

void Haro::saveData()
{
    QFile file("/home/syize/Documents/C++/coursework-a-table-pet-Haro/res/file/file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out<<size<<bodyNum<<earsNum<<x()<<y();//存储体型、装扮编号参数、窗口坐标
    file.close();
}





