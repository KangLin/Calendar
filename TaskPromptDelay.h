#ifndef TASKPROMPTDELAY_H
#define TASKPROMPTDELAY_H

#pragma once
#include "TaskPrompt.h"

class CTaskPromptDelay : CTaskPrompt
{
    Q_OBJECT

public:
    explicit CTaskPromptDelay(QObject* parent = nullptr);
    explicit CTaskPromptDelay(const QString szText,
                        const QString szTitle = tr("Prompt"),
                        int nInterval = 5 * 60 * 1000,
                        int nPromptInterval = 1000,
                        QObject *parent = nullptr);
    CTaskPromptDelay(const CTaskPromptDelay &task);

    QString GetDescription() const override;
    virtual int SaveSettings(QDomElement &e) override;

    /**
     * @brief Check if the task can run
     * @return : 0, The task is finished. other, The task is continue.
     */
    virtual int Check() override;

private Q_SLOTS:
    void slotDelay5Minute(bool checked);

private:
    int Init();
    QList<QSharedPointer<CTaskPromptDelay>> m_Delay;
    bool m_bStop;
    QMenu m_Menu;

    int AddDelay(int nMinute);
};

Q_DECLARE_METATYPE(CTaskPromptDelay)
#endif // TASKPROMPTDELAY_H
