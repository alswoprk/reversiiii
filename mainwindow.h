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



    void on_ending_button_clicked();

    void on_normal_mode_clicked();

    void on_limited_mode_clicked();

private:
    Ui::MainWindow *ui;
    void initialize_board(); //starting board
    bool check_in_slot(int row_idx, int column_idx); //check whether value is in slot
    void update_board(int row_idx, int column_idx); //updating board after piece is put down
    bool check_adjacency(int row_idx, int column_idx); //check whether piece can be put down
    void change_pieces(int start_idx, int end_idx, int current_player, int direction, int row_idx, int column_idx); //change value of pieces
    void update_board_icons(); //change icons of pieces
    void update_board_score(); //count score
    void end_the_game(); //ending the game when board is full
    int button_slots[8][8]={0}; //initialize to zero

    bool limit_mode=false; //when limit mode is on
    int turn=0; //creating turns
    int starting_player=0;
    int player1_score=0; //scores declared as global so that game can end anytime and scores can be remembered
    int player2_score=0;


};
#endif // MAINWINDOW_H
