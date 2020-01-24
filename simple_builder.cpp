/* simple builder implementation of builder design pattern */
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <sstream>
#include <iostream>
using namespace std;

struct html_builder;

struct html_element
{
	string name,
		text;
	vector<html_element> elements;
	
	html_element() {}
	html_element(string const & name, string const & text);
	string str(int indent = 0) const;
	static html_builder builder(string root_name);
	static unique_ptr<html_builder> builder_ptr(string root_name);  //!< also -> semantic is possible

	size_t const indent_size = 2;
};

struct html_builder
{
	html_builder(string root_name);
	html_builder & add_child(string child_name, string child_text);
	html_builder * add_child_ptr(string child_name, string child_text);  //!< also -> semantic is possible
	string str() const {return root.str();}
	operator html_element() const {return root;}
	
	html_element root;
};

html_element::html_element(string const & name, string const & text)
	: name{name}, text{text}
{}

string html_element::str(int indent) const
{
	string i(indent*indent_size, ' ');
	
	ostringstream oss;
	oss << i << "<" << name << ">" << "\n";
	if (text.size() > 0)
		oss << string((indent+1)*indent_size, ' ') << text << "\n";
	
	for (auto const & e : elements)
		oss << e.str(indent + 1);
	
	oss << i << "</" << name << ">\n";
	return oss.str();
}

html_builder html_element::builder(string root_name)
{
	return move(html_builder{root_name});
}

unique_ptr<html_builder> html_element::builder_ptr(string root_name)
{
	return make_unique<html_builder>(root_name);
}

html_builder::html_builder(string root_name)
{
	root.name = root_name;
}

html_builder & html_builder::add_child(string child_name, string child_text)
{
	root.elements.emplace_back(child_name, child_text);
	return *this;
}

html_builder * html_builder::add_child_ptr(string child_name, string child_text)
{
	root.elements.emplace_back(child_name, child_text);
	return this;
}

int main(int argc, char * argv[])
{
	// build using builder directly
	html_builder builder{"ul"};
	builder.add_child("li", "hello").add_child("li", "world");
	cout << "builder=" << builder.str() << "\n";
	
	// but we can ommit builder at all
	html_element root = html_element::builder("ul")
		.add_child("li", "hello")
		.add_child("li", "world");
	
	cout << "root=" << root.str() << "\n";
	
	// also -> semantic API can be used for building
	html_element root2 = *html_element::builder_ptr("ul")
		->add_child_ptr("li", "hello")
		->add_child_ptr("li", "hello");
		
	cout << "root2=" << root2.str() << "\n";
	
	cout << "done\n";

	 return 0;
}
