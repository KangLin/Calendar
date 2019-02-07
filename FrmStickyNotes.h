#ifndef FRMSTICKYNOTES_H
#define FRMSTICKYNOTES_H

#include <QWidget>
#include <iostream>

namespace Ui {
class CFrmStickyNotes;
}

class CFrmStickyNotes : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmStickyNotes(QWidget *parent = nullptr);
    ~CFrmStickyNotes();
    
    int Load(std::istream in);
    int Save(std::ostream out);
    
private:
    Ui::CFrmStickyNotes *ui;
};

#endif // FRMSTICKYNOTES_H
