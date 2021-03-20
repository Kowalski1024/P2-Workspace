#include <iostream>
#include <string>
#include <regex>

void Input(int mask[], int ipv4[]){
    std::string num = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    std::regex IPv4_r("^(" + num + "\\.){3}" + num + "$");
    std::regex mask_r("^(255.0.0.0)|(255.255.0.0)|(255.255.255.0)$");
    std::string ip_str, mask_str;
    do {
        std::cout << "Insert IP\n";
        std::cin >> ip_str;
    }while(!std::regex_match(ip_str, IPv4_r));
    do {
        std::cout << "Insert mask\n";
        std::cin >> mask_str;
    } while(!std::regex_match(mask_str, mask_r));
    std::stringstream p(ip_str);
    std::stringstream k(mask_str);
    char h;
    for (int i=0; i<3; i++) {
        p >> ipv4[i] >> h;
        k >> mask[i] >> h;
    }
    p >> ipv4[3];
    k >> mask[3];
}

int main() {
    int maskInt[4];
    int ipv4Int[4];
    int subnet[4];
    Input(maskInt, ipv4Int);
    std::bitset<8> maskBit[4]{maskInt[0], maskInt[1],maskInt[2],maskInt[3]};
    std::bitset<8> ipBit[4]{ipv4Int[0],ipv4Int[1],ipv4Int[2],ipv4Int[3]};
    for(int i=0; i<4; i++) {
        subnet[i] = (int)(ipBit[i] & maskBit[i].flip()).to_ulong();
    }

//    for(int i=0; i<4; i++) {
//        std::cout << (ipv4[i] & mask[i]) << std::endl;
//    }
}
