#pragma once

#include <cstdio>
#include <array>
#include "combinatorics_math.hpp"

template<size_t N, size_t K>
class CombinationRankMaker {
public:
    size_t rank(const std::array<uint8_t, K> combination) const {
        // https://www.dcode.fr/combination-rank
        // "With c_i elements in increasing order c_1, c_2, ..., c_k of a
        // combination of k elements among n the total number of elements, the
        // formula for calculating rank without listing all combinations is:
        // (nCk) - ((n-c_1)Ck) - ((n-c_2)C(k-1))-...-((n-c_k)C1)"
        //
        // That assumes 1-based combinations with ranks starting at 1, so each
        // element in the combination has 1 added to it, and the end result has 1
        // subtracted from it to make the rank 0-based.
        size_t rank = _choices[N][K];

        for (size_t i = 0; i < K; ++i) {
            rank -= _choices[N - (combination[i] + 1)][K - i];
        }
        return rank - 1;
    }

private:
    static constexpr std::array<std::array<size_t, K + 1>, N + 1> _choices = [] {
        std::array<std::array<size_t, K + 1>, N + 1> choices{};
        for (size_t n = 0; n <= N; ++n) {
            for (size_t k = 0; k <= K; ++k) {
                choices[n][k] = choose(n, k);
            }
        }
        return choices;
    }();
};