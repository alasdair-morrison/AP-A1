#include <iostream>

bool play{true};

void printBoard(){
std::cout << 
       "     I     I     \n"
       "     I     I     \n"
       "_____I_____I_____\n"
       "     I     I     \n"
       "     I     I     \n"
       "_____I_____I_____\n"
       "     I     I     \n"
       "     I     I     \n"
       "     I     I     \n";
}

void playerMove(char b[2][2]){
    int move{0};
    while(true){
        std::cout << "Enter your move, using numeric keyboard method.";
        std::cin >> move;
        int row = 2-(move-1)/3;
        int col=(move-1)%3;
        if (b[row][col]!= ' . '){
            std::cout << "Invalid move, try again";
        }
        else{
            b[row][col]=' x ';
            break;
        }
    }
}

bool checkPlayAgain(){
    bool validInput{false};
    char input{};
    while (validInput == false){
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

    printBoard();

    while(play==true){
        //play tha game
    
    play = checkPlayAgain();
    }
    std::cout <<"Thank you for playing!!";
}