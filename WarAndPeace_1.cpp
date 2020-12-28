#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Names to search for.
const string ALEXEEVICH = "Makar Alexeevich";
const string BAZDEEV = "Joseph Bazdeev";
const string DRUBETSKOY = "Boris Drubetskoy";
vector<string> names(3);
const string book = "WarAndPeace.txt";
string myText;

void create_vector_string();
void find_word(string line, uint16_t line_counter);
void print_header();

int main()
{
  ifstream book_read;
  book_read.open(book);
  if (book_read.fail())
  {
    cout << "Failed to open " << book << endl;
    return -1;
  }

  /***** Complete this program. *****/
  print_header();
  create_vector_string();

  uint16_t line_counter;

  while (getline(book_read, myText))
  {
    line_counter++;
    // Output the text from the file
    //cout << "main" << myText << endl;
    find_word(myText, line_counter);
  }

  book_read.close();

  return 0;
}

void create_vector_string()
{
  names[0] = ALEXEEVICH;
  names[1] = BAZDEEV;
  names[2] = DRUBETSKOY;

  // cout << names[0] << endl
  //      << names[1] << endl
  //      << names[2] << endl;
}

void find_word(string myText_t, uint16_t line_counter_t)
{
  //cout << myText_t << line_counter_t << "find_word" << endl;
  for (uint8_t i = 0; i <= 2; i++)
  {
    size_t pos = myText_t.find(names[i]);
    if (pos != string::npos)

      cout << setw(5) << line_counter_t
           << setw(10) << pos+1
           << "  " << names[i] << endl;
  }
}

void print_header()
{
  cout << setw(5)
       << "LINE"
       << setw(10)
       << "POSITION"
       << setw(6)
       << "NAME"
       << endl;
}