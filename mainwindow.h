#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStopTimer();
    void updateDisplay();
    void resetTimer();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int remainingTime;
    bool timerRunning;
};
#endif // MAINWINDOW_H
