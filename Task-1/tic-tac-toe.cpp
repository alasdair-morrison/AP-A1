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

for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
        std::cout<<board[i][j];
    }
    std::cout<<"\n";
}
}



void playerMove(char b[3][3]) {
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
            b[row][col] = 'x';
            return;
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
            return true;
        }
        else{
            return false;
        } 
    } 
}

bool checkWinCons(int a[8]){
    for(int i=0; i<3; i++){
        if(a[i]==a[i+3] && a[i]==a[i+6]){return true;}
        if(a[i*3]==a[i*3+1] && a[i*3]==a[i*3+2]){return true;}
    }
    if(a[0]==a[4] && a[0]==a[8]){return true;}
    if(a[2]==a[4] && a[2]==a[6]){return true;}
    return false;
}

int main(){

    //printBoard();

    while(play==true){
        for(int i=0; i<10; i++){
            playerMove(board);
            printBoard(board);
            if 
        }
        play = checkPlayAgain();
    }
    std::cout <<"Thank you for playing!!";
}