#include "std.h"
#include <numeric>
#include <cmath>
double Std::eval() const
{
    std::vector<double> sqr_el_m_mean = data;
    double n = (double) data.size();
    double mean = std::accumulate(data.begin(), data.end(), 0) / n;
    for(auto& el: sqr_el_m_mean){
        el = (el - mean) * (el - mean);
    }
    return sqrt(std::accumulate(sqr_el_m_mean.begin(), sqr_el_m_mean.end(), 0) / (n - 1.));
}
