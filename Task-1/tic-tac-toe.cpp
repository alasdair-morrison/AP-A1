#include <iostream>

bool play{true};
bool played{false};

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
    bool p{true};
    while (validInput == false && played == true){
        std::cout << "Would you like to play again? (y/n) " ;
        std::cin >> input;
        if(input!='y' && input!='n'){
            std::cout << "Invalid input, y/n only \n";
        }
        else if(input == 'y'){
            validInput == true;
            p=true;
        }
        else{
            validInput=true;
            p=false;
        } 
    } 
    return p;
}



int main(){

    printBoard();

    while(play==true){
        //play tha game

    played = true;
    
    play = checkPlayAgain();
    }
    std::cout <<"Thank you for playing!!";
}