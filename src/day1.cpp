#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <cmath>


int main() {

    /**
     * Parse input
     */
    std::vector<int> col1;
    std::vector<int> col2;


    std::ifstream inputFile("../input/day1.txt"); 
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int num1, num2;

        if (iss >> num1 >> num2) {
            col1.push_back(num1);
            col2.push_back(num2);
        }
    }

    inputFile.close();

    /**
     * Start puzzle
     */

    sort(col1.begin(), col1.end());
    sort(col2.begin(), col2.end());

    //Define iterators
    auto it1 = col1.begin();
    auto it2 = col2.begin();

    int ret = 0;

    std::cout << "Total score is = ";
    for (int i = 0; i < col1.size(); i++) {
        int frec = 0;
        frec = count(col2.begin(), col2.end(), col1[i]);
        ret = ret + (col1[i] * frec);
    }
    std::cout << ret << " \n";

    return 0;
}