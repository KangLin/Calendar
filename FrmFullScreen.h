#ifndef FRMLOCKSCREEN_H
#define FRMLOCKSCREEN_H

#pragma once
#include <QWidget>

namespace Ui {
class CFrmFullScreen;
}

class CFrmFullScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmFullScreen(QWidget *parent = 0);
    ~CFrmFullScreen();
    
    int Prompt(const QString szPrompt, int nValue = 0, int nMin = 0,  int nMax = 100, bool bInverted = false);
    
private:
    Ui::CFrmFullScreen *ui;
};

#endif // FRMLOCKSCREEN_H
