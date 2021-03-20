#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string num = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    std::regex IPv4_r("^(" + num + "\\.){3}" + num + "$");
    std::regex mask_r("^((255\\.){3}"+num+"|((255\\.){2}"+num+".0)|((255\\.)"+num+".0.0)|("+num+".0.0.0))");
    std::string tekst;
    while(std::cin >> tekst) {
        if(std::regex_match(tekst, mask_r))
        {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }
    int mask[4];
    int IP[4];


}
