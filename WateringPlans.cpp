/**
 * Assignment 1. Watering Plans
 *
 * A simple simulation with control statements and nested loops.
 *
 * CS 144 Advanced C++ Programming
 * Spring 2019
 *
 * Author: Ron Mak
 *         Department of Computer Science
 *         San Jose State University
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    const int UNITS_PER_CAN = 3;

    int plant_count;            // count of plants
    int plant_number;           // plant #1, #2, #3, ...
    int unwatered_count;        // count of unwatered plants
    int water_amount;           // amount of water in the watering can
    int steps;                  // number of steps taken
    int cum_steps;              // cumulative number of steps taken for a plan
    int cum_step_units_near;    // cumulative step-units for Plan Near
    int cum_step_units_far;     // cumulative step-units for Plan Far
    bool trip_done;             // true if a trip is done

    const string INPUT_FILE_NAME = "counts.txt";

    ifstream input;
    input.open(INPUT_FILE_NAME);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    // Loop once for each number of plants read from the input file.
    // Stop when the number of plants is 0 or less.
    // During each loop, simulate Plan Near and Plan Far.
    do
    {
        input >> plant_count;
        if (plant_count <= 0) return 0;

        // Plan Near

        cout << endl;
        cout << "==========================" << endl;
        cout << " Plan Near with " << plant_count << " plants" << endl;
        cout << "==========================" << endl;
        cout << endl;
        cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
        cout << "---------  ----------  ----------  ---------------" << endl;

        unwatered_count = plant_count;
        cum_steps = 0;
        cum_step_units_near = 0;

        // Loop once per trip from the faucet until all the plants are watered.
        // During each loop, fill the can, water plants according to plan,
        // and return to the faucet.
        while (unwatered_count > 0)
        {
            // Fill the can.
            water_amount = UNITS_PER_CAN;

            // Walk to the nearest unwatered plant with a full can.
            plant_number = plant_count - unwatered_count + 1;
            steps = plant_number;
            cum_steps += steps;
            cum_step_units_near += steps*water_amount;

            // Water plants while walking away from the faucet.
            // Loop once per plant until either the can is empty
            // or all the plants have been watered.
            // During each loop, water one plant.
            do
            {
                cout << "Plant " << setw(2) << plant_number
                     << setw(9)  << cum_steps
                     << setw(11) << water_amount
                     << setw(16) << cum_step_units_near << endl;

                water_amount--;
                unwatered_count--;
                trip_done = (water_amount == 0) || (unwatered_count == 0);

                if (!trip_done)
                {
                    // Walk away from the faucet to the next unwatered plant.
                    plant_number++;

                    cum_steps++;
                    cum_step_units_near += water_amount;
                }
            } while (!trip_done);

            // Walk back to the faucet with an empty or partially filled can.
            steps = plant_number;
            cum_steps += steps;
            cum_step_units_near += steps*water_amount;

            cout << "FAUCET "
                 << setw(10) << cum_steps
                 << setw(11) << water_amount
                 << setw(16) << cum_step_units_near << endl;
        }

        cout << endl;
        cout << "Plan Near: Total steps = " << cum_steps
             << ", total step-units = " << cum_step_units_near << endl;

        // Plan Far

        cout << endl;
        cout << "=========================" << endl;
        cout << " Plan Far with " << plant_count << " plants" << endl;
        cout << "=========================" << endl;
        cout << endl;
        cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
        cout << "---------  ----------  ----------  ---------------" << endl;

        unwatered_count = plant_count;
        cum_steps = 0;
        cum_step_units_far = 0;

        // Loop once per trip from the faucet until all the plants are watered.
        // During each loop, fill the can, water plants according to plan,
        // and return to the faucet.
        while (unwatered_count > 0)
        {
            // Fill the can.
            water_amount = UNITS_PER_CAN;

            // Walk to the farthest unwatered plant with a full can.
            plant_number = unwatered_count;
            steps = plant_number;
            cum_steps += steps;
            cum_step_units_far += steps*water_amount;

            // Water plants while walking back towards the faucet.
            // Loop once per plant until either the can is empty
            // or all the plants have been watered.
            // During each loop, water one plant.
            do
            {
                cout << "Plant " << setw(2) << plant_number
                     << setw(9)  << cum_steps
                     << setw(11) << water_amount
                     << setw(16) << cum_step_units_far << endl;

                water_amount--;
                unwatered_count--;
                trip_done = (water_amount == 0) || (unwatered_count == 0);

                if (!trip_done)
                {
                    // Walk towards the faucet to the next unwatered plant.
                    plant_number--;

                    cum_steps++;
                    cum_step_units_far += water_amount;
                }
            } while (!trip_done);

            // Walk back to the faucet with an empty or partially filled can.
            steps = plant_number;
            cum_steps += steps;
            cum_step_units_far += steps*water_amount;

            cout << "FAUCET "
                 << setw(10) << cum_steps
                 << setw(11) << water_amount
                 << setw(16) << cum_step_units_far << endl;
        }

        cout << endl;
        cout << "Plan Far: Total steps = " << cum_steps
             << ", total step-units = " << cum_step_units_far << endl;

        // Which plan is better? Better means fewer step-units.
        cout << endl;
        cout << "*** With " << plant_count << " plants, ";
        if (cum_step_units_far == cum_step_units_near)
        {
            cout << "both plans are equal." << endl;
        }
        else if (cum_step_units_far < cum_step_units_near)
        {
            cout << "Plan Far is better with "
                 << cum_step_units_near - cum_step_units_far
                 << " fewer step-units." << endl;
        }
        else
        {
            cout << "Plan Near is better with "
                 << cum_step_units_far - cum_step_units_near
                 << " fewer step-units." << endl;
        }

    } while (plant_count > 0);

    return 0;
}
