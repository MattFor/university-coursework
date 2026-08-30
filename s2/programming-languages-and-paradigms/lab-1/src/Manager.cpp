//
// Created by MattFor on 12/03/2025.
//

#include "../headers/Intern.h"
#include "../headers/Manager.h"

void Manager::ChangeSalary(const int newSalary, Employee* employee)
{
    // Check if the employee is actually an Intern.
    if (auto* intern = dynamic_cast<Intern*>(employee))
    {
        // Manager is a friend of Intern, so it can access Intern's private salary.
        intern->salary = newSalary;
    }
    else
    {
        // Otherwise, update the salary field in Employee.
        employee->salary = newSalary;
    }
}


void Manager::IntroduceYourself()
{
    printf("I am the manager, woohoo!\n");
};
