#ifndef CONDITION_H
#define CONDITION_H


class Condition
{
public:
    Condition();
    void setId(int id_l){id = id_l;}
    int getId(){return id;}

    void setType(int tp){type = tp;}
    int getType(){return type;}

    void setTrueOrFalse(bool flag){trueOrFalse = flag;}
    bool getTrueOrFalse(){return trueOrFalse;}

    int id;
    int type; // 0 : if, 1: while etc
    bool trueOrFalse; // connected edge
};

#endif // CONDITION_H
