#include <iostream>
#include <type_traits>

#include <string>
#include <vector>
#include <list>
#include <tuple>

#include "tuple.h"


template<typename T,
    typename = typename std::enable_if<std::is_integral<T>::value, void>::type>
void print_ip(T ip) 
{
    int bytes[sizeof(T)];
    
    for(size_t i = sizeof(T); i > 0;) {
        bytes[--i] = static_cast<uint8_t>(ip & 0xff);
        ip >>= 8;
    }

    std::cout << "integral:  ";
    std::cout << bytes[0];
    for(size_t i = 1; i < sizeof(T); ++i) {
        std::cout << "." << bytes[i];
    }
    std::cout << std::endl;
}


template<typename T, 
    typename = 
        decltype(cbegin(std::declval<T>()), cend(std::declval<T>()), void())
>
void print_ip(const T& ip) 
{
    std::cout << "container: ";
    auto cit = ip.cbegin();
    std::cout << *cit;
    for(++cit; cit != ip.cend(); ++cit) {
        std::cout << "." << *cit;
    }
    std::cout << std::endl;
}


template<>
void print_ip<std::string>(const std::string& ip) 
{
    std::cout << "string:    "<< ip << std::endl;
}


template<typename T, typename ...Args>
void print_ip(const std::tuple<T, Args...>& ip)
{
    const std::size_t last = sizeof...(Args);
    std::size_t index = 0;

    auto put = [&index](const T& t) { 
        std::cout << t;
        if(index++ != last) std::cout << ".";
    };

    std::cout << "tuple:     ";
    tuple::for_each(ip, put);
    std::cout << std::endl;
}


int main() 
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));

    std::string str("10.0.0.1");
    print_ip(str);

    std::vector<int> vec = {192, 168, 1, 0};
    print_ip(vec);
    
    std::list<const char*> list = {"172", "16", "28", "255"};
    print_ip(list);

    auto tuple1 = std::make_tuple("128");
    auto tuple4 = std::make_tuple(192, 168, 0, 28);
    print_ip(tuple1);
    print_ip(tuple4);
}
