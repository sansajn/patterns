# about

repository contains design patterns sample implementations from various sources like [mdp], ...

## build

[SCons](https://scons.org/) is used as a build tool, so to build samples just fire

```bash
scons -j8
```

command from patterns directory.

### builder

`simple_builder.cpp`: simple builder design pattern implementation from [mdp], chapter 2, pg. 28

`groovy_style_builder.cpp`: groovy style DSL like builder design patter implementation from [mdp], chapter 2, pg. 30

`composite_builder.cpp`: multiple composition builder design pattern implementation from [mdp], chapter 2, pg. 31

[mdp]: https://leanpub.com/design-patterns-modern-cpp/	"Design Patterns in Modern C++"

Adam Hlavatovič
