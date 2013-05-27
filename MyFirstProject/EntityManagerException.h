//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __entitymanagerexception_H_
#define __entitymanagerexception_H_

#include <iostream>
#include <exception>


class EntityManagerException : public std::exception {
    virtual char const *what() const throw();
};


#endif //__entitymanagerexception_H_
