#ifndef UPDATEPSWDDIALOG_H
#define UPDATEPSWDDIALOG_H

#include <QDialog>

namespace Ui {
class UpdatePswdDialog;
}

class UpdatePswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdatePswdDialog(QWidget *parent = nullptr);
    ~UpdatePswdDialog();

private slots:
    void on_pbSure_clicked();

    void on_pbCancle_clicked();

private:
    Ui::UpdatePswdDialog *ui;
};

#endif // UPDATEPSWDDIALOG_H
