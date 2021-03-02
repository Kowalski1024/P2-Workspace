#include <iostream>
#include <string>

void first_solution(int n) {
    std::string arr[n];
    std::string *ptr = arr;
    for (int i = 0; i < n; ++i) {
        std::cin >> *(ptr + i);
    }

    printf("Solution 1\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: %s\n", i, (*(ptr + i)).c_str());
    }
}

int main() {
    int const n = 2;
    first_solution(n);
    return 0;
}