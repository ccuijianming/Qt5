#include "QFormTable.h"
#include "ui_QFormTable.h"

#include <QMessageBox>

QFormTable::QFormTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(this);
    theSelection=new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel); //设置数据模型
    ui->tableView->setSelectionModel(theSelection); //设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

QFormTable::~QFormTable()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("消息"),
//                             QString::fromLocal8Bit("FormTable 窗口被删除和释放"));
    delete ui;
}

void QFormTable::on_actSetSize_triggered()
{
    //模态对话框，动态创建，用过后删除
    QWDialogSize *dlgTableSize=new QWDialogSize(this);
    Qt::WindowFlags flags=dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags|Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->iniRowColumn(theModel->rowCount(),theModel->columnCount());
    int ret=dlgTableSize->exec();//以模态方式显示对话框
    if(ret==QDialog::Accepted)
    {
        //OK按钮被按下，获取对话框上的输入，设置行数和列数
        int rows=dlgTableSize->rowCount();
        theModel->setRowCount(rows);
        int cols=dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
    }
    delete dlgTableSize;
}

void QFormTable::on_actSetHeader_triggered()
{
    //一次创建，多次调用，对话框关闭时只是隐藏
    if(dlgSetHeaders==NULL)//如果对象没有被创建过，就创建对象
        dlgSetHeaders=new QWDialogHeaders(this);
    if(dlgSetHeaders->headerList().count()!=theModel->columnCount())
    {
        //如果表头列数变化，重新初始化
        QStringList strList;
        for (int i=0;i<theModel->columnCount();i++)//获取现有的表头标题
            strList.append(theModel->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
        dlgSetHeaders->iniHeaderList(strList);//用于对话框初始化显示
    }
    int ret=dlgSetHeaders->exec();//以模态方式显示对话框
    if(ret==QDialog::Accepted)//OK键被按下
    {
        QStringList strList=dlgSetHeaders->headerList();//获取对话框上修改后的StringList
        theModel->setHorizontalHeaderLabels(strList);//设置模型的表头标题
    }
}

void QFormTable::setACellText(int row,int column,QString &text)
{
    //定位到单元格，并设置字符串
    QModelIndex index=theModel->index(row-1,column-1);//获取模型索引
    theSelection->clearSelection(); //清除现有选择
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select); //定位到单元格
    theModel->setData(index,text,Qt::DisplayRole);//设置单元格字符串
}

void QFormTable::setActLocateEnable(bool enable)
{
    ui->actLocate->setEnabled(enable);
}

void QFormTable::on_tableView_clicked(const QModelIndex &index)
{
    //单击单元格时发射信号，传递单元格的行号、列号
    emit cellIndexChanged(index.row(),index.column());
}

void QFormTable::on_actLocate_triggered()
{
    //创建StayOnTop的对话框，对话框关闭时自动删除
    dlgLocate=new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags=dlgLocate->windowFlags();
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    dlgLocate->setSpinRange(theModel->rowCount(),theModel->columnCount());
    QModelIndex curIndex=theSelection->currentIndex();
    if (curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(),curIndex.column());
    //对话框发射信号，设置单元格文字
    connect(dlgLocate,SIGNAL(changeCellText(int,int,QString&)),
            this,SLOT(setACellText(int,int,QString&)));
    //对话框发射信号，设置actLocate的属性
    connect(dlgLocate,SIGNAL(changeActionEnable(bool)),
            this,SLOT(setActLocateEnable(bool)));
    //主窗口发射信号，修改对话框上的spinBox的值
    connect(this,SIGNAL(cellIndexChanged(int,int)),
            dlgLocate,SLOT(setSpinValue(int,int)));
    dlgLocate->show(); //非模态显示对话框
}
