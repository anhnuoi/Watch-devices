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
        qint16 vendorID=(info.hasVendorIdentifier()?info.vendorIdentifier():0);
        QString imei = "N/A"; // Placeholder for IMEI
        QString status = "Available";
        if (vendorID!=0 && vendorID==1256)
        {
        Device device(model, serialNumber, imei, status);
        devices.append(device);
        }
    }

    if (!devices.isEmpty()) {
        emit devicesDetected(devices);
    }
    return devices;
}

/*
void MainForm::autoDetect()
{
    const auto infos = QSerialPortInfo::availablePorts();
    QList<QString> listportplugged=pluggedDevices.keys();
    QList<QString> listport;
    for (const QSerialPortInfo &info : infos) {
        QString description = info.description();
        qint16 vendorID=(info.hasVendorIdentifier()?info.vendorIdentifier():0);
        QString devName=info.systemLocation();
        QString deviceName = info.portName();
        listport.append(deviceName);
         && description.contains("USB") && !listportplugged.contains(deviceName))
        {
            DeviceModel *device = new DeviceModel();
            QString serialNumber = info.serialNumber();

            if (!serialNumber.isEmpty())
            {
                device->setDownloadMode(false);
                device->setSerialNumber(serialNumber);
            }
            else if(!deviceName.isEmpty())
            {
                device->setPath(devName);
                device->setDownloadMode(true);
            }
            else
            {
                break;
            }
            device->setName(deviceName);
            addDevice(device);
            qDebug() << "added device: " << device->getName() << device->getPath()<<device->getSerialNumber();
        }
    }
    foreach (QString port, listportplugged) {
        if (!listport.contains(port)) {removeDevice(port);
            qDebug() << "remove device: " << port;}
    }
    //     qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
    //    qDebug() << "The slow operation took" << timer.nsecsElapsed() << "nanoseconds";

}
QHash <QString, Device*> pluggedDevices;
*/
