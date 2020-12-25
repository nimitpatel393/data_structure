/**
 * Assignment 2. Monty Hall Problem
 *
 * Simulate the Monty Hall probability problem.
 * Are you better off making a second door choice or
 * staying with your first door choice to win the car?
 * See https://en.wikipedia.org/wiki/Monty_Hall_problem
 *
 * Author: Ron Mak
 *         Department of Computer Science
 *         San Jose State University
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

//#define NDEBUG
#include <cassert>

using namespace std;
typedef int Door;

const int SIMULATION_COUNT = 100;

/**
 * Run a simulation.
 * @param sequence the sequence number.
 * @param win1 number of first choice wins.
 * @param win2 number of second choice wins.
 */
void simulate(int sequence, int& win1, int& win2);

/**
 * Hide the car behind a door.
 * @return the door that the car is hidden behind.
 */
Door hide_car();

/**
 * @return the player's first door choice, which is either 1, 2, or 3.
 */
Door make_first_choice();

/**
 * Open a door that is not:
 * @param first_choice_door the player's first door choice.
 * @param car_behind_door the door that the car is hidden behind.
 * @return the door to open.
 */
Door open_door(Door first_choice_door, Door car_behind_door);

/**
 * Return the player's second door choice, which cannot be:
 * @param first_door the player's first choice door.
 * @param opened_door the opened door.
 * @return the second door choice.
 */
Door make_second_choice(Door first_door, Door opened_door);

/**
 * @return a random door 1, 2, or 3.
 */
Door random_door();

/**
 * Return a random door 1, 2, or 3 that is not:
 * @param a_door a door.
 * @param another_door another door, which can be equal to a_door.
 * @return the random door.
 */
Door random_door_not(Door a_door, Door another_door);

/**
 * Choose door 1, 2, or 3 that is not:
 * @param first_door the player's first door choice.
 * @param opened_door the opened door.
 * @return the remaining door.
 */
Door choose_remaining_door(Door first_door, Door opened_door);

/**
 * Main
 */
int main()
{
    int win1 = 0, win2 = 0;

    cout << "   #     Car   First  Opened  Second    Win    Win" << endl;
    cout << "        here  choice    door  choice  first second" << endl;
    cout << endl;

    srand(time(NULL));  // seed the random number generator

    // Run the simulations.
    for (int i = 1; i <= SIMULATION_COUNT; i++) simulate(i, win1, win2);

    cout << endl;
    cout << setw(4) << win1 << " wins if stay with the first choice" << endl;
    cout << setw(4) << win2 << " wins if switch to the second choice" << endl;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);

    cout << endl;
    cout << "Win ratio of switch over stay: ";
    cout << static_cast<double>(win2)/win1 << endl;
}

void simulate(int sequence, int& win1, int& win2)
{
    // Perform a simulation.
    Door car_behind_door    = hide_car();
    Door first_choice_door  = make_first_choice();
    Door opened_door        = open_door(first_choice_door,
                                        car_behind_door);
    Door second_choice_door = make_second_choice(first_choice_door,
                                                 opened_door);

    // Print the results.
    cout << setw(4) << sequence << setw(8) << car_behind_door;
    cout << setw(8) << first_choice_door << setw(8) << opened_door;
    cout << setw(8) << second_choice_door;

    if (first_choice_door == car_behind_door)
    {
        cout << "    yes";  // the car was behind the first door choice
        win1++;
    }
    else
    {
        cout << "           yes";  // it was behind the second door choice
        win2++;
    }

    cout << endl;
}

Door hide_car()
{
    // The simulation randomly chooses the door to hide the car.
    return random_door();
}

Door make_first_choice()
{
    // The simulation randomly makes the player's first door choice.
    return random_door();
}

Door open_door(Door first_choice_door, Door car_behind_door)
{
    // Monty Hall knows which door the car is behind
    // and so he opens a door that has a goat behind it.
    Door opened_door = random_door_not(first_choice_door, car_behind_door);

    assert(   (opened_door != first_choice_door)
           && (opened_door != car_behind_door));
    return opened_door;
}

Door make_second_choice(Door first_door, Door opened_door)
{
    // The player's second door choice can't be
    // the first door choice or the opened door.
    Door second_choice = choose_remaining_door(first_door, opened_door);

    assert(   (second_choice != first_door)
           && (second_choice != opened_door));
    return second_choice;
}

Door random_door()
{
    return rand()%3 + 1;
}

Door random_door_not(Door a_door, Door another_door)
{
    Door door;

    // If doors a_door and another_door are the same, then randomly
    // choose between the other two doors to return.
    // Otherwise, return the third door.
    do {
        door = random_door();
    } while ((door == a_door) || (door == another_door));

    return door;
}

Door choose_remaining_door(Door first_door, Door opened_door)
{
    // Check door 1 and door 2.
    for (Door door = 1; door <= 2; door++)
    {
        if ((door != first_door) && (door != opened_door)) return door;
    }

    return 3;  // if not door 1 or door 2
}
