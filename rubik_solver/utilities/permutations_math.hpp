#pragma once

inline constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

// Calculate nPk: n!/(n-k)!.
inline constexpr int pick(int n, int k) {
    return factorial(n) / factorial(n - k);
}

// Calculate nCk: n!/((n-k)!*k!).
inline constexpr int choose(int n, int k) {
    return (n < k)
           ? 0
           : factorial(n) / (factorial(n - k) * factorial(k));
}