#include <iostream>
#include <algorithm>
#include <random>
#include <vector>


void printOutBoard(char board[3][3]);
void choiceChar(char &player, char &computer);

int playerchoiceNumber(char board[3][3]);
int computerchoiceNumber(char board[3][3], char self , char adversary);

void placeCharacteronBoard(char character, char board[3][3], int indexChoice, bool playerInput = false);
bool checkVictoryConditions(char board[3][3], char sign);

bool checkdraw(char board[3][3]);
std::vector <int> getvalidMoves(char board[3][3]);
int minimax(char board[3][3], bool is_maximizing, char self , char adversary);



int main(){

    char board[3][3] = {};
    char player;
    char computer;

    int playerChoice;
    int computerChoice;

    bool gamefinish = false;
    bool draw = true;
    std::string winnername;
    std::fill(&board[0][0], &board[0][0] + 3 * 3, ' ');

    choiceChar(player, computer);
    // main game loop


    while (true){
        // Player Move
        playerChoice = playerchoiceNumber(board);
        placeCharacteronBoard(player, board, playerChoice, true);
        printOutBoard(board);
        gamefinish = checkVictoryConditions(board, player);
        if (gamefinish){
            winnername = "Player";
            break;
        }
        // computer move 
        computerChoice = computerchoiceNumber(board, computer, player);
        placeCharacteronBoard(computer, board, computerChoice);
        printOutBoard(board);
        gamefinish = checkVictoryConditions(board, computer);
        if (gamefinish){
            winnername = "Computer";
            break;
        }
        // check for draw
        draw = checkdraw(board);
        if(draw){
            break;
        }

     
    }
    std::cout << (draw ? "It's a draw!\n": "Congratulations Player: " + winnername + " won\n");


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
        std::cout << "Please povide a valid input (x or o) \n";
        continue;
    }
    char charInput = std::tolower(input[0]);
    switch (charInput) {
        case 'x':
            player = 'X';
            computer = 'O';
            return;
        case 'o':
            player = 'O';
            computer = 'X';
            return;
        default:
            std::cout << "Please povide a valid input (x or o)\n";
    }
}
}
void placeCharacteronBoard(char character, char board[3][3], int indexChoice, bool playerInput){
    int index = playerInput ? indexChoice-1:indexChoice;
    int cols = index % 3;
    int rows = index / 3;

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
        for (int j=0; j < 3;j++){
            counts = 0;
            for (int i=0; i < 3; i++){
                if (board[i][j] == sign) counts ++; 
            
            }
            if (counts == 3){
                return true;
            }
        }
        // diagnonal check
        if ((board[0][0] == sign && board[1][1] == sign && board[2][2] == sign)||
            (board[0][2] == sign && board[1][1] == sign && board[2][0] == sign)){
                return true;
            }
        return false;


    }

int playerchoiceNumber(char board[3][3]){
        int choice;
        while(true){
        std::cout << "Where do u want to place your sign (1-9)? \n";
        std::cin >> choice;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout << "Please provide correct input!\n";
            continue;
        }
        if(choice >= 1 && choice <= 9){
                int cols = (choice - 1) % 3;
                int rows = (choice - 1) / 3;
                if (board[rows][cols] == ' '){
                    return choice;
                }
                else {
                    std::cout << "This position is already occupied!\n";
                }
    }
        else{
            std::cout << "Please provide correct input!\n";
    }
}
}
int minimax(char board[3][3], bool is_maximizing, char self , char adversary){
        bool winner = false;
        int bestscore;
        int score;
        winner = checkVictoryConditions(board, self);
        if (winner) return 1;
        // check victory position adversary
        winner = checkVictoryConditions(board, adversary);
        if (winner) return -1;
        winner = checkdraw(board);
        if (winner) return 0;
        //maximizer
        if (is_maximizing){
            bestscore = -1000;
            for(int move : getvalidMoves(board)){
                // place on board
                placeCharacteronBoard(self, board, move);
                score =  minimax(board, false, self, adversary);
                // remove from board
                placeCharacteronBoard(' ', board, move);
                bestscore = std::max(bestscore, score);
            }
            return bestscore;
        }
        // minimizer
        else{
            bestscore = 1000;
            for (int move : getvalidMoves(board)){ 
                // place on board
                placeCharacteronBoard(adversary, board, move);
                score = minimax(board, true, self, adversary);
                //remove from board
                placeCharacteronBoard(' ', board, move);
                bestscore = std::min(bestscore, score);
            }
        return bestscore;
        }



}
std::vector<int> getvalidMoves(char board[3][3]){
    std::vector <int> validMoves;
    int index = 0;
    for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == ' ') validMoves.push_back(index);
                index++;
                
            }   
        }
    return validMoves;


}

int computerchoiceNumber(char board[3][3], char self , char adversary){
        int bestMove;
        int bestScore = -1000;
        int score;

        for(int move: getvalidMoves(board)){
            placeCharacteronBoard(self, board, move);
            score = minimax(board, false, self, adversary);
            //remove from board
            placeCharacteronBoard(' ', board, move);
            
        if (score >bestScore){
            bestScore=score;
            bestMove = move;
        }
        }
        return bestMove;


}


bool checkdraw(char board[3][3]){
    for(int i = 0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == ' ') return false;

        }
    }
    return true;
    }
