#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

enum choices {ROCK=1, PAPER, SCISSORS};

int letter_to_score(char x){
    switch(x){
        case 'A':
            return ROCK;
        case 'B':
            return PAPER;
        default:
            return SCISSORS;
    }
}

int determine_play(int x, char y){
    switch(y){
        case 'X':
            switch(x){
                case ROCK:
                    return SCISSORS;
                case PAPER:
                    return ROCK;
                default:
                    return PAPER;
            }
        case 'Z':
            switch(x){
                case ROCK:
                    return PAPER;
                case PAPER:
                    return SCISSORS;
                default:
                    return ROCK;
            }
        default:
            return x;
    }
}

int get_round_score(int x, int y){
    int score = y;
    if ((x == ROCK && y==PAPER) || (x == PAPER && y == SCISSORS) 
                                || (x == SCISSORS && y == ROCK)){
        score += 6;
    }
    else if (x == y){
        score += 3;
    }
    return score;
}

int main() {
    std::string line;
    char temp;
    int player1, player2;
    int total = 0;
    
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::istringstream ss(line);
            ss >> temp;
            player1 = letter_to_score(temp);
            ss >> temp;
            player2 = determine_play(player1, temp);
            total += get_round_score(player1, player2);
        }
        myfile.close();
    }
    
    std::cout << "Your total score: " << total << "\n\n";

    return 0;
}