#include "mainwindow.h"
#include "./ui_mainwindow.h"

int turn=0; //global variable to call on


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->stackedWidget->

    QPushButton *button_slots[8][8]; //creating slot names as array; define in header
    for(int i=0; i<8; ++i){
        for(int j=0; j<8; ++j){
            QString butName="button"+QString::number(i)+QString::number(j);
            button_slots[i][j]=MainWindow::findChild<QPushButton *>(butName);
            connect(button_slots[i][j], SIGNAL(released()), this, SLOT(button_slots_pressed())); //connecting buttons
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

//
void MainWindow::button_slots_pressed(){

    QPushButton *button = (QPushButton *)sender();

    //CHANGE IMAGE DIRECTORY HERE!
    QPixmap player1_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_icon"); //create button icons
    QPixmap player2_icon("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_icon");
    QIcon icon1(player1_icon);
    QIcon icon2(player2_icon);

    //check whether button has icon already with if

    //setting label without qt designer and only comes out for warning signs
    //set label for only couple seconds or terminate when clicked on

    if(turn%2==0){ //changing turns
        button->setIcon(icon1);

        QPixmap player2; //changing signs of player status
        player2.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_status.png"); //CHANGE IMAGE DIRECTORY HERE!

        ui->player_status->setPixmap(player2);
        ui->player_status->show();

        //send value of icon; find way to figure out which button was pressed
    }
    else{
        button->setIcon(icon2);

        QPixmap player1; //changing signs of player status
        player1.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_status.png"); //CHANGE IMAGE DIRECTORY HERE!

        ui->player_status->setPixmap(player1);
        ui->player_status->show();
    }



    turn+=1;

    //button->setIcon(icon1);

}
//

void MainWindow::on_rules_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_return_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_choose_player1_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap player1;
    player1.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_status.png"); //CHANGE IMAGE DIRECTORY HERE!

    ui->player_status->setPixmap(player1);
    ui->player_status->show();
}


void MainWindow::on_choose_player2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap player2;
    player2.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_status.png"); //CHANGE IMAGE DIRECTORY HERE!

    ui->player_status->setPixmap(player2);
    ui->player_status->show();
    turn+=1;
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
