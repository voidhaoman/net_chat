#ifndef DANMUDIALOG_H
#define DANMUDIALOG_H

#include <QDialog>

namespace Ui {
class DanmuDialog;
}

class DanmuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DanmuDialog(QWidget *parent = nullptr);
    ~DanmuDialog();

private slots:
    void on_leDanmu_returnPressed();

private:
    Ui::DanmuDialog *ui;
signals:
    void danmuText(QString);
};

#endif // DANMUDIALOG_H
