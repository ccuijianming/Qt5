#include "QWDialogHeaders.h"
#include "ui_QWDialogHeaders.h"

QWDialogHeaders::QWDialogHeaders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);
    model=new QStringListModel(this);
    ui->listView->setModel(model);
}

QWDialogHeaders::~QWDialogHeaders()
{
    QMessageBox::information(this,QString::fromLocal8Bit("提示"),
                             QString::fromLocal8Bit("设置表头标题对话框被删除"));
    delete ui;
}

void QWDialogHeaders::iniHeaderList(QStringList &headers)
{
    model->setStringList(headers);
}

QStringList QWDialogHeaders::headerList()
{
    return model->stringList();
}
