//
// Created by MattFor on 12/03/2025.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee
{
public:
    virtual ~Employee() = default;

    Employee(const std::string& name, const std::string& surname, const int salary)
    {
        this->name = name;
        this->surname = surname;
        this->salary = salary;
    }

    int salary = 0;

    std::string name = "Unset";
    std::string surname = "Unset";

    virtual void IntroduceYourself() = 0;
};

#endif //EMPLOYEE_H
