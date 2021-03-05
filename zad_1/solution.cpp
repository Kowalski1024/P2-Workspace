#include <iostream>
#include <cstring>

// Tomasz Wojnar
// github https://github.com/Kowalski1024/P2_workspace

void StringStyle(int n) {
    std::string arr[n];
    std::string *ptr = arr;
    for (int i = 0; i < n; ++i) {
        std::cin >> *(ptr + i);
    }

    printf("Solution 1\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: %s - length %d\n", i, (*(ptr + i)).c_str(), (ptr + i)->size());
    }
}

void CStyle(int n) {
    char * arr[n];
    for (int i = 0; i < n; ++i) {
        char * buffer = new char;
        gets(buffer);
        char * surname = (char*) malloc(strlen(buffer)+1);
        strcpy(surname, buffer);
        delete buffer;
        *(arr+i) = surname;
    }

    printf("Solution 2\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: %s - length %d\n", i, *(arr+i), strlen(*(arr+i)));
        free(*(arr+i));
    }
}

int main() {
    int const n = 2;
    StringStyle(n);
    CStyle(n);
    return 0;
}