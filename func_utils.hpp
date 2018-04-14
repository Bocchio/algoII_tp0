#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <functional>

// // Some functional programming utilities
// // Function pointer, container
// template <typename T, typename F>
// // Maps function to a container that supports iterators
// void map(F f, T& object) {
//     for (typename T::iterator it = object.begin(); it != object.end(); ++it)
//         f(*it);
// }

// // Index version, can't use typename F again in C++98
// template <typename T, typename G>
// void map(void (f)(G, size_t), T& object) {
//     for (typename T::iterator it = object.begin(); it != object.end(); ++it)
//         f(*it, it - object.begin());
// }

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

// // Or fold, pretty useful
// template <typename T, typename G>
// G reduce(std::function<G(G, G)> f, T& object, G initializer = 0) {
//     G result = initializer;

//     for (typename T::iterator it = object.begin(); it != object.end(); ++it)
//         result = f(result, *it);

//     return result;
// }

// Index version
template <typename T, typename F, typename G>
G reduce(F f, T& object, G initializer = 0) {
    G result = initializer;

    for (typename T::iterator it = object.begin(); it != object.end(); ++it)
        result = f(result, *it, it - object.begin());  // Passing the index
                                                       // might be useful
    return result;
}

#endif  // UTILS_HPP_
