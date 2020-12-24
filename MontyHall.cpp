#include <iostream>
#include <fstream>

/***** Complete this program. *****/

using namespace std;
typedef int Door;

const int SIMULATION_COUNT = 100;

void simulate( ... );

Door hideCar();

Door openDoor( ... );

Door makeFirstChoice();

Door makeSecondChoice( ... );

int main()
{
    int win1 = 0, win2 = 0;

    ...

    // Run the simulations.
    for (int i = 1; i <= SIMULATION_COUNT; i++) simulate(i, win1, win2);

    ...
}