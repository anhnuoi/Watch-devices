#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <QTimer>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
    , serial(new QSerialPort(this))
    , deviceManager(new DeviceManager(this))
{
    ui->setupUi(this);

    // Set up the model for the table view
    setupModel();

    // Connect the model to the table view
    ui->deviceTableView->setModel(model);

    // Adjust column width to fit the view's width proportionally
    adjustColumnWidths();

    // Connect buttons to their slots
    connect(ui->auditAllButton, &QPushButton::clicked, this, &MainWindow::on_auditAllButton_clicked);
    connect(ui->auditButton, &QPushButton::clicked, this, &MainWindow::on_auditButton_clicked);

    // Connect the DeviceManager signal to updateDeviceTable slot
    connect(deviceManager, &DeviceManager::devicesDetected, this, &MainWindow::updateDeviceTable);

    // Set up a timer to periodically check for devices
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() { deviceManager->detectDevices(); });
    timer->start(1000); // Check every second
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    model->setColumnCount(5); // Increased column count to 5 to accommodate checkboxes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr(""));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Model"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Serial Number"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IMEI"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Status"));
}

void MainWindow::updateDeviceTable(const QList<Device> &devices)
{
    // Clear the current table
    model->removeRows(0, model->rowCount());

    for (const Device &device : devices) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem()); // Placeholder for checkbox
        items.append(new QStandardItem(device.getModel()));
        items.append(new QStandardItem(device.getSerialNumber()));
        items.append(new QStandardItem(device.getImei()));
        items.append(new QStandardItem(device.getStatus()));

        model->appendRow(items);
    }

    // Add checkboxes after updating the device list
    addCheckBoxes();
}

void MainWindow::adjustColumnWidths()
{
    int totalWidth = ui->deviceTableView->viewport()->width();

    // Calculate the width for each column based on a percentage
    int checkBoxColumnWidth = totalWidth * 0.02;
    int modelColumnWidth = totalWidth * 0.23;
    int serialNumberColumnWidth = totalWidth * 0.275;
    int imeiColumnWidth = totalWidth * 0.275;
    int statusColumnWidth = totalWidth * 0.2;

    ui->deviceTableView->setColumnWidth(0, checkBoxColumnWidth);
    ui->deviceTableView->setColumnWidth(1, modelColumnWidth);
    ui->deviceTableView->setColumnWidth(2, serialNumberColumnWidth);
    ui->deviceTableView->setColumnWidth(3, imeiColumnWidth);
    ui->deviceTableView->setColumnWidth(4, statusColumnWidth);
}

void MainWindow::addCheckBoxes()
{
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *item = model->item(row, 0);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_auditAllButton_clicked()
{
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *item = model->item(row, 0);
        item->setCheckState(Qt::Checked);
    }
    // Code to send audit request for all devices goes here
}

void MainWindow::on_auditButton_clicked()
{
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *item = model->item(row, 0);
        if (item->checkState() == Qt::Checked) {
            // Code to send audit request for the checked device goes here
        }
    }
}

