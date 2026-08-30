#include <iostream>

#include "headers/Intern.h"
#include "headers/Manager.h"
#include "headers/Employee.h"

int main()
{
    auto* manager = new Manager("Jan", "Kowalski", 300000000);
    auto* intern = new Intern("Janek", "Kowal", 1);

    manager->IntroduceYourself();
    intern->IntroduceYourself();

    Manager::ChangeSalary(2, intern);
    // Proszę sprawdzić w debuggerze, że intern salary zmienia się z 1 na 2.
}