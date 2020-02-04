#include <iostream>
using std::cout;
using std::endl;

enum button
{
	BUTTON_X,
	BUTTON_Y,
	BUTTON_A,
	BUTTON_B
};

bool is_pressed(button b) {return false;}
void jump() {cout << "jump" << endl;}
void fire_gun() {cout << "fire" << endl;}
void swap_weapon() {cout << "swap weapon" << endl;}
void lurch_innefectivity() {cout << "lurch" << endl;}

namespace input_handling_command {

struct command
{
	virtual ~command() {}
	virtual void execute() = 0;
};

struct jump_command : public command
{
	void execute() override {jump();}
};

struct fire_command : public command
{
	void execute() override {fire_gun();}
};

struct swap_weapon_command : public command
{
	void execute() override {swap_weapon();}
};

struct lurch_command : public command
{
	void execute() override {lurch_innefectivity();}
};

class input_handler
{
public:
	void handle_input()
	{
		if (is_pressed(BUTTON_X)) _button_x->execute();
		else if (is_pressed(BUTTON_Y)) _button_y->execute();
		else if (is_pressed(BUTTON_A)) _button_a->execute();
		else if (is_pressed(BUTTON_B)) _button_b->execute();
	}
	
private:
	command * _button_x,
		* _button_y,
		* _button_a,
		* _button_b;
};

}  // input_handling_command

int main(int argc, char * argv[])
{
	return 0;
}
