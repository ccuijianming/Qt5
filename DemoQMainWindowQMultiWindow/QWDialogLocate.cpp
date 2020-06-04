#include "QWDialogLocate.h"
#include "ui_QWDialogLocate.h"

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    delete ui;
}

void QWDialogLocate::showEvent(QShowEvent *event)
{
    //窗口显示事件，发射信号使actTab_Locate不能用
    Q_UNUSED(event);
    emit changeActionEnable(false);
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    //窗口关闭事件，发射信号使actTab_Locate能用
    Q_UNUSED(event);
    emit changeActionEnable(true);
}

void QWDialogLocate::setSpinRange(int rowCount,int colCount)
{
    //设置SpinRange数值
    ui->spinBoxRow->setMaximum(rowCount);
    ui->spinBoxColumn->setMaximum(colCount);
}

void QWDialogLocate::setSpinValue(int rowNo,int colNo)
{
    //响应主窗口信号，更新spinBox的值
    ui->spinBoxRow->setValue(rowNo+1);
    ui->spinBoxColumn->setValue(colNo+1);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    //发射信号，定位到单元格并运置字符串
    int row=ui->spinBoxRow->value(); //行号
    int col=ui->spinBoxColumn->value();//列号
    QString text=ui->lineEdit->text();//文字
    emit changeCellText(row,col,text); //发射信号
    if (ui->chkBoxRow->isChecked()) //行增
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
    if (ui->chkBoxColumn->isChecked()) //列增
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());
}
