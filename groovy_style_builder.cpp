/* groovy style builder pattern implementation from [MDP] chapter 2 */
#include <string>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

namespace html {

struct tag
{
	string name,
		text;
	vector<tag> children;
	vector<pair<string, string>> attributes;

	friend ostream & operator<<(ostream & os, tag const & t);
	
protected:
	tag(string const & name, string const & text);
	tag(string const & name, vector<tag> const & children);
};

struct P : tag
{
	explicit P(string const & text)
		: tag{"p", text}
	{}
	
	P(initializer_list<tag> children)
		: tag{"p", children}
	{}
};

struct IMG : tag
{
	explicit IMG(string const & url)
		: tag{"img", ""}
	{
		attributes.emplace_back("src", url);
	}
};

tag::tag(string const & name, string const & text)
	: name{name}, text{text}
{}

tag::tag(string const & name, vector<tag> const & children)
	: name{name}, children{children}
{}

ostream & operator<<(ostream & os, tag const & t)
{
	os << "<" << t.name;
	
	for (auto const & attr : t.attributes)
		os << " " << attr.first << "='" << attr.second << "'";
	
	if (t.children.size() == 0 && t.text.empty())
		os << "/>\n";
	else
	{
		os << ">\n";
		if (!t.text.empty())
			os << t.text << "\n";
		
		for (auto const & child : t.children)
			os << child;
		
		os << "</" << t.name << ">\n";
	}
	
	return os;
}

}  // html


int main(int argc, char * argv[])
{
	using namespace html;
	
	cout << 
	
		P{
			IMG{"http://pokemon.com/pikachu.png"}
		} 
		
		<< "\n";
	
	return 0;
}

