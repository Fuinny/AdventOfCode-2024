#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void BubbleSort(int* array);

const int kTotalAmountOfData = 1000;

int main() {
    ifstream file;
    int total_distance = 0, total_similarity = 0;
    int leftList[1000], rightList[1000], distanceList[1000], similarityList[1000];

    file.open("Data.txt");
    int current_element = 0;
    while (!file.eof()) {
        file >> leftList[current_element];
        file >> rightList[current_element];
        current_element++;
    }
    file.close();

    BubbleSort(leftList);
    BubbleSort(rightList);

    for (int i = 0; i < kTotalAmountOfData; i++) {
        similarityList[i] = 0;
        int current_number = leftList[i];
        for (int j = 0; j < kTotalAmountOfData; j++) {
            if (current_number == rightList[j]) {
                similarityList[i] += 1;
            }
        }
    }

    for (int i = 0; i < kTotalAmountOfData; i++) {
        distanceList[i] = abs(leftList[i] - rightList[i]);
        similarityList[i] = leftList[i] * similarityList[i];
    }

    for (int i = 0; i < kTotalAmountOfData; i++) {
        total_distance += distanceList[i];
        total_similarity += similarityList[i];
    }

    cout << "Total distance: " << total_distance << endl;
    cout << "Total similarity: " << total_similarity << endl;

    cout << "\nPress any key to exit...";
    cin.get();

    return 0;
}

void BubbleSort(int* array) {
    for (int i = 0; i < kTotalAmountOfData; i++) {
        for (int j = 0; j < kTotalAmountOfData - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
