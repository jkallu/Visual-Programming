#ifndef BLOCK_H
#define BLOCK_H

#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <fstream>

class Block : public QWidget
{
public:
    Block(int id_l);
    void initBlock();
    void setId(int id_l);
    void setBlockEnabled(bool flagEn){flagEnabled = flagEn;}
    bool isBlockEnabled(){return flagEnabled;}

    int id;
    int count;
    QLabel *lblName;
    QLabel *lblNameGrid;
    QLineEdit *leName;
    QGridLayout *boxLayout;
    QGroupBox *groupBox;

private:
    bool flagEnabled;
};

#endif // BLOCK_H
