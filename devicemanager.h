#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <device.h>
class DeviceManager : public QObject
{
    Q_OBJECT
public:
    DeviceManager(QObject *parent = nullptr);
    QList<Device> detectDevices();

signals:
    void devicesDetected(const QList<Device> &devices);
};

#endif // DEVICEMANAGER_H
