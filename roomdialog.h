#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>

namespace Ui {
class RooMDialog;
}

class RooMDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RooMDialog(QWidget *parent = nullptr);
    ~RooMDialog();

    QString getName() const;
    void setName(const QString &value);

private slots:
    void on_btEnter_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RooMDialog *ui;
    QString name;//房主
};

#endif // ROOMDIALOG_H
