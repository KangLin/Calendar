// 作者：康林 <kl222@126.com>

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
    
    CTasksList::POSITION pos = m_plstTasks->GetFirst();
    QSharedPointer<CTasks> tasks = m_plstTasks->GetNext(pos);
    while(tasks)
    {
        QGroupBox *pGb = new QGroupBox(
                    tr("Tasks: %1; Id: %2").arg(tasks->GetTitle(),
                                 QString::number(tasks->GetId())),
                    ui->widget);
        if(!pGb)
            break;
        ui->widget->layout()->addWidget(pGb);

        CTasks::POSITION posTasks = tasks->GetFirst();
        QSharedPointer<CTask> task = tasks->GetNext(posTasks);
        while(task)
        {
            if(!pGb->layout())
            {
                pGb->setLayout(new QHBoxLayout(pGb));
            }
            
            QVBoxLayout *pVbLayout = new QVBoxLayout(pGb);
            pGb->layout()->addItem(pVbLayout);
            
            QLabel *label = new QLabel(pGb);
            if(tasks->GetCurrent() == task)
            {
                QPalette lablePalette = label->palette();
                lablePalette.setColor(QPalette::Window,
                                      lablePalette.color(QPalette::Highlight));
                label->setPalette(lablePalette);
            }
            label->setText(tr("Id: %1 Title: %2").arg(
                            QString::number(task->GetId()), task->GetTitle()));
            pVbLayout->addWidget(label);
            CViewTaskProperty *m_pProperty = new CViewTaskProperty(task, pGb);
            pVbLayout->addWidget(m_pProperty);
            task = tasks->GetNext(posTasks);
        }
        tasks = m_plstTasks->GetNext(pos);
    }    
}

CFrmTaskProperty::~CFrmTaskProperty()
{
    delete ui;
    qDebug() << "CFrmTaskProperty::~CFrmTaskProperty";
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
