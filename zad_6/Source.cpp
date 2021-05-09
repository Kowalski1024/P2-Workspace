#include <iostream>
#include <string>
using namespace std;

// ------------------------------
///           Capitan
// ------------------------------
class Capitan {
private:
    string m_name;
    string m_surname;
public:
    Capitan(string name, string surname);
    void setName(string name);
    string getName() const;
    void setSurname(string surname);
    string getSurname() const;
};

Capitan::Capitan(string name, string surname) : m_name(name), m_surname(surname) {}


/// setters
void Capitan::setName(string name) { m_name = name; }
void Capitan::setSurname(string surname) { m_surname = surname; }

/// getters
string Capitan::getName() const { return m_name; }
string Capitan::getSurname() const { return m_surname; }

// ------------------------------
///             Ship
// ------------------------------
class Ship {
private:
    string m_name;
    int m_crew;
    int m_foodRations;
protected:
    Capitan m_capitan = Capitan("Susan", "Ivanova");
public:
    friend std::ostream& operator<<(std::ostream& stream, const Ship& ship);
    virtual void calculateFoodRations();
    virtual ~Ship();
    void calculateFoodRations(bool dessert);
    Ship(string shipName, int crewAmount=18);
    void setCrew(int amount);
    int getCrew();
    void setCapitan(string name, string surname);
    string getCapitan();
    int getFoodRations();
    void setFoodRations(int value);
};

Ship::Ship(string shipName, int crewAmount) : m_name(shipName), m_crew(crewAmount), m_foodRations(0) {}

std::ostream& operator<<(std::ostream& stream, const Ship& ship)
{
    stream << "Capitan: " << ship.m_capitan.getName() + " " + ship.m_capitan.getSurname()
             << ", name: " << ship.m_name
             << ", crew: " << ship.m_crew;
    return stream;
}

void Ship::calculateFoodRations() {
    m_foodRations = 3*m_crew;
}

void Ship::calculateFoodRations(bool dessert) {
    if(dessert) {
        m_foodRations = 4*m_crew;
        return;
    }
    m_foodRations = 3*m_crew;
}

/// setters
void Ship::setCrew(int amount) { m_crew = amount; }
void Ship::setCapitan(string name, string surname) {
    m_capitan.setName(name);
    m_capitan.setSurname(surname);
}
int Ship::getFoodRations() { return m_foodRations; }

/// getters
int Ship::getCrew() { return m_crew; }
string Ship::getCapitan() {
    return m_capitan.getName() + " " + m_capitan.getSurname();
}

Ship::~Ship() {

}

void Ship::setFoodRations(int value) {
    m_foodRations = value;
}

// ------------------------------
///        PassengerShip
// ------------------------------
class PassengerShip : public virtual Ship {
private:
    int m_passengers;
public:
    PassengerShip(string shipName, int crewAmount=30);
    void addSubPassengers(int passengers);
    void calculateFoodRations() override;
    int numberOfPeople();
    void setPassengers(int passengers);
    int getPassengers();
};

PassengerShip::PassengerShip(string shipName, int crewAmount) : Ship(shipName, crewAmount), m_passengers(30) {}

void PassengerShip::addSubPassengers(int passengers) {
    m_passengers += passengers;
}

void PassengerShip::calculateFoodRations() {
    setFoodRations(3*(getCrew() + m_passengers));
}

/// setters
void PassengerShip::setPassengers(int passengers) {
    m_passengers = passengers;
}

/// getters
int PassengerShip::numberOfPeople() {
    return getCrew()+m_passengers+1; // + capitan
}
int PassengerShip::getPassengers() { return m_passengers; }

// ------------------------------
///           CombatShip
// ------------------------------
class CombatShip : public virtual Ship {
private:
    int m_turretsAmount;
public:
    CombatShip(string shipName, int crewAmount=50, int turrets=8);
    int getTurretsAmount();
};

CombatShip::CombatShip(string shipName, int crewAmount, int turrets) : Ship(shipName, crewAmount), m_turretsAmount(turrets) {}

/// getters
int CombatShip::getTurretsAmount() { return m_turretsAmount; }

// ------------------------------
///      TransportCombatShip
// ------------------------------
class TransportCombatShip : public PassengerShip, public CombatShip {
public:
    TransportCombatShip(string shipName, int crewAmount=100, int turrets=16);
};

TransportCombatShip::TransportCombatShip(string shipName, int crewAmount, int turrets) :
        Ship(shipName, crewAmount),
        PassengerShip(shipName, crewAmount),
        CombatShip(shipName, crewAmount, turrets) {}

int main(){
    Ship* ship = new Ship("Enterprise");
    cout << "Ship" << endl;
    cout << *ship << endl;
    ship->Ship::calculateFoodRations();
    cout << "Food for crew: " << ship->getFoodRations();
    ship->Ship::calculateFoodRations(true);
    cout << " with dessert " << ship->getFoodRations() << endl << endl;
    delete ship;

    PassengerShip* passengerShip = new PassengerShip("Titanic");
    cout << "Passenger Ship is child  of the Ship" << endl;
    cout << *passengerShip << ", passengers " << passengerShip->getPassengers() << ", total " <<
        passengerShip->numberOfPeople() << endl;
    passengerShip->Ship::calculateFoodRations();
    cout << "Food for crew: " << passengerShip->getFoodRations();
    passengerShip->Ship::calculateFoodRations(true);
    cout << " with dessert " << passengerShip->getFoodRations() << endl;
    passengerShip->calculateFoodRations();
    cout<< "Food for ship: " << passengerShip->getFoodRations() << endl << endl;
    delete passengerShip;

    CombatShip* combatShip = new CombatShip("Mayflower");
    combatShip->setCapitan("Thomas", "Smith");
    cout << "Combat Ship is child of the Ship" << endl;
    cout << *combatShip << ", turrets " << combatShip->getTurretsAmount() << endl;
    combatShip->Ship::calculateFoodRations();
    cout << "Food for crew: " << combatShip->getFoodRations();
    combatShip->Ship::calculateFoodRations(true);
    cout << " with dessert " << combatShip->getFoodRations() << endl;
    combatShip->calculateFoodRations();
    cout<< "Food for ship: " << combatShip->getFoodRations() << endl << endl;
    delete combatShip;

    TransportCombatShip* transportCombatShip = new TransportCombatShip("Mayflower");
    transportCombatShip->setCapitan("Thomas", "Smith");
    cout << "Transport Combat Ship is of the child CombatShip and PassengerShip" << endl;
    cout << *transportCombatShip << ", passengers " << transportCombatShip->getPassengers() << ", total " <<
         transportCombatShip->numberOfPeople() << ", turrets " << transportCombatShip->getTurretsAmount() << endl;
    transportCombatShip->Ship::calculateFoodRations();
    cout << "Food for crew: " << transportCombatShip->getFoodRations();
    transportCombatShip->Ship::calculateFoodRations(true);
    cout << " with dessert " << transportCombatShip->getFoodRations() << endl;
    transportCombatShip->calculateFoodRations();
    cout<< "Food for ship: " << transportCombatShip->getFoodRations() << endl;
    delete transportCombatShip;
}

/*
  nie dziala zbyt dobrze...
      string command, tmp;
    string name;
    int x;
    while(n != -1) {
        switch (n) {
            case 0:
                cout << "Choose ship type (write number):"
                        "\n1 Ship\n2 PassengerShip\n3 CombatShip\n4 TransportCombatShip\n" << endl;
                cin >> n;
                cin.clear();
                cout << "Name: ";
                cin >> name;
                cout << name << endl;
                delete ship;
                switch (n) {
                    case 1: ship = new Ship(name); break;
                    case 2: ship = new PassengerShip(name); break;
                    case 3: ship = new CombatShip(name); break;
                    case 4: ship = new TransportCombatShip(name); break;
                }
                break;
            case 2:
                if(command=="foodShip") {
                    ship->calculateFoodRations();
                    cout << "Food for crew and passengers: " << ship->getFoodRations() << endl;
                } else if(command=="passengers") {
                    cout <<
                }
            case 1:
                if(command=="changeShip") {
                    n=0;
                } else if(command=="getCapitan") {
                    cout << ship->getCapitan() << endl;
                } else if(command=="setCapitan") {
                    cout << "Name: ";
                    getline(cin, command);
                    cout << "Surname: ";
                    getline(cin, tmp);
                    ship->setCapitan(command, tmp);
                } else if(command=="getCrew") {
                    cout << ship->getCrew() << endl;
                }  else if(command=="setCrew") {
                    cout << "Amount: ";
                    cin >> x;
                    ship->setCrew(x);
                } else if(command=="foodCrew") {
                    cout << "Give dessert? type 1 if yes or 0 if not\n";
                    cin >> x;
                    if(x) {
                        ship->Ship::calculateFoodRations(true);
                    } else {
                        ship->Ship::calculateFoodRations(false);
                    }
                    cout << "Food for crew: " << ship->getFoodRations() << endl;
                } else if(command=="END") {
                    n=-1;
                    break;
                } else {
                    cout << "Unknown command\n";
                }

        }
        cout << "Write command" << endl;
        cin >> command;
    }
 */