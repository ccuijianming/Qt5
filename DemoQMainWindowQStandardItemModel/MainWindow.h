﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define FixedColumnCount 6    //文件固定 6 列

#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QTextCodec>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);

    void on_actOpen_triggered();

    void on_actAppend_triggered();

    void on_actInsert_triggered();

    void on_actDelete_triggered();

    void on_actAlignLeft_triggered();

    void on_actAlignCenter_triggered();

    void on_actAlignRight_triggered();

    void on_actFontBold_triggered(bool checked);

    void on_actModelData_triggered();

    void on_actSave_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *LabCurFile;    //当前文件
    QLabel *LabCellPos;    //当前单元格行列号
    QLabel *LabCellText;   //当前单元格内容
    QStandardItemModel *theModel; //数据模型
    QItemSelectionModel *theSelection; //选择模型
    void iniModelFromStringList (QStringList &aFileContent); //从 StringList 初始化数据模型
};
#endif // MAINWINDOW_H
