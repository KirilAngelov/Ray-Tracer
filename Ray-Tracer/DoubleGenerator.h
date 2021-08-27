#pragma once
#include <functional>
#include <random>

class DoubleGenerator
{
public:
	DoubleGenerator(double low, double high, std::random_device& rd) :
		r(std::bind(std::uniform_real_distribution<>(low, high), std::default_random_engine(rd()))) 
	{
	};

	double operator()() 
	{
		return r();
	}

private:
	std::function<double()> r;
};

