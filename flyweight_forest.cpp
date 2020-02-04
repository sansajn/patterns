/* forest renderer flyweight design pattern sample from [GmPP], chapter 3 */

namespace flyweight {

class mesh {};
class skeleton {};
class texture {};
class pose {};
class vector {};
class color {};

static const int WIDTH = 1024,
	HEIGHT = 1024;
	
static texture GRASS_TEXTURE,
	HILL_TEXTURE,
	RIVER_TEXTURE;
	
int random(int max) {return 0;}

	namespace heavy_tree {

class tree
{
private:
	mesh _model;
	texture _bark,
		_leaves;
	vector _position;
	double _height,
		_thickness;
	color _bark_tint,
		_leaf_tint;
};
		
};  // heavy_tree

	namespace split_tree {

class tree_model
{
private:
	mesh _model;
	texture _bark,
		_leaves;
};

class tree
{
private:
	tree_model * _model;
	vector _position;
	double _height,
		_thickness;
	color _bark_tint,
		_leaf_tint;
};
		
	}  // split_tree


}  // flyweight


int main(int argc, char * argv[])
{
	return 0;
}

