#pragma once

#include <string>

namespace Constants {
    
#if __APPLE__
    const std::string CWD = "/Users/willy/Documents/code/posd2023f";
#elif _WIN32
    const std::string CWD = "F:\Code\posd2023f";
#elif __linux__
    const std::string CWD = "/mnt/f/Code/posd2023f";
#endif

}