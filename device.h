#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Device
{
public:
    Device(const QString &model, const QString &serialNumber, const QString &imei, const QString &status);

    QString getModel() const;
    QString getSerialNumber() const;
    QString getImei() const;
    QString getStatus() const;

private:
    QString model;
    QString serialNumber;
    QString imei;
    QString status;
};

#endif // DEVICE_H
