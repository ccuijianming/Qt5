#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

private slots:
    void on_actOpen_triggered();

    void on_actFont_triggered();

    void on_actCut_triggered();

    void on_actCopy_triggered();

    void on_actPaste_triggered();

    void on_actUndo_triggered();

    void on_actRedo_triggered();

private:
    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H
