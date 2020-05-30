#include "QWDialogLocate.h"
#include "ui_QWDialogLocate.h"
#include <MainWindow.h>

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

void QWDialogLocate::setSpinRange(int rowCount,int colCount)
{
    //设置SpinRange数值
    ui->spinBoxRow->setMaximum(rowCount);
    ui->spinBoxColumn->setMaximum(colCount);
}

void QWDialogLocate::setSpinValue(int rowNo,int colNo)
{
    //设置SpinBox数值
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    //定位到单元格，并设置字符串
    int row=ui->spinBoxRow->value()-1; //行号
    int col=ui->spinBoxColumn->value()-1;//列号
    MainWindow *parWind = (MainWindow*)parentWidget(); //获取主窗口
    parWind->setACellText(row,col,ui->lineEdit->text()); //设置单元格文字
    if (ui->chkBoxRow->isChecked()) //行增
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
    if (ui->chkBoxColumn->isChecked()) //列增
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    //窗口关闭事件，关闭时释放本窗口
    Q_UNUSED(event);
    MainWindow *parWind = (MainWindow*)parentWidget(); //获取父窗口指针
    parWind->setActLocateEnable(true);//使能 actLocate
    parWind->setDlgLocateNull();//将窗口指针设置为NULL
}
