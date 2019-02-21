#include <tuple>

namespace tuple
{

template<std::size_t INDEX, typename Callback, typename ...Args>
struct _for_each
{
    static void next(const std::tuple<Args...>& tuple, Callback callback)
    {
        const std::size_t last = sizeof...(Args) - 1;
        const std::size_t index = last - INDEX;

        callback(std::get<index>(tuple));

        _for_each<INDEX - 1, Callback, Args...>
            ::next(tuple, callback);
    }
};


template<typename Callback, typename ...Args>
struct _for_each<0, Callback, Args...>
{  
    static void next(const std::tuple<Args...>& tuple, Callback callback)
    {
        const std::size_t last = sizeof...(Args) - 1;
        callback(std::get<last>(tuple));
    }
};


template<typename Callback, typename ...Args>
void for_each(const std::tuple<Args...>& tuple, Callback callback)
{
    const size_t size = sizeof...(Args);
    _for_each<size - 1, Callback, Args...>::next(tuple, callback);
}

} // tuple