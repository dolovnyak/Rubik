#pragma once

#include <cstdio>
#include <cstdint>
#include <utility>
#include "combinatorics_math.hpp"

template<size_t N>
class UnorderedPairSetRankMaker {
public:
     /// Rank the set of pairs in lexicographic order.
     /// Each input set pair must be in ascending order, and there must not be any duplicate numbers amongst the _pairs.
     /// Examples when N is 8:
     /// {0,1}, {2,3}, {4,5}, {6,7} -> 0
     /// {2,3}, {6,7}, {4,5}, {0,1} -> 1259
     /// {2,4}, {0,1}, {3,5}, {6,7} -> 1260
     /// {6,7}, {4,5}, {2,3}, {0,1} -> 2519
     ///
     /// This works by looping over each pair and finding its rank among _pairs that exclude numbers preceding it,
     /// then multiplying each rank by its variable base.
     ///
     /// So for {2,3}, {6,7}, {4,5}, {0,1}:
     /// {2,3} has rank 13.
     /// {6,7} has rank 14 among _pairs excluding 2 and 3.
     /// {4,5} has rank 5 among _pairs excluding 2, 3, 6, and 7.
     /// {0,1} is ignored.
     /// 13*6C2*4C2*2C2 + 14*4C2*2C2 + 5*2C2 = 1259.
    size_t rank(const std::array<std::pair<uint8_t, uint8_t>, N / 2>& set) const {
        size_t rank = 0;

        unsigned remaining_number = N * (N - 1) / 2;
        std::array<std::pair<uint8_t, std::uint8_t>, N * (N - 1) / 2> remaining = _pairs;

        for (unsigned n = 0; n < (N - 2) / 2; ++n) {
            unsigned remaining_index = 0;
            const std::pair<uint8_t, uint8_t>& current_pair = set[n];

            for (unsigned r = 0; r < remaining_number; ++r) {
                const std::pair<uint8_t, uint8_t>& remaining_pair = remaining[r];

                if (current_pair == remaining_pair) {
                    // Found the pair: rank it relative to the remaining pairs, and multiply it by the base for digit n.
                    rank += r * _bases[n];
                } else if (current_pair.first != remaining_pair.first && current_pair.first != remaining_pair.second &&
                           current_pair.second != remaining_pair.first && current_pair.second != remaining_pair.second) {
                    // The pair excludes the numbers in set[n], so keep it in the
                    // list of remaining _pairs for the next digit's rank.
                    remaining[remaining_index] = remaining_pair;
                    ++remaining_index;
                }
            }

            // Number of remaining _pairs.
            remaining_number = remaining_index;
        }

        return rank;
    }


private:
    /// This holds all unordered _pairs of two numbers in the range [0, N] in lexicographic order.
    /// See GeneratePairs.  Storage required follows the triangular number sequence: 1,3,6,10,15,... (1+2+3+4+5+...).
    /// So if N is 8 (8 numbers), 7 _pairs will start with 0,
    /// 6 will start with 1, 5 will start with 2, ..., giving 7+6+5+4+3+2+1=28 _pairs.
    /// N is 8:
    /// {0 1}, {0 2}, ..., {0 7}
    /// {1 2}, {1 3}, ..., {1 7}
    /// ...
    /// {6 7}
    static constexpr std::array<std::pair<uint8_t, uint8_t>, N * (N - 1) / 2> _pairs = [] {
        std::array<std::pair<uint8_t, uint8_t>, N * (N - 1) / 2> pairs{};

        int pairs_index = 0;
        for (size_t i = 1; i < N - 1; ++i) {
            for (size_t j = i - 1; j < N - 2; ++j) {
                pairs[pairs_index].first = j;
                pairs[pairs_index].second = i;
                ++pairs_index;
            }
        }
        return pairs;
    }();

    /// Variable base for each number, for example 6C2*4C2*2C2, 4C2*2C2, 2C2.
    static constexpr std::array<size_t , (N - 2) / 2> _bases = [] {
        /// Pre-computed list of bases for each ranked pair. The last base is 2C2, the second to last base is 4C2*2C2,
        /// then 6C2*4C2*2C2, etc.
        std::array<size_t , (N - 2) / 2> bases{};
        bases[(N - 2) / 2 - 1] = 1; // 2C2.
        for (int i = (N - 2) / 2 - 2; i >= 0; --i) {
            bases[i] = bases[i + 1] * choose<size_t>((N - 2) - 2 * i, 2);
        }
        return bases;
    }();
};
