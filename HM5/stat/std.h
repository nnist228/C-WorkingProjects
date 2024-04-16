#ifndef STD_H
#define STD_H
#include "statistics.h"
#include <vector>
class Std : public IStatistics {
public:
	Std() = default;

	inline virtual void update(double next) override {
		data.push_back(std::move(next));
	}

	virtual double eval() const override;

	inline virtual const char * name() const override {
		return "pct";
	}

private:
	std::vector<double> data;
};
#endif