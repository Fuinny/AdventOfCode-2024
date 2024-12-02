#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<int> GetNumbersInLine(string& line);
bool CheckReport(vector<int> levels);
bool CheckReportsWithDampener(vector<int> levels);

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
        if (CheckReport(reports[i])) {
            save_reports_count++;
        }
    }

    int fixed_save_reports_count = 0;
    for (int i = 0; i < reports.size(); i++) {
        if (CheckReportsWithDampener(reports[i])) {
            fixed_save_reports_count++;
        }
    }

    cout << "Safe reports (without problem dampener): " << save_reports_count << endl;
    cout << "Safe reports (with problem dampener): " << fixed_save_reports_count << endl;

    cout << "\nPress any key to exit...";
    cin.get();

    return 0;
}

// Extracts all numbers from a given line and returns them as a vector.
vector<int> GetNumbersInLine(string& line) {
    vector<int> numbers;
    istringstream stream(line);

    int current_number = 0;
    while (stream >> current_number) {
        numbers.push_back(current_number);
    }

    return numbers;
}

// Checks if a report is "safe" based on this criteria:
// 1. The values are strictly increasing or decreasing.
// 2. The difference between adjacent values is between 1 and 3 (inclusive).
bool CheckReport(vector<int> levels) {
    bool is_safe = true;

    // Check if levels are strictly increasing.
    for (int i = 0; i < levels.size() - 1; i++) {
        if (levels[i] > levels[i + 1]) {
            is_safe = false;
            break;
        }
    }

    // Check if levels are strictly decreasing if not increasing.
    if (!is_safe) {
        is_safe = true;
        for (int i = 0; i < levels.size() - 1; i++) {
            if (levels[i] < levels[i + 1]) {
                is_safe = false;
                break;
            }
        }
    }

    // Check if adjacent differences are within the allowed range.
    if (is_safe) {
        const int kMinDiffer = 1, kMaxDiffer = 3;
        for (int i = 0; i < levels.size() - 1; i++) {
            if ((abs(levels[i] - levels[i + 1]) < kMinDiffer) || (abs(levels[i] - levels[i + 1]) > kMaxDiffer)) {
                is_safe = false;
            }
        }
    }

    return is_safe;
}

// Checks if the report can be made "safe" by removing one level.
bool CheckReportsWithDampener(vector<int> levels) {
    for (int i = 0; i < levels.size(); i++) {
        int temp = levels[i];
        levels.erase(levels.begin() + i);

        if (CheckReport(levels)) {
            return true;
        }   

        levels.insert(levels.begin() + i, temp);
    }

    return false;
}
