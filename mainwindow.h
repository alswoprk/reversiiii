#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>


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
    bool check_in_slot(int row_idx, int column_idx); //check whether value is in slot
    void update_board(int row_idx, int column_idx); //updating board after piece is put down
    bool check_adjacency(int row_idx, int column_idx); //check whether piece can be put down
    int button_slots[8][8];


};
#endif // MAINWINDOW_H
