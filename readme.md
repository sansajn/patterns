# about

repository contains design patterns sample implementations from various sources like [DPiM], ...

## build

[SCons](https://scons.org/) software construction tool is used to build samples, so just fire

```bash
scons -j8
```

command from patterns directory and you're done.

# samples

## structural patterns

### flyweight

`flyweight.cpp`: custom flyweight (`user` class) design pattern implementation compared with `boost::flyweight` (`user2` class) implementation from [DPiM], chapter 11

`flyweight_tiles.cpp`: Tile based world implented using flyweight design pattern (bare pointer without any magic) from [GmPP], chapter 3. There are three basic implementations there 1) enum based (`tile_enum` and `tile_byte`), 2) object based (`tile_field`) and 3) object hierarchy based (`tile_virtual`).

`flyweight_forest.cpp`: Tree representation for forest renderer flyweight design pattern sample from [GmPP], chapter 3. Class `heavy_tree::tree` splited into to classes `split_tree::tree_model` and `split_tree::tree` where `tree_mode` it is our *flyweight*. 

*TODO: Add more flyweight pattern boost [samples](https://www.boost.org/doc/libs/1_68_0/libs/flyweight/doc/examples.html).*


### proxy

`lazybitmap.cpp`: lazy loaded bitmap as a sample for (virtual) proxy design pattern from [DPiM], chapter 12


## creational patterns

### builder

`simple_builder.cpp`: simple builder design pattern implementation from [DPiM], chapter 2, pg. 28

`groovy_style_builder.cpp`: groovy style DSL like builder design patter implementation from [DPiM], chapter 2, pg. 30

`composite_builder.cpp`: multiple composition builder design pattern implementation from [DPiM], chapter 2, pg. 31


## behavioural patterns

### template method

`board_game.cpp`: generic board game algorithm and inheritance based chess implementation as sample for template method design pattern from [DPiM], chapter 23

`operation_solver.cpp`: math, list operation solving algorithm sample implemented using template method design pattern


[DPiM]: https://leanpub.com/design-patterns-modern-cpp/	"Design Patterns in Modern C++"

[GmPP]: https://gameprogrammingpatterns.com/	"Game Programming Patterns"

[HoDP]: https://www.packtpub.com/application-development/hands-design-patterns-c	"Hands-On Design Patterns with C++"

[CwMC]: http://leanpub.com/concurrencywithmodernc	"Concurrency with Modern C++"

[PTBB]: https://www.apress.com/gp/book/9781484243978	"Pro TBB"

[FPiC]: https://www.manning.com/books/functional-programming-in-c-plus-plus	"Functional Programming in C++"


Adam Hlavatovič
