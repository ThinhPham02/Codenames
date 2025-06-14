#ifndef CODENAMES_H
#define CODENAMES_H

#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;

class CodeNames {
    private:
        int redAgents = 9;
        int blueAgents = 8;
        
        vector<string> board;
        vector<string> keyCard;
        vector<string> guessedword;
        vector<string> displayBoard;

        string blue = "    B";
        string red = "   Red";
        string white = "  [   ]";    
        string black = "[ BLACK ]";    

        void PrintKeyCard() {
            ofstream file("KeyCard.txt", ios::trunc);
            for (int i = 0; i < keyCard.size(); i++) {
                file << setw(18) << left << keyCard[i];
                if ((i + 1) % 5 == 0) { file << endl << endl; }
            }
            file.close();
        }

        void BoardSetUp() {
            string word;
            for (int i = 0; i < 25; i++) {
                while (true) {
                    word = getWord();
                    if (checkWord(word)) { 
                        board.push_back(word);
                        break; 
                    }
                }
            }
            displayBoard = board;
        }

        void KeyCardSetUp() {
            addCards(1, black);
            addCards(7, white);
            addCards(8, blue);
            addCards(9, red);

            vector<string> swap;
            shuffle(keyCard, swap);
        }

        void addCards(int num, string color) {
            for (int i = 0; i < num; i++) {
                keyCard.push_back(color);
            }
        }

        void shuffle(vector<string>& take, vector<string>& add) {
            for (int i = 0; i < 25; i++) {
                Take(take, add);
            }
            for (int j = 0; j < 25; j++) {
                Take(add, take);
            }
        }

        void Take(vector<string>& take, vector<string>& add) {
            int index = rand() % take.size();
            string word = take[index];
            take.erase(take.begin() + index);
            add.push_back(word);
        }

        bool checkWord(string word) {
            for (string w : board) {
                if (w == word) {
                    return false;
                }
            }
            return true;
        }

        string getWord() {
            int count = 0;
            string word;
            ifstream file("Dictionary.txt");

            while (file >> word) {
                count++;
            }

            int pickWord = rand() % count + 1;

            file.clear();                 // Clear EOF and any other flags
            file.seekg(0, ios::beg); 

            int current = 0;
            while (file >> word) {
                current++;
                if (current == pickWord) {
                    break;
                }
            }

            return word;
        }

        void Intro() {
            cout << "=========================\n";
            cout << "🔐 WELCOME TO CODENAMES 🔐\n";
            cout << "=========================\n\n";

            cout << "Two rival spymasters know the secret identities of 25 agents.\n";
            cout << "Their teammates know these agents only by their *codenames* — single-word clues like\n";
            cout << "\"Disease\", \"Germany\", or even \"Carrot\". Yes, *carrot* — anything goes in the field.\n\n";

            cout << "🎯 OBJECTIVE:\n";
            cout << "Each team must contact all of their agents before the other team does —\n";
            cout << "but beware... one of the codenames belongs to an assassin.\n";
            cout << "Guess the assassin, and your team loses instantly.\n\n";

            cout << "🕹️ GAME OVERVIEW:\n";
            cout << "- 25 codename cards are laid out in a 5x5 grid.\n";
            cout << "- A key card reveals which codenames belong to red agents, blue agents, bystanders, or the assassin.\n";
            cout << "- Each spymaster takes turns giving a *one-word clue* and a number.\n\n";

            cout << "🧠 HOW CLUES WORK:\n";
            cout << "- A clue is a single word + a number (e.g., \"Animal 2\").\n";
            cout << "- The number tells teammates how many words relate to the clue.\n";
            cout << "- Teammates may guess up to (number + 1) words — one at a time.\n";
            cout << "- A correct guess keeps the turn going. A wrong one ends it.\n\n";

            cout << "⚠️ TURN RESULTS:\n";
            cout << "- Guess your team's agent: you continue.\n";
            cout << "- Guess a bystander: your turn ends.\n";
            cout << "- Guess the opposing team's agent: your turn ends *and* helps them.\n";
            cout << "- Guess the assassin: 💀 INSTANT LOSS.\n\n";

            cout << "🏆 VICTORY:\n";
            cout << "The first team to identify all their agents wins — unless someone finds the assassin first...\n\n";

            cout << "🕵️‍♂️ Good luck, agents. Trust no one. Think carefully. Speak cleverly.\n\n";
        }

    public: 
        CodeNames() {
            srand(time(nullptr));
            setUp();
        }

        void setUp() {
            Intro();
            BoardSetUp();
            KeyCardSetUp();
            PrintKeyCard();
            Start();

            cout << "What a match! That one’s going straight into the Codename Hall of Fame.\n\n";
        }

        void Start() {
            int num;
            int turn = 0;
            string team1;
            string team2;
            string agent;
            string color;
            string codename;

            cout << "====================================\n";
            cout << "🎮  Welcome to CODENAMES: Showdown! 🎮\n";
            cout << "====================================\n\n";

            cout << "🟥 First team, please enter your name: \n";
            getline(cin, team1);

            cout << "🟦 Second team, please enter your name: \n";
            getline(cin, team2);

            cout << "\n🎉 Welcome, " << "🟥 " + team1 << " and " << "🟦 " + team2 << ", to the battlefield of wits!\n";
            cout << "Red agents remaining: " << redAgents << "\n";
            cout << "Blue agents remaining: " << blueAgents << "\n";
            cout << "🔴 " << team1 << ", you will make the first move.\n\n";

            while(true) {
                turn++;
                int currentTeamAgents = (turn % 2 == 0) ? blueAgents : redAgents;
                int otherTeamAgents = (turn % 2 == 0) ? redAgents : blueAgents;
                string currentTeam = (turn % 2 == 0) ? "🟦 " + team2 : "🟥 " + team1;
                string otherTeam = (turn % 2 == 0) ? "🟥 " + team1 : "🟦 " + team2;
                
                cout << "\n🔍 Review the codenames in play before making your move:\n\n";
                printDisplayBoard();

                cout << "🕵️‍♂️ " << currentTeam << "'s Spymaster, enter your clue.\n";
                cout << "🔑 Codename (one word): \n";
                cin >> codename;

                while (!checkClue(codename)) {
                    cout << "🔍 That clue reveals a codename on the board. Spymaster, select a new, stealthier clue for your team.\n";
                    cin >> codename;
                }

                cout << "🔢 How many agents are related to \"" << codename << "\"? \n";
                cin >> num;

                while (num > currentTeamAgents || num < 0) {
                    cout << "\n❗ \"" << num << "\"? That's outside mission parameters. Choose between 0 and " << currentTeamAgents << ".\n";
                    cout << "🎯 How many agents are you targeting with \"" << codename << "\"? ";
                    cin >> num;
                }

                cout << "\n==========================================\n";
                cout << "🗝️  Clue Given: \"" << codename << "\" — " << num << " agent(s) connected.\n";
                cout << "🧠 " << currentTeam << ", it's time to identify your agents.\n";
                cout << "==========================================\n\n";

                int holder = num;
                if (num == 0) { holder = 25; }
                for (int i = 0; i < holder + 1; i++) {
                    if (num == 0 && i > 0) {
                        char inp;
                        cout << "\n 🕵️ Do you want to push your luck and keep going? (y/n): \n";
                        cin >> inp;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (tolower(inp) != 'y') {
                            cout << "Turn ended.\n\n";
                            break;
                        }
                    }
                    if (i == num && num != 0) {
                        char inp;
                        cout << "\n🔁 You've used all " << num << " guesses from the clue.\n";
                        cout << "Would you like to make the optional extra guess? (y/n): \n";
                        cin >> inp;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (tolower(inp) != 'y') {
                            cout << "Turn ended.\n\n";
                            break;
                        }
                    }
                    
                    printDisplayBoard();
                    cout << "\n🧠 " << currentTeam << ", guess agent #" << (i + 1) << ": \n";
                    cin >> agent;
                    transform(agent.begin(), agent.end(), agent.begin(), ::tolower);

                    while (!checkWordInBoard(agent)) {
                        cout << "🧠 Try again, " << currentTeam << " — choose a codename from the grid: \n";
                        cin >> agent;
                        transform(agent.begin(), agent.end(), agent.begin(), ::tolower);
                    }

                    cout << "\n\n🔎 You selected: \"" << agent << "\"\n\n";
                    
                    color = setBoard(agent);
                    if (setLive(color, turn, num)) { break; }
                    
                }

                currentTeamAgents = (turn % 2 == 0) ? blueAgents : redAgents;
                otherTeamAgents = (turn % 2 == 0) ? redAgents : blueAgents;
                
                 if (currentTeamAgents == 0) {
                    cout << "\n🎉 Victory for " << currentTeam << "! What a masterful job spotting all your agents!\n\n";
                    cout << "Better luck next time, " << otherTeam << ". You were so close, but the mission slips away...\n\n";
                    return;
                }
                if (otherTeamAgents == 0) {
                    cout << "\nBravo, " << otherTeam << "! You caught their mistake and used it to reveal the final agent. A brilliant decode — the mission is yours!\n\n";
                    cout << currentTeam << ", a single misstep exposed your operation — and the enemy capitalized. Their agents stayed hidden, yours... not so lucky. Regroup and decode smarter next time.\n\n";
                    return;
                }
                if (color == black) {
                    cout << "\n🧠 What a brilliant trap, " << otherTeam << "! You've proven to be the true master of this mind game. Well deserved victory!\n\n";;
                    cout << "\nNooo! " << currentTeam << ", the enemy set the perfect trap — and you took the bait.\n\n";
                    return;
                }
            }
        }

        // Check for game over
        bool setLive(string& color, int turn, int num) {
            if (color == red) {
                cout << ">> Red agent neutralized.\n";
                redAgents--;
            }
            if (color == blue) {
                cout << ">> Blue agent neutralized.\n";
                blueAgents--;
            }
            if (color == white) {
                cout << "-- Civilian encountered. No action taken.\n";
            }
            if (color == black) {
                cout << "!! Assassin found 🔥 Mission failed!\n";
                return true; 
            }
            cout << "Red agents remaining: " << redAgents << "\n";
            cout << "Blue agents remaining: " << blueAgents << "\n";
            if (redAgents == 0 || blueAgents == 0) { return true; }
            if (num == 0 && color == white) { return true; }
            if (color == blue && turn % 2 != 0 && num == 0) { return true; }
            if (color == red && turn % 2 == 0 && num == 0) { return true; }

            return false;
        }

        string setBoard(string codename) {
            int index;
            for (int i = 0; i < board.size(); i++) {
                string holder = board[i];
                transform(holder.begin(), holder.end(), holder.begin(), ::tolower);
                if (codename == holder) {
                    index = i;
                }
            }
            guessedword.push_back(codename);
            string color = keyCard[index];
            displayBoard[index] = color;
            return color;
        }

        bool checkClue(string clue) {
            for (int i = 0; i < board.size(); i++) {
                string holder = board[i];
                transform(holder.begin(), holder.end(), holder.begin(), ::tolower);
                if (clue == holder) {
                    cout << "Danger! Your clue is the same as a codename on the board. Try again, spy.\n";
                    return false;
                }
            }
            return true;
        }

        bool checkWordInBoard(string codename) {
            if (find(guessedword.begin(), guessedword.end(), codename) != guessedword.end()) {
                cout << "Agent \"" << codename << "\" has already been revealed. Pick another target.\n";
                return false;
            }
            for (int i = 0; i < board.size(); i++) {
                string holder = board[i];
                transform(holder.begin(), holder.end(), holder.begin(), ::tolower);
                if (codename == holder) {
                    return true;
                }
            }
            cout << "❌ \"" << codename << "\"? That agent's gone rogue or never existed!\n";
            return false;
        }

        void printBoard() {
            cout << "\n";
            for (int i = 0; i < board.size(); ++i) {
                cout << setw(18) << left << board[i];
                if ((i + 1) % 5 == 0) cout << endl << endl;
            }
        }

        void printKeyCard() {
            cout << "\n";
            for (int i = 0; i < keyCard.size(); ++i) {
                cout << setw(18) << left << keyCard[i];
                if ((i + 1) % 5 == 0) cout << endl << endl;
            }
        }

        void printDisplayBoard() {
            cout << "\n";
            for (int i = 0; i < displayBoard.size(); ++i) {
                cout << setw(18) << left << displayBoard[i];
                if ((i + 1) % 5 == 0) cout << endl << endl;
            }
        }
};

#endif