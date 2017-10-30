#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <time.h>

class Variable
{
public:
	bool manual;
	double value;
	time_t ontime;
	time_t offtime;
	time_t runtime;
	time_t update;
public:
	Variable(void);
public:
	double& GetValue(void);
	void SetValueAuto(double &v);
	void SetValueManual(double &v);
	time_t OnTime(void);
	time_t OffTime(void);
	time_t Runtime(void);
	void SetRuntime(time_t t);
};

#endif//__VARIABLE_H__
