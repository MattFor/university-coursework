//
// Created by MattFor on 17.03.2025.
//

#include "Member.h"

Member::Member(const std::string& name)
{
    this->name = name;
    booksBorrowed = 0;
}

std::string Member::getName() const
{
    return name;
}

unsigned int Member::getBooksBorrowed() const
{
    return booksBorrowed;
}

void Member::setName(const std::string& name)
{
    this->name = name;
}

void Member::setBooksBorrowed(unsigned int count)
{
    booksBorrowed = count;
}

void Member::borrowBook()
{
    booksBorrowed++;
}

void Member::returnBook()
{
    if (booksBorrowed > 0)
    {
        booksBorrowed--;
    }
}
