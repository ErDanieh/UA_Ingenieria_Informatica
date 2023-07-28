//Daniel Asensi Roch 48776120C
#include <iostream>
using namespace std;

unsigned long steps1 = 0;
unsigned long steps3 = 0;
unsigned long steps2 = 0;

//Prototipos
unsigned long pow2_1(unsigned pot);
unsigned long pow2_2(unsigned pot);
unsigned long pow2_3(unsigned pot);

int main()
{
    for (unsigned i = 1; i < 32; i++)
    {
        steps3 = 0;
        steps2 = 0;
        steps1 = 0;
        pow2_1(i);
        pow2_2(i);
        pow2_3(i);
        cout <<  i << "\t " << steps1 << "\t" << steps2 << "\t" << steps3 << endl;
    }
    return 0;
}

unsigned long pow2_1(unsigned pot)
{
    if (pot == 0)
    {
        steps1++;
        return 1;
    }
    else
    {
        steps1++;
        return 2 * pow2_1(pot - 1);
    }
}

unsigned long pow2_2(unsigned pot)
{
    if (pot == 0)
    {
        steps2++;
        return 1;
    }
    else
    {
        steps2++;
        return pow2_2(pot - 1) + pow2_2(pot - 1);
    }
}

unsigned long pow2_3(unsigned pot)
{
    int r;

    if (pot == 0)
    {
        steps3++;
        return 1;
    }
    else
    {
        steps3++;
        r = pow2_3(pot / 2);
        if (pot % 2 == 0)
        {
            return r * r;
        }
        else
        {
            return r * r * 2;
        }
    }
}

