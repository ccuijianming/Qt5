#include "QWDialogSize.h"
#include "QWDialogHeaders.h"
#include "QWDialogLocate.h"

#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>

namespace Ui {
class QFormTable;
}

class QFormTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFormTable(QWidget *parent = nullptr);
    ~QFormTable();

private slots:
    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

    void setACellText(int row,int column,QString &text);//设置单元格内容

    void setActLocateEnable(bool enable); //设置 actLocate 的 enabled 属性

    void on_actLocate_triggered();

    void on_tableView_clicked(const QModelIndex &index);

signals:
    void cellIndexChanged(int rowNo, int colNo) ;//当前单元格发生变化

private:
    Ui::QFormTable *ui;

    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QWDialogHeaders *dlgSetHeaders=NULL;
    QWDialogLocate *dlgLocate=NULL;
};

#endif // QFORMTABLE_H
