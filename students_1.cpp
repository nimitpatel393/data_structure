/**
 * Assignment 4. Student scores
 * Spring 2020
 *
 * Build dynamic arrays to store student names and scores
 * read from an input file. Access the arrays to print the
 * student names and scores.
 *
 * Author: Ron Mak
 *         Department of Computer Engineering
 *         San Jose State University
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const string INPUT_FILE_NAME = "students.txt";

typedef string   *NamePtr;   // -> a student name
typedef string   *NameArray; // -> dynamic array of student names
typedef int      *ScorePtr;  // -> a score
typedef int      *ScoreRow;  // -> dynamic array (row) of student scores
typedef ScoreRow *RowArray;  // -> dynamic array of pointers to score rows
typedef ScoreRow *RowPtr;    // -> a pointer to a score row

/**
 * Read the course name and the count of students.
 * Create dynamic arrays for the student names and scores.
 * @param input the input file stream.
 * @param course the course name.
 * @param names the dynamic array of names.
 * @param rows the dynamic array of pointers to the rows of scores.
 * @return the count of students.
 */
int create_dynamic_arrays(ifstream& input, string& course,
                          NameArray& names, RowArray& rows);

/**
 * Fill the dynamic array of student names and the
 * dynamic array of pointers to the score rows.
 * @param input the input stream.
 * @param student_count the count of students.
 * @param names the dynamic array of student names.
 * @param names the dynamic array of pointers to the score rows.
 */
void fill_dynamic_arrays(ifstream& input, int student_count,
                         const NameArray names, const RowArray rows);

/**
 * Read a student's assignment scores and fill
 * the dynamic integer array (row) of the scores.
 * @param input the input stream.
 * @param score_count the count of scores for this student.
 * @param row_ptr the pointer to the score row.
 */
void fill_score_row(ifstream& input, int score_count, const RowPtr row_ptr);

/**
 * Print the scores for each student in the course.
 * @param course the name of the course.
 * @param names the dynamic array of student names.
 * @param rows the dynamic array of pointers to the scores rows.
 */
void print_student_scores(const string course, int student_count,
                          const NameArray names, const RowArray rows);

/**
 * Deallocate the dynamic arrays.
 * @param student_count the count of students.
 * @param names the dynamic array of student names.
 * @param rows the dynamic array of pointers to the scores rows.
 */
void delete_dynamic_arrays(int student_count, NameArray names, RowArray rows);

/**
 * Main.
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

    string course;
    NameArray names = nullptr;  // -> array of student names
    RowArray  rows  = nullptr;  // -> array of pointers to the
                                //    rows of student scores

    int student_count = create_dynamic_arrays(input, course, names, rows);
    print_student_scores(course, student_count, names, rows);
    delete_dynamic_arrays(student_count, names, rows);

    return 0;
}

int create_dynamic_arrays(ifstream& input, string& course,
                          NameArray& names, RowArray& rows)
{
    int student_count;

    // Read the course name and student count.
    // Create the dynamic array of student names and the
    // dynamic array of pointers to the rows of student scores.
    input >> course >> student_count;
    names = new string[student_count];
    rows  = new ScoreRow[student_count];

    // Create the dynamic array of pointers
    // to the rows of student scores.
    fill_dynamic_arrays(input, student_count, names, rows);

    return student_count;
}

void fill_dynamic_arrays(ifstream& input, int student_count,
                         const NameArray names, const RowArray rows)
{
    int score_count;
    string first_name, last_name;
    NamePtr name_ptr = names;  // -> first name of the names array
    RowPtr  row_ptr  = rows;   // -> first pointer to the score rows

    // Loop once per student.
    while (student_count > 0)
    {
        // Read a student name and the number of assignments.
        // Use name_ptr to enter the name into the name array.
        input >> first_name >> last_name >> score_count;
        *name_ptr = first_name + " " + last_name;

        // Create a dynamic integer array as a row of student scores.
        // Make it one larger for the -1 sentinel at the end. Fill the array.
        *row_ptr = new int[score_count + 1];
        fill_score_row(input, score_count, row_ptr);

        name_ptr++;       // -> next element of the name array
        row_ptr++;        // -> next element of the row array
        student_count--;  // decrement the copy of the student count
    }
}

void fill_score_row(ifstream& input, int score_count, const RowPtr row_ptr)
{
    ScorePtr score_ptr = *row_ptr;  // -> first score of the row

    // Loop once per assignment score of the student.
    while (score_count > 0)
    {
        input >> *score_ptr;  // read the next score into the score row
        score_ptr++;          // -> next score of the row
        score_count--;        // decrement the copy of the score count
    }

    *score_ptr = -1;  // sentinel to mark the end of this score row
}

void print_student_scores(const string course, int student_count,
                          const NameArray names, const RowArray rows)
{
    NamePtr name_ptr = names;  // -> first name of student names
    RowPtr  row_ptr  = rows;   // -> first pointer to the score rows

    cout << "STUDENT SCORES for " << course << endl;

    // Loop once per row of student scores.
    while (student_count > 0)
    {
        cout << endl;
        cout << *name_ptr << endl;  // print the student's name

        int *score_ptr = *row_ptr;  // -> first score of the row

        // No scores?
        if (*score_ptr < 0)
        {
            cout << "   (none)";
        }

        // Else loop to print each score in the row.
        // Stop at the -1 sentinel.
        else while (*score_ptr >= 0)
        {
            cout << setw(5) << *score_ptr;
            score_ptr++;  // -> next score of the row
        }
        cout << endl;

        name_ptr++;       // -> next name in the name array
        row_ptr++;        // -> next pointer to a score row
        student_count--;  // decrement the copy of the student count
    }
}

void delete_dynamic_arrays(int student_count, NameArray names, RowArray rows)
{
    RowPtr row_ptr = rows;  // -> the first row pointer

    // Loop once per row of student scores.
    while (student_count > 0)
    {
        delete [] *row_ptr;  // delete the row of scores

        row_ptr++;           // -> next pointer to a score row
        student_count--;     // decrement the copy of the student count
    }

    delete [] rows;   // delete the array of row pointers
    delete [] names;  // delete the array of names
}
