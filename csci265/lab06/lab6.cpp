
// lab6.cpp

#include "lab6.h"

int main()
{
    // create a vector of lists of integers
    vector<list<int> > VLI;

    // initialize a vector with two lists of integers (1,2,3 and 10,20,30,40)
    insert_list(VLI, { 1, 2, 3 });
    insert_list(VLI, { 10, 20, 30, 40 });

    print(VLI);

}
