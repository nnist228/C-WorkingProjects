#include "pct.h"
#include <limits>
#include <algorithm>
#include <cmath>

double Pct::eval() const {
    int K = std::floor((double) (data.size() - 1) * proc);
    double aN = proc * (double) data.size();
    if(K + 1 < aN){
        return data.at(K+1);
    } else if(K + 1 == aN){
        return (data.at(K) + data.at(K+1)) / 2.;
    } else{
        return data.at(K);
    }
}

void Pct::update(double next) {
    if(data.empty()){
        data.push_back(next);
    } else{
       SpecialInsert(std::move(next)); 
    }
}

void Pct::SpecialInsert(double next){
    bool inserted{false};
    for(size_t begin{0}, end{data.size() - 1}, middle {(begin + end) / 2}; !inserted;){
        if(data.at(begin) >= next){
            data.insert(data.begin(), next);
            inserted = true;
        } else if(data.at(end) <= next){
            data.insert(data.begin() + end + 1, next);
            inserted = true;
        } else if(data.at(middle) <= next){
            begin = middle + 1;
            end = end - 1;
            middle = (begin + end) / 2;
        } else{
            begin = begin + 1;
            end = middle - 1;
            middle = (begin + end) / 2;
        }
    }
}

