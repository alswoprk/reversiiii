#include "mainwindow.h"
#include "./ui_mainwindow.h"

//int turn=0; //global variable to call on

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap choosing_player, starting_page, rules_page, ending_page, playing_page, choose_mode_page;
    choosing_player.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/choose_player.png"); //CHANGE IMAGE DIRECTORY HERE!
    starting_page.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/start_page.png");
    rules_page.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/rules_page.png");
    playing_page.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/playing_background.png");
    ending_page.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/ending_page.png");
    choose_mode_page.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/choose_mode_page.png");

    //ui->player_status->show();
    ui->choose_player_label->setPixmap(choosing_player);
    ui->start_page_label->setPixmap(starting_page);
    ui->rule_page_label->setPixmap(rules_page);
    ui->playing_background->setPixmap(playing_page);
    ui->ending_page_label->setPixmap(ending_page);
    ui->choose_mode_background->setPixmap(choose_mode_page);

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
    ui->stackedWidget->setCurrentIndex(5);
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

void MainWindow::end_the_game()
{
    int winner;
    ui->stackedWidget->setCurrentIndex(4);
    if(player1_score>player2_score){ //decide winner
        winner=1;
    }
    else if(player2_score>player1_score){
        winner=2;
    }
    else{
        winner=3;

    }

    if(winner==3){
        ui->final_winner->setText("1&2");

    }
    else{
        ui->player1_final->setText(QString::number(player1_score));
        ui->player2_final->setText(QString::number(player2_score));
        ui->final_winner->setText(QString::number(winner));
    }


    //set winner label
}

void MainWindow::update_board_score() //updating score
{
    player1_score=0;
    player2_score=0;
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
        end_the_game();
    }

}


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

        start_idx=row_idx+1;
        end_idx=start_idx;

        while(button_slots[end_idx][column_idx]==opponent_player){

            end_idx+=1; //find when stops
        }

        if(button_slots[end_idx][column_idx]==current_player){

            change_pieces(start_idx, end_idx, current_player, 1, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================
    if(button_slots[row_idx-1][column_idx]==opponent_player){ //case for when top part is true
        //works until here
        start_idx=row_idx-1;
        end_idx=start_idx;

        while(button_slots[end_idx][column_idx]==opponent_player){

            end_idx-=1; //find when stops
        }

        if(button_slots[end_idx][column_idx]==current_player){

            change_pieces(end_idx, start_idx, current_player, 1, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================
    if(button_slots[row_idx][column_idx+1]==opponent_player){ //case for when right part is true
        //works until here
        start_idx=column_idx+1;
        end_idx=start_idx;


        while(button_slots[row_idx][end_idx]==opponent_player){

            end_idx+=1; //find when stops
        }

        if(button_slots[row_idx][end_idx]==current_player){

            change_pieces(start_idx, end_idx, current_player, 2, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================
    if(button_slots[row_idx][column_idx-1]==opponent_player){ //case for when top part is true

        start_idx=column_idx-1;
        end_idx=start_idx;

        while(button_slots[row_idx][end_idx]==opponent_player){

            end_idx-=1; //find when stops
        }

        if(button_slots[row_idx][end_idx]==current_player){

            change_pieces(end_idx, start_idx, current_player, 2, row_idx, column_idx); //1 means row needs to change, 2 means col needs to change
        }
    }
    //================================================================




}

bool MainWindow::check_in_slot(int row_idx, int column_idx){ //check whether in slot
    if (button_slots[row_idx][column_idx]==1 ||button_slots[row_idx][column_idx]==2 )
        return true;
    else
        return false;
}

bool MainWindow::check_adjacency(int row_idx, int column_idx){ //check adjacent places to see if can be placed
    if(button_slots[row_idx-1][column_idx]==1||button_slots[row_idx-1][column_idx]==2)
        return false;
    else if(button_slots[row_idx+1][column_idx]==1||button_slots[row_idx+1][column_idx]==2)
        return false;
    else if(button_slots[row_idx][column_idx+1]==1||button_slots[row_idx][column_idx+1]==2)
        return false;
    else if(button_slots[row_idx][column_idx-1]==1||button_slots[row_idx][column_idx-1]==2)
        return false;
    else if(button_slots[row_idx-1][column_idx-1]==1||button_slots[row_idx-1][column_idx-1]==2)
        return false;
    else if(button_slots[row_idx-1][column_idx+1]==1||button_slots[row_idx-1][column_idx+1]==2)
        return false;
    else if(button_slots[row_idx+1][column_idx-1]==1||button_slots[row_idx+1][column_idx-1]==2)
        return false;
    else if(button_slots[row_idx+1][column_idx+1]==1||button_slots[row_idx+1][column_idx+1]==2)
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

    //ui->warning_1->setText("You placed on row: "+just_row_idx);
    //ui->warning_2->setText("You placed on column: "+just_column_idx);


    QPixmap warning1, good;
    warning1.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/error_message.png"); //CHANGE IMAGE DIRECTORY HERE!
    good.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/good_message.png"); //CHANGE IMAGE DIRECTORY HERE!



    if(check_in_slot(row_idx, column_idx)){ //check whether button has been placed with something already
        //set error message


        ui->warning_1->setPixmap(warning1);
        ui->warning_1->show();



        //setting label without qt designer and only comes out for warning signs
        //set label for only couple seconds or terminate when clicked on
    }
    else if(check_adjacency(row_idx, column_idx)){
        //if no adjacency, set error message
        //check if can put down piece

        ui->warning_1->setPixmap(warning1);
        ui->warning_1->show();
    }

    else{

        ui->warning_1->setPixmap(good); //show good sign when placed correctly
        ui->warning_1->show();



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


    if(limit_mode==true){
        if(starting_player==1){
            if(turn==10)
                end_the_game();

        }
        else{
            if(turn==11)
                end_the_game();
        }
    }

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
    starting_player=1;
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap player1;
    player1.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player1_status.png"); //CHANGE IMAGE DIRECTORY HERE!

    ui->player_status->setPixmap(player1);
    ui->player_status->show();






    initialize_board();


}


void MainWindow::on_choose_player2_clicked()
{
    starting_player=2;
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap player2;
    player2.load("C:/HGU/Grade4_Sem2/Programming2/reversiiii/tosize_2/player2_status.png"); //CHANGE IMAGE DIRECTORY HERE!

    ui->player_status->setPixmap(player2);
    ui->player_status->show();
    turn+=1;

    initialize_board();

}


void MainWindow::on_ending_button_clicked()
{
    end_the_game();
}


void MainWindow::on_normal_mode_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_limited_mode_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    limit_mode=true;
}

