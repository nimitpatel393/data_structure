#include <iostream>
#include <string>

using namespace std;

int main()
{
    string line("  A line of text.   ");

    cout << "|" << line << "|" << endl;

    cout << line.find_first_not_of(" ") << " "
         << line.find_last_not_of(" ") << endl;

    line.erase(0, line.find_first_not_of(" "));
    line.erase(line.find_last_not_of(" ") + 1);

    cout << "|" << line << "|" << endl;
    return 0;
}
