#include <iostream>
#include <string>
#include <regex>

void Input(int address[][4]) {
    std::string ip_num = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    std::string mask_num = "(255|254|252|248|240|224|192|128|0)";
    std::regex IPv4_r("^(" + ip_num + "\\.){3}" + ip_num + "$");
    std::regex mask_r("^(255\\." + mask_num + ".0.0)|((255\\.){2}" + mask_num + ".0)|((255\\.){3}" + mask_num + ")$");
    std::string ip_str, mask_str;
    char str[15];
    char * temp;

    do {
        std::cout << "Insert IP\n";
        std::cin >> str;
    } while (!std::regex_match(str, IPv4_r));

    // ip address to int
    temp = std::strtok(str, ".");
    for(int i=0; i<3; i++) {
        address[0][i] = std::atoi(temp);
        temp = std::strtok(nullptr, ".");
    }
    address[0][3] = std::atoi(temp);

    do {
        std::cout << "Insert mask\n";
        std::cin >> str;
    } while (!std::regex_match(str, mask_r));

    temp = std::strtok(str, ".");
    for(int i=0; i<3; i++) {
        address[1][i] = std::atoi(temp);
        temp = std::strtok(nullptr, ".");
    }
    address[1][3] = std::atoi(temp);
//    delete str;
}

int main() {
    int address[3][4];
    Input(address);
    for (int i = 0; i < 4; i++) {
        address[2][i] = (address[0][i] & address[1][i]);
    }
    std::string str[3] = {"IPv4:\n", "Mask:\n", "Subnet:\n"};
    for(int i=0; i<3; i++) {
        std::cout << str[i];
        for(int j=0; j<3; j++) {
            std::cout << std::bitset<8>(address[i][j]) << ".";
        }
        std::cout << std::bitset<8>(address[i][3]) << std::endl;
        printf("%d.%d.%d.%d\n", address[i][0], address[i][1], address[i][2], address[i][3]);
        printf("%x.%x.%x.%x\n", address[i][0], address[i][1], address[i][2], address[i][3]);
    }
}
