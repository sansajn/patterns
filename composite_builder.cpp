/* composite builder design pattern implementation from [MDP] chapter 2 */
#include <string>
#include <iostream>
using namespace std;

class person_builder;
class person_address_builder;
class person_job_builder;

class person
{
	
public:
	static person_builder create();
	person(person && other);
	person & operator=(person && other);
	~person() {cout << "person destroyed\n";}
	friend ostream & operator<<(ostream & os, person const & p);
	
private:
	person() {cout << "person created\n";}

	// address
	string street_address,
		post_code,
		city;
		
	// employment
	string company_name,
		position;
	int annual_income = 0;
	
	friend person_builder; 
	friend person_address_builder;
	friend person_job_builder;
};

class person_builder_base
{
public:
	operator person() const {return move(_person);}
	person_address_builder lives() const;
	person_job_builder works() const;
	
protected:
	explicit person_builder_base(person & p) : _person(p) {}
	
	person & _person;
};

class person_builder : public person_builder_base
{
public:
	person_builder() : person_builder_base{_person} {}
	
private:
	person _person;
};

class person_address_builder : public person_builder_base
{
public:
	using self = person_address_builder;
	
	explicit person_address_builder(person & p);
	self & at(string street_address);
	self & with_postcode(string post_code);
	self & in(string city);
};

class person_job_builder : public person_builder_base
{
public:
	using self = person_job_builder;
	
	explicit person_job_builder(person & p);
	self & at(string company_name);
	self & as_a(string position);
	self & earning(int annual_income);
};


int main(int argc, char * argv[])
{
	person p = person::create()
		.lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
		.works().at("PragmaSoft").as_a("Consultant").earning(10e6);
	
	cout << p << "\n"
		<< "done!\n";
		
	return 0;
}


person::person(person && other)
	: street_address{move(other.street_address)}
	, post_code{move(other.post_code)}
	, city{move(other.city)}
	, company_name{move(other.company_name)}
	, position{move(other.position)}
	, annual_income{move(other.annual_income)}
{
	cout << "person move created\n";
}

person & person::operator=(person && other)
{
	cout << "person moved\n";
	
	if (this == &other)
		return *this;
	
	street_address = move(other.street_address);
	post_code = move(other.post_code);
	city = move(other.city);
	company_name = move(other.company_name);
	position = move(other.position);
	annual_income = other.annual_income;
	return *this;
}
	
ostream & operator<<(ostream & os, person const & p)
{
	return os << "street_address: " << p.street_address
		<< " post_code: " << p.post_code
		<< " city: " << p.city
		<< " company_name: " << p.company_name
		<< " position: " << p.position
		<< " annual_income: " << p.annual_income;
}

person_builder person::create()
{
	return person_builder{};
}

person_address_builder person_builder_base::lives() const
{
	return person_address_builder{_person};
}

person_job_builder person_builder_base::works() const
{
	return person_job_builder{_person};
}

person_address_builder::person_address_builder(person & p)
	: person_builder_base{p}
{}
	
person_address_builder::self & person_address_builder::at(string street_address)
{
	_person.street_address = street_address;
	return *this;
}
	
person_address_builder::self & person_address_builder::with_postcode(string post_code)
{
	_person.post_code = post_code;
	return *this;
}

person_address_builder::self & person_address_builder::in(string city)
{
	_person.city = city;
	return *this;
}

person_job_builder::person_job_builder(person & p)
	: person_builder_base{p}
{}
	
person_job_builder::self & person_job_builder::at(string company_name)
{
	_person.company_name = company_name;
	return *this;
}

person_job_builder::self & person_job_builder::as_a(string position)
{
	_person.position = position;
	return *this;
}

person_job_builder::self & person_job_builder::earning(int annual_income)
{
	_person.annual_income = annual_income;
	return *this;
}
