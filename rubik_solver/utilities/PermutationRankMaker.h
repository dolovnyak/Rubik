#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include <bitset>
#include <iostream>
#include "permutations_math.hpp"

#define MAX_PERMUTATION_N 12
/// This class generate index for permutation of size N picked K ways.
/// max N is 12
template<size_t N, size_t K = N>
class PermutationRankMaker {
public:
    PermutationRankMaker() {
        static_assert(N <= MAX_PERMUTATION_N, "PermutationRankMaker: exceeded max N");

        /// generate ones-count tables.
        for (int i = 0; i < (1 << N) - 1; ++i) {
            std::bitset<N> bits(i);
            this->_ones_count_lookup[i] = bits.count();
        }
    }

    /// Calculate the lexicographic rank (the index) of a permutation in O(n) complexity.
    size_t rank(const std::array<uint8_t, K>& permutation) const {
        /// This will hold the Lehmer code (in a factorial number system).
        std::array<size_t, K> lehmer;

        /// Set of "seen" digits in the permutation.
        std::bitset<N> seen;

        /// The first digit of the Lehmer code is always the first digit of the permutation.
        lehmer[0] = permutation[0];

        /// Mark the digit as seen (bitset uses right-to-left indexing).
        seen[N - 1 - permutation[0]] = 1;

        for (size_t i = 1; i < K; ++i) {
            seen[N - 1 - permutation[i]] = 1;

            // The number of "seen" digits to the left of this digit is the
            // count of ones left of this digit.
            int ones_number = _ones_count_lookup[seen.to_ulong() >> (N - permutation[i])];

            lehmer[i] = permutation[i] - ones_number;
        }

        // Convert the Lehmer code to base-10.
        size_t index = 0;

        for (size_t i = 0; i < K; ++i) {
            index += lehmer[i] * kFactorials[i];
        }

        return index;
    }

private:
    // Precomputed table containing the number of ones in the binary
    // representation of each number.  The largest N-bit number is
    // 2^N-1 = (1 << N) - 1.
    std::array<size_t, (1 << N) - 1> _ones_count_lookup;

    // Precomputed table of kFactorials (or "picks" if N != K).  They're in
    // reverse order.
    static constexpr std::array<int, MAX_PERMUTATION_N> kFactorials = [] {
        std::array<int, MAX_PERMUTATION_N> factorials{};
        for (size_t i = 0; i < K; ++i) {
            factorials[i] = pick(N - 1 - i, K - 1 - i);
        }
        return factorials;
    }();
};
