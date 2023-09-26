#ifndef SETWIN_H
#define SETWIN_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QShowEvent>
#include <QSettings>
#include <QFileDialog>

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
    void onHideHaroCheckBoxChanged(int);

public slots:
    void onChangeGameButtonClicked();

private:
    Ui::SetWin *ui;
    QSettings* settings;
    // check game whenever show setting window
    void showEvent(QShowEvent* event);

signals:
    void sliderValueChanged(int);
    void hideHaroSignal(int);
    void showHaroSignal(int);
};

#endif // SETWIN_H
