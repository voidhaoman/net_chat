#ifndef VIDEIOSURFACE_H
#define VIDEIOSURFACE_H
#include <QObject>
#include <QAbstractVideoSurface>

class VideioSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideioSurface(QObject * parent=nullptr);
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);
signals:
    void vedeioChanged(QVideoFrame);
};

#endif // VIDEIOSURFACE_H
