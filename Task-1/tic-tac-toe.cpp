#include <iostream>

bool play{true};
char board[3][3] = {
    {'.', '.', '.'},
    {'.', '.', '.'},
    {'.', '.', '.'}
};

void printBoard(char board[3][3]){
// std::cout << 
//        "     I     I     \n"
//        "     I     I     \n"
//        "_____I_____I_____\n"
//        "     I     I     \n"
//        "     I     I     \n"
//        "_____I_____I_____\n"
//        "     I     I     \n"
//        "     I     I     \n"
//        "     I     I     \n";

std::cout<<"\n";
for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
        std::cout<<board[i][j];
    }
    std::cout<<"\n";
}
}



void playerMove(char b[3][3], char p) {
    int move{0};

    while (true) {
        std::cout << "Enter your move (1-9) using numeric keypad layout): ";
        std::cin >> move;

        if (move < 1 or move > 9) {
            std::cout << "Invalid number, try again.\n";
            continue;
        }

        int row = 2 - (move - 1) / 3;
        int col = (move - 1) % 3;

        std::cout << b[row][col];

        if (b[row][col] != '.') {
            std::cout << "Invalid move, try again.\n";
        }
        else {
            b[row][col] = p;
            return;
        }
    }
}

void resetboard(char a[3][3]){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            a[i][j]='.';
        }
    }
}

bool checkPlayAgain(){
    char input{};
    while (true){
        std::cout << "Would you like to play again? (y/n) " ;
        std::cin >> input;
        if(input!='y' && input!='n'){
            std::cout << "Invalid input, y/n only \n";
        }
        else if(input == 'y'){
            resetboard(board);
            return true;
        }
        else{
            return false;
        } 
    } 
}


bool checkWinCons(char a[3][3], char p){
    for(int i=0; i<3; i++){
        //checking straights for winners
        if(a[i][0]==p && a[i][1]==p && a[i][2]==p){return true;}
        if(a[0][i]==p && a[1][i]==p && a[2][i]==p){return true;}
    }
    //check diagonals for winners
    if(a[0][0]==p && a[1][1]==p && a[2][2]==p){return true;}
    if(a[0][2]==p && a[1][1]==p && a[2][0]==p){return true;}
    return false;
}

int main(){

    //printBoard();

    while(play==true){
        int i = 0;
        bool winnercheck = false;
        char playerturn='x';
            while(i<9 && winnercheck == false){
                if(i%2==0){playerturn='x';}
                else{playerturn='o';}
                playerMove(board,playerturn);
                printBoard(board);
                winnercheck = checkWinCons(board,playerturn);
                i++;
        }
        if (winnercheck == true){
            std::cout<< playerturn << " has won!\n";
        }
        else{std::cout<<"The match was a draw!\n";}
        play = checkPlayAgain();
    }
    std::cout <<"Thank you for playing!!";
}