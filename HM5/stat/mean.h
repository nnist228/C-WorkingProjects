#ifndef MEAN_H
#define MEAN_H
#include "statistics.h"
#include <limits>
#include <numeric>
#include <vector>
class Mean : public IStatistics {
public:
	Mean() = default;

	inline virtual void update(double next) override {
		data.push_back(std::move(next));
	}

	inline virtual double eval() const override {
		double sum = std::accumulate(data.begin(), data.end(), 0);
		return (sum / (double) data.size());
	}

	inline virtual const char * name() const override {
		return "mean";
	}

private:
	std::vector<double> data;
};
#endif