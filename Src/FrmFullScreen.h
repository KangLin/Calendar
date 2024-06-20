// 作者：康林 <kl222@126.com>

#ifndef FRMLOCKSCREEN_H
#define FRMLOCKSCREEN_H

#pragma once
#include <QWidget>
#include <QTimer>
#include <QImage>

namespace Ui {
class CFrmFullScreen;
}

class CFrmFullScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmFullScreen(QWidget *parent = nullptr);
    virtual ~CFrmFullScreen();
    
    int Prompt(const QString szPrompt, int nValue = 0, int nMin = 0,  int nMax = 100, bool bInverted = false);
    int SetBackgroupImage(const QString szImage);
    int SetBackgroupImage(const QImage img);
    
protected:
    virtual void paintEvent(QPaintEvent *event);
    
private Q_SLOTS:
    void slotTimeout();
    
private:
    Ui::CFrmFullScreen *ui;
    QTimer m_Timer;
    QImage m_bpBackgroup;
};

#endif // FRMLOCKSCREEN_H
