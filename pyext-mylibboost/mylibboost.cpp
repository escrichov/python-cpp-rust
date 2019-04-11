#include <iostream>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <stdint.h>
using namespace boost::python;
using namespace std;

void say_hello(const char* name) {
    cout << "Hello " <<  name << "!\n";
}

uint64_t count_byte_doubles(char * str) {
  uint64_t count = 0;
  while (str[0] && str[1]) {
    if (str[0] == str[1]) count++;
    str++;
  }
  return count;
}

BOOST_PYTHON_MODULE(hello)
{
    def("say_hello", say_hello);
    def("count_byte_doubles", count_byte_doubles);
}
