#ifndef PCB_H
#define PCB_H
#include <QString>
#include <cstdlib>
#include <ctime>
//#include "mainwindow.h"
#define Random(x) (rand()%x+1) //产生一个1-x的随机数

typedef struct pcbNode{
    int PID;//进程名
    int PTI;//所需时间
    int PSO;//所需资源
    int PRI;//优先权
    int PMB;//Memorybase
    QString state;//状态
    pcbNode* Pnext;
    pcbNode* Pfront;
}pcb;

class PCB {
private:
    int _size;
    pcbNode* pHeader;//哨兵
    pcbNode* pTrailer;//哨兵

public:
    PCB();
    ~PCB();

    int getSize() const;//获取规模
    pcbNode* getEnque();//获取队首

    void changeState(QString str);
    void insertPCB(int e1, int e2, int e3);//尾插法插入节点
    void copyPCB(pcbNode *p);//复制节点
    void deletePCB(pcbNode *n);//删除节点
    void exchangePCB(PCB &P);//转移节点
    void swapPCB(pcbNode *p, pcbNode *q);//交换节点
    void bubblePCB();//冒泡排序


    int toRemove(pcbNode *p);

    friend class MainWindow;
};

static PCB qWait;//后备队列
static PCB qReady;//就绪队列
static PCB qRun;//运行队列
static PCB qSus;//挂起队列
static PCB qFin;//完成队列
static int num = 100;
#endif // PCB_H
