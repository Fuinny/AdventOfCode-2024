#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int main() {
    ifstream file;
    string line;
    vector<string> corrupted_memory;

    file.open("Data.txt");
    int current_row = 0;
    while (!file.eof()) {
        while (getline(file, line)) {
            corrupted_memory.push_back(line);
        }
        current_row++;
    }
    file.close();

    // Regex pattern that matches "mul(x, y)" or "do()" or "don't()"
    regex valid_memory_pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    smatch match;

    int total_product = 0;
    for (int i = 0; i < corrupted_memory.size(); i++) {
        string::const_iterator search_start = corrupted_memory[i].cbegin();
        string::const_iterator search_end = corrupted_memory[i].cend();
        while (regex_search(search_start, search_end, match, valid_memory_pattern)) {
            // Only process "mul(x, y)" patterns.
            if (match[0] != "do()" && match[0] != "don't()") {
                int first_match = stoi(match[1].str());
                int second_match = stoi(match[2].str());

                total_product += first_match * second_match;
            }

            search_start = match.suffix().first;
        }
    }

    bool is_do_enabled = true;
    int total_product_with_conditions = 0;
    for (int i = 0; i < corrupted_memory.size(); i++) {
        string::const_iterator search_start = corrupted_memory[i].cbegin();
        string::const_iterator search_end = corrupted_memory[i].cend();
        while (regex_search(search_start, search_end, match, valid_memory_pattern)) {
            // Only process "mul(x, y)" patterns.
            if (is_do_enabled && (match[0] != "do()" && match[0] != "don't()")) {
                int first_match = stoi(match[1].str());
                int second_match = stoi(match[2].str());

                total_product_with_conditions += first_match * second_match;
            }

            if (match[0] == "do()") {
                is_do_enabled = true;
            }
            else if (match[0] == "don't()") {
                is_do_enabled = false;
            }

            search_start = match.suffix().first;
        }
    }

    cout << "Total product (without conditions): " << total_product << endl;
    cout << "Total product (with conditions): " << total_product_with_conditions << endl;


    cout << "\nPress any key to exit...";
    cin.get();

    return 0;
}
