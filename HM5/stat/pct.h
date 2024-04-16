#ifndef PCT_H
#define PCT_H
#include "statistics.h"
#include <vector>
class  Pct: public IStatistics {
public:
	Pct(double procentile = .5): proc(procentile){};

	virtual void update(double) override;

	virtual double eval() const override;

	inline virtual const char * name() const override {
		return "pct";
	}

private:
	std::vector<double> data;
    double proc;
	void SpecialInsert(double);
};
#endif