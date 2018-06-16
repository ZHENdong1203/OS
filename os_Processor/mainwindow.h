#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QMessageBox>
#include <QMenu>
#include <QPoint>
#include "pcb.h"
#include "memory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setQueModel(PCB *p, QTableView *qtv);
    void setMemoBaseModel(PCB *p, QTableView *qtv);
    void setMemoryModel(memory *m, QTableView *qtv);
    void sortMemory(memory *m);
    int alloMemory();
    void setSpace(QString a, QString b, QString c);

    void callBack();
    void paintEvent(QPaintEvent *event);

    QMenu *rightMenu;  //右键菜单
    QMenu *nrightMenu;
    QAction *susAction;  //挂起
    QAction *nosusAction; //解挂

    friend class PCB;
    friend class memory;
private slots:

    void on_OKpushButton_clicked();

    //void on_CancelpushButton_clicked();

    void on_InsertpushButton_clicked();

    void on_IResetpushButton_clicked();

    void on_IBackpushButton_clicked();

    void on_PRIhorizontalSlider_valueChanged(int value);

    void on_PTIhorizontalSlider_valueChanged(int value);

    void on_PSOhorizontalSlider_valueChanged(int value);

    void on_RunpushButton_clicked();

    void on_pushButton_clicked();

    void clicked_susrightMenu(const QPoint &pos);

    void clicked_nosusrightMenu(const QPoint &pos);

    void createSusMenu();
    void createNoSusMenu();

    void on_susMenu_clicked();
    void on_nosusMenu_clicked();
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
