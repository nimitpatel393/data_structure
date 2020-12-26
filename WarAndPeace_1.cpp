#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Names to search for.
const string ALEXEEVICH  = "Makar Alexeevich";
const string BAZDEEV     = "Joseph Bazdeev";
const string DRUBETSKOY  = "Boris Drubetskoy";

const string INPUT_FILE_NAME = "WarAndPeace.txt";

int main()
{
    ifstream input;
    input.open(INPUT_FILE_NAME);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    /***** Complete this program. *****/
}