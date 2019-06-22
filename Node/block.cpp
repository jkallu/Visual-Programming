#include "block.h"

Block::Block(int id_l)
{
    initBlock();
    setId(id_l);
}

void Block::initBlock(){
    flagEnabled = true;
    leName = new QLineEdit;

    lblName = new QLabel("Name");
    lblNameGrid = new QLabel;

    groupBox = new QGroupBox("Block");
    groupBox->setFlat(true);

    boxLayout = new QGridLayout;
    boxLayout->addWidget(lblName, 0, 0);
    boxLayout->addWidget(leName, 0, 1);
    //boxLayout->addStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setMinimumWidth(300);
}

void Block::setId(int id_l){
    id = id_l;
}
