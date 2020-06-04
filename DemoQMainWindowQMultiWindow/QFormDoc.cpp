#pragma execution_character_set("utf-8")
#include "QFormDoc.h"
#include "ui_QFormDoc.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFontDialog>

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
    //使用UI设计的Actions设计工具栏
    QToolBar* locToolBar = new QToolBar(tr("文档"),this); //创建工具栏
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actUndo);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actClose);
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QVBoxLayout *Layout = new QVBoxLayout();
    Layout->addWidget(locToolBar); //设置工具栏和编辑器上下布局
    Layout->addWidget(ui->plainTextEdit);
    Layout->setContentsMargins(2,2,2,2); //减小边框的宽度
    Layout->setSpacing(2);
    this->setLayout(Layout); //设置布局
}

QFormDoc::~QFormDoc()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("消息"),
//                             QString::fromLocal8Bit("QFormDoc对象被删除和释放"));
    delete ui;
}

void QFormDoc::on_actOpen_triggered()
{
    //打开文件
    QString curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
    //调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,"文本文件(*.txt);;所有文件(*.*)");
    if (aFileName.isEmpty())
        return; //如果未选择文件，退出
    QFile aFile(aFileName);  //以文件方式读出
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
    {
        QTextStream aStream(&aFile); //用文本流读取文件
        ui->plainTextEdit->clear();//清空
        while(!aStream.atEnd())
        {
            QString str=aStream.readLine();//读取文件的一行
            ui->plainTextEdit->appendPlainText(str); //添加到文本框显示
        }
        aFile.close();//关闭文件
    }
}

void QFormDoc::on_actFont_triggered()
{
    bool ok = true;
    QFont font = QFontDialog::getFont(&ok);
    if (ok)
    {
        ui->plainTextEdit->setFont(font);
    }
}

void QFormDoc::on_actCut_triggered()
{
    ui->plainTextEdit->cut();
}

void QFormDoc::on_actCopy_triggered()
{
    ui->plainTextEdit->copy();
}

void QFormDoc::on_actPaste_triggered()
{
    ui->plainTextEdit->paste();
}

void QFormDoc::on_actUndo_triggered()
{
    ui->plainTextEdit->undo();
}

void QFormDoc::on_actRedo_triggered()
{
    ui->plainTextEdit->redo();
}
