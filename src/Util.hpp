#ifndef UTIL_HPP
#define UTIL_HPP

#include <sys/stat.h>

// Function: FileExists
/**
    Check if a file exists
@param[in] filename - the name of the file to check

@return    true if the file exists, else false

*/
bool inline FileExists(const std::string& filename)
{
    struct stat buf;
    return stat(filename.c_str(), &buf) != -1;
}

#endif // !UTIL_HPP
