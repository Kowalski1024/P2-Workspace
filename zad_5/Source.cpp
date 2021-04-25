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
    bool doSomething();
    void printLevel();
    void printLevel(string fileName);
    explicit Dziennik(tier level = FINEST);
    ~Dziennik();

private:
    string m_messages[7] = {
            "DEFCON 5",
            "DEFCON 4",
            "DEFCON 3",
            "Prepare to DEFCON 2",
            "Sirens were turned on to warn of a possible nuclear attack",
            "DEFCON 2",
            "DEFCON 1",
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
    cout << "Normal combat readiness" << endl;
    return true;
}

bool Dziennik::finer() {
    cout << "Increased combat readiness" << endl;
    return true;
}

bool Dziennik::fine() {
    cout << "USAF Air Force ready for mobilization" << endl;
    return true;
}

bool Dziennik::config() {
    cout << "President secured in the plane" << endl;
    return true;
}

bool Dziennik::info() {
    cout << "Please go to fallout shelters" << endl;
    return true;
}

bool Dziennik::warning() {
    cout << "Prepare to nuclear attack" << endl;
    return true;
}

bool Dziennik::severe() {
    cout << "Nuclear war inevitable" << endl;
    return true;
}

Dziennik::Dziennik(tier level) : m_level(level) {
    cout << "Diary was created with level " << getTierName() << endl;
}

Dziennik::~Dziennik() {
    cout << "Diary has been destroyed" << endl;
}

string Dziennik::getTierMessage() {
    return m_messages[(int)m_level];
}

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
    cout << "Enter a new message " << getTierName() << endl;
    cin >> mess;
    m_messages[(int)m_level] = mess;
    cout << "Changed to: " << mess << endl;
}

void Dziennik::raiseLevel() {
    if((int)m_level >= 6) {
        cout << "This is the highest level" << endl;
        return;
    }
    setLevel((int)m_level+1);
}

void Dziennik::reduceLevel() {
    if((int)m_level <= 0) {
        cout << "This is the lowest level" << endl;
        return;
    }
    setLevel((int)m_level-1);
}

void Dziennik::printLevel(string fileName) {
    ofstream file;
    file.open(fileName, std::ios_base::app);
    file << getTierName() << ": " << getTierMessage() << endl;
    cout << "Saved to file " << fileName << endl;
}

void Dziennik::printLevel() {
    cout << getTierName() << ": " << getTierMessage() << endl;
}

int main() {
    Dziennik *diary = new Dziennik();
    cout << "Commands: raise, reduce, PRF [file], PRT, change, info, clear" << endl;
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
        }  else if(command == "info") {
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


