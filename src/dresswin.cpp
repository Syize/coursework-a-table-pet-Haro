#include "dresswin.h"
#include "ui_dresswin.h"
#include "resources.h"

DressWin::DressWin(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::DressWin)
{

    this->ui->setupUi(this);

    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
    setWindowOpacity(0.95);//设置透明度
    // setStyleSheet("background-color:white;");

    #ifdef _WIN32
        // On Windows we need to set Qt::Tool so this app won't show in Windows' taskbar
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    #else
        // On Linux we need to set Qt::X11BypassWindowManagerHint so this app won't show in taskbar
        // Note if you want to use this app on wayland, you need to install x11-wayland and set env QT_QPA_PLATFORM="xcb" to force qt use X11 backend
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    #endif

    this->setWindowIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Dress)))); //设置窗口图标

    this->initWindow();

    // read settings
    this->settings = new QSettings("Haro", "Haro");
    this->bodysGroup->button(this->settings->value("Body", 0).toInt())->setChecked(true);
    this->earsGroup->button(this->settings->value("Ear", 0).toInt())->setChecked(true);
}

void DressWin::initWindow()
{
    // Add body preview and select button to scrollArea
    // Calculate widget height size at first
    int maximum_num = Body::BodyNum > Ear::EarNum ? Body::BodyNum : Ear::EarNum;
    // Preview area is 240x240, select button is 80x40. We want there to be some overlap between preview area so it will looks more compact
    // Overlap size between preview area in the same line, between preview area and select button is both 30
    // The length from select button to the left side of its corresponding preview area is 80
    // Here is the conceptual graphs
    /* --------------------------------------------------------------
     * |<---------------240-------------->|                         |
     * |                         |<---------------240-------------->|
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * |          preview 1      |<--30-->|   preview 2             |
     * |                         |        |                         |
     * |                         |        |                         |
     * |          button 1       |        |   button 2              |
     * |            \            |        |     \                   |
     * |          ^ ----^------  |        |   ----^------  ^        |
     * |          | |  30     |  |        |   |  30     |  |        |
     * ----------40-|---v-----|---------------|---v-----|-40---------
     * |          | |         |  |        |   |         |  |        |
     * |          v -----------  |        |   -----------  v        |
     * |            <---80---->  |        |   <---80---->           |
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * |          preview 3      |        |   preview 4             |
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * |                         |        |                         |
     * --------------------------------------------------------------
     */

    // resize scrollAreaWidget
    int currentWidth = this->ui->scrollAreaWidgetContents->width();
    this->ui->scrollAreaWidgetContents->resize(currentWidth, maximum_num * 240 + 20);
    // set button style
    this->setStyleSheet("QPushButton{border:none; background-color:rgb(200,200,200); border-radius: 15px; border-style:outset;}"
                        "QPushButton::hover{background-color:rgb(170,200,255);}"
                        "QPushButton:checked{background-color:rgb(100,120,230);}");
    // create button group
    this->bodysGroup = new QButtonGroup;
    this->earsGroup = new QButtonGroup;
    // set exclusive
    this->bodysGroup->setExclusive(true);
    this->earsGroup->setExclusive(true);

    // add body preview area and select button
    this->bodyButtons = new QPushButton[Body::BodyNum];
    this->bodyPreviews = new QLabel[Body::BodyNum];
    for (int i = 0; i < Body::BodyNum; i++)
    {
        this->bodyPreviews[i].setParent(this->ui->scrollAreaWidgetContents);
        this->bodyPreviews[i].setFixedSize(240, 240);
        this->bodyPreviews[i].move(0, 240 * i);
        this->bodyPreviews[i].setScaledContents(true);
        this->bodyPreviews[i].setPixmap(QPixmap(QString(Body::getBody((enum Body::BodyName)i))).scaled(240, 240));

        this->bodyButtons[i].setParent(this->ui->scrollAreaWidgetContents);
        this->bodyButtons[i].setStyleSheet("QPushButton{border:none; background-color:rgb(200,200,200); border-radius: 15px; border-style:outset;}"
                                           "QPushButton::hover{background-color:rgb(170,200,255);}"
                                           "QPushButton:checked{background-color:rgb(100,120,230);}");
        this->bodyButtons[i].setFixedSize(80, 40);
        this->bodyButtons[i].move(80, 240 * (i + 1) - 30);
        this->bodyButtons[i].setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Choose))));
        this->bodyButtons[i].setCheckable(1);
        this->bodysGroup->addButton(&(this->bodyButtons[i]), i);
    }

    // add ear preview area and select button
    this->earButtons = new QPushButton[Ear::EarNum];
    this->earPreviews = new QLabel[Ear::EarNum];
    this->dummyPreviews = new QLabel[Ear::EarNum];
    for (int i = 0; i < Ear::EarNum; i++)
    {
        this->dummyPreviews[i].setParent(this->ui->scrollAreaWidgetContents);
        this->dummyPreviews[i].setFixedSize(240, 240);
        this->dummyPreviews[i].move(210, 240 * i);
        this->dummyPreviews[i].setScaledContents(true);
        this->dummyPreviews[i].setPixmap(QPixmap(QString(Body::getBody(Body::Dummy))).scaled(240, 240));

        this->earPreviews[i].setParent(this->ui->scrollAreaWidgetContents);
        this->earPreviews[i].setFixedSize(240, 240);
        this->earPreviews[i].move(210, 240 * i);
        this->earPreviews[i].setScaledContents(true);
        this->earPreviews[i].setPixmap(QPixmap(QString(Ear::getEar((enum Ear::EarName)i))).scaled(240, 240));

        this->earButtons[i].setParent(this->ui->scrollAreaWidgetContents);
        this->earButtons[i].setStyleSheet("QPushButton{border:none; background-color:rgb(200,200,200); border-radius: 15px; border-style:outset;}"
                                          "QPushButton::hover{background-color:rgb(170,200,255);}"
                                          "QPushButton:checked{background-color:rgb(100,120,230);}");
        this->earButtons[i].setFixedSize(80, 40);
        this->earButtons[i].move(290, 240 * (i + 1) - 30);
        this->earButtons[i].setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Choose))));
        this->earButtons[i].setCheckable(1);
        this->earsGroup->addButton(&(this->earButtons[i]), i);
    }

    // set default checked button
    this->bodyButtons[0].setChecked(true);
    this->earButtons[0].setChecked(true);

    //当信号存在重载函数时，需要使用函数指针进行强制类型转换
    connect(bodysGroup,
            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::idClicked),
            this,&DressWin::bodyChange);
    connect(earsGroup,
            static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::idClicked),
            this,&DressWin::earsChange);
}

DressWin::~DressWin()
{
    delete ui;
}

void DressWin::bodyChange(int id)
{
    emit this->bodyChangeSignal(id);
    // bodyNum = id;
}

void DressWin::earsChange(int id)
{
    emit this->earChangeSignal(id);
    // earsNum = id;
}