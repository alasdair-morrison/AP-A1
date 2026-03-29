#include <iostream>
#include <random>

bool play{true};
char board[3][3] = {
    {'.', '.', '.'},
    {'.', '.', '.'},
    {'.', '.', '.'}
};

//Function to print out current 3x3 board
void printBoard(char board[3][3]){
std::cout<<"\n";
for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
        std::cout<<board[i][j];
    }
    std::cout<<"\n";
}
}


//function to allow player to choose square
void playerMove(char b[3][3], char p) {
    int move{0};

    while (true) {
        std::cout << "Enter your move (1-9) using numeric keypad layout): ";
        std::cin >> move;

        //Checks if user has entered number within acceptable range
        if (move < 1 or move > 9) {
            std::cout << "Invalid number, try again.\n";
            continue;
        }

        //converts input into rows and coloumbs to use with 2d-array
        int row = 2 - (move - 1) / 3;
        int col = (move - 1) % 3;

        //checks if square is empty
        if (b[row][col] != '.') {
            std::cout << "Invalid move, try again.\n";
        }
        else {
            b[row][col] = p;
            return;
        }
    }
}

//Function for AI
void AIMove(char b[3][3], char p) {

    while (true) {
        //generates random number between 1-9
        std::mt19937 gen(std::random_device{}()); // random seed
        std::uniform_int_distribution<int> dist(1, 9); // range [1, 9]
        int move = dist(gen);

        //converts into row s and coloumbs to use with 2d-array
        int row = 2 - (move - 1) / 3;
        int col = (move - 1) % 3;

        //makes sure square isn't full
        if (b[row][col] == '.') {
            b[row][col] = p;
            return;
        }
    }
}

//Resets 3x3 board array if player wants to play again
void resetboard(char a[3][3]){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            a[i][j]='.';
        }
    }
}

//checks if player wants to play again
bool checkPlayAgain(){
    char input{};
    while (true){
        std::cout << "Would you like to play again? (y/n) " ;
        std::cin >> input;

        //makes sure user has entered a valid character
        if(input!='y' && input!='n'){
            std::cout << "Invalid input, y/n only \n";
        }

        //if user wants to play again, reset board and return true
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
        //checking straights for winners (three of either y or x)
        if(a[i][0]==p && a[i][1]==p && a[i][2]==p){return true;}
        if(a[0][i]==p && a[1][i]==p && a[2][i]==p){return true;}
    }
    //check diagonals for winners (three of either y or x)
    if(a[0][0]==p && a[1][1]==p && a[2][2]==p){return true;}
    if(a[0][2]==p && a[1][1]==p && a[2][0]==p){return true;}
    return false;
}

int main(){

    while(play==true){
        //initialise starter values
        int i = 0;
        bool winnercheck = false;
        char playerturn='x';

        //checks what mode the player would like to play
        int input{3};
        while(input != 2 && input != 1){
            std::cout << "Play AI or Person (1/2)? " ;
            std::cin >> input;
        }

        if(input==1){
            //while the board is not full and noone has reached three in a row
            while(i<9 && winnercheck == false){
                if(i%2==0){
                    //set the turn to x and allow the player to choose a square
                    playerturn='x';
                    playerMove(board,playerturn);
                }

                //sets the turn to "o" and chooses random square
                else{
                    playerturn='o';
                    AIMove(board,playerturn);
                }

                //prints current board after the current turn is over and checks for winners
                printBoard(board);
                winnercheck = checkWinCons(board,playerturn);
                i++;
            }
        }

        if(input==2){
            //while the board is not full and noone has reached three in a row
            while(i<9 && winnercheck == false){
                //switches between naughts and crosses every turn
                if(i%2==0){playerturn='x';}
                else{playerturn='o';}

                //allows current player to choose square and prints board
                playerMove(board,playerturn);
                printBoard(board);

                //checks for a winner
                winnercheck = checkWinCons(board,playerturn);
                i++;
            }
        }  

        //Print win situation e.g."x's has won" or "match waws a draw"
        if (winnercheck == true){std::cout<< playerturn << " has won!\n";}
        else{std::cout<<"The match was a draw!\n";}

        //checks if the player wants to play again
        play = checkPlayAgain();
    }
    //friendly message before closing program (:
    std::cout <<"Thank you for playing!!";
}