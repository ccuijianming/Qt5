#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(this);
    theSelection=new QItemSelectionModel(theModel);
    ui->tableView->setModel (theModel); //设置数据模型
    ui->tableView->setSelectionModel(theSelection); //设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actSetSize_triggered()
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

void MainWindow::on_actSetHeader_triggered()
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

void MainWindow::on_actLocate_triggered()
{
    //创建StayOnTop的对话框，对话框关闭时自动删除
    //通过控制actLocate的enable属性避免重复点击
    ui->actLocate->setEnabled(false);
    dlgLocate=new QWDialogLocate(this);//创建对话框，传递指针
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);//对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    Qt::WindowFlags flags=dlgLocate->windowFlags();//获取已有flags
    dlgLocate->setWindowFlags(flags|Qt::WindowStaysOnTopHint);//设置对话框固定大小,StayOnTop
    //对话框初始化设置
    dlgLocate->setSpinRange(theModel->rowCount(),theModel->columnCount());
    QModelIndex curIndex=theSelection->currentIndex();
    if(curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(),curIndex.column());
    dlgLocate->show();//非模态显示对话框
}

void MainWindow::setACellText(int row,int column,QString text)
{
    //定位到单元格，并设置字符串
    QModelIndex index=theModel->index(row,column);//获取模型索引
    theSelection->clearSelection(); //清除现有选择
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select); //定位到单元格
    theModel->setData(index,text,Qt::DisplayRole);//设置单元格字符串
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //单击单元格时，将单元格的行号、列号设置到对话框上
    if(dlgLocate!=NULL) //对话框存在
        dlgLocate->setSpinValue(index.row()+1,index.column()+1);
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actLocate->setEnabled(enable);
}

void MainWindow::setDlgLocateNull()
{
    dlgLocate=NULL;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //窗口关闭时询问是否退出
    QMessageBox::StandardButton result=QMessageBox::question
            (this,"确认","确定要退出本程序吗？",QMessageBox::Yes|
             QMessageBox::No|QMessageBox::Cancel,QMessageBox::No);
    if (result==QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
