#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

    void on_start_button_clicked();

    void on_rules_button_clicked();

    void on_return_button_clicked();

    void on_choose_player1_clicked(); //choosing players

    void on_choose_player2_clicked();

    void button_slots_pressed();//checking for each button



private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
