//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __entitymanagerexception_H_
#define __entitymanagerexception_H_

#include <iostream>
#include <exception>

namespace poison {
    class EntityManagerException : public std::exception {
        virtual const char* what() const throw() {
            return "entity manager error";
        }
    };
}



#endif //__entitymanagerexception_H_
