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

*TODO: Add more samples from flyweight [examples](https://www.boost.org/doc/libs/1_68_0/libs/flyweight/doc/examples.html).*


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


[DPiM]: https://leanpub.com/design-patterns-modern-cpp/	"Design Patterns in Modern C++"

Adam Hlavatovič
