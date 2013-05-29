//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/28/13.





#ifndef __ComponentsHolder_H_
#define __ComponentsHolder_H_

#include <iostream>
#include <deque>
#include <unordered_map>
#include <memory>

template <typename T>
struct Objects {
    typename std::deque<T>::const_iterator start;
    typename std::deque<T>::const_iterator end;
};

template <typename T>
class ObjectsHolder {

protected:
    std::deque<T> objects_;
public:
    Objects<T> getObjects() const;
    void addObject(std::shared_ptr<T> object);
};

//template <typename Key, typename Value>
//class IndexedObjectsHolder {

//protected:
//    std::unordered_map<Key, Value> objects_;
//public:
//    bool hasKey(Key key) const { return objects_.find(key) == objects_.end(); }
//    Value& getObject(Key key) const { return objects_.at(key); }
//    void addObject(std::shared_ptr<T> object);
//};


#endif //__ComponentsHolder_H_
