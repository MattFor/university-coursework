#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager final : public Employee
{
public:
    Manager(const std::string& name, const std::string& surname, const int salary)
        : Employee(name, surname, salary) {}

    int employee_count = 0;

    void IntroduceYourself() override;
    static void ChangeSalary(int salary, Employee* employee);
};

#endif // MANAGER_H
