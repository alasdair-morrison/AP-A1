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
        if(a[i]==a[i+1]=a[i+2]){return true;}
        if()
    }
}

int main(){

    printBoard();

    while(play==true){
        //play tha game
    
    play = checkPlayAgain();
    }
    std::cout <<"Thank you for playing!!";
}