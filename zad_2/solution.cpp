#include <iostream>
#include <string>
#include <memory>

struct Document {
    std::string programmingLanguage = "c++";
    int commits = 1;
};

struct Employee {
    std::string name = "Jan";
    std::string surname = "Kowalski";
    std::string level = "junior";
    std::shared_ptr<Document> project;
};

int main() {
    Employee * worker_1 = new Employee;
    std::shared_ptr<Document> project_nr1(new Document);
    (*worker_1).project = project_nr1;
    std::cout << "Name: " << worker_1->name << "\nSurname: " << worker_1->surname << std::endl;
    std::cout << "Programming language: " << worker_1->project->programmingLanguage << std::endl;

    Employee * worker_2 =  new Employee;
    std::cout << "\nNew worker\n" << "Enter name and surname:";
    std::cin >> worker_2->name >> worker_2->surname;
    std::shared_ptr<Document> project_nr2(new Document);
    std::cout << "Enter programming language:";
    std::cin >> project_nr2->programmingLanguage;
    project_nr2->commits = 0;
    (*worker_2).project = project_nr2;

    std::cout << "\nNew worker created\n";
    std::cout << "Name: " << worker_2->name << "\nSurname: " << worker_2->surname << std::endl;
    std::cout << "Programming language:" << worker_2->project->programmingLanguage << std::endl;

    return 0;
};