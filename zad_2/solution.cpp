#include <iostream>
#include <string>
#include <memory>

// Tomasz Wojnar
// github https://github.com/Kowalski1024/P2_workspace

struct Document {
    std::string programmingLanguage = "c++";
    int commits = 1;
};

struct Employee {
    std::string name = "Jan";
    std::string surname = "Kowalski";
    std::string level = "junior";
    std::shared_ptr <Document> project_smart;
    Document *project_classic;
};

void classic() {
    Employee *worker_1 = new Employee;
    Document *project_nr1 = new Document;
    (*worker_1).project_classic = project_nr1;
    std::cout << "Name: " << worker_1->name << "\nSurname: " << worker_1->surname << std::endl;
    std::cout << "Programming language: " << worker_1->project_classic->programmingLanguage << std::endl;

    Employee *worker_2 = new Employee;
    std::cout << "\nNew worker\n" << "Enter name and surname:";
    std::cin >> worker_2->name >> worker_2->surname;
    Document *project_nr2 = new Document;
    std::cout << "Enter programming language:";
    std::cin >> project_nr2->programmingLanguage;
    project_nr2->commits = 0;
    (*worker_2).project_classic = project_nr2;

    std::cout << "\nNew worker created\n";
    std::cout << "Name: " << worker_2->name << "\nSurname: " << worker_2->surname << std::endl;
    std::cout << "Programming language: " << worker_2->project_classic->programmingLanguage << "\n\n";

    delete project_nr1;
    delete worker_1;
    delete project_nr2;
    delete worker_2;
}

void smartPointers() {
    Employee *worker_1 = new Employee;
    std::shared_ptr <Document> project_nr1(new Document);
    (*worker_1).project_smart = project_nr1;
    std::cout << "Name: " << worker_1->name << "\nSurname: " << worker_1->surname << std::endl;
    std::cout << "Programming language: " << worker_1->project_smart->programmingLanguage << std::endl;

    Employee *worker_2 = new Employee;
    std::cout << "\nNew worker\n" << "Enter name and surname: ";
    std::cin >> worker_2->name >> worker_2->surname;
    std::shared_ptr <Document> project_nr2(new Document);
    std::cout << "Enter programming language: ";
    std::cin >> project_nr2->programmingLanguage;
    project_nr2->commits = 0;
    (*worker_2).project_smart = project_nr2;

    std::cout << "\nNew worker created\n";
    std::cout << "Name: " << worker_2->name << "\nSurname: " << worker_2->surname << std::endl;
    std::cout << "Programming language:" << worker_2->project_smart->programmingLanguage << std::endl;

    delete worker_1;
    delete worker_2;
}

int main() {
    std::cout << "Classic structure\n";
    classic();
    std::cout << "Structure with smart pointers\n";
    smartPointers();
    return 0;
};