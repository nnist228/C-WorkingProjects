#ifndef MIN_H
#define MIN_H
#include "statistics.h"
#include <limits>
class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	inline virtual void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	inline virtual double eval() const override {
		return m_min;
	}

	inline virtual const char * name() const override {
		return "min";
	}

private:
	double m_min;
};
#endif