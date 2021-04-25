#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

enum tier {
    FINEST, FINER, FINE, CONFIG, INFO, WARNING, SEVERE
};

class Dziennik {
public:
    void setLevel(tier level);
    void changeMessage();
    void raiseLevel();
    void reduceLevel();
    void printLevel();
    bool doSomething();
    void printLevel(string fileName);
    explicit Dziennik(tier level = FINEST);
    ~Dziennik();

private:
    string m_messages[7] = {
            "Stan bardzo dobry",
            "Stan dobry",
            "Stan dostateczny",
            "Potrzebna jest uwaga uzytkowanika",
            "Wykryto anomalie",
            "Stan zagrozenia",
            "Stan wysokiego zagrozenia",
    };
    void setLevel(int level);
    bool finest();
    bool finer();
    bool fine();
    bool config();
    bool info();
    bool warning();
    bool severe();
    string getTierName();
    string getTierMessage();
    tier m_level;
};

bool Dziennik::finest() {
    cout << "Done!" << endl;
    return true;
}

bool Dziennik::finer() {
    cout << "Done!" << endl;
    return true;
}

bool Dziennik::fine() {
    cout << "Done!" << endl;
    return true;
}

bool Dziennik::config() {
    cout << "Done!" << endl;
    return true;
}

bool Dziennik::info() {
    cout << "Done!" << endl;
    return true;
}

bool Dziennik::warning() {
    cout << "Done!" << endl;
    return true;
}

bool Dziennik::severe() {
    cout << "Done!" << endl;
    return true;
}

Dziennik::Dziennik(tier level) : m_level(level) {
    cout << "Stworzono nowy dziennik z poziomem " << getTierName() << endl;
}

Dziennik::~Dziennik() {
    cout << "Dziennik zostal zniszczony" << endl;
}

string Dziennik::getTierMessage() {
    return m_messages[(int)m_level];
}

// jakas funkcjonalnosc zalezonosci od poziomu (brak pomyslow co moglobyc takiego)
bool Dziennik::doSomething() {
    switch (m_level) {
        case FINEST:
            return finest();
        case FINER:
            return finer();
        case FINE:
            return fine();
        case CONFIG:
            return config();
        case INFO:
            return info();
        case WARNING:
            return warning();
        case SEVERE:
            return severe();
        default:
            return -1;
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
    m_level = static_cast<tier>(level);
}

void Dziennik::changeMessage() {
    string mess;
    cout << "Podaj nowy komunikat dla poziomu " << getTierName() << endl;
    cin >> mess;
    m_messages[(int)m_level] = mess;
    cout << "Zmieniono na: " << mess << endl;
}

void Dziennik::raiseLevel() {
    if((int)m_level >= 6) {
        cout << "Jest to najwyzszy poziom" << endl;
        return;
    }
    setLevel((int)m_level+1);
}

void Dziennik::reduceLevel() {
    if((int)m_level <= 0) {
        cout << "Jest to najnizszy poziom" << endl;
        return;
    }
    setLevel((int)m_level-1);
}

void Dziennik::printLevel(string fileName) {
    ofstream file;
    file.open(fileName, std::ios_base::app);
    file << "Poziom " << getTierName() << ": " << getTierMessage() << endl;
    cout << "Zapisano do pliku " << fileName << endl;
}

void Dziennik::printLevel() {
    cout << "Poziom " << getTierName() << ": " << getTierMessage() << endl;
}

int main() {
    Dziennik *diary = new Dziennik();
    cout << "Polecenia: raise, reduce, PRF [file], PRT, change, take, clear" << endl;
    string command;
    cin >> command;
    while(command != "END") {
        if(command == "raise") {
            diary->raiseLevel();
            diary->printLevel();
        } else if(command == "reduce") {
            diary->reduceLevel();
            diary->printLevel();
        } else if(command == "PRF") {       // print information to file
            string fileName;
            cin >> fileName;
            diary->printLevel(fileName);
        } else if(command == "PRT") {       // print information to stdout
            diary->printLevel();
        }  else if(command == "change") {   // change message on actual level
            diary->changeMessage();
        }  else if(command == "take") {
            if(diary->doSomething()) {
                cout << "Successful" << endl;
            } else {
                cout << "Fail" << endl;
            }
        } else if(command == "clear") {
            diary->setLevel(FINEST);
            diary->printLevel();
        }
        cin >> command;
    }
    delete diary;
    return 0;
}


