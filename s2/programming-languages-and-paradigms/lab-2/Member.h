//
// Created by MattFor on 17.03.2025.
//

#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <iostream>

class Member
{
    std::string name;
    unsigned int booksBorrowed;

public:
    explicit Member(const std::string& name);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] unsigned int getBooksBorrowed() const;

    void setName(const std::string& name);
    void setBooksBorrowed(unsigned int count);

    void borrowBook();
    void returnBook();
};

#endif // MEMBER_H
