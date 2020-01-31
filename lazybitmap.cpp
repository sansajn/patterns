/* lazy loaded bitmap as (virtual) proxy design pattern sample from MDP, chapter 12 */ 
#include <string>
#include <memory>
#include <iostream>

using std::string;
using std::unique_ptr;
using std::make_unique;
using std::cout;

class image 
{
public:
	virtual void draw() const = 0;
};

class bitmap : public image
{
public:
	bitmap(string const & file_name)
	{
		cout << "laoding image from '" << file_name << "'\n";
	}
	
	void draw() const override
	{
		cout << "drawing image\n";
	}
};

class lazy_bitmap : public image
{
public:
	lazy_bitmap(string const & file_name)
		: _file_name{file_name}
	{}
	
	void draw() const override
	{
		if (!_bmp)
			_bmp = make_unique<bitmap>(_file_name);
		
		_bmp->draw();
	}
	
private:
	string _file_name;
	mutable unique_ptr<bitmap> _bmp;
};

void draw_image(image & img)
{
	cout << "about to draw the image\n";
	img.draw();
	cout << "done drawing the image\n";
}

int main(int argc, char * argv[])
{
	lazy_bitmap bmp{"pokemon.jpg"};
	draw_image(bmp);
	cout << "done!\n";
	return 0;
}
