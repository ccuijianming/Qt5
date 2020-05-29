#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnListAppend_clicked();

    void on_btnListInsert_clicked();

    void on_btnListDelete_clicked();

    void on_btnListClear_clicked();

    void on_btnTextClear_clicked();

    void on_btnListToText_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QStringListModel *theModel;
    QModelIndex index;
};
#endif // WIDGET_H
