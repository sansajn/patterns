/* generic board game algorithm and inheritance based chess implementation as sample for template method design pattern from [DPiM], chapter 23 */
#include <string>
#include <iostream>
using namespace std;

class game
{
public:
	explicit game(int number_of_players)
		: _current_player{0}
		, _number_fo_players{number_of_players}
	{}
	
	void run()
	{
		start();
		while (!have_winner())
			take_turn();
		cout << "player " << get_winner() << " wins\n";
	}
	
protected:
	virtual void start() {}
	virtual bool have_winner() = 0;
	virtual void take_turn() {}
	virtual int get_winner() = 0;
	
	int _current_player,
		_number_fo_players;
};

class chess : public game
{
public:
	explicit chess()
		: game{2}
		, _turns{0}
		, _max_turns{10}
	{}
	
protected:
	void start() override;
	bool have_winner() override;
	void take_turn() override;
	int get_winner() override;
	
private:
	int _turns,
		_max_turns;
};


int main(int argc, char * argv[])
{
	chess g;
	g.run();
	cout  << "done\n";
	return 0;
}

void chess::start()
{
	cout << "starting a game of chess with " << _number_fo_players << " players\n";
}

bool chess::have_winner()
{
	return _turns == _max_turns;
}

void chess::take_turn()
{
	cout << "turn " << _turns << " taken by player " << _current_player << "\n";
}

int chess::get_winner()
{
	return _current_player;
}
