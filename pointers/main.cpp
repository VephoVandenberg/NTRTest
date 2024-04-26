#include <iostream>

int main(int argc, char **argv)
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << *(arr + 3) << std::endl;

    return 0;
}