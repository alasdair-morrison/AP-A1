#include <iostream>

bool play{true}
bool played{false};

int main(){
    std::cout << "Hello world" ;

    if(play==true){
        //play tha game
    }
    
    bool validInput{false};
    char input{};
    while (validInput == false && played == true){
        std::cout << "Would you like to play again? (y/n) " ;
        std::cin >> input;
        if(input!='y' && input!='n'){
            std::cout << "Invalid input, y/n only";
        }
        else if(input == 'n'){
            validInput == true;
        }
        else{
          play=false;
          validInput=true;
        } 
    } 
    std::cout <<"Thank you for playing!!";
}