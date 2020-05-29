#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitterMain);
    //状态栏初始化创建
    labCellIndex=new QLabel("当前单元格坐标：",this);
    labCellIndex->setMinimumWidth(250);
    labCellType=new QLabel("当前单元格类型：",this);
    labCellType->setMinimumWidth(200);
    labStudID=new QLabel("学生ID：",this);
    labStudID->setMinimumWidth(200);
    //加到状态栏
    ui->statusbar->addWidget(labCellIndex);
    ui->statusbar->addWidget(labCellType);
    ui->statusbar->addWidget(labStudID);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSetHeader_clicked()      //设置表头
{
    QTableWidgetItem *headerItem;
    QStringList headerText; //表头用QStringList来表示
    headerText<<"姓 名"<<"性 别"<<"出生日期"<<"民 族"<<"分 数"<<"是否党员";
//    ui->tableInfo->setHorizontalHeaderLabels(headerText);
    ui->tableInfo->setColumnCount(headerText.count());  //表头列数与headerText相等
    for(int i=0;i<ui->tableInfo->columnCount();i++) //列编号从0开始
    {
//        cellItem=ui->tableInfo->horizontalHeaderItem(i);
        headerItem=new QTableWidgetItem(headerText.at(i));
        //新建QTableWidgetItem，利用headerText.at(i)获取i行字符串
        QFont font=headerItem->font();  //获取字体设置
        font.setBold(true); //设置为粗体
        font.setPointSize(12);  //字体大小
        headerItem->setTextColor(Qt::red);  //字体颜色
        headerItem->setFont(font);  //设置字体
        ui->tableInfo->setHorizontalHeaderItem(i,headerItem); //设置表头单元格item
    }
//    ui->tableInfo->setItemDelegateForColumn(colScore,*delegate);    //设置自定义代理组件
}

void MainWindow::on_btnSetRows_clicked()
{
    int rows=ui->spinBox->text().toInt();
    ui->tableInfo->setRowCount(rows);
}

void MainWindow::on_btnIniData_clicked()        //初始化表格内容
{
    QString strName,strSex;
    bool isParty=false;
    QDate birth;
    birth.setDate(1980,4,7);    //初始化一个日期
    ui->tableInfo->clearContents(); //只清除工作区，不清除表头
    int Rows=ui->tableInfo->rowCount(); //数据区行数
    for(int i=0;i<Rows;i++) //数据区第1行编号为0
    {
        strName=QString::asprintf("学生%d",i);    //学生姓名
        if((i%2)==0)    //奇偶行设置性别
            strSex="男";
        else
            strSex="女";
        createItemsARow(i,strName,strSex,birth,"汉族",70,isParty); //为某一行创建items
        birth=birth.addDays(20);
        isParty=!isParty;
    }
}

void MainWindow::createItemsARow(int rowNum,QString Name,QString Sex,QDate birth,
                    QString Nation,int score,bool isPM)    //为某一行创建item
{
    QTableWidgetItem *item;
    QString str;
    uint StudID=201605000;  //学号基数

    //姓名
    //新建item，设置单元格type为自定义的MainWindow::ctName
    item=new QTableWidgetItem(Name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //文本对齐格式
    StudID+=rowNum; //学号=基数+行号
    item->setData(Qt::UserRole,QVariant(StudID));   //设置studID为data
    ui->tableInfo->setItem(rowNum,MainWindow::colName,item);    //为单元格设置item

    //性别
    QIcon icon;
    if(Sex=="男")
        icon.addFile(":/boy.bmp");
    else
        icon.addFile(":/girl.bmp");
    item=new QTableWidgetItem(Sex,MainWindow::ctSex); //新建一个Item，设置单元格type为自定义的 MainWindow::ctSex
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//为单元格设置Item
    ui->tableInfo->setItem(rowNum,MainWindow::colSex,item);//为单元格设置Item

    //出生日期
    str=birth.toString("yyyy-MM-dd"); //日期转换为字符串
    item=new QTableWidgetItem(str,MainWindow::ctBirth);//新建一个Item，设置单元格type为自定义的 MainWindow::ctBirth
    item->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter); //文本对齐格式
    ui->tableInfo->setItem(rowNum,MainWindow::colBirth,item);//为单元格设置Item

    //民族
    item=new QTableWidgetItem(Nation,MainWindow::ctNation); //新建一个Item，设置单元格type为自定义的 MainWindow::ctNation
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文本对齐格式
    ui->tableInfo->setItem(rowNum,MainWindow::colNation,item);//为单元格设置Item

    //分数
    str.setNum(score);
    item=new QTableWidgetItem(str,MainWindow::ctScore);//新建一个Item，设置单元格type为自定义的 MainWindow::ctPartyM
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文本对齐格式
    ui->tableInfo->setItem(rowNum,MainWindow::colScore,item);//为单元格设置Item

    //是否党员
    item=new QTableWidgetItem("党员",MainWindow::ctPartyM);//新建一个Item，设置单元格type为自定义的 MainWindow::ctPartyM
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文本对齐格式
    if (isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackgroundColor(Qt::yellow);//Qt::green  lightGray  yellow
    ui->tableInfo->setItem(rowNum,MainWindow::colPartyM,item);//为单元格设置Item
}

void MainWindow::on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    //当前选择单元格发生变化时的响应
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);

    QTableWidgetItem* item=ui->tableInfo->item(currentRow,currentColumn); //获取单元格的 Item
    if (item==NULL)
        return;

    labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行，%d 列",currentRow+1,currentColumn+1));

    int cellType=item->type();//获取单元格的类型
    labCellType->setText(QString::asprintf("当前单元格类型：%d",cellType));

    item=ui->tableInfo->item(currentRow,MainWindow::colName); //取当前行第1列的单元格的 item
    int ID=item->data(Qt::UserRole).toInt();//读取用户自定义数据
    labStudID->setText(QString::asprintf("学生ID：%d",ID));//学生ID
}

void MainWindow::on_btnInsertRow_clicked()
{
    //插入一行
    int curRow=ui->tableInfo->currentRow();//当前行号
    ui->tableInfo->insertRow(curRow); //插入一行，但不会自动为单元格创建item
    createItemsARow(curRow,"新生","男",QDate::fromString("1990-1-1","yyyy-M-d"),"苗族",60,true); //为某一行创建items
}

void MainWindow::on_btnAppendRow_clicked()
{
    //添加一行
    int curRow=ui->tableInfo->rowCount();//总体行号
    ui->tableInfo->insertRow(curRow);//在表格尾部添加一行
    createItemsARow(curRow,"新生","女",QDate::fromString("2000-1-1","yyyy-M-d"),"满族",50,false); //为某一行创建items
}

void MainWindow::on_btnDelCurRow_clicked()
{
    //删除当前行及其items
    int curRow=ui->tableInfo->currentRow();//当前行号
    ui->tableInfo->removeRow(curRow); //删除当前行及其items
}

void MainWindow::on_btnResizeRow_clicked()
{
    //自动调整行高
    ui->tableInfo->resizeRowsToContents();  //自动调整所有行的高度，以适应其内容。
//    ui->tableInfo->resizeRowToContents(int row);    //自动调整行号为row的高度。
}

void MainWindow::on_btnResizeCol_clicked()
{
    //自动调整列宽
    ui->tableInfo->resizeColumnsToContents();  //自动调整所有列的宽度，以适应其内容。
//    ui->tableInfo->resizeColumnToContents(int Column);    //自动调整列号为Column的宽度。
}

void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{
    //设置编辑模式
    if (checked)
        //双击或获取焦点后单击，进入编辑状态
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //不允许编辑
}

void MainWindow::on_chkBoxRowColor_clicked(bool checked)
{
    ui->tableInfo->setAlternatingRowColors(checked);
}

void MainWindow::on_chkBoxHeaderH_clicked(bool checked)
{
    //是否显示水平表头
    ui->tableInfo->horizontalHeader()->setVisible(checked);
}

void MainWindow::on_chkBoxHeaderV_clicked(bool checked)
{
    //是否显示垂直表头
    ui->tableInfo->verticalHeader()->setVisible(checked);
}

void MainWindow::on_rBtnSelectRow_clicked()
{
    //选择行为：行选择
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::on_rBtnSelectItem_clicked()
{
    //选择行为：单元格选择
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void MainWindow::on_btnReadToEdit_clicked()
{
    //将 QTableWidget的所有行的内容提取字符串，显示在QPlainTextEdit里
    QString str;
    QTableWidgetItem *cellItem;

    ui->plainTextEdit->clear(); //文本编辑器清空
    for (int i=0;i<ui->tableInfo->rowCount();i++) //逐行处理
    {
        str=QString::asprintf("第 %d 行： ",i+1);
        for (int j=0;j<ui->tableInfo->columnCount()-1;j++) //逐列处理，但最后一列是check型，单独处理
        {
            cellItem=ui->tableInfo->item(i,j); //获取单元格的item
            str=str+cellItem->text()+"   "; //字符串连接
        }
        cellItem=ui->tableInfo->item(i,colPartyM);  //最后一列，党员
        if (cellItem->checkState()==Qt::Checked)  //根据check状态显示文字
            str=str+"党员";
        else
            str=str+"群众";
        ui->plainTextEdit->appendPlainText(str); //添加到编辑框作为一行
    }
}
