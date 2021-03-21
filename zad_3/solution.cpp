#include <iostream>
#include <string>
#include <regex>

void Input(int mask[], int ipv4[]) {
    std::string ip_num = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    std::string mask_num = "(255|254|252|248|240|224|192|128|0)";
    std::regex IPv4_r("^(" + ip_num + "\\.){3}" + ip_num + "$");
    std::regex mask_r("^(255\\." + mask_num + ".0.0)|((255\\.){2}" + mask_num + ".0)|((255\\.){3}" + mask_num + ")$");
    std::string ip_str, mask_str;
    char * str = new char;
    char * temp;

    do {
        std::cout << "Insert IP\n";
        std::cin >> str;
    } while (!std::regex_match(str, IPv4_r));

    // ip address to int
    temp = std::strtok(str, ".");
    for(int i=0; i<3; i++) {
        ipv4[i] = std::atoi(temp);
        temp = std::strtok(nullptr, ".");
    }
    ipv4[3] = std::atoi(temp);


    do {
        std::cout << "Insert mask\n";
        std::cin >> str;
    } while (!std::regex_match(str, mask_r));

    temp = std::strtok(str, ".");
    for(int i=0; i<3; i++) {
        mask[i] = std::atoi(temp);
        temp = std::strtok(nullptr, ".");
    }
    mask[3] = std::atoi(temp);
    delete str;
}

int main() {
    int maskInt[4];
    int ipv4Int[4];
    int subnet[4];
    Input(maskInt, ipv4Int);
    std::bitset<8> maskBit[4]{maskInt[0], maskInt[1], maskInt[2], maskInt[3]};
    std::bitset<8> ipBit[4]{ipv4Int[0], ipv4Int[1], ipv4Int[2], ipv4Int[3]};
    for (int i = 0; i < 4; i++) {
        subnet[i] = (int) (ipBit[i] & maskBit[i].flip()).to_ulong();
    }
    std::bitset<8> subnetBit[4]{subnet[0], subnet[1], subnet[2], subnet[3]};
    std::cout << "IPv4:\n";
    std::cout << ipBit[0] << "." << ipBit[1] << "." << ipBit[2] << "." << ipBit[3] << std::endl;
    printf("%d.%d.%d.%d\n", ipv4Int[0], ipv4Int[1], ipv4Int[2], ipv4Int[3]);
    printf("%x.%x.%x.%x\n", ipv4Int[0], ipv4Int[1], ipv4Int[2], ipv4Int[3]);
    std::cout << "Mask:\n";
    std::cout << maskBit[0].flip() << "." << maskBit[1].flip() << "."
              << maskBit[2].flip() << "." << maskBit[3].flip() << std::endl;
    printf("%d.%d.%d.%d\n", maskInt[0], maskInt[1], maskInt[2], maskInt[3]);
    printf("%x.%x.%x.%x\n", maskInt[0], maskInt[1], maskInt[2], maskInt[3]);
    std::cout << "Subnet:\n";
    std::cout << subnetBit[0] << "." << subnetBit[1] << "." << subnetBit[2] << "." << subnetBit[3] << std::endl;
    printf("%d.%d.%d.%d\n", subnet[0], subnet[1], subnet[2], subnet[3]);
    printf("%x.%x.%x.%x\n", subnet[0], subnet[1], subnet[2], subnet[3]);
}
