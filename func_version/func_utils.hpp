#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <functional>

// Some functional programming utilities
// Applies a function to each element of a container
template <typename T, typename F>
void map(F f, T& object) {
    for (typename T::iterator it = object.begin(); it != object.end(); ++it)
        f(*it, it - object.begin());
}

// Filters-out the elements that don't meet F condition
template <typename T, typename F>
T filter(F f, T& object) {
    T result;

    for (typename T::iterator it = object.begin(); it != object.end(); ++it)
        if (f(*it))
            result.append(*it);

    return result;
}

// Or fold, pretty useful
template <typename T, typename F, typename G>
G reduce(F f, T& object, G initializer = 0) {
    G result = initializer;

    for (typename T::iterator it = object.begin(); it != object.end(); ++it)
        result = f(result, *it, it - object.begin());  // Passing the index
                                                       // might be useful
    return result;
}

#endif  // UTILS_HPP_
