#include <iostream>
#include <iomanip>

#include "include/utils.h"

std::string bytes_to_hr(uint64_t bytes, int precision) {
    double f_bytes = static_cast<double>(bytes);
    const std::string units[] = {"B", "K", "M", "G", "T", "P"};

    int i = 0;
    while (f_bytes > 1024) {
        f_bytes /= 1024;
        i++;
    }

    std::stringstream stream;

    stream << std::fixed << std::setprecision(precision) << f_bytes;

    return stream.str() + units[i];
}