#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QWidget>

namespace Ui {
class CreateRoom;
}

class CreateRoom : public QWidget
{
    Q_OBJECT

public:
    explicit CreateRoom(QWidget *parent = nullptr);
    ~CreateRoom();

private:
    Ui::CreateRoom *ui;
};

#endif // CREATEROOM_H
