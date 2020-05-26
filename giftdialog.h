#ifndef GIFTDIALOG_H
#define GIFTDIALOG_H

#include <QDialog>

namespace Ui {
class GiftDialog;
}

class GiftDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GiftDialog(QWidget *parent = nullptr);
    ~GiftDialog();



private slots:
    void on_pb6_clicked();

    void on_pb100_clicked();

    void on_pb1000_clicked();

private:
    Ui::GiftDialog *ui;
signals:
    void giftMoney(int);
};

#endif // GIFTDIALOG_H
