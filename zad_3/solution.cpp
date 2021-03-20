#include <iostream>
#include <string>
#include <regex>

int main() {
    std::regex IPv4("([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    std::string tekst;
    std::cin >> tekst;
    while(std::cin >> tekst) {
        if(std::regex_match(tekst, IPv4))
        {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }
    int mask[4];
    int IP[4];


}
