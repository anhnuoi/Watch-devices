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
{
    ui->setupUi(this);

    // Set up the model for the table view
    setupModel();

    // Connect the model to the table view
    ui->deviceTableView->setModel(model);

    // Adjust column width to fit the view's width proportionally
    adjustColumnWidths();

    // Add checkboxes to the first column
    addCheckBoxes();

    // Set up a timer to periodically check for devices
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::detectDevices);
    timer->start(1000); // Check every second

    // Connect the resize event of the deviceTableView to adjust column widths
    connect(ui->deviceTableView->horizontalHeader(), &QHeaderView::sectionResized, this, &MainWindow::adjustColumnWidths);

    // Connect buttons to their slots
    connect(ui->auditAllButton, &QPushButton::clicked, this, &MainWindow::on_auditAllButton_clicked);
    connect(ui->auditButton, &QPushButton::clicked, this, &MainWindow::on_auditButton_clicked);
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

void MainWindow::detectDevices()
{
    // Clear the current table
    model->removeRows(0, model->rowCount());

    // Get the list of available serial ports
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : serialPortInfos) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem()); // Placeholder for checkbox
        items.append(new QStandardItem(info.description()));
        items.append(new QStandardItem(info.serialNumber()));
        items.append(new QStandardItem("N/A")); // Placeholder for IMEI
        items.append(new QStandardItem("Available"));

        model->appendRow(items);
    }

    // Add checkboxes after updating the device list
    addCheckBoxes();
}

void MainWindow::adjustColumnWidths()
{
    int totalWidth = ui->deviceTableView->viewport()->width();

    // Calculate the width for each column based on a percentage
    int checkBoxColumnWidth = totalWidth * 0.05;
    int modelColumnWidth = totalWidth * 0.2375;
    int serialNumberColumnWidth = totalWidth * 0.2375;
    int imeiColumnWidth = totalWidth * 0.2375;
    int statusColumnWidth = totalWidth * 0.2375;

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

void MainWindow::updateDeviceTable()
{
    // Placeholder for future device information updates, like IMEI
}
