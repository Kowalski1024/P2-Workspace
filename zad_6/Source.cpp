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
    virtual void calculateFoodRations();
    void calculateFoodRations(bool dessert);
    void recruitment(int amount);
    Ship(string shipName, int crewAmount);
    void setCrew(int amount);
    int getCrew();
    void setCapitan(string name, string surname);
    string getCapitan();
    void setFoodRations(int value);
};

Ship::Ship(string shipName, int crewAmount) : m_name(shipName), m_crew(crewAmount) {}

void Ship::recruitment(int amount) {
    m_crew += amount;
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
void Ship::setFoodRations(int value) { m_foodRations = value; }

/// getters
int Ship::getCrew() { return m_crew; }
string Ship::getCapitan() {
    return m_capitan.getName() + " " + m_capitan.getSurname();
}

// ------------------------------
///        PassengerShip
// ------------------------------
class PassengerShip : public virtual Ship {
private:
    int m_passengers;
public:
    PassengerShip(string shipName, int crewAmount);
    void addSubPassengers(int passengers);
    void calculateFoodRations() override;
    int numberOfPeople();
    void setPassengers(int passengers);
    int getPassengers();
};

PassengerShip::PassengerShip(string shipName, int crewAmount) : Ship(shipName, crewAmount) {}

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
    CombatShip(string shipName, int crewAmount, int turrets);
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
    TransportCombatShip(string shipName, int crewAmount, int turrets);
};

TransportCombatShip::TransportCombatShip(string shipName, int crewAmount, int turrets) :
        Ship(shipName, crewAmount),
        PassengerShip(shipName, crewAmount),
        CombatShip(shipName, crewAmount, turrets) {}
