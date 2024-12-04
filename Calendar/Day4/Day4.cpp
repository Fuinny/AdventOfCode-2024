#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string kWord = "XMAS";
const int kWordSize = 4;

bool CheckIfWordExists(const vector<string> text, const int current_row, const int current_col, const int row_amount, const int col_amount, int dx, int dy);
int FindWord(const vector<string> text);
bool CheckIfXWordExists(const vector<string> text, const int current_row, const int current_col, const int row_amount, const int col_amount);
int FindXWord(const vector<string> text);

int main() {
    ifstream file;
    string current_line;
    vector<string> text;

    file.open("Data.txt");
    while (getline(file, current_line)) {
        text.push_back(current_line);
    }
    file.close();

    cout << FindWord(text) << endl;
    cout << FindXWord(text) << endl;

    cout << "\nPress any key to exit...";
    cin.get();

    return 0;
}

bool CheckIfWordExists(const vector<string> text, const int current_row, const int current_col, const int row_amount, const int col_amount, int dx, int dy) {
    for (int i = 0; i < kWordSize; i++) {
        int new_row = current_row + i * dx;
        int new_col = current_col + i * dy;

        if (new_row < 0 || new_col < 0 || new_row >= row_amount || new_col >= col_amount || text[new_row][new_col] != kWord[i]) {
            return false;
        }
    }

    return true;
}

int FindWord(const vector<string> text) {
    const int r = text.size();
    const int c = text[0].size(); // Since all strings are the same length.

    int word_count = 0;

    // All 8 possible directions.
    vector<pair<int, int>> directions = {
        {0, 1}, {1, 0}, {1, 1}, {-1, -1},
        {0, -1}, {-1, 0}, {1, -1}, {-1, 1}
    };

    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            if (text[row][col] == 'X') {
                for (auto [dx, dy] : directions) {
                    if (CheckIfWordExists(text, row, col, r, c, dx, dy)) {
                        cout << "Match at (" << row << ", " << col << ") in direction (" << dx << ", " << dy << ")\n";
                        word_count++;
                    }
                }
            }
        }
    }

    return word_count;
}

bool CheckIfXWordExists(const vector<string> text, const int current_row, const int current_col, const int row_amount, const int col_amount) {
    // All 4 possible diagonals.
    vector<pair<int, int>> directions = {
        {1, 1}, {-1, -1},{1, -1}, {-1, 1}
    };

    int m_count = 0, s_count = 0;
    vector<pair<int, int>> m_positions, s_positions;

    for (auto [dx, dy] : directions) {
        int new_row = current_row + dx;
        int new_col = current_col + dy;

        if (new_row < 0 || new_col < 0 || new_row >= row_amount || new_col >= col_amount || (text[new_row][new_col] != 'M' && text[new_row][new_col] != 'S')) {
            return false;
        }

        if (text[new_row][new_col] == 'M') {
            m_positions.push_back({ new_row, new_col });
            m_count++;
        }
            
        if (text[new_row][new_col] == 'S') {
            s_positions.push_back({ new_row, new_col });
            s_count++;
        }
            
    }

    if (m_count == 2 && s_count == 2) {
        // Check if 'M' positions are on the same row or column.
        bool m_same_row = m_positions[0].first == m_positions[1].first;
        bool m_same_col = m_positions[0].second == m_positions[1].second;

        // Check if 'S' positions are on the same row or column.
        bool s_same_row = s_positions[0].first == s_positions[1].first;
        bool s_same_col = s_positions[0].second == s_positions[1].second;

        return (m_same_row || m_same_col) && (s_same_row || s_same_col);
    }
        return false;
    }

int FindXWord(const vector<string> text) {
    const int r = text.size();
    const int c = text[0].size(); // Since all strings are the same length.

    int word_count = 0;

    for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
            if (text[row][col] == 'A') {
                if (CheckIfXWordExists(text, row, col, r, c)) {
                    word_count++;
                }
            }
        }
    }

    return word_count;
}
