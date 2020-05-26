#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
private slots:
    void on_btnRegister_clicked();
    void on_btnLogin_clicked();
    void on_btnUpdate_clicked();
signals:
    void updatePswd();
};

#endif // LOGINWIDGET_H
