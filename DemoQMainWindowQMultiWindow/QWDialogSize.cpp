#include "QWDialogSize.h"
#include "ui_QWDialogSize.h"

QWDialogSize::QWDialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
}

QWDialogSize::~QWDialogSize()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("提示"),
//                             QString::fromLocal8Bit("设置表格行列数对话框被删除"));
    delete ui;
}

void QWDialogSize::iniRowColumn(int row,int column)
{
    //初始化数据显示
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColumn->setValue(column);
}

int QWDialogSize::rowCount()
{
    //用于主窗口调用获得行数的输入值
    return ui->spinBoxRow->value();
}

int QWDialogSize::columnCount()
{
    //用于主窗口调用获得列数的输入值
    return ui->spinBoxColumn->value();
}
