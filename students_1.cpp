#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

void delete_arrays(string *names, int **scores, int count);
void extractor(string each_line, string *names, int **scores, int count);
void score_dump(string numbers, int **scores, int count);
void print(string *names, int **scores, int count);

const string student_file_name = "students.txt";
uint8_t extract_student_number(string first_line);

bool first_line_flag = 1;
int count;

int main()
{
    ifstream student_input_stream;
    student_input_stream.open(student_file_name);
    if (student_input_stream.fail())
    {
        cout << "Failed to open " << student_file_name << endl;
        return -1;
    }

    /***** Complete this program. *****/
    string temp;

    getline(student_input_stream, temp);

    uint8_t student_count = extract_student_number(temp);

    string *names = new string[student_count];
    int **scores = new int *[student_count];

    //cout << *names << *scores << endl;

    while (getline(student_input_stream, temp))
    {
        extractor(temp, names, scores, count);
        count++;
    }
    print(names, scores, student_count);
    delete_arrays(names, scores, student_count);
    return 0;
}

uint8_t extract_student_number(string first_line)
{
    string student_num = first_line.substr(4, string::npos);
    //cout << student_num << endl;
    uint8_t temp_student = stoi(student_num, nullptr, 10);
    first_line_flag = 0;

    return temp_student;
}

void delete_arrays(string *names, int **scores, int count)
{
    for (int i = 0; i < count; i++)
    {
        //cout << names[i] << scores[i][1] << endl;
        delete[] scores[i];
    }
    delete[] names;
    delete[] scores;
}

void extractor(string each_line, string *names, int **scores, int count)
{
    string space = " ", name, numbers;
    int pos = each_line.find(space), counter = 0;
    //cout<<"Here"<<pos<<endl;

    do
    {
        // cout << pos << endl;
        pos = each_line.find(space, pos + 1);
        counter++;
        if (counter == 1)
        {
            name = each_line.substr(0, pos);
            numbers = each_line.substr(pos + 1);
            names[count] = name;
            //cout<<name<<endl<<numbers<<endl;
        }
    } while (pos != string::npos);
    score_dump(numbers, scores, count);
    //counter=0;
}

void score_dump(string numbers, int **scores, int count)
{
    //cout<<numbers<<endl;
    string space = " ", temp;
    int iteration, o_pos, size, pos = numbers.find(space);

    temp = numbers.substr(0, pos);
    iteration = stoi(temp, nullptr, 10);
    scores[count] = new int[iteration];
    //  numbers = numbers.substr(2);
    //pos = numbers.find(space);

    //cout << iteration << endl;
    for (int i = 0; i < iteration + 1; i++)
    {
        //cout << numbers << endl;
        if (pos != string::npos)
        {
            o_pos = pos;
            pos = numbers.find(space, pos + 1);
            temp = numbers.substr(o_pos, pos - o_pos);
            //cout << temp << endl;
            scores[count][i] = stoi(temp);
            // cout << scores[count][i] << "index " << count << i << endl;
        }
    }
}

void print(string *names, int **scores, int count)
{
    cout << "STUDENT SCORES for C++" << endl
         << endl;
    for (int i = 0; i < count; i++)
    {
        int ii = 0;
        cout << names[i] << endl;
        if (scores[i][ii] == 0)
            cout << "(none)";
        while (scores[i][ii] != 0)
        {
            cout << scores[i][ii] << " ";
            ii++;
        }
        cout << endl
             << endl;
    }
}