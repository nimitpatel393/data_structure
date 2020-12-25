/**
 * War and Peace (draft: no split names)
 *
 * Search for the following names in the novel:
 *     Boris Drubetskoy
 *     Joseph Bazdeev
 *     Makar Alexeevich
 *
 * For each name, print its starting line number and position and
 * the name itself. Does not check for names split across two lines.
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
 * @param names the names.
 */
void search_lines(ifstream& input, const vector<string>& names);

/**
 * Print a name with the line number and position.
 * @param line_number the line number
 * @param position the position
 * @param name the name
 */
void print_name(const int line_number, const int position, const string& name);

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
    cout << " LINE  POSITION  NAME" << endl;
    search_lines(input, names);
}

void search_lines(ifstream& input, const vector<string>& names)
{
    string line;
    int line_number = 0;

    // Loop over each line of the input file.
    while (getline(input, line))
    {
        // For each line, loop over each name.
        for (int i = 0; i < names.size(); i++)
        {
            string name = names.at(i);
            int index;

            // Is the entire name in this line? If yes, print it.
            index = line.find(name);

            // Yes: Print it.
            if (index != string::npos)
            {
                print_name(line_number, index, name);
            }
        }

        line_number++;
    }
}

void print_name(const int line_number, const int position, const string& name)
{
    // Add 1 because the first line is 1 and the first position is 1.
    cout << setw(5) << line_number+1 << setw(10) << position+1
         << "  " << name << endl;
}
