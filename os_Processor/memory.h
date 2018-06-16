#ifndef MEMORY_H
#define MEMORY_H

#include <QString>
class memory{
public:
    int ms;//整型起始地址
    int ml;//整型地址长度
    QString memorystart;//字符串型起始地址
    QString memorylength;//字符串型地址长度
    QString memorystate;//字符串型分区状态

    memory();
    //可写接口
    void setMemory(QString a, QString b, QString c);//设置分区数据
    void copyMemory(memory &a);//分区数据拷贝
    //辅助函数
    void setMS();
    void setML();

    friend class MainWindow;
};

static memory m[10];
#endif // MEMORY_H
