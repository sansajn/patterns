/*! tile based game, flyweight design pattern sample from GmPP */
#include <chrono>
#include <iostream>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

static const int SIZE = 128;

high_resolution_clock::time_point start_time;

void start_profile()
{
	start_time = high_resolution_clock::now();
}

void end_profile()
{
	start_time = high_resolution_clock::now();
}

void end_profile(char const * message)
{
	auto dt = high_resolution_clock::now() - start_time;
	printf("%s: %ldus\n", message, duration_cast<microseconds>(dt).count());
}

int pick_tile(int x, int y)
{
	return (x*7 + y*13) % 4;
}

namespace tile_enum {
	
enum tile
{
	TILE_GRASS = 0,
	TILE_FOREST,
	TILE_MOUNTAIN,
	TILE_WATER
};

struct world
{
	tile tiles[SIZE * SIZE];
	
	world()
	{
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				tiles[y*SIZE + x] = (tile)pick_tile(x, y);
	}
	
	int add_tiles()
	{
		int sum = 0;
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				switch (tiles[y*SIZE + x])
				{
					case TILE_GRASS: sum += 1; break;
					case TILE_FOREST: sum += 2; break;
					case TILE_MOUNTAIN: sum += 3; break;
					case TILE_WATER: sum += 4; break;
				}
		return sum;
	}
};

}  // tile_enum

namespace tile_byte {

enum tile
{
	TILE_GRASS = 0,
	TILE_FOREST,
	TILE_MOUNTAIN,
	TILE_WATER
};

struct world
{
	unsigned char tiles[SIZE * SIZE];
	
	world()
	{
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				tiles[y*SIZE + x] = (tile)pick_tile(x, y);
	}
	
	int add_tiles()
	{
		int sum = 0;
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				switch (tiles[y*SIZE + x])
				{
					case TILE_GRASS: sum += 1; break;
					case TILE_FOREST: sum += 2; break;
					case TILE_MOUNTAIN: sum += 3; break;
					case TILE_WATER: sum += 4; break;
				}
		return sum;
	}
};

	
}  // tile_byte


namespace tile_field {

struct tile
{
	int weight;
};

struct world
{
	tile tile_types[4];
	tile * tiles[SIZE * SIZE];

	world()
	{
		tile_types[0].weight = 1;
		tile_types[1].weight = 2;
		tile_types[2].weight = 3;
		tile_types[3].weight = 4;
		
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				tiles[y*SIZE + x] = &tile_types[pick_tile(x, y)];
	}
	
	int add_tiles()
	{
		int sum = 0;
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				sum += tiles[y*SIZE + x]->weight;
		return sum;
	}
};
	
}  // tile_field

namespace tile_virtual {

struct tile
{
	virtual int weight() = 0;
};

struct grass_tile : public tile
{
	int weight() override {return 1;}
};

struct forest_tile : public tile
{
	int weight() override {return 2;}
};

struct mountine_tile : public tile
{
	int weight() override {return 3;}
};

struct water_tile : public tile
{
	int weight() override {return 4;}
};

struct world
{
	grass_tile grass;
	forest_tile forest;
	mountine_tile mountain;
	water_tile water;
	tile * tile_types[4];
	tile * tiles[SIZE * SIZE];
	
	world()
	{
		tile_types[0] = &grass;
		tile_types[1] = &forest;
		tile_types[2] = &mountain;
		tile_types[3] = &water;
		
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				tiles[y*SIZE + x] = tile_types[pick_tile(x, y)];
	}
	
	int add_tiles()
	{
		int sum = 0;
		for (int y = 0; y < SIZE; ++y)
			for (int x = 0; x < SIZE; ++x)
				sum += tiles[y*SIZE + x]->weight();
		return sum;
	}
};

}  // tile_virtual


int main(int argc, char * argv[])
{
	for (int i = 0; i < 1; ++i)
	{
		{
			tile_enum::world world;
			start_profile();
			int sum = world.add_tiles();
			end_profile("tile enum");
			printf("%d\n", sum);
		}
		
		{
			tile_byte::world world;
			start_profile();
			int sum = world.add_tiles();
			end_profile("tile byte");
			printf("%d\n", sum);
		}
		
		{
			tile_field::world world;
			start_profile();
			int sum = world.add_tiles();
			end_profile("tile field");
			printf("%d\n", sum);
		}
		
		{
			tile_virtual::world world;
			start_profile();
			int sum = world.add_tiles();
			end_profile("tile virtual");
			printf("%d\n", sum);
		}
	}
	return 0;
}
