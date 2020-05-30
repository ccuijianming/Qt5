#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCloseEvent>
#include <QWDialogSize.h>
#include <QWDialogHeaders.h>
#include <QWDialogLocate.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setACellText(int row,int column,QString text);
    void setActLocateEnable(bool enable);
    void setDlgLocateNull();

private slots:
    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

    void on_actLocate_triggered();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QWDialogHeaders *dlgSetHeaders=NULL;
    QWDialogLocate *dlgLocate=NULL;
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
