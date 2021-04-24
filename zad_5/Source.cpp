#include <iostream>
#include <fstream>

using namespace std;

enum tier {
    FINEST, FINER, FINE, CONFIG, INFO, WARNING, SEVERE
};

class Dziennik {
public:
    void setLevel(tier level);
    void setLevel(int level);
    void raiseLevel();
    void reduceLevel();
    void printLevel();
    void printLevel(string fileName);
    string getLevel();
    explicit Dziennik(tier level = FINEST);

    ~Dziennik();

private:
    string getTierName();
    string getTierMessage();
    tier m_level;
};

Dziennik::Dziennik(tier level) : m_level(level) {
    cout << "Stworzono nowy dziennik z poziomem " << getTierName() << endl;
}

Dziennik::~Dziennik() {
    cout << "Dziennik zostal zniszczony" << endl;
}

string Dziennik::getTierMessage() {
    switch (m_level) {
        case FINEST:
            return "FINEST";
        case FINER:
            return "FINER";
        case FINE:
            return "FINE";
        case CONFIG:
            return "CONFIG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case SEVERE:
            return "SEVERE";
        default:
            return "NULL";
    }
}

string Dziennik::getTierName() {
    switch (m_level) {
        case FINEST:
            return "FINEST";
        case FINER:
            return "FINER";
        case FINE:
            return "FINE";
        case CONFIG:
            return "CONFIG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case SEVERE:
            return "SEVERE";
        default:
            return "NULL";
    }
}

void Dziennik::setLevel(tier level) {
    m_level = level;
}

void Dziennik::setLevel(int level) {
    if(level > 6) {
        level = 6;
    } else if(level < 0) {
        level = 0;
    }
    m_level = static_cast<tier>(level);
}

void Dziennik::raiseLevel() {
    setLevel((int)m_level+1);
}

void Dziennik::reduceLevel() {
    setLevel((int)m_level-1);
}

string Dziennik::getLevel() {
    return getTierName();
}

int main() {
    Dziennik *test = new Dziennik();
    string command;
    delete test;
    return 0;
}


