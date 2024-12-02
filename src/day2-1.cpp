#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool comp(int a, int b) { return a > b; }

int main() {

  /**
   * Parse input
   */
  std::vector<std::vector<int>> lines;

  std::ifstream inputFile("../input/day2.txt");
  if (!inputFile.is_open()) {
    std::cerr << "Unable to open input file" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::vector<int> numbers;
    int num;

    while (iss >> num) {
      numbers.push_back(num);
    }

    lines.push_back(numbers);
  }
  inputFile.close();

  /**
   * Start puzzle
   */
  int count = 0;

  for (int i = 0; i < lines.size(); i++) {
    bool p_damp = true;
    bool safe = true;
    bool TendsUp = true;
    bool TendFixed = false;

    for (int j = 0; j < lines[i].size() - 1; j++) {
      int a = lines[i][j];
      int b = lines[i][j + 1];
      int diff = std::abs(a - b);

      if (!TendFixed){
        (a < b ) ? TendsUp = true : TendsUp = false;
        TendFixed = true;
      }

      std::cout << a << " ";

      if (diff < 1 || diff > 3) {
        if (p_damp) {
          continue;
        }
      } else {
        safe = false;
        std::cout << b << " ";
        std::cout << "ERROR ";
        break;
      }
    }
    if (safe) {
      std::cout << " OK ";
      count++;
    }
    std::cout << "\n";
  }

  std::cout << "Number of safe reports = ";
  std::cout << count << " \n";

  return 0;
}
