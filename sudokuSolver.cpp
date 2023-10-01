#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>

using namespace std;
auto start = chrono::steady_clock::now();

vector<int> getPossibleValues(int row, int column, vector<vector<int>> &sudoku);
vector<int> getRowValues(int row, vector<vector<int>> &sudoku);
vector<int> getColumnValues(int column, vector<vector<int>> &sudoku);
vector<int> getGridValues(int row, int column, vector<vector<int>> &sudoku);
bool solve(vector<vector<int>> sudoku);

int main() {

    vector <vector<int>> sudoku {
        {0,0,1,2,0,0,0,0,0},
        {0,6,4,3,0,0,0,0,2},
        {0,0,0,0,0,9,0,3,0},
        {9,0,0,0,0,0,0,0,5},
        {1,0,0,6,0,0,0,0,0},
        {0,5,6,0,0,7,4,0,0},
        {0,2,3,9,0,0,0,0,4},
        {5,0,0,0,0,0,0,0,0},
        {0,0,0,0,8,0,7,0,0},
    };

    solve(sudoku);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    return 0;
}

vector<int> getGridValues(int row, int column, vector<vector<int>> &sudoku) {
    vector<int> gridValues;
    int starting_row = (row / 3)*3;
    int ending_row = ((row / 3) + 1)*3;
    int starting_column = (column / 3)*3;
    int ending_column = ((column / 3) + 1)*3;

    for (int i = starting_row; i < ending_row; ++i) {
        for (int j = starting_column; j < ending_column; ++j) {
            gridValues.push_back(sudoku[i][j]);
        }
    }

    return gridValues;
}

vector<int> getRowValues(int row, vector<vector<int>> &sudoku) {
    vector<int> rowValues;

    for (int v: sudoku[row]) {
        rowValues.push_back(v);
    }
    
    return rowValues;
}

vector<int> getColumnValues(int column, vector<vector<int>> &sudoku) {
    vector<int> columnValues;
    for (int row=0; row < 9; ++row) {
        columnValues.push_back(sudoku[row][column]);
    }

    return columnValues;
}

vector<int> getPossibleValues(int row, int column, vector<vector<int>> &sudoku) {

    vector<int> rowValues = getRowValues(row, sudoku);
    vector<int> columnValues = getColumnValues(column, sudoku);
    vector<int> gridValues = getGridValues(row, column, sudoku);

    vector<int> possV {1,2,3,4,5,6,7,8,9};

    for (auto v: rowValues) {
        std::vector<int>::iterator index = find(possV.begin(), possV.end(), v);
        if (index != possV.end()) {
            possV.erase(index);
        }
    }

    for (auto v: columnValues) {
        std::vector<int>::iterator index = find(possV.begin(), possV.end(), v);
        if (index != possV.end()) {
            possV.erase(index);
        }
    }

    for (auto v: gridValues) {
        std::vector<int>::iterator index = find(possV.begin(), possV.end(), v);
        if (index != possV.end()) {
            possV.erase(index);
        }
    }

    return possV;

}

bool solve(vector<vector<int>> sudoku_copy) {
    static bool flag = false;
    for (int i=0; i<9; ++i) {
        for (int j=0; j<9; ++j) {
            if (sudoku_copy[i][j] != 0)
                continue;

            vector<int> possV = getPossibleValues(i, j, sudoku_copy);
            for (auto possible_value: possV) {
                sudoku_copy[i][j] = possible_value;
                if (solve(sudoku_copy)) {
                    return true;
                };
            }
            return false;
        }
    }
    for (auto ii: sudoku_copy) {
        for (auto jj: ii) {
            cout << jj << " ";
        }
        cout << endl;
    }
    return true;
}

