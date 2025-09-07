#include <iostream>
#include <algorithm>



void printOutBoard(char board[3][3]);
void choiceChar(char &player, char &computer);

int playerchoiceNumber(char board[3][3]);
int computerchoiceNumber(char board[3][3]);

void placeCharacteronBoard(char character, char board[3][3], int playerChoice);
bool checkVictoryConditions(char board[3][3], char sign);


int main(){

    char board[3][3] = {};
    char player;
    char computer;

    int playerChoice;
    int computerChoice;

    bool gamefinish = false;
    std::string winnername;
    std::fill(&board[0][0], &board[0][0] + 3 * 3, ' ');
    // main game loop


    while (true){
        playerChoice = playerchoiceNumber(board);
        placeCharacteronBoard(player, board, playerChoice);
        printOutBoard(board);
        gamefinish = checkVictoryConditions(board, player);
        if (gamefinish){
            winnername = "Player";
            break;
        }
     // computer move 

     
    };
    std::cout << "Congratulations Player: " << winnername << "won";
    


    return 0;
}

void printOutBoard(char board[3][3]){
    std::cout <<  "_____________\n";
    for (int row = 0; row < 3; row++){
            std::cout << "| ";
        for(int col = 0; col < 3; col++){
            std::cout << " " << (board[row][col] == ' ' ? ' ' : board[row][col]) << " |";
        }
        std::cout << '\n';
        std::cout << "_____________\n";  
    }
}

void choiceChar(char &player, char &computer){
    while(true){
    std::string input;
    std::cout << "Which Symbol do u want to choose (x or o)? \n";
    std::cin >> input;

    if (input.size() != 1){
        std::cout << "Please povide a valid input (x or o)";
    }
    char charInput = std::tolower(input[0]);
    switch (charInput) {
        case 'x':
            player = 'X';
            computer = 'O';
            break;
        case 'o':
            player = 'O';
            computer = 'X';
            break;
        default:
            std::cout << "Please povide a valid input (x or o)";
    }
}
}
void placeCharacteronBoard(char character, char board[3][3], int playerChoice){
    int cols = (playerChoice - 1) % 3;
    int rows = (playerChoice - 1) / 3;

    board[rows][cols] = character;
}

bool checkVictoryConditions(char board[3][3], char sign){
        int counts;
        // horizontal check
        for (int i = 0; i < 3; i++){ // rows
            counts = 0;
        for (int j = 0; j < 3; j++){ // cols
            if (board[i][j] == sign) counts ++;
        }
        if (counts == 3){
            return true;
        }

        }
        //Vertical check
        for (int j=0; j < 0;j++){
            counts = 0;
            for (int i=0; i < 0; i++){
                if (board[i][j] == sign) counts ++; 
            
            }
            if (counts == 3){
                return true;
            }
        }
        // diagnonal check
        if ((board[0][0] == sign && board[1][1] == sign && board[2][2])||
            (board[0][2] == sign && board[1][1] == sign && board[0][2])){
                return true;
            }
        return false;


    }

int playerchoiceNumber(char board[3][3]){
        int choice;
        while(true){
        std::cout << "Where do u want to place your sign (1-9)\n ?";
        std::cin >> choice;
        if(choice >= 1 && choice <= 9){
                int cols = (choice - 1) % 3;
                int rows = (choice - 1) / 3;
                if (board[rows][cols] == ' '){
                    return choice;
                }
                else {
                    std::cout << "This position is already occupied!";
                }
    }
        else{
            std::cout << "Please provide correct input!";
    }
}
}

int computerchoiceNumber(char board[3][3]){
        int choice;
        while(true){
        std::cout << "Where do u want to place your sign (1-9)\n ?";
        std::cin >> choice;
        if(choice >= 1 && choice <= 9){
                int cols = (choice - 1) % 3;
                int rows = (choice - 1) / 3;
                if (board[rows][cols] == ' '){
                    return choice;
                }
                else {
                    std::cout << "This position is already occupied!";
                }
    }
        else{
            std::cout << "Please provide correct input!";
    }
}
}
