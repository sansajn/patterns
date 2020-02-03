/* math, list operation solving algorithm sample implemented using template method design pattern */
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;

class operation
{
public:
	using arguments = map<string, string>;
	
	bool solve(arguments const & input, arguments & output)
	{
		if (!read_input(input))
			return false;
		
		if (!operate())
			return false;
		
		return write_output(output);
	}
	
	virtual ~operation() {}
	
protected:
	virtual bool read_input(arguments const & input) = 0;
	virtual bool operate() = 0;
	virtual bool write_output(arguments & output) = 0;
};

class math_operation : public operation
{
public:
	math_operation();
	
private:
	bool read_input(arguments const & input) override;
	bool operate() override;
	bool write_output (arguments & output) override;
	
	int _a, 
		_b, 
		_result;
	
	char _operation;
};

class list_operation : public operation
{
private:
	bool read_input(arguments const & input) override;
	bool operate() override;
	bool write_output(arguments & output) override;
	
	list<int> _arr;
};

int main(int argc, char * argv[])
{
	map<string, string> in, out;
	
	// 10+20=30
	in.emplace("a", "10");
	in.emplace("b", "30");
	in.emplace("operation", "+");
	math_operation a;
	a.solve(in, out);
	cout << "a result=" << out["result"] << "\n";  // 40
	
	in.clear();
	out.clear();
	
	// 1 2 3 4 5 -> 5 4 3 2 1
	in.emplace("array", "1 2 3 4 5");
	list_operation b;
	b.solve(in, out);
	cout << "b result=" << out["result"] << "\n";  // 5 4 3 2 1
	
	return 0;
}

math_operation::math_operation()
	: _a{0}, _b{0}, _result{0}, _operation{0}
{}

bool math_operation::read_input(arguments const & input)
{
	arguments::const_iterator ait = input.find("a");
	if (ait == input.end())
		return false;
	
	_a = lexical_cast<int>(ait->second);

	arguments::const_iterator bit = input.find("b");
	if (bit == input.end())
		return false;
	
	_b = lexical_cast<int>(bit->second);
	
	arguments::const_iterator oit = input.find("operation");
	if (oit == input.end())
		return false;
	
	_operation = oit->second[0];
	
	return true;
}

bool math_operation::operate()
{
	switch (_operation)
	{
		case '+': _result = _a + _b; 
			return true;
			
		case '-': _result = _a - _b;
			return true;
			
		case '*': _result = _a * _b;
			return true;
			
		case '/': 
			if (_b == 0) 
				return false;
			_result = _a / _b;
			return true;
			
		default:
			return false;
	}
}

bool math_operation::write_output(arguments & output)
{
	return output.emplace("result", to_string(_result))
		.second;
}

bool list_operation::read_input(arguments const & input)
{
	_arr.clear();
	
	arguments::const_iterator it = input.find("array");
	if (it == input.end())
		return false;
	
	using iter = istream_iterator<int>;
	istringstream in{it->second};
	copy(iter{in}, iter{}, back_inserter(_arr));
	
	return in.eof();
}

bool list_operation::operate()
{
	_arr.reverse();
	return true;
}

bool list_operation::write_output(arguments & output)
{
	ostringstream out;
	copy(begin(_arr), end(_arr), ostream_iterator<int>(out, " "));
	return output.emplace("result", out.str())
		.second;
}
