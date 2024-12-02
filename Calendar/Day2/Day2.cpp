#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> GetNumbersInLine(string& line);
bool CheckReport(vector<int> levels);
bool FixAndCheckReport(vector<int> levels);

int main() {
    ifstream file;
    vector<vector<int>> reports;

    file.open("Data.txt");
    string line;
    int current_line_number = 0;
    while (getline(file, line)) {
        reports.push_back(GetNumbersInLine(line));
        current_line_number++;
    }
    file.close();

    int save_reports_count = 0;
    for (int i = 0; i < reports.size(); i++) {
        if (CheckReport(reports[i]))
            save_reports_count++;
    }
    int fixed_save_reports_count = 0;
    for (int i = 0; i < reports.size(); i++) {
        if (FixAndCheckReport(reports[i]))
            fixed_save_reports_count++;
    }

    cout << "Save without removing any level: " << save_reports_count << endl;
    cout << "Save with removing level: " << fixed_save_reports_count << endl;

    cout << "\nPress any key to exit...";
    cin.get();

    return 0;
}

vector<int> GetNumbersInLine(string& line) {
    vector<int> numbers;
    istringstream stream(line);
    int current_number = 0;
    while (stream >> current_number) {
        numbers.push_back(current_number);
    }
    return numbers;
}

bool CheckReport(vector<int> levels) {
    bool is_save = true;

    // Check for increasing.
    for (int i = 0; i < levels.size() - 1; i++) {
        if (levels[i] > levels[i + 1]) {
            is_save = false;
            break;
        }
    }

    // Check for decreasing.
    if (!is_save) {
        is_save = true;
        for (int i = 0; i < levels.size() - 1; i++) {
            if (levels[i] < levels[i + 1]) {
                is_save = false;
                break;
            }
        }
    }

    // Check if the difference between two numbers is within the range [1, 3]
    if (is_save) {
        const int kMinDiffer = 1, kMaxDiffer = 3;
        for (int i = 0; i < levels.size() - 1; i++) {
            if ((abs(levels[i] - levels[i + 1]) < kMinDiffer) || (abs(levels[i] - levels[i + 1]) > kMaxDiffer))
                is_save = false;
        }
    }
    return is_save;
}

bool FixAndCheckReport(vector<int> levels) {
    bool is_save = false;
    for (int i = 0; i < levels.size(); i++) {
        int temp = levels[i];
        levels.erase(levels.begin() + i);

        is_save = true;

        // Check for increasing.
        for (int i = 0; i < levels.size() - 1; i++) {
            if (levels[i] > levels[i + 1]) {
                is_save = false;
                break;
            }
        }

        // Check for decreasing.
        if (!is_save) {
            is_save = true;
            for (int i = 0; i < levels.size() - 1; i++) {
                if (levels[i] < levels[i + 1]) {
                    is_save = false;
                    break;
                }
            }
        }

        // Check if the difference between two numbers is within the range [1, 3].
        if (is_save) {
            const int kMinDiffer = 1, kMaxDiffer = 3;
            for (int i = 0; i < levels.size() - 1; i++) {
                if ((abs(levels[i] - levels[i + 1]) < kMinDiffer) || (abs(levels[i] - levels[i + 1]) > kMaxDiffer))
                    is_save = false;
            }
        }

        if (is_save)
            return is_save;

        levels.insert(levels.begin() + i, temp);
    }

    return is_save;
}
