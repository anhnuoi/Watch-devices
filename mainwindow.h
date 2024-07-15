#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QTimer>
#include <QSerialPortInfo>

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
    void detectDevices();
    void adjustColumnWidths();
    void on_auditAllButton_clicked();
    void on_auditButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QSerialPort *serial;

    void setupModel();
    void updateDeviceTable();
    void addCheckBoxes();
};

#endif // MAINWINDOW_H
