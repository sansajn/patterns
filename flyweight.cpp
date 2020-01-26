/* custom flyweight design pattern implementation (\c user) compared with boost::flyweight implementation from [MDP] chapter 11 */
#include <string>
#include <iostream>
#include <cstdint>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
using namespace std;
using namespace boost;
using namespace flyweights;

using key = uint32_t;

struct user
{
	user(string const & first_name, string const & last_name)
		: first_name{add(first_name)}, last_name{add(last_name)}
	{}
	
	string const & get_first_name() const
	{
		return names.left.find(first_name)->second;
	}
	
	string const & get_last_name() const
	{
		return names.left.find(last_name)->second;
	}
	
	static void info()
	{
		for (auto const & entry : names.left)
			cout << "key=" << entry.first << ", value=" << entry.second << "\n";
	}
	
	friend ostream & operator<<(ostream & os, user const & u)
	{
		return os
			<< "first_name=" << u.first_name << " " << u.get_first_name()
			<< " last_name=" << u.last_name << " " << u.get_last_name();
	}
	
protected:
	static bimap<key, string> names;
	static key seed;
	
	static key add(string const & name)
	{
		auto it = names.right.find(name);
		if (it != names.right.end())
			return it->second;
		else  // add it
		{
			key id = ++seed;
			names.insert({seed, name});
			return id;
		}
	}
	
	key first_name, last_name;
};

key user::seed = 0;
bimap<key, string> user::names{};

void naive_flyweight()
{
	user john_doe{"John", "Doe"},
		jane_doe{"Jane", "Doe"};
	
	cout << "John " << john_doe << "\n"
		<< "Jane " << jane_doe << "\n";

	user::info();
}


// boost::flyweight user implementation

struct user2
{
	flyweight<string> first_name, last_name;
	
	user2(string const & first_name, string const & last_name)
		: first_name{first_name}, last_name{last_name}
	{}
};

void boost_flyweight()
{
	user2 john_doe{"John", "Doe"},
		jane_doe{"Jane", "Doe"};
		
	cout << boolalpha
		<< (&john_doe.first_name.get() == &jane_doe.first_name.get()) << "\n"
		<< (&john_doe.last_name.get() == &jane_doe.last_name.get()) << "\n";
}

int main(int argc, char * argv[])
{
	naive_flyweight();
	boost_flyweight();
	return 0;
}
