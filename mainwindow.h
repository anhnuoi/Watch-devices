#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QTimer>
#include <QSerialPortInfo>
#include "device.h"
#include "devicemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_auditAllButton_clicked();
    void on_auditButton_clicked();
    void adjustColumnWidths();
    void updateDeviceTable(const QList<Device> &devices);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSerialPort *serial;
    DeviceManager *deviceManager;

    void setupModel();
    void addCheckBoxes();
};

#endif // MAINWINDOW_H
