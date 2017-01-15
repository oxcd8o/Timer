# Timer

## Basic usage
It's as simple as this:
```c++
#include <timer.h>

Timer timer;
/* Do some work */
std::cout << "Elapsed: " << timer << std::endl;
```
It will display elapsed time in predefined format like this:
```
Elapsed: 1.738110s
```

## More complex usage
You may get integer amount of microseconds if you pass integer template parameter to function `as<T>()`:
```c++
auto microseconds_int = timer.as<int>();
auto microseconds_uint64_t = timer.as<uint64_t>();
auto microseconds_long_long = limer.as<long long>();
```
Or floating point amount of seconfs if you pass floating point template argument:
```c++
auto seconds_float = timer.as<float>();
auto seconds_double = timer.as<double>();
```
Or even string representation in predefined format (used in `operator<<`):
```c++
auto seconds_string = timer.as<std::string>();
```

## Pro usage
If you want the timer to show elapsed time with specific precision, then you may specify it explicitly:
```c++
auto nanoseconds = timer.as<int, std::chrono::nanoseconds>();
```
Note, that attempt to specify precision with std::string as representation type will lead to compilation error. If you want some arbitrary stringification, you must write it yourself.

## Raw data
If methods above are too inflexible for you, you may get raw `std::chrono::duration` and use is as you wish:
```c++
auto time_point = timer.raw();
```
Or you may get `std::chrono::time_point` representing timer start time:
```c++
const auto& start = timer.start();
```
