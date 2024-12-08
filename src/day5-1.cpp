#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> parse_input1()
{
    vector<pair<int, int>> data;
    ifstream inputFile("../input/day5_1_ex.txt");
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

    return data;
}

vector<vector<int>> parse_input2()
{
    vector<vector<int>> data;
    ifstream inputFile("../input/day5_2_ex.txt");
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

    return data;
}

/**
 * @brief Reorder rules into a new structure
 */
vector<pair<int, vector<int>>> reorder_rules(vector<pair<int, int>> rules)
{
    vector<pair<int, vector<int>>> prime_rules;

    for (size_t i = 0; i < rules.size(); ++i)
    {
        int first = rules[i].first;
        int second = rules[i].second;

        bool found = false;

        // Search in prime_rules if the ID already exists
        for (size_t j = 0; j < prime_rules.size(); ++j)
        {
            if (prime_rules[j].first == first)
            {
                prime_rules[j].second.push_back(second);
                found = true;
                break;
            }
        }

        // If the ID is not found, create a new entry in prime_rules
        if (!found)
        {
            vector<int> seconds = {second};
            prime_rules.push_back(make_pair(first, seconds));
        }
    }

    return prime_rules;
}

/**
 * Logic:
 * if id exists for line[i] in prime rules?
 *  - save prime_rules.second into rules
 *  - check if line[n] are in rules
 *  if all of the elements are ok, continue checking until the end of the line
 *      only return the line for calculation if the line has ben modified with bad_line as flag
 *      that means that if we get to the end with no bad_line, we just continue to the next line
 *  else {one if the elements is of line is not in the rules for the current id}
 *  - move the current id to the back and retry
 * else {id does not exist in prime_rules}
 *  - move the current id to the back of the line and retry
 */
static bool validate_line(vector<int> &line, const vector<pair<int, vector<int>>> &prime_rules)
{
    bool bad_line = false;
    size_t i = 0;
    while (i < line.size() - 1)
    {
        int id = line[i];
        bool found_id = false;
        vector<int> rules;

        /**
         * PART 1
         */

        // Search for the ID in prime_rules
        size_t j = 0;
        int ovf = 0;
        // If the ID is not found, the line is invalid, swap and retry
        while (!found_id)
        {
            while (j < prime_rules.size())
            {
                if (prime_rules[j].first == id)
                {
                    found_id = true;
                    rules = prime_rules[j].second; // Get the associated rules
                    // cout << "id found, saving rules" << endl;
                    break;
                }
                j++;
            }
            if (!found_id)
            {
                // As the line is modified, this one will be returned
                bad_line = true;
                // Move the current index one to the back of the line
                line.push_back(move(line[i]));
                line.erase(line.begin() + i);
                cout << "id not found, trying to find rules for id+1" << endl;
                ovf++;
            }
            if (ovf > line.size())
            {
                cerr << "the vector has overflowed" << endl;
                cerr << "avoiding infinite loop" << endl;
                break;
            }
        }

         /**
         * PART 2
         */
        // Check if the next element is in the rules
        int next_element = line[i + 1];
        
        if (find(rules.begin(), rules.end(), next_element) == rules.end())
        {
            // As the line is modified, this one will be returned
            bad_line = true;
            // Move the current index one to the back of the line
            line.push_back(std::move(line[i]));
            line.erase(line.begin() + i);
        }
        else {
            i++;
        }
    }

    // Return only if the line has been corrected
    return bad_line;
}

int main()
{
    vector<pair<int, int>> rules = parse_input1();
    vector<vector<int>> updates = parse_input2();
    vector<pair<int, vector<int>>> prime_rules = reorder_rules(rules);

    int sum = 0;

    for (size_t i = 0; i < updates.size(); ++i)
    {
        vector<int> line = updates[i];

        if (line.empty())
        {
            continue;
        }

        if (validate_line(line, prime_rules))
        {
            int middle_index = line.size() / 2;
            sum += line[middle_index];
        }
    }

    cout << "Total sum = " << sum << endl;

    return 0;
}
