#include "setwin.h"
#include "ui_setwin.h"
#include "resources.h"
#include <QSlider>
#include <QSpinBox>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QCheckBox>
#include <iostream>
#include <QStringList>
#include <QApplication>
#include <stdlib.h>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QFileDevice>
#include <QIODevice>
#include <QTextStream>

SetWin::SetWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWin)
{
    ui->setupUi(this);

    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
    setWindowOpacity(0.95);//设置透明度
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

    // this->setWindowIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Setting)))); //设置窗口图标

    // bind slot
    QObject::connect(this->ui->haroSizeSlider, &QSlider::valueChanged, this, &SetWin::onSliderValueChanged);
    QObject::connect(this->ui->sliderValueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
    QObject::connect(this->ui->changeGameButton, &QPushButton::clicked, this, &SetWin::onChangeGameButtonClicked);
    QObject::connect(this->ui->hideWhenRunGame, &QCheckBox::stateChanged, this, &SetWin::onHideHaroCheckBoxChanged);
    QObject::connect(this->ui->startOnBoot, &QCheckBox::stateChanged, this, &SetWin::onBootOnStartCheckBoxChanged);
    // QObject::connect(this->ui->sliderValueSpinBox, &QSpinBox::valueChanged, this, &SetWin::onSpinBoxValueChanged);
    // read settings
    this->settings = new QSettings("Haro", "Haro");
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
    this->ui->sliderValueSpinBox->setValue(value);
    emit this->sliderValueChanged(value);
    // haroSize = value;
    // sizeNum->setNum(haroSize);
}

void SetWin::onSpinBoxValueChanged(int value)
{
    this->ui->haroSizeSlider->setValue(value);
    emit this->sliderValueChanged(value);
}

int SetWin::getSize()
{
    return this->ui->haroSizeSlider->value();
}

void SetWin::showEvent(QShowEvent* event)
{
    QString gamePath = this->settings->value("Game/File", "").toString();
    if (gamePath.length() == 0)
    {
        // no selected game
        this->ui->gameIconLabel->setPixmap(QPixmap(QString(HaroIcon::getIcon(HaroIcon::Icon))).scaled(40, 40));
        this->ui->hideWhenRunGame->setEnabled(false);
    }
    else
    {
        // get game name
        QFileInfo gameInfo(gamePath);
        QString gameName = gameInfo.fileName();
        // get game icon
        QFileSystemModel* model = new QFileSystemModel;
        model->setRootPath(gameInfo.path());
        QIcon gameIcon = model->iconProvider()->icon(gameInfo);
        this->ui->gameIconLabel->setPixmap(gameIcon.pixmap(gameIcon.availableSizes().last()).scaled(40, 40));
        this->ui->gameIconLabel->setToolTip(gameName);
        this->ui->hideWhenRunGame->setEnabled(true);
        this->ui->hideWhenRunGame->setChecked(
            this->settings->value("Game/Hide", true).toBool()
        );
        this->ui->startOnBoot->setChecked(
            this->settings->value("AutoStart", false).toBool()
        );
    }
    event->accept();
}

void SetWin::onChangeGameButtonClicked()
{
    // hide haro so it won't stay on the top of select window
    emit this->hideHaroSignal(1);
    // get file path
    QString gamePath = QFileDialog::getOpenFileName(this, tr("Select Program"), "./", tr("Executable(*.exe);;Link(*.lnk);;All(*.*)"));
    // save settings
    this->settings->setValue("Game/File", gamePath);
    this->settings->sync();
    // show haro
    emit this->showHaroSignal(1);
}

void SetWin::onHideHaroCheckBoxChanged(int state)
{
    if (state == 0)
    {
        this->settings->setValue("Game/Hide", false);
    }
    else
    {
        this->settings->setValue("Game/Hide", true);
    }
    this->settings->sync();
}

void SetWin::onBootOnStartCheckBoxChanged(int state)
{
    if (state == 0)
    {
        // remove auto start entry based on plantform
        #ifdef _WIN32
            // haven't work out on Windows
        #else
            // remove auto start desktop from $HOME/.config/autostart
            // get home path
            QString homePath(getenv("HOME"));
            // check if it's "/"
            if (homePath.compare(QString("/")) != 0)
            {
                // auto start dir path
                QString autoStartDirPath = homePath + "/.config/autostart/";
                QDir* autoStartDir = new QDir(autoStartDirPath);
                // check if autostart directory exists
                if (autoStartDir->exists())
                {
                    // auto start desktop file path
                    QString autoStartDesktopDesPath = autoStartDirPath + "Haro.desktop";
                    QFile autoStartDesktop(autoStartDesktopDesPath);
                    autoStartDesktop.moveToTrash();
                    
                    // save to settings
                    this->settings->setValue("AutoStart", false);
                }
            }
        #endif
    }
    else
    {
        // add auto start entry based on plantform
        #ifdef _WIN32
            // haven't work out on Windows
        #else
            // put desktop file in $HOME/.config/autostart
            // get home path
            QString homePath(getenv("HOME"));
            // check if it's "/"
            if (homePath.compare(QString("/")) != 0)
            {
                // auto start dir path
                QString autoStartDirPath = homePath + "/.config/autostart/";
                QDir* autoStartDir = new QDir(autoStartDirPath);
                // check if autostart directory exists
                if (! autoStartDir->exists())
                {
                    autoStartDir->mkdir(autoStartDirPath);
                }
                // auto start desktop file path
                QString autoStartDesktopDesPath = autoStartDirPath + "Haro.desktop";
                // get executable path
                QString appFilePath = QApplication::applicationFilePath();
                // export autostart desktop file to /tmp
                QFile autoStartDesktop(":/file/res/file/Haro-autostart.desktop");
                autoStartDesktop.copy(QString("/tmp/Haro.desktop"));
                // replace {HARO_PATH} with appFilePath
                QFile autoStartDesktopTemp("/tmp/Haro.desktop");
                // change permission
                autoStartDesktopTemp.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
                autoStartDesktopTemp.open(QIODevice::ReadWrite);
                QTextStream stream(&autoStartDesktopTemp);
                QString streamContent = stream.readAll();
                streamContent.replace("{HARO_PATH}", appFilePath);
                autoStartDesktopTemp.seek(0);
                stream << streamContent;
                autoStartDesktopTemp.close();
                // move desktop file to autostart dir
                autoStartDesktopTemp.rename(autoStartDesktopDesPath);
                // save to settings
                this->settings->setValue("AutoStart", true);

                // this->settingProcess->setProgram(QString("touch"));
                // QStringList arguments;
                // arguments << "/tmp/test";
                // this->settingProcess->setArguments(arguments);
                // this->settingProcess->start();   
            }
        #endif
    }
}