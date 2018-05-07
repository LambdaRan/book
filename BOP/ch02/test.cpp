#include <iostream>

#include <stdint.h>

int main() 
{
    int arr[3] = {3, 1, 2};
    int *p = &arr[2];
    std::cout << p[-1] << std::endl;

    std::cout << arr[-1] << std::endl;


    // std::cout << "INT8_MIN " << INT8_MIN << "\n";
    // std::cout << "INT16_MIN " << INT16_MIN << "\n";
    // std::cout << "INT32_MIN " << INT32_MIN << "\n";
    // std::cout << "INT64_MIN " << INT64_MIN << "\n";

    // std::cout << "INT8_MAX " << INT8_MAX << "\n";
    // std::cout << "INT16_MAX " << INT16_MAX << "\n";
    // std::cout << "INT32_MAX " << INT32_MAX << "\n";
    // std::cout << "INT64_MAX " << INT64_MAX << "\n"; 

    // std::cout << "UINT8_MAX " << UINT8_MAX << "\n"; 
    // std::cout << "UINT16_MAX " << UINT16_MAX << "\n"; 
    // std::cout << "UINT32_MAX " << UINT32_MAX << "\n"; 
    // std::cout << "UINT64_MAX " << UINT64_MAX << "\n";   
    std::cout << std::endl;
}