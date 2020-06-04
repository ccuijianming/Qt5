#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QFormDoc.h"
#include "QFormTable.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->setTabsClosable(true);//Page有关闭按钮，可被关闭
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    this->setAutoFillBackground(true);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //绘制窗口背景图片
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->toolBar->height(),this->width(),this->height()-ui->toolBar->height()-ui->statusbar->height(),QPixmap(":/background.jpg"));
}

void MainWindow::on_actWidgetEmbedded_triggered()
{
    //创建QFormDoc窗体，并在tabWidget中显示
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int cur=ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()+1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actWidgetSeparate_triggered()
{
    QFormDoc *formDoc = new QFormDoc(); //不指定父窗口，用show()显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    //formDoc->setWindowTitle(QString::fromLocal8Bit("基于QWidget的窗体，无父窗口，关闭时删除"));
    QString str=(u8"基于QWidget的窗体，无父窗口，关闭时删除");
    formDoc->setWindowTitle(str);
    formDoc->setWindowFlag(Qt::Window,true);
    //formDoc->setWindowFlag(Qt::CustomizeWindowHint,true);
    //formDoc->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);
    //formDoc->setWindowFlag(Qt::WindowCloseButtonHint,true);
    //formDoc->setWindowFlag(Qt::WindowStaysOnTopHint,true);
    //formDoc->setWindowState(Qt::WindowMaximized);
    //formDoc->setWindowModality(Qt::WindowModal);
    formDoc->setWindowOpacity(0.9);//设置窗口的透明度
    formDoc->show(); //在单独的窗口中显示
}

void MainWindow::on_actMainWindowEmbedded_triggered()
{
    QFormTable *formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int cur=ui->tabWidget->addTab(formTable,QString::asprintf("Table %d",ui->tabWidget->count()+1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actMainWindowSeparate_triggered()
{
    QFormTable* formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    //formTable->setWindowTitle(QString::fromLocal8Bit("基于 QMainWindow 的窗口，指定父窗口，关闭时删除"));
    QString str=(u8"基于 QMainWindow 的窗口，指定父窗口，关闭时删除");
    formTable->setWindowTitle(str);
    formTable->show();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    //关闭Tab
    if (index<0)
        return;
    QWidget *aForm=ui->tabWidget->widget(index);
    aForm->close();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    bool en=ui->tabWidget->count()>0; //再无页面时，actions禁用
    ui->tabWidget->setVisible(en);
}
