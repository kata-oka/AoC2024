#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <cmath>


int main() {
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

    

    sort(col1.begin(), col1.end());
    sort(col2.begin(), col2.end());

    int sum = 0;
    std::cout << "Total sum is = \n";
    for (int i = 0; i < col1.size(); i++) {
        sum = sum + std::abs(col1[i] - col2[i]);
    }
    std::cout << sum << " ";

    return 0;
}