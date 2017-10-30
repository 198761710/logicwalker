#include <math.h>
#include <stdlib.h>
#include "variable.h"


Variable::Variable(void)
{
	value  = 0.0;
	manual = false;
	update = time_t(0);
	ontime = time_t(0);
	offtime= time(0);
	runtime= time_t(0);
}
double& Variable::GetValue(void)
{
	return value;
}
void Variable::SetValueAuto(double &v)
{
	if( manual )
	{
		return;
	}
	SetValueManual(v);
}
void Variable::SetValueManual(double &v)
{
	value = v;
	update = time(0);
	if( value >= 0.9999 || value <= -0.9999 )
	{
		if( time_t(0) == ontime )
		{
			ontime = update;
		}
		offtime = time_t(0);
	}
	else
	{
		if( time_t(0) == offtime )
		{
			offtime = update;
		}
		if( time_t(0) != ontime )
		{
			runtime += labs(update - ontime);
			ontime = time_t(0);
		}
	}
}
time_t Variable::OnTime(void)
{
	if( fabs(value) >= 0.9999 )
	{
		return labs(time(0) - ontime);
	}
	return time_t(0);
}
time_t Variable::OffTime(void)
{
	if( fabs(value) < 0.9999 )
	{
		return labs(time(0) - offtime);
	}
	return time_t(0);
}
time_t Variable::Runtime(void)
{
	return runtime + OnTime();
}
void Variable::SetRuntime(time_t t)
{
	runtime = t;
}
