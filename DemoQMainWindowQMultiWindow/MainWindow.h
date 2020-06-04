#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);

private slots:
    void on_actWidgetEmbedded_triggered();

    void on_actWidgetSeparate_triggered();

    void on_actMainWindowEmbedded_triggered();

    void on_actMainWindowSeparate_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
