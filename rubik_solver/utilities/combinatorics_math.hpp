#pragma once

template <class T>
inline constexpr size_t factorial(T n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

// Calculate nPk: n!/(n-k)!.
template <class T>
inline constexpr size_t pick(T n, T k) {
    return factorial(n) / factorial(n - k);
}

// Calculate nCk: n!/((n-k)!*k!).
template <class T>
inline constexpr size_t choose(T n, T k) {
    return (n < k)
           ? 0
           : factorial(n) / (factorial(n - k) * factorial(k));
}