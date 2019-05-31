#ifndef DLGCONTAINER_H
#define DLGCONTAINER_H

#include <QDialog>

namespace Ui {
class CDlgContainer;
}

class CDlgContainer : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgContainer(QWidget *parent = nullptr);
    virtual ~CDlgContainer() override;
    
    int setWidget(QWidget* pWidget);
    
private:
    Ui::CDlgContainer *ui;
    
protected:
    virtual void showEvent(QShowEvent *event) override;
private slots:
    void on_pbOk_clicked();
    void on_pbCancle_clicked();
};

#endif // DLGCONTAINER_H
