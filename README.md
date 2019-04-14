# Creme

Creme is a widget-based GUI library for games and other interactive software.
Its widgets are rendered using a tileset, allowing you to change the
looks of your application by simply changing your tileset.

One major feature of Creme is its anchoring system provided through its custom
`cm_value` structure. It allows you to express position and size
in terms of other areas. As such, anchoring the *left* edge of `widget_1`
to the *right* edge of `widget_2` automatically updates `widget_1`'s *left*
value whenever `widget_2`'s *right* value changes. It is similar (inspired,
actually) to Qt's QML anchoring system.

Creme is non-intrusive in regards to your rendering system: instead
of risking harming your rendering state, it provides a list of basic commands
that you can interpret and render when and how you want.

Creme never allocates memory by itself (and never frees them as well). This
might sound harsh but the benefits are greater than the hurdle:
you will retain full control of your memory, allowing
you to use whatever allocation strategy is best for your platform.

It is written in plain C90, ensuring high compatibility with many systems and
platforms.

**Features**

- Looks of your application can be easily changed
- Your GUI is as beautiful as your tileset
- Anchoring makes really easy to position widgets
- Treats your memory with respect
- Clean and straightforward API
- Render technology agnostic

## Running examples

if you wish to build and run examples, you will need to clone this repository
and also update its submodules.

```
git clone git@github.com:mobius3/creme.git
cd creme.git
git submodule update --init
```

You also need to run CMake with flags `CREME_BUILD_EXTRAS`
and `CREME_BUILD_EXAMPLES`:

```
mkdir build && cd build
cmake .. -DCREME_BUILD_EXTRAS=1 -DCREME_BUILD_EXAMPLES=1
cmake --build .
```

Examples will be inside the `bin/` folder.