/**
 * War and Peace
 *
 * Search for the following names in the novel:
 *     Boris Drubetskoy
 *     Joseph Bazdeev
 *     Makar Alexeevich
 *
 * For each name, print its starting line number and position
 * and the name itself. A name can be split across two lines.
 * The first line is 1 and the first line position is 1.
 *
 * Author: Ron Mak
 *         Department of Computer Engineering
 *         San Jose State University
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Names to search for.
const string ALEXEEVICH  = "Makar Alexeevich";
const string BAZDEEV     = "Joseph Bazdeev";
const string DRUBETSKOY  = "Boris Drubetskoy";

// The full names are listed in alphabetical order.
const vector<string> FULL_NAMES = { ALEXEEVICH, BAZDEEV, DRUBETSKOY };

const string INPUT_FILE_NAME = "WarAndPeace.txt";

/**
 * Search the input file for the names.
 * @param input the input stream.
 * @param names the names.
 */
void search_file(ifstream& input, const vector<string>& names);

/**
 * Search each line of the input file for the names. A name can be split
 * across two lines. Print the line number and position of each found name.
 * If there are multiple names in a line, print them in alphabetical order.
 * @param input the input stream.
 * @param full_names the first and last names.
 * @param first_names the first names.
 * @param last_names the last names.
 * @param prev_line_indexes indexes of the first names on the previous line.
 */
void search_lines(ifstream& input, const vector<string>& full_names,
                  vector<string>& first_names, vector<string>& last_names,
                  vector<int>& prev_line_indexes);

/**
 * Split a full name into its first and last names.
 * @param name the full name.
 * @param first the first name.
 * @param last the last name.
 */
void split_name(const string& name, string& first, string& last);

/**
 * Print a name with the line number and position.
 * @param line_number the line number
 * @param position the position
 * @param name the name
 */
void print_name(const int line_number, const int position, const string& name);

/**
 * Remove any leading and trailing blanks from the line.
 * @param line the line.
 */
void trim(string& line);

/**
 * Main
 */
int main()
{
    ifstream input;

    input.open(INPUT_FILE_NAME);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    // Pass the FULL_NAMES array even though it's a global constant
    // to make it easier to change it to a non-global constant later.
    search_file(input, FULL_NAMES);

    return 0;
}

void search_file(ifstream& input, const vector<string>& names)
{
    // Maintain vectors first_names, last_names, and prev_line_indexes
    // in parallel: the ith entry of each vector is for the ith name.

    // To store first and last names split from the full names.
    vector<string> first_names, last_names;

    // To store the index of a first name on the previous line
    // if it was at the end of the line.
    vector<int> prev_line_indexes;

    // Loop over each name.
    for (string name : names)
    {
        // Split each name into its first name and last name.
        string first, last;
        split_name(name, first, last);
        first_names.push_back(first);
        last_names.push_back(last);

        // Initialize each corresponding previous line index to -1.
        prev_line_indexes.push_back(-1);
    }

    cout << " LINE  POSITION  NAME" << endl;
    search_lines(input, names, first_names, last_names, prev_line_indexes);
}

void search_lines(ifstream& input, const vector<string>& full_names,
                  vector<string>& first_names, vector<string>& last_names,
                  vector<int>& prev_line_indexes)
{
    string line;
    int line_number = 0;

    // Loop over each line of the input file.
    // Function getline() returns false if past the end of the file.
    while (getline(input, line))
    {
        // First trim the input line.
        trim(line);

        // Loop over each full name to search for it in the line.
        for (int i = 0; i < full_names.size(); i++)
        {
            string full_name = full_names.at(i);
            int index;

            // Was the first name at the end of the previous line?
            if (prev_line_indexes.at(i) > 0)
            {
                // Is the last name at the beginning of the current line?
                string last_name = last_names.at(i);
                index = line.find(last_name);

                // If yes, then print the name with the previous line number
                // and the starting position of the first name.
                if (index == 0)
                {
                    print_name(line_number-1, prev_line_indexes.at(i), full_name);
                }

                prev_line_indexes.at(i) = -1;
            }

            // Is the entire name in this line? If yes, print it.
            index = line.find(full_name);

            // Yes: Print it.
            if (index != string::npos)
            {
                print_name(line_number, index, full_name);
            }

            // No: Check if just the first name is at end of this line.
            else
            {
                string first_name = first_names.at(i);
                index = line.find(first_name);

                // Yes it is. Remember the starting index of the first name.
                if (   (index != string::npos)
                    && (index + first_name.length() >= line.length()))
                {
                    prev_line_indexes.at(i) = index;
                }
            }
        }

        line_number++;
    }
}

void split_name(const string& name, string& first, string& last)
{
    vector<string> parts;
    int space_pos = name.find(' ');  // position of the space

    first = name.substr(0, space_pos);                // first name
    last  = name.substr(space_pos+1, name.length());  // last name
}

void print_name(const int line_number, const int position, const string& name)
{
    // Add 1 because the first line is 1 and the first position is 1.
    cout << setw(5) << line_number+1 << setw(10) << position+1
         << "  " << name << endl;
}

void trim(string& line)
{
    // Remove leading blanks.
    line.erase(0, line.find_first_not_of(" "));

    // Remove trailing blanks.
    line.erase(line.find_last_not_of(" ") + 1);
}
