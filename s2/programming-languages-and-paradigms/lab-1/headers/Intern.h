#ifndef INTERN_H
#define INTERN_H

#include "Employee.h"

class Intern final : public Employee
{
    int salary = 0;

public:
    Intern(const std::string& name, const std::string& surname, const int salary)
        : Employee(name, surname, salary), salary(salary) {}

    void IntroduceYourself() override;

    friend class Manager;
};

#endif // INTERN_H
