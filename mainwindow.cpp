#include "mainwindow.h"
#include "./ui_mainwindow.h"

int turn=0; //global variable to call on

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->stackedWidget->

    QPushButton *button_slots_connect[8][8]; //creating slot names as array; define in header
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            QString butName="button"+QString::number(i)+QString::number(j);
            button_slots_connect[i][j]=MainWindow::findChild<QPushButton *>(butName);
            connect(button_slots_connect[i][j], SIGNAL(released()), this, SLOT(button_slots_pressed())); //connecting buttons
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_start_button_clicked()
{
    //ui->stackedWidget(start_page)->show()
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::update_board_icons(){ //change icons; does not get until here!!!!!
    QPixmap player1_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_icon"); //create button icons
    QPixmap player2_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_icon");
    QIcon icon1(player1_icon);
    QIcon icon2(player2_icon);

    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            QString butName="button"+QString::number(i)+QString::number(j);
            //MainWindow::findChild<QPushButton *>(butName);

            if(button_slots[i][j]==1){
                //ui->warning_1->setText("update board icons");
                MainWindow::findChild<QPushButton *>(butName)->setIcon(icon1);
            }
            else if(button_slots[i][j]==2){
                MainWindow::findChild<QPushButton*>(butName)->setIcon(icon2);
            }

        }
    }
}

void MainWindow::end_the_game(int player1_score, int player2_score)
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::update_board_score()
{
    int player1_score=0;
    int player2_score=0;
    int end_game=0;

    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            if(button_slots[i][j]==1)
                player1_score++;
            else if(button_slots[i][j]==2)
                player2_score++;
            else if(button_slots[i][j]==0)
                end_game++;
        }
    }

    ui->score_player1->setText(QString::number(player1_score));
    ui->score_player2->setText(QString::number(player2_score));

    if(end_game==0){
        end_the_game(player1_score, player2_score);
    }

}

//does not get until here either!!!
void MainWindow::change_pieces(int start_idx, int end_idx, int current_player, int direction, int row_idx, int column_idx){ //change value of board
    if(direction==1){ //when row needs to change; check up and down
        for(int i=start_idx; i<end_idx+1; ++i){
            button_slots[i][column_idx]=current_player;
        }


    }else{ //when col needs to change; check sideways
        for(int i=start_idx; i<end_idx+1; ++i){
            button_slots[row_idx][i]=current_player;
        }
    }

    update_board_icons(); //final update based on value of boxes

    update_board_score();
}


//CURRENTLY WORKING ON HERE!
void MainWindow::update_board(int row_idx, int column_idx) //updating board after piece is down; determine what needs to change
{
    int current_player=button_slots[row_idx][column_idx];
    int opponent_player=0;

    int start_idx=0; //starting and ending indexes
    int end_idx=0;

    if(current_player==1) //finding opponent and current player value
        opponent_player=2;
    else
        opponent_player=1;
    //total of 4 cases for now


    //================================================================
    if(button_slots[row_idx+1][column_idx]==opponent_player){ //case for when bottom part is true
        //works until here
        start_idx=row_idx+1;
        end_idx=start_idx;

        while(button_slots[end_idx][column_idx]==opponent_player){
            //ui->warning_2->setText("hiii");
            end_idx+=1; //find when stops
        }

        if(button_slots[end_idx][column_idx]==current_player){
            //ui->warning_1->setText("It works!");
            change_pieces(start_idx, end_idx, current_player, 1, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================
    if(button_slots[row_idx-1][column_idx]==opponent_player){ //case for when top part is true
        //works until here
        start_idx=row_idx-1;
        end_idx=start_idx;

        while(button_slots[end_idx][column_idx]==opponent_player){
            ui->warning_2->setText("hiii");
            end_idx-=1; //find when stops
        }

        if(button_slots[end_idx][column_idx]==current_player){
            //ui->warning_1->setText("It works!");
            change_pieces(end_idx, start_idx, current_player, 1, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================
    if(button_slots[row_idx][column_idx+1]==opponent_player){ //case for when right part is true
        //works until here
        start_idx=column_idx+1;
        end_idx=start_idx;
        ui->warning_2->setText("hiii"); //testing; this works!

        while(button_slots[row_idx][end_idx]==opponent_player){
            //ui->warning_2->setText("hiii"); //testing
            end_idx+=1; //find when stops
        }

        if(button_slots[row_idx][end_idx]==current_player){
            ui->warning_1->setText("It works!"); //testing
            change_pieces(start_idx, end_idx, current_player, 2, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================
    if(button_slots[row_idx][column_idx-1]==opponent_player){ //case for when top part is true

        start_idx=column_idx-1;
        end_idx=start_idx;

        while(button_slots[row_idx][end_idx]==opponent_player){
            //ui->warning_2->setText("hiii");
            end_idx-=1; //find when stops
        }

        if(button_slots[row_idx][end_idx]==current_player){
            //ui->warning_1->setText("It works!");
            change_pieces(end_idx, start_idx, current_player, 2, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================




}

bool MainWindow::check_in_slot(int row_idx, int column_idx){
    if (button_slots[row_idx][column_idx]==1 ||button_slots[row_idx][column_idx]==2 )
        return true;
    else
        return false;
}

bool MainWindow::check_adjacency(int row_idx, int column_idx){
    if(button_slots[row_idx-1][column_idx]==1||button_slots[row_idx-1][column_idx]==2)
        return false;
    else if(button_slots[row_idx+1][column_idx]==1||button_slots[row_idx+1][column_idx]==2)
        return false;
    else if(button_slots[row_idx][column_idx+1]==1||button_slots[row_idx][column_idx+1]==2)
        return false;
    else if(button_slots[row_idx][column_idx-1]==1||button_slots[row_idx][column_idx-1]==2)
        return false;
    else
        return true; //true means cannot place there
}

void MainWindow::button_slots_pressed(){

    QPushButton *button = (QPushButton *)sender();

    QString button_name=button->objectName();

    //CHANGE IMAGE DIRECTORY HERE!
    QPixmap player1_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_icon"); //create button icons
    QPixmap player2_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_icon");
    QIcon icon1(player1_icon);
    QIcon icon2(player2_icon);

    int row_idx; //find rows and columns of button
    int column_idx;

    QString just_row_idx=button_name.mid(6, 1); //take just numbers of the value
    QString just_column_idx=button_name.mid(7, 1);

    row_idx=just_row_idx.toInt(); //convert values to int
    column_idx=just_column_idx.toInt();

    ui->warning_1->setText("You placed on row: "+just_row_idx);
    ui->warning_2->setText("You placed on column: "+just_column_idx);


    if(check_in_slot(row_idx, column_idx)){ //check whether button has been placed with something already
        //set error message
        ui->warning_1->setText("Cannot place here!");
        ui->warning_2->setText("Cannot place here!");


        //setting label without qt designer and only comes out for warning signs
        //set label for only couple seconds or terminate when clicked on
    }
    else if(check_adjacency(row_idx, column_idx)){
        //if no adjacency, set error message
        //check if can put down piece
        ui->warning_1->setText("Cannot place here!");
        ui->warning_2->setText("Cannot place here!");

    }

    else{



    if(turn%2==0){ //changing turns
        button->setIcon(icon1);

        QPixmap player2; //changing signs of player status
        player2.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_status.png"); //CHANGE IMAGE DIRECTORY HERE!

        ui->player_status->setPixmap(player2);
        ui->player_status->show();

        button_slots[row_idx][column_idx]=1; //send value of icon




    }
    else{
        button->setIcon(icon2);

        QPixmap player1; //changing signs of player status
        player1.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_status.png"); //CHANGE IMAGE DIRECTORY HERE!

        ui->player_status->setPixmap(player1);
        ui->player_status->show();

        button_slots[row_idx][column_idx]=2; //send value of icon
    }


    update_board(row_idx, column_idx); //change or reverse colors when necessary
    turn+=1; //changing turns

    //button->setIcon(icon1);
    }

    update_board_score(); //update scores

}


void MainWindow::on_rules_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_return_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::initialize_board()
{

    QPixmap player1_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_icon"); //create button icons
    QPixmap player2_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_icon");
    QIcon icon1(player1_icon);
    QIcon icon2(player2_icon);

    ui->button33->setIcon(icon1); //initializing board
    ui->button34->setIcon(icon2);
    ui->button43->setIcon(icon2);
    ui->button44->setIcon(icon1);
    button_slots[3][3]=1;
    button_slots[3][4]=2;
    button_slots[4][3]=2;
    button_slots[4][4]=1;

}

void MainWindow::on_choose_player1_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap player1;
    player1.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_status.png"); //CHANGE IMAGE DIRECTORY HERE!

    ui->player_status->setPixmap(player1);
    ui->player_status->show();




    initialize_board();


}


void MainWindow::on_choose_player2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap player2;
    player2.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_status.png"); //CHANGE IMAGE DIRECTORY HERE!

    ui->player_status->setPixmap(player2);
    ui->player_status->show();
    turn+=1;

    initialize_board();

}


//===============================================
//start of game code
//===============================================

/*

//#include "widget.h"

#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define NUM_ROWS 8
#define NUM_COLS 8
#define EMPTY 0
#define WHITE 1
#define BLACK 2

// 원래는
// const int NUM_ROWS = 8;
// const int NUM_COLS = 8;


//Funtions
int determine_game_type_new_or_existing();
void initialize_game_board(int gb [][NUM_COLS]);
//void put_piece(int gb [][NUM_COLS], int player);
bool check_pull_board(int gb [][NUM_COLS]);
int switchplayer (int player);
int checkAdjacency(int gb [][NUM_COLS], int r, int c, int dir, int player);
void set(int gb [][NUM_COLS], int r, int c, int ply, int dir, int res);

int main()
{
    int gameboard [NUM_ROWS][NUM_COLS];
    //잘 모르겠음
    int player;

    initialize_game_board(gameboard);
    player = 1; //첫번째 플레이어
    while(check_pull_board(gameboard)){
        //
        int row, col;
        cout << "player, Where should I put the piece?";
        cout << "row : " << endl;
        cin >> row;
        cout << "col : " << endl;
        cin >> col;
        //row, col = put_piece(gameboard, player);

        int adjacency=0;

        for(int dir=0; dir<8; dir++){
         int res=checkAdjacency(gameboard, row, col, dir, player);
         if(res>0){
          adjacency+=res;

          //둘러싸고 있는 돌들은 우리 돌로 바꾸기.
          set(gameboard, row, col, player, dir, res);
         }
        }
        player = switchplayer(player);

    }
    for(int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < NUM_COLS; j++){
            cout << gameboard[i][j] << " ";
        }
        cout << endl;
    }

}


void initialize_game_board(int gb [][NUM_COLS]) //done using ui
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
            gb[i][j] = EMPTY;
    }
    gb[3][3] = WHITE; //1:white
    gb[4][4] = WHITE;
    gb[3][4] = BLACK; //2:black
    gb[4][3] = BLACK;
}

bool check_pull_board(int gb [][NUM_COLS])
{
    int n_empty = 0;
    for (int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLS; j++){
            if(gb[i][j]==EMPTY)
                n_empty += 1;
        }
    }

    if(n_empty == 0){
        return false;
    }else{
        return true;
    }
}

int switchplayer (int player) { //switched using turn value
    if (player == 1)
    {
        player =2;
    }
    else
    {
        player=1;
    }
    return(player);
}

int checkAdjacency(int gb [][NUM_COLS], int r, int c, int dir, int ply)
{
 //dir은 8방향을 의미 : 0~7까지 유효하다.
    int nOppCount=0;
    int nMyCount=0;

    while(1)
   {
    switch(dir){
    case 0:
        c--;
        break;
    case 1:
        c++;
        break;
    case 2:
        r--;
        break;
    case 3:
        r++;
        break;
    case 4:
        r--; c--;
        break;
    case 5:
        r++; c--;
        break;
    case 6:
        r--; c++;
        break;
    case 7:
        r++; c++;
        break;
    default:
        break;
  }

    if(r<0 || c<0 || r>7 || c>7) //더이상 진행이 되지 않는다.
        break;

    if (ply==1)
    {
        gb[r][c] = BLACK;
        nMyCount++;
        break;
    }else if (ply==2){
        gb[r][c] = WHITE;
        nOppCount++;
    }else {
        break;
    }
  }
    if(nOppCount>0 && nMyCount==1)
        return nOppCount;
    else
        return 0;
}


void set(int gb [][NUM_COLS], int r, int c, int ply, int dir, int res)
{
    int nCount=0;

    while(1)
    {
        switch(dir){
            case 0:
                c--;
                break;
            case 1:
                c++;
                break;
            case 2:
                r--;
                break;
            case 3:
                r++;
                break;
            case 4:
                r--; c--;
                break;
            case 5:
                r++; c--;
                break;
            case 6:
                r--; c++;
                break;
            case 7:
                r++; c++;
                break;
            default:
                break;
    }
    if (ply==1)
     {
         gb[r][c] = BLACK;
     }else{
         gb[r][c] = WHITE;
     }
  nCount++;
  if(nCount==res) break;
 }
}


*/
