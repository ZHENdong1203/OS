#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <windows.h>
#include <QElapsedTimer>
#include<QPainter>

bool hhh = false, fff = false;
int MMM =0, Size = 0;


void MainWindow::paintEvent(QPaintEvent *event)
{
QPainter paint(this);
paint.setPen(Qt::black);
paint.drawRect(1490,50,220,590);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->insertPRIlineEdit->setFocusPolicy(Qt::NoFocus);
    ui->insertPTIlineEdit->setFocusPolicy(Qt::NoFocus);
    ui->insertPSOlineEdit->setFocusPolicy(Qt::NoFocus);

    ui->Runningtable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->Runningtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Runningtable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Suspendtable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->Suspendtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Suspendtable->setSelectionMode(QAbstractItemView::SingleSelection);
    createSusMenu();
    createNoSusMenu();
    connect(ui->Runningtable,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_susrightMenu(QPoint)));
    connect(ui->Suspendtable,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_nosusrightMenu(QPoint)));

    QElapsedTimer et;
    et.start();
    while(et.elapsed()<300)
        QCoreApplication::processEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setQueModel(PCB *p, QTableView *qtv) {
    int flag = p->getSize();
    pcbNode *pEnd = p->getEnque();
    QStandardItemModel *qmodel = new QStandardItemModel();
    qmodel->setColumnCount(5);
    qmodel->setHeaderData(0, Qt::Horizontal, tr("PID"));
    qmodel->setHeaderData(1, Qt::Horizontal, tr("PRI"));
    qmodel->setHeaderData(2, Qt::Horizontal, tr("SOURCE"));
    qmodel->setHeaderData(3, Qt::Horizontal, tr("TIME"));
    qmodel->setHeaderData(4, Qt::Horizontal, tr("STATE"));

    for(int i = 0; i < flag; i++) {
        qmodel->setItem(i,0,new QStandardItem(QString::number(pEnd->PID)));
        qmodel->setItem(i,1,new QStandardItem(QString::number(pEnd->PRI)));
        qmodel->setItem(i,2,new QStandardItem(QString::number(pEnd->PSO)));
        qmodel->setItem(i,3,new QStandardItem(QString::number(pEnd->PTI)));
        qmodel->setItem(i,4,new QStandardItem(pEnd->state));

        pEnd = pEnd->Pnext;
    }

    qtv->setModel(qmodel);

    qtv->setSelectionBehavior(QAbstractItemView::SelectRows);
    qtv->setSelectionMode(QAbstractItemView::SingleSelection);
    qtv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //qmodel->clear();
}

void MainWindow::setMemoBaseModel(PCB *p, QTableView *qtv){
    int flag = p->getSize();
    pcbNode *pEnd = p->getEnque();
    QStandardItemModel *qmodel = new QStandardItemModel();
    qmodel->setColumnCount(3);
    qmodel->setHeaderData(0, Qt::Horizontal, tr("PID"));
    qmodel->setHeaderData(1, Qt::Horizontal, tr("MEMORY"));
    qmodel->setHeaderData(2, Qt::Horizontal, tr("BASE"));

    for(int i = 0; i < flag; i++) {
        qmodel->setItem(i,0,new QStandardItem(QString::number(pEnd->PID)));
        qmodel->setItem(i,1,new QStandardItem(QString::number(pEnd->PSO)));
        qmodel->setItem(i,2,new QStandardItem(QString::number(pEnd->PMB)));

        pEnd = pEnd->Pnext;
    }

    qtv->setModel(qmodel);
    qtv->setColumnWidth(0,80);
    qtv->setColumnWidth(1,75);
    qtv->setColumnWidth(2,75);

    qtv->setSelectionBehavior(QAbstractItemView::SelectRows);
    qtv->setSelectionMode(QAbstractItemView::SingleSelection);
    qtv->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_OKpushButton_clicked()
{
   if(ui->QRandomradioButton->isChecked()){
       int flag = 3;
       while(flag){
           int ti = rand()%10+10;//产生一个10-19的随机数
           int so = rand()%10+1;//产生一个1-10的随机数
           int ri = rand()%5+1;//产生一个1-5的随机数
           qWait.insertPCB(ti, so, ri);
           flag--;
       }
       setQueModel(&qWait, ui->Waitingtable);
   }
   else if(ui->QInsertradioButton->isChecked()){
       ui->stackedWidget->setCurrentIndex(1);  //设置索引1所在的页面为当前页面
   }
}

/*void MainWindow::on_CancelpushButton_clicked()
{
    if( ui->QRandomradioButton->isCheckable())
       ui->QRandomradioButton->setChecked( false );
    //ui->QRandomradioButton->setChecked(false);
    //ui->QInsertradioButton->setChecked(false);
    if( ui->QInsertradioButton->isCheckable())
       ui->QInsertradioButton->setChecked( false );
}*/

void MainWindow::on_InsertpushButton_clicked()
{
    int ti = ui->insertPTIlineEdit->text().toInt();//所需时间
    int so = ui->insertPSOlineEdit->text().toInt();//所需资源
    int ri = ui->insertPRIlineEdit->text().toInt();//优先级
    qWait.insertPCB(ti, so, ri);
    QMessageBox::about(NULL, "提示", "插入节点成功！");
    setQueModel(&qWait, ui->Waitingtable);
}

void MainWindow::on_IResetpushButton_clicked()
{
    ui->PRIhorizontalSlider->setSliderPosition(1);
    ui->PTIhorizontalSlider->setSliderPosition(1);
    ui->PSOhorizontalSlider->setSliderPosition(1);
}

void MainWindow::on_IBackpushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_PRIhorizontalSlider_valueChanged(int value)
{
    QString str = QString::number(value);
    ui->insertPRIlineEdit->setText(str);
}

void MainWindow::on_PTIhorizontalSlider_valueChanged(int value)
{
    QString str = QString::number(value);
    ui->insertPTIlineEdit->setText(str);
}

void MainWindow::on_PSOhorizontalSlider_valueChanged(int value)
{
    QString str = QString::number(value);
    ui->insertPSOlineEdit->setText(str);
}

void MainWindow::on_RunpushButton_clicked()
{
    int i = 0;
    QString st1 = "Ready";
    QString st2 = "Running";
    QString st3 = "Suspend";
    QString st4 = "Finished";
    qWait.bubblePCB();
    //num=100
    while(qWait.getSize() && num ){//获取规模
        qWait.getEnque()->PMB = alloMemory(); //获取队首,PMB内存基址
        MMM = MMM + qWait.getEnque()->PSO; //PSO所需资源
        num = num - qWait.getEnque()->PSO;
        qWait.changeState(st1);
        qWait.exchangePCB(qReady);
    }

    setQueModel(&qWait, ui->Waitingtable);
    setMemoBaseModel(&qReady, ui->baseTableView);
    while(num != 100){                //优先级调度
        if(qRun.getSize() == 0){
            qReady.getEnque()->PRI--;//优先级-1
            qReady.getEnque()->PTI--;//所需时间-1
            qReady.exchangePCB(qRun);
            qRun.changeState(st2);
            setQueModel(&qReady, ui->Readytable);
            setQueModel(&qRun, ui->Runningtable);
        }
        if(qRun.getEnque()->PTI == 0){
            setSpace(QString::number(qRun.getEnque()->PMB), QString::number(qRun.getEnque()->PSO), "未分");
            qRun.exchangePCB(qFin);
            qFin.changeState(st4);
            callBack();
            num += qFin.getEnque()->PSO;
            setQueModel(&qRun, ui->Runningtable);
            setQueModel(&qFin, ui->Finishtable);
            ui->Finishtable->repaint();
        }//进程完成后进入完成队列，回收资源
        else if(hhh){
            qRun.exchangePCB(qSus);
            qSus.changeState(st3);
            setQueModel(&qSus, ui->Suspendtable);
            hhh = false;
        }//挂起
        else if(qRun.getEnque()->PRI < qReady.getEnque()->PRI){
            qRun.changeState(st1);
            qRun.exchangePCB(qReady);
            //qReady.changeState(st1);
            qReady.bubblePCB();
            setQueModel(&qReady, ui->Readytable);
        }
        else {
            qRun.getEnque()->PRI--;
            qRun.getEnque()->PTI--;
            setQueModel(&qRun, ui->Runningtable);
            QElapsedTimer et;
            et.start();
            while(et.elapsed()<300)
                QCoreApplication::processEvents();
            ui->Runningtable->repaint();
        }
        QElapsedTimer et;
        et.start();
        while(et.elapsed()<300)
            QCoreApplication::processEvents();

        Sleep(200);
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::clicked_susrightMenu(const QPoint &pos){
    rightMenu->exec(QCursor::pos());
}

void MainWindow::clicked_nosusrightMenu(const QPoint &pos){
    rightMenu->exec(QCursor::pos());
}

void MainWindow::createSusMenu()
{
    rightMenu = new QMenu;
    susAction = new QAction("挂起",this);

    rightMenu->addAction(susAction);
    connect(susAction,SIGNAL(triggered()),this,SLOT(on_susMenu_clicked()));
}

void MainWindow::createNoSusMenu()
{
    nrightMenu = new QMenu;
    nosusAction = new QAction("解挂",this);

    rightMenu->addAction(nosusAction);
    connect(nosusAction,SIGNAL(triggered()),this,SLOT(on_nosusMenu_clicked()));
}

void MainWindow::on_susMenu_clicked(){
    hhh = true;
}
void MainWindow::on_nosusMenu_clicked(){
    qSus.exchangePCB(qReady);
    setQueModel(&qSus, ui->Suspendtable);
    QElapsedTimer et;
    et.start();
    while(et.elapsed()<300)
        QCoreApplication::processEvents();

}

void MainWindow::setMemoryModel(memory *m, QTableView *qtv){
    int flag = 10;
    QStandardItemModel *qmodel = new QStandardItemModel();
    qmodel->setColumnCount(3);
    qmodel->setHeaderData(0, Qt::Horizontal, tr("起始地址"));
    qmodel->setHeaderData(1, Qt::Horizontal, tr("长度"));
    qmodel->setHeaderData(2, Qt::Horizontal, tr("状态"));

    for(int i = 0; i < flag; i++) {
        qmodel->setItem(i,0,new QStandardItem(m[i].memorystart));
        qmodel->setItem(i,1,new QStandardItem(m[i].memorylength));
        qmodel->setItem(i,2,new QStandardItem(m[i].memorystate));

    }

    qtv->setModel(qmodel);
    qtv->setColumnWidth(0,80);
    qtv->setColumnWidth(1,75);
    qtv->setColumnWidth(2,75);

    qtv->setSelectionBehavior(QAbstractItemView::SelectRows);
    qtv->setSelectionMode(QAbstractItemView::SingleSelection);
    qtv->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::sortMemory(memory *m){
    memory e;
    for(int j = 1; j < 10; j++) {
        e.copyMemory(m[j]);
        int i = j - 1;
        while(i > 0 && m[i].ms > e.ms){
            m[i+1].copyMemory(m[i]);
            i--;
        }
        if(i+1 != j)
            m[i+1].copyMemory(e);
    }
}

int MainWindow::alloMemory(){
    int M = 0;
    sortMemory(m);
    if(m[0].ms != 101){
        for(int i = 0; i < 10; i++){
            if(m[i].ml > qWait.getEnque()->PSO){
                M = m[i].ms;
                m[i].ms += qWait.getEnque()->PSO;
                m[i].ml -= qWait.getEnque()->PSO;
                m[i].setMemory(QString::number(m[i].ms), QString::number(m[i].ml), "未分");
                return M;
            }
            else if(m[i].ml == qWait.getEnque()->PSO){
                M = m[i].ms;
                m[i].ms = 101;
                m[i].ml = 101;
                m[i].setMemory(" ", " ", "空表目");
                sortMemory(m);
                Size--;
                return M;
            }
        }
    }
    else {
        if(MMM<100){
        M = MMM;
        return M;
        }
    }
}

void MainWindow::setSpace(QString a, QString b, QString c){
    m[Size].setMemory(a, b, c);
    sortMemory(m);
    Size++;
    sortMemory(m);
    setMemoryModel(m, ui->memoryTableView);
}

void MainWindow::callBack(){
    for(int i = 0; i < 10; i++) {
        if(m[i].ms + m[i].ml == m[i+1].ms){
            m[i].ml += m[i+1].ml;
            m[i].setMemory(QString::number(m[i].ms), QString::number(m[i].ml), "未分");
            m[i+1].setMemory(" ", " ", "空表目");
            sortMemory(m);
            setMemoryModel(m, ui->memoryTableView);
        }
        }
}
