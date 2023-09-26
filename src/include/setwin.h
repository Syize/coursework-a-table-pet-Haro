#ifndef SETWIN_H
#define SETWIN_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QString>

namespace Ui {
class SetWin;
}

class SetWin : public QWidget
{
    Q_OBJECT

public:
    explicit SetWin(QWidget *parent = nullptr);
    ~SetWin();

    void setSize(int);//设置size值
    // return windows size
    int getSize();

private slots:
    void onSliderValueChanged(int value);//滑动条槽函数
    void onSpinBoxValueChanged(int value);

private:
    Ui::SetWin *ui;

signals:
    void sliderValueChanged(int);
};

#endif // SETWIN_H
