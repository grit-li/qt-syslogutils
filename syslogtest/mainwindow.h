#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

private slots:
    void on_SetLogLevel_clicked(void);

private slots:
    void PrintTestOutput(void);

private:
    Ui::MainWindow *ui;
    QTimer* m_timer;
};
#endif // MAINWINDOW_H
