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
	
	// methods to bind commands ...
	
private:
	command * _button_x,
		* _button_y,
		* _button_a,
		* _button_b;
};

}  // input_handling_command


namespace command_actors {

class game_actor  // player character
{
public:
	void jump() {}
	void fire_gun() {}
	void swap_weapon() {}
	void lurch_innefectivity() {}
};

struct command
{
	virtual ~command() {}
	virtual void execute(game_actor & actor) = 0;
};

struct jump_command : public command
{
	void execute(game_actor & actor) override {actor.jump();}
};

struct fire_command : public command
{
	void execute(game_actor & actor) override {actor.fire_gun();}
};

struct swap_weapon_command : public command
{
	void execute(game_actor & actor) override {actor.swap_weapon();}
};

struct lurch_command : public command
{
	void execute(game_actor & actor) override {actor.lurch_innefectivity();}
};

class input_handler
{
public:
	command * handle_input()
	{
		if (is_pressed(BUTTON_X)) return _button_x;
		else if (is_pressed(BUTTON_Y)) return _button_y;
		else if (is_pressed(BUTTON_A)) return _button_a;
		else if (is_pressed(BUTTON_B)) return _button_b;
	}
	
private:
	command * _button_x,
		* _button_y,
		* _button_a,
		* _button_b;
};

void execute_command()
{
	input_handler input;
	game_actor player;
	
	command * cmd = input.handle_input();
	if (cmd)
	{
		cmd->execute(player);
	}
	
	// use(actor)
}

}  // command_actors




int main(int argc, char * argv[])
{
	return 0;
}
