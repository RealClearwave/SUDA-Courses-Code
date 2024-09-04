#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const pair<T1,T2> &pair) const {
        return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
    }
};

class GameOfLife {
private:
    vector<vector<int>> grid;
    int rows, cols;
    int stepCount;
    queue<pair<int, int>> updateQueue;
    unordered_set<pair<int, int>, pair_hash> cellsToCheck;

public:
    GameOfLife(int r, int c) : rows(r), cols(c), stepCount(0) {
        grid = vector<vector<int>>(rows, vector<int>(cols, 0));
    }

    void printGrid() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (grid[i][j] ? "X" : ".") << " ";
            }
            cout << endl;
        }
    }
    
    void addCellToQueue(int x, int y) {
        if (x < 0 || x >= rows || y < 0 || y >= cols) return;
        pair<int, int> cell = {x, y};
        if (cellsToCheck.find(cell) == cellsToCheck.end()) {
            updateQueue.push(cell);
            cellsToCheck.insert(cell);
        }
    }

    void update() {
        vector<vector<int>> nextGrid = grid;
        int qSize = updateQueue.size();
        for (int i = 0; i < qSize; ++i) {
            pair<int, int> cell = updateQueue.front();
            updateQueue.pop();
            cellsToCheck.erase(cell);
			for (int j = -1; j <= 1; ++j)
				for (int k = -1; k <= 1; ++k){
		            int x = cell.first + j;
		            int y = cell.second + k;
		            if (x < 0 || x >= rows) continue;
					if (y < 0 || y >= cols) continue;
					
		            int liveNeighbors = countLiveNeighbors(x, y);
		
		            if (grid[x][y] == 1) {
		                if (liveNeighbors < 2 || liveNeighbors > 3) { //Alive -> Dead
		                    nextGrid[x][y] = 0;
		                    addNeighborsToQueue(x, y);
		                }
		            } else {
		                if (liveNeighbors == 3) { //Dead -> Alive
		                    nextGrid[x][y] = 1;
		                    addNeighborsToQueue(x, y);
		                }
		            }
				}   
        }

        grid = nextGrid;
        ++stepCount;
        cout << "Step: " << stepCount << endl;
        printGrid();
    }

    void addNeighborsToQueue(int x, int y) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 || j != 0) {
                    addCellToQueue(x + i, y + j);
                }
            }
        }
    }

    int countLiveNeighbors(int x, int y) const {
        int liveCount = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int nx = x + i, ny = y + j;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                    liveCount += grid[nx][ny];
                }
            }
        }
        return liveCount;
    }

    void randomConfiguration() {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = rand() % 2;
                if (grid[i][j] == 1) {
                    addNeighborsToQueue(i, j);
                }
            }
        }
        stepCount = 0;
    }

    void saveConfiguration(const string &filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto &row : grid) {
                for (int cell : row) {
                    outFile << cell << " ";
                }
                outFile << "\n";
            }
            outFile.close();
            cout << "Configuration saved to " << filename << endl;
        } else {
            cerr << "Unable to open file for writing.\n";
        }
    }

    void loadConfiguration(const string &filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            int r = 0;
            while (getline(inFile, line) && r < rows) {
                istringstream ss(line);
                for (int c = 0; c < cols; ++c) {
                    ss >> grid[r][c];
                    if (grid[r][c] == 1) {
                        addNeighborsToQueue(r, c);
                    }
                }
                ++r;
            }
            inFile.close();
            cout << "Configuration loaded from " << filename << endl;
            stepCount = 0;
        } else {
            cerr << "Unable to open file for reading.\n";
        }
    }

    void showCredits() const {
        cout << "Game of Life implemented by Tianyu Wang 2362401031\n";
        cout << "Based on the original concept by John Conway.\n";
    }

    void runUntilConvergence() {
        unordered_set<string> previousStates;
        while (true) {
            string currentState = gridToString();
            if (previousStates.find(currentState) != previousStates.end()) {
                cout << "Game has converged to a stable state or a repeating cycle." << endl;
                break;
            }
            previousStates.insert(currentState);
            system("cls");
            update();
            if (updateQueue.empty()) {
                cout << "No more updates needed; the game is stable." << endl;
                break;
            }
        }
    }

    string gridToString() const {
        stringstream ss;
        for (const auto &row : grid) {
            for (int cell : row) {
                ss << cell;
            }
        }
        return ss.str();
    }
};

void Shell(GameOfLife &game) {
    string command;
    deque<string> commandHistory;
    cout << "Welcome to the Game of Life Shell!\n";
    cout << "Commands: print, update, random, run\nsave <filename>, load <filename>, credit, quit\n";
    while (true) {
        cout << ">>";
        getline(cin, command);

        if (command.empty() && !commandHistory.empty()) {
            command = commandHistory.back();
            cout << command << endl;
        }

        commandHistory.push_back(command);
        if (command == "print") {
            game.printGrid();
        } else if (command == "update") {
            game.update();
        } else if (command == "random") {
            game.randomConfiguration();
            game.printGrid();
        } else if (command.find("save") == 0) {
            string filename = command.substr(5);
            game.saveConfiguration(filename);
        } else if (command.find("load") == 0) {
            string filename = command.substr(5);
            game.loadConfiguration(filename);
        } else if (command == "credit") {
            game.showCredits();
        } else if (command == "run") {
            game.runUntilConvergence();
        } else if (command == "quit") {
            break;
        } else {
            cout << "Unknown command. Try again.\n";
        }
    }
}

int main() {
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of cols: ";
    cin >> cols;
    cin.ignore();

    GameOfLife game(rows, cols);
    Shell(game);

    return 0;
}
