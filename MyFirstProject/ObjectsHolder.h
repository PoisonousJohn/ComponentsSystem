//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/28/13.





#ifndef __ComponentsHolder_H_
#define __ComponentsHolder_H_

#include <iostream>
#include <deque>
#include <memory>

template <typename T>
struct Objects {
    typename std::deque<T>::const_iterator start;
    typename std::deque<T>::const_iterator end;
};

template <typename T>
class ObjectsHolder {

private:
    std::deque<T> components_;
public:
    Objects<T> getObjects() const;
    void addObject(std::shared_ptr<T> object);
};


#endif //__ComponentsHolder_H_
