#ifndef TASKPROMPTDELAY_H
#define TASKPROMPTDELAY_H

#include "TaskPrompt.h"

class CTaskPromptDelay : public CTaskPrompt
{
    Q_OBJECT
public:
    explicit CTaskPromptDelay(QObject *parent = nullptr);
    explicit CTaskPromptDelay(const QString szContent,
                            const QString szTitle = tr("PromptDelay"),
                            int nInterval = 5 * 60 * 1000,
                            int nPromptInterval = 1000,
                            QObject *parent = nullptr);
    CTaskPromptDelay(const CTaskPromptDelay &task);
    
    virtual QString GetDescription() const override;
    
    /**
     * @brief Check if the task can run
     * @return : 0, The task is finished. other, The task is continue.
     */
    virtual int Check() override;
    virtual int onStart() override;
    
private Q_SLOTS:
    void slotDelay5Minute(bool checked);
    void slotDelayCustomize(bool checked);

private:
    int Init();
    int AddDelay(int nMinute);
    
    bool m_bStop;
    QMenu m_Menu;
    
    QVector<QSharedPointer<CTaskPromptDelay> > m_Delay;
};

Q_DECLARE_METATYPE(CTaskPromptDelay)
#endif // TASKPROMPTDELAY_H
