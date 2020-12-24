#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

/*** Complete this program. ***/

int main()
{
    const int UNITS_PER_CAN = 3;
    const string INPUT_FILE_NAME = "counts.txt";
    int plant_count, cum_step, water_amount, cum_step_unit, near, far;

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
        if (plant_count == 0)
            break;
        cum_step = 0;
        water_amount = 3;
        cum_step_unit = 0;

        // Plan Near

        cout << endl;
        cout << "==========================" << endl;
        cout << " Plan Near with " << plant_count << " plants" << endl;
        cout << "==========================" << endl;
        cout << endl;
        cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
        cout << "---------  ----------  ----------  ---------------" << endl;

        for (int8_t i = 0; i < plant_count; i++)
        {

            for (int8_t j = 0; j < UNITS_PER_CAN; j++)
            {
                if (i < plant_count)
                {
                    cum_step++;
                    cum_step_unit += (UNITS_PER_CAN - j);

                    cout << "Plant " << i + 1 << setw(10)
                         << cum_step << setw(11)
                         << water_amount << setw(16)
                         << cum_step_unit << endl;

                    water_amount--;
                    i++;
                }
                else
                {
                    cum_step += i;
                    cum_step_unit += (i * water_amount);
                    cout << "FAUCET " << setw(10)
                         << cum_step << setw(11)
                         << water_amount << setw(16)
                         << cum_step_unit << endl;
                    break;
                }
            }
            if (water_amount == 0)
            {
                cum_step += i;
                cout << "FAUCET " << setw(10)
                     << cum_step << setw(11)
                     << water_amount << setw(16)
                     << cum_step_unit << endl;
                if (i < plant_count)
                {
                    cum_step += i;
                    cum_step_unit += (i * UNITS_PER_CAN);
                }

                i--;
                water_amount = 3;
            }
        }
        near = cum_step_unit;
        cout << "\n"
             << "Plan Near: Total steps = " << cum_step
             << ", total step-units = " << cum_step_unit << endl;

        /*** Complete the code for Plan Near. ***/

        // Plan Far

        cout << endl;
        cout << "=========================" << endl;
        cout << " Plan Far with " << plant_count << " plants" << endl;
        cout << "=========================" << endl;
        cout << endl;
        cout << "Where      Cum. steps  Water amt.  Cum. step-units" << endl;
        cout << "---------  ----------  ----------  ---------------" << endl;

        /*** Complete the code for Plan Far. ***/

        cum_step = 0;
        water_amount = 3;
        cum_step_unit = 0;

        for (int8_t i = plant_count; i > 0; i--)
        {
            cum_step += i;
            cum_step_unit += UNITS_PER_CAN * i;

            for (int8_t j = UNITS_PER_CAN; j > 0; j--)
            {
                cout << "Plant " << i + 0 << setw(10)
                     << cum_step << setw(11)
                     << water_amount << setw(16)
                     << cum_step_unit << endl;
                water_amount--;
                cum_step_unit += water_amount;
                cum_step++;
                i--;

                if (i == 0)
                {
                    cum_step += i;
                    cout << "FAUCET " << setw(10)
                         << cum_step << setw(11)
                         << water_amount << setw(16)
                         << cum_step_unit << endl;
                    j = 0;
                    break;
                }
            }
            if ((water_amount == 0) && (i != 0))
            {
                cum_step += i;
                cout << "FAUCET " << setw(10)
                     << cum_step << setw(11)
                     << water_amount << setw(16)
                     << cum_step_unit << endl;

                i++;
                water_amount = 3;
            }
        }

        far = cum_step_unit;
        cout << "\n"
             << "Plan Far: Total steps = " << cum_step
             << ", total step-units = " << cum_step_unit << endl;

        // Which plan is better? Better means fewer step-units.
        cout << endl;
        cout << "*** With " << plant_count << " plants, ";

        if (near > far)
        {
            cout << "Plan Far is better with "
                 << (near - far)
                 << " fewer step-units."
                 << endl<<endl;
        }
        else
        {
            cout << "Plan Near is better with "
                 << (far - near)
                 << " fewer step-units."
                 << endl;
        }

        /*** Complete the code to determine the better plan. ***/

    } while (plant_count > 0);

    return 0;
}
