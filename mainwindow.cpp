#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
    , remainingTime(0)
    , timerRunning(false)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font-size:28pt; font-weight:700; text-align: center; color: white");
    ui->label->setText("00:00:00");

    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::startStopTimer);
    connect(ui->resetBtn, &QPushButton::clicked, this, &MainWindow::resetTimer);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay);

    ui->hrsSpinbox->setRange(0, 23);
    ui->minSpinbox->setRange(0, 59);
    ui->secSpinbox->setRange(0, 59);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startStopTimer()
{
    if (timerRunning) {
        timer->stop();
        ui->startBtn->setText("START");
        timerRunning = false;
    } else {
        int hours = ui->hrsSpinbox->value();
        int minutes = ui->minSpinbox->value();
        int seconds = ui->secSpinbox->value();
        remainingTime = hours * 3600 + minutes * 60 + seconds;

        if (remainingTime > 0) {
            timer->start(1000);
            ui->startBtn->setText("STOP");
            timerRunning = true;
        }
    }
}

void MainWindow::updateDisplay()
{
    if (remainingTime > 0) {
        remainingTime--;

        int hours = remainingTime / 3600;
        int minutes = (remainingTime % 3600) / 60;
        int seconds = remainingTime % 60;

        ui->label->setText(QString::asprintf("%02d:%02d:%02d", hours, minutes, seconds));
    } else {
        timer->stop();
        ui->startBtn->setText("START");
        timerRunning = false;
    }
}

void MainWindow::resetTimer()
{
    timer->stop();
    remainingTime = 0;

    ui->label->setText("00:00:00");
    ui->startBtn->setText("START");
    timerRunning = false;

    ui->hrsSpinbox->setValue(0);
    ui->minSpinbox->setValue(0);
    ui->secSpinbox->setValue(0);
}
