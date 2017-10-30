#ifndef __TOKEN_H__
#define __TOKEN_H__
#include <string>
using namespace std;

class Variable;
class Token
{
public:
	signed type;
	double value;
	string name;
	Variable *var;
public:
	Token(void);
	Token(signed t, const string& n);
public:
	void SetContext(class Context&);
	void SetVariable(class Variable&);
	const double& GetValue(void);
	bool SetValue(const double&);
	bool SetValueAuto(const double&);
	bool SetValueManual(const double&);
	const time_t OnTime(void);
	const time_t OffTime(void);
	const time_t GetRuntime(void);
	void SetRuntime(const time_t t);
private:
	void TokenValue(void);
};
#endif//__TOKEN_H__
