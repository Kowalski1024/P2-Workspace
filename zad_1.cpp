#include <iostream>
#include <cstring>

void FirstSolution(int n) {
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

void SecondSolution(int n) {
    char * arr[n];
    for (int i = 0; i < n; ++i) {
        char * surname = new char;
        gets(surname);
        *(arr+i) = surname;
    }

    printf("Solution 2\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: %s - length %d\n", i, *(arr+i), strlen(*(arr+i)));
        delete *(arr+i);
    }
}

int main() {
    int const n = 2;
    int x;
    std::cout << "write 1 or 2\n";
    std::cin >> x;
    std::cin.clear();
    if(x==1) {
        FirstSolution(n);
    } else if (x==2) {
        SecondSolution(n);
    }
    return 0;
}