#include "setwin.h"
#include "ui_setwin.h"
#include "resources.h"
#include <QSlider>

SetWin::SetWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWin)
{
    ui->setupUi(this);

    // QBitmap bmp(this->size());//设置圆角边框
    // bmp.fill();
    // QPainter p(&bmp);
    // p.setPen(Qt::NoPen);
    // p.setBrush(Qt::black);
    // p.drawRoundedRect(bmp.rect(),50,50);
    // setMask(bmp);
    // setWindowOpacity(0.95);//设置透明度
    // setStyleSheet("background-color:white;");

    // Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    // setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);//保持窗口置顶2

    // this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    // QPalette palette = QPalette();
    // palette.setColor(QPalette::Window, QColor(0x00, 0xFF, 0x00, 0x00));
    // this->setPalette(palette);
    // make window stay on top and hide window frame based on system
    #ifdef _WIN32
        // On Windows we need to set Qt::Tool so this app won't show in Windows' taskbar
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    #else
        // On Linux we need to set Qt::X11BypassWindowManagerHint so this app won't show in taskbar
        // Note if you want to use this app on wayland, you need to install x11-wayland and set env QT_QPA_PLATFORM="xcb" to force qt use X11 backend
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    #endif

    this->setWindowIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Setting)))); //设置窗口图标

    // bind slot
    QObject::connect(this->ui->haroSizeSlider, &QSlider::valueChanged, this, &SetWin::onSliderValueChanged);

}

SetWin::~SetWin()
{
    delete ui;
}

void SetWin::setSize(int size)
{
    this->ui->haroSizeSlider->setValue(size);

    // QFont ft;
    // ft.setPointSize(12);
    // QPalette pa;
    // pa.setColor(QPalette::WindowText,Qt::blue);
    // sizeNum = new QLabel(this);
    // sizeNum->move(120,100);
    // sizeNum->resize(120,20);
    // sizeNum->setFont(ft);
    // sizeNum->setPalette(pa);
    // sizeNum->setNum(haroSize);
    // sizeNum->show();

    // ui->sizeSlider->setValue(haroSize);
}

void SetWin::onSliderValueChanged(int value)
{
    // set number
    this->ui->sliderValueLabel->setText(QString("%1 px").arg(value));
    emit this->sliderValueChanged(value);
    // haroSize = value;
    // sizeNum->setNum(haroSize);
}
