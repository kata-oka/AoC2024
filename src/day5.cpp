#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> parse_input1()
{
    vector<pair<int, int>> data;
    ifstream inputFile("../input/day5_1.txt");
    if (!inputFile.is_open())
    {
        cerr << "Unable to open input file" << endl;
        return data;
    }

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string token;
        int p1, p2;

        if (getline(iss, token, '|'))
        {
            p1 = stoi(token);
        }
        if (getline(iss, token, '|'))
        {
            p2 = stoi(token);
        }

        data.emplace_back(p1, p2);
    }

    inputFile.close();

    // for (const auto& pair : data) {
    //     cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    // }

    return data;
}

vector<vector<int>> parse_input2()
{
    vector<vector<int>> data;
    ifstream inputFile("../input/day5_2.txt");
    if (!inputFile.is_open())
    {
        cerr << "Unable to open input file" << endl;
        return data;
    }

    string line;
    while (getline(inputFile, line))
    {
        vector<int> row;
        istringstream iss(line);
        string token;
        int p;

        while (getline(iss, token, ','))
        {
            p = stoi(token);
            row.push_back(p);
        }

        data.emplace_back(row);
    }

    inputFile.close();

    // for (const auto& row : data) {
    //     for (const auto& num : row) {
    //         cout << num << " ";
    //     }
    //     cout << endl;
    // }

    return data;
}

/**
 * @brief New rules vector where
 * First: The ID is the first on the rule
 * Second: A subvector of all seconds found for that first
 */
vector<pair<int, vector<int>>> reorder_rules(vector<pair<int, int>> rules)
{
    vector<pair<int, vector<int>>> prime_rules;
    for (const auto &rule : rules)
    {
        bool found = false;
        for (auto &prime : prime_rules)
        {
            if (rule.first == prime.first)
            {
                prime.second.push_back(rule.second);
                found = true;
                break;
            }
        }
        if (!found)
        {
            prime_rules.emplace_back(rule.first, vector<int>{rule.second});
        }
    }

    // for (const auto &prime : prime_rules)
    // {
    //     cout << "ID: " << prime.first << " -> [ ";
    //     for (const auto &second : prime.second)
    //     {
    //         cout << second << " ";
    //     }
    //     cout << "]" << endl;
    // }

    return prime_rules;
}

static bool validate_line(vector<int> &line, const vector<pair<int, vector<int>>> &prime_rules)
{
    for (size_t i = 0; i < line.size() - 1; ++i)
    {
        int id = line[i];

        // Search rules for this ID
        auto it = find_if(prime_rules.begin(), prime_rules.end(),
                          [id](const pair<int, vector<int>> &rule)
                          { return rule.first == id; });

        // If no rules, error
        if (it == prime_rules.end())
        {
            return false;
        }

        const vector<int> &rules = it->second;

        // Check if next element is in rules
        int next_element = line[i + 1];
        if (find(rules.begin(), rules.end(), next_element) == rules.end())
        {
            return false;  // False if next element is not in rules
        }
    }

    return true;
}

int main()
{
    vector<pair<int, int>> rules = parse_input1();

    vector<vector<int>> updates = parse_input2();

    vector<pair<int, vector<int>>> prime_rules = reorder_rules(rules);

    int sum = 0;
    // Runs the update list
    for (auto &line : updates)
    {
        if (line.empty())
            continue;

        if (validate_line(line, prime_rules))
        {
            int middle_index = line.size() / 2;
            sum += line[middle_index];
        }
    }

    cout << "Total sum = " << sum << endl;

    return 0;
}