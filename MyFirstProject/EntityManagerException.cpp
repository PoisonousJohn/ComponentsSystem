//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.




#include "EntityManagerException.h"

char const * EntityManagerException::what() const throw() {
    return "entity manager error";
}
