#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QCloseEvent>

#include <QWidget>
#include <QListWidgetItem >

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    QString getName() const;
    void setName(const QString &value);

    QStringList getList() const;
    void setList(const QStringList &value);

private:
    Ui::MainWidget *ui;
    QString name;

public slots:
    void onRefreshRoom(QStringList list);
protected:
    virtual void closeEvent(QCloseEvent* event);
private slots:
    void on_pbCreate_clicked();
    void on_lsRoom_itemDoubleClicked(QListWidgetItem *item);

    void on_pbRefresh_clicked();

signals:
    void createRoom();
    void enterRoom(QString);


};

#endif // MAINWIDGET_H
