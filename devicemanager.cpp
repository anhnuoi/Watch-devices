#include "devicemanager.h"
#include <QSerialPortInfo>

DeviceManager::DeviceManager(QObject *parent)
    : QObject(parent)
{
}

QList<Device> DeviceManager::detectDevices()
{
    QList<Device> devices;
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : serialPortInfos) {
        QString model = info.description();
        QString serialNumber = info.serialNumber();
        QString imei = "N/A"; // Placeholder for IMEI
        QString status = "Available";

        Device device(model, serialNumber, imei, status);
        devices.append(device);
    }

    emit devicesDetected(devices);
    return devices;
}
