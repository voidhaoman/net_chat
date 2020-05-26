#ifndef BARRAGE_H
#define BARRAGE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class Barrage : public QWidget
{
    Q_OBJECT
public:
    explicit Barrage(QString text,QWidget *parent = nullptr);
    QTimer *timer;
    QString text;
    QLabel *label;
    int idx;
signals:

public slots:
    void onTimeout();
};

#endif // BARRAGE_H
