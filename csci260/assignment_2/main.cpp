//------------------------------------------------------------------------------
// @file    main.cpp
// @author  Matthew Hird
// @date    November 7, 2018
//
// @brief   The main function for the program pex2. Checks commandline
//          arguments, then starts UniversityRecords controller class.
//------------------------------------------------------------------------------

#include <iostream>
#include "university_records.h"


int main(int argc, char **argv) {
    UniversityRecords universityRecords;
    universityRecords.run();
    
    return 0;
}