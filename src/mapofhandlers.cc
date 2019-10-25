#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include <exception>
#include <functional>
#include <boost/core/demangle.hpp>

template<typename T, typename U=std::string>
using map_to_handler = std::map<std::string, 
                                std::function<U(T*)>>;
struct AB {
 std::string p = {"345"};
} abinst;

std::string get_AB_p (AB*b) {
  return b->p;
}

main()
{
    map_to_handler<AB> mab;
    mab["p"] = [](AB*t)->std::string{return t->p;} ;
    char input[33] ;
    const char* s = std::fgets(input,sizeof(input),stdin);
    if (!s) return 1;
    if (char* p = std::strstr(input,"\n")) { *p = 0; }
    std::string sg;
    try {
        auto func = mab.at(input);
        sg = func(&abinst);
        std::cout<< sg <<" was returned\n";
    }
    catch (std::out_of_range &error) {
        std::cerr<< "could not find it\n";
    }
    return 0;
}
