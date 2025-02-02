#ifndef DRESSWIN_H
#define DRESSWIN_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QSettings>

namespace Ui {
class DressWin;
}

class DressWin : public QWidget
{
    Q_OBJECT

public:
    DressWin(QWidget *parent = nullptr);
    ~DressWin();

signals:
    void bodyChangeSignal(int);
    void earChangeSignal(int);

private:
    // init window
    void initWindow();
    void bodyChange(int);//槽函数-点击按钮切换对应装扮序号
    void earsChange(int);
    QPushButton *bodyButtons, *earButtons;
    QLabel *bodyPreviews, *earPreviews, *dummyPreviews;
    QButtonGroup *bodysGroup,*earsGroup;//按钮组
    Ui::DressWin *ui;
    QSettings* settings;
};

#endif // DRESSWIN_H
