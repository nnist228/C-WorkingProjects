#ifndef MAX_H
#define MAX_H
#include "statistics.h"
#include <limits>
class Max : public IStatistics {
public:
	Max():m_max{std::numeric_limits<double>::lowest()} {
	}

	inline virtual void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	inline virtual double eval() const  override {
		return m_max;
	}

	inline virtual const char * name() const override {
		return "max";
	}


private:
	double m_max;
};
#endif