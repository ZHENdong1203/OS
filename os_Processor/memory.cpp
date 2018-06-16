#include "memory.h"

memory::memory(){
    ms = 101;
    ml = 101;
    memorystart = " ";
    memorylength = " ";
    memorystate = "空表目";
}

void memory::setMemory(QString a, QString b, QString c){
    memorystart = a;
    memorylength = b;
    memorystate = c;
    setMS();
    setML();
}

void memory::copyMemory(memory &a){
    memorystart = a.memorystart;
    memorylength = a.memorylength;
    memorystate = a.memorystate;
    setMS();
    setML();
}

void memory::setMS(){
    if(memorystart == " ")
        ms = 101;
    else
        ms = memorystart.toInt();
}

void memory::setML(){
    if(memorylength == " ")
        ml = 101;
    else
        ml = memorylength.toInt();
}



