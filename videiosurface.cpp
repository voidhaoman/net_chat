#include "videiosurface.h"
#include <QList>

VideioSurface::VideioSurface(QObject *parent)
    :QAbstractVideoSurface (parent)
{

}
//用于设置程序支持的原始视频格式
QList<QVideoFrame::PixelFormat> VideioSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    //返回图像的处理格式
    //window下转换的图片格式是Format_RGB32,苹果格式是Format_ARGB32
    return QList<QVideoFrame::PixelFormat>()<<QVideoFrame::Format_RGB32;
}
//获取当前帧的视频源数据
bool VideioSurface::present(const QVideoFrame &frame)
{
    emit vedeioChanged(frame);
    return true;
}
