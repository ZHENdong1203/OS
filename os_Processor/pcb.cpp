#include "pcb.h"
#include <iostream>
#include <QElapsedTimer>
#include <QCoreApplication>

PCB::PCB(){
    _size = 0;
    pHeader = new pcbNode;
    pTrailer = new pcbNode;
    pHeader->Pnext = pTrailer;
    pTrailer->Pfront = pHeader;
}

PCB::~PCB() {
    while (pHeader->Pnext != pTrailer)
        toRemove(pHeader->Pnext);
    delete pHeader;
    delete pTrailer;
}//析构函数

int PCB::getSize() const {
    return _size;
}

pcbNode* PCB::getEnque() {
    return pHeader->Pnext;
}//获取队首

void PCB::changeState(QString str) {
    getEnque()->state = str;
}//改变状态

void PCB::insertPCB(int e1, int e2, int e3) {
    pcbNode *pNew = new pcbNode;
    pNew->PID = Random(1000);//获取0-999之间的随机数
    pNew->PTI = e1;
    pNew->PSO = e2;
    pNew->PRI = e3;
    pNew->state = "Waiting";
    pTrailer->Pfront->Pnext = pNew;
    pNew->Pfront = pTrailer->Pfront;
    pNew->Pnext = pTrailer;
    pTrailer->Pfront = pNew;
    _size++;
}//新建一个进程

void PCB::copyPCB(pcbNode *p) {
    pcbNode *pNew = new pcbNode;
    pNew->PID = p->PID;
    pNew->PTI = p->PTI;
    pNew->PSO = p->PSO;
    pNew->PRI = p->PRI;
    pNew->PMB = p->PMB;
    pNew->state = p->state;
    pTrailer->Pfront->Pnext = pNew;
    pNew->Pfront = pTrailer->Pfront;
    pNew->Pnext = pTrailer;
    pTrailer->Pfront = pNew;
    _size++;
}

void PCB::deletePCB(pcbNode *n){
    int e = toRemove(n);
}

void PCB::exchangePCB(PCB &P) {
    pcbNode *p = pHeader->Pnext;
    deletePCB(pHeader->Pnext);
    P.copyPCB(p);
}

void PCB::swapPCB(pcbNode *p, pcbNode *q) {
    int temp;
    QString Temp;

    temp = p->PID;
    p->PID = q->PID;
    q->PID = temp;

    temp = p->PTI;
    p->PTI = q->PTI;
    q->PTI = temp;

    temp = p->PSO;
    p->PSO = q->PSO;
    q->PSO = temp;

    temp = p->PRI;
    p->PRI = q->PRI;
    q->PRI = temp;

    temp = p->PMB;
    p->PMB = q->PMB;
    q->PMB = temp;

    Temp = p->state;
    p->state = q->state;
    q->state = Temp;
}//交换两个进程的信息

void PCB::bubblePCB() {
    int count = _size;
    pcbNode *p = pHeader->Pnext;
    while(count > 0){
        for(p = pHeader->Pnext; p->Pnext != pTrailer; p = p->Pnext){
            if(p->PRI < p->Pnext->PRI){
                swapPCB(p, p->Pnext);
                QElapsedTimer et;
                et.start();
                while(et.elapsed()<300)
                    QCoreApplication::processEvents();
            }
        }
        count--;
        p = pHeader->Pnext;
    }
}

int PCB::toRemove(pcbNode *p) {
    //std::cout << p << "--" << pTrailer << "---" << pHeader <<std::endl;
    int e = p->PID;
    p->Pfront->Pnext = p->Pnext;
    p->Pnext->Pfront = p->Pfront;
    delete p;
    _size--;
    return e;
}
