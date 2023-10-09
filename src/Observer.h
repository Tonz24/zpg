//
// Created by Tonz on 09.10.2023.
//

#pragma once
#include <vector>

template <typename ...T>
class Observer {
public:
    virtual void update(T... t) = 0;
};

template <typename... T>
class Subject{
public:

    void attach(Observer<T...>* o){
        this->observers.push_back(o);
    }

    void detach(Observer<T...>* o){
        auto it = observers.find(observers.begin(), observers.end(), o);

        if (it != observers.end()){
            observers.erase(observers.begin() + it);
        }
    }

    void notify(T... t){
        for (Observer<T...>* i: observers){
            i->update(t...);
        }
    }

private:
    std::vector<Observer<T...>*> observers{};
};


