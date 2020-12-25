#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
/***** Complete this program. *****/
using namespace std;
typedef int Door;

const int SIMULATION_COUNT = 100000;

void print_head();

void print_tail(int &win1, int &win2);

Door hideCar();

Door makeFirstChoice();

Door openDoor(Door car_here, Door first_choice);

Door makeSecondChoice(Door first_choice, Door opened_door);

void simulate(int i, int &win1, int &win2);

int main()
{
    srand(time(NULL));
    int win1 = 0, win2 = 0;

    print_head();

    for (int i = 1; i <= SIMULATION_COUNT; i++)
    {
        simulate(i, win1, win2);
    }
    print_tail(win1, win2);
    return 0;
}

void simulate(int i, int &win1, int &win2)
{
    Door car_here, first_choice, opened_door, second_choice;

    car_here = hideCar();
    first_choice = makeFirstChoice();
    opened_door = openDoor(car_here, first_choice);
    second_choice = makeSecondChoice(first_choice, opened_door);

    cout << i << setw(10)
         << car_here << setw(10)
         << first_choice << setw(10)
         << opened_door << setw(10)
         << second_choice;

    if (first_choice == car_here)
    {
        cout << setw(10) << "yes" << endl;
        win1++;
    }
    else if (second_choice == car_here)
    {
        cout << setw(20) << "yes" << endl;
        win2++;
    }
}

Door hideCar()
{
    Door hide_car;
    hide_car = 1 + (rand() % 3);
    return hide_car;
}

Door makeFirstChoice()
{
    Door first_choice_t;
    first_choice_t = 1 + (rand() % 3);
    return first_choice_t;
}

Door openDoor(Door car_here_t, Door first_choice_t)
{
    Door open_Door_temp;
    int flag = 0;
    do
    {
        open_Door_temp = 1 + (rand() % 3);
        if ((open_Door_temp != car_here_t) && (open_Door_temp != first_choice_t))
        {
            flag = 1;
        }
    } while (!flag);

    return open_Door_temp;
}

Door makeSecondChoice(Door first_choice_t, Door opened_door_t)
{
    Door open_Door2_temp;
    int flag = 0;
    do
    {
        open_Door2_temp = 1 + (rand() % 3);
        if ((open_Door2_temp != opened_door_t) && (open_Door2_temp != first_choice_t))
        {
            flag = 1;
        }
    } while (!flag);

    return open_Door2_temp;
}

void print_head()
{
    cout << "#" << setw(10)
         << "Car" << setw(10)
         << "First" << setw(10)
         << "Opened" << setw(10)
         << "Second" << setw(10)
         << "Win" << setw(10)
         << "Win" << endl;

    cout << setw(11)
         << "here" << setw(10)
         << "choice" << setw(10)
         << "door" << setw(10)
         << "choice" << setw(10)
         << "first" << setw(10)
         << "second" << endl;
}

void print_tail(int &win1, int &win2)
{
    double ratio = (double)(win2) / (win1);
    cout << win1
         << "wins if stay with the first choice"
         << endl
         << win2
         << "wins if switch to the second choice"
         << endl
         << "Win ratio of switch over stay: "
         << ratio
         << endl;
}