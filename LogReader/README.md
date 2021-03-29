This is an excersize to implement Log Reader functionality which allows to retrieve lines from a specified file
containing specified filter.

**The solution was intentionally implemented without C++11 (and higher) and STL features according to the requirements.**

It's the cross-platform project which is developed for Linux/Windows operating systems.
By default, the LogReader library is compiled as DLL. It's allowed to build it as a static library by running of the
following CMake command:
```sh
cmake -DLOG_READER_STATIC=ON
```
Or by setting of the following CMake option to ON within the main `CMakeLists.txt` file:
```sh
option (LOG_READER_STATIC "Link LogReader as static library" OFF)
```

I've implemented naive algorithm to find lines containing a pre-set filter. As first we are reading a specified file
line-by-line. Then, we analyze the filter per each symbol and check supported symbols (`*`, `?`, substrings). When a
substring is read from the filter its existance is checked within the read line.

> **NOTE:** Currently I've decided to not implement automatic tests becuase it's not clear how it will be working
within the requirements for this excercize (no STL, no C++11, no exceptions and so on). So, I've decided to focus
on manual testing only.

To run the sample please execute the following command from the `bin` folder:
```sh
log_reader_sample.exe -file <path_to_the_file> -filter <desired_filter>
```
For example:
```sh
log_reader_sample.exe -file "D:\\test.txt" -filter "*zabcedfg*???1zy"
```
> **NOTE:** The demo is designed with pre-defined line length (1000 symbols) which is used to put read lines (matching
specified filter) from a file. If the resulting line is longer then it's just concatenated but still returned to the user.
But generally, it's up to a further user to handle it.