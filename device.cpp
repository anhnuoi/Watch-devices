#include "device.h"

Device::Device(const QString &model, const QString &serialNumber, const QString &imei, const QString &status)
    : model(model), serialNumber(serialNumber), imei(imei), status(status)
{
}

QString Device::getModel() const
{
    return model;
}

QString Device::getSerialNumber() const
{
    return serialNumber;
}

QString Device::getImei() const
{
    return imei;
}

QString Device::getStatus() const
{
    return status;
}
