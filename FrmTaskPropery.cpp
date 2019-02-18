#include "Global/GlobalDir.h"
#include "FrmTaskPropery.h"
#include "ui_FrmTaskProperty.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QList>
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDir>
#include <QLabel>

CFrmTaskProperty::CFrmTaskProperty(CTasksList *plstTasks,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTaskProperty)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    m_plstTasks = plstTasks;
    
    if(!ui->widget->layout())
    {
        setLayout(new QVBoxLayout(ui->widget));
    }
    if(!ui->widget->layout())
        return;
    
    int nIndex = 0;
    
    QSharedPointer<CTasks> tasks = m_plstTasks->Get(nIndex++);
    while(tasks)
    {
        QGroupBox *pGb = new QGroupBox(
                    tr("Tasks: %1; Id: %2").arg(tasks->GetTitle(),
                                 QString::number(tasks->GetId())),
                    ui->widget);
        if(!pGb)
            break;
        ui->widget->layout()->addWidget(pGb);
        int n = 0;
        QSharedPointer<CTask> task = tasks->Get(n++);
        while(task)
        {
            if(!pGb->layout())
            {
                pGb->setLayout(new QHBoxLayout(pGb));
            }
            
            QVBoxLayout *pVbLayout = new QVBoxLayout(pGb);
            pGb->layout()->addItem(pVbLayout);
            
            QLabel *lable = new QLabel(pGb);
            if(tasks->Get() == task)
            {
                QPalette lablePalette = lable->palette();
                lablePalette.setColor(QPalette::Foreground,
                                      lablePalette.color(QPalette::Highlight));
                lable->setPalette(lablePalette);
            }
            lable->setText(tr("Id: %1 标题: %2").arg(
                            QString::number(task->GetId()), task->GetTitle()));
            pVbLayout->addWidget(lable);
            CViewTaskProperty *m_pProperty = new CViewTaskProperty(task, pGb);
            pVbLayout->addWidget(m_pProperty);
            task = tasks->Get(n++);
        }
        tasks = m_plstTasks->Get(nIndex++);
    }    
}

CFrmTaskProperty::~CFrmTaskProperty()
{
    delete ui;
}

void CFrmTaskProperty::on_pbSave_clicked()
{
    // Save configure
    m_plstTasks->SaveSettings();
    close();
}

void CFrmTaskProperty::on_pbCancle_clicked()
{
    close();
}
