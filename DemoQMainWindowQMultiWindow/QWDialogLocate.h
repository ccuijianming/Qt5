#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();

public slots:
    void setSpinRange(int rowCount,int colCount);

    void setSpinValue(int rowNo,int colNo);

signals:
    void changeCellText(int row,int column,QString &text);
    void changeActionEnable(bool en);

private:
    Ui::QWDialogLocate *ui;

    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

private slots:
    void on_btnSetText_clicked();
};

#endif // QWDIALOGLOCATE_H
