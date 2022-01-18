#include "CornerDB.hpp"

size_t CornerDB::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<uint8_t, kCornersNumber> corners_start_permutation = {
            cube.GetCornerIndex(Cube::Corner::ULB),
            cube.GetCornerIndex(Cube::Corner::URB),
            cube.GetCornerIndex(Cube::Corner::URF),
            cube.GetCornerIndex(Cube::Corner::ULF),
            cube.GetCornerIndex(Cube::Corner::DLF),
            cube.GetCornerIndex(Cube::Corner::DLB),
            cube.GetCornerIndex(Cube::Corner::DRB),
            cube.GetCornerIndex(Cube::Corner::DRF)
    };

    // Compute the Lehmer code using Korf's linear algorithm.  It's discussed
    // in his paper, Large-Scale Parallel Breadth-First Search
    // (https://www.aaai.org/Papers/AAAI/2005/AAAI05-219.pdf).
    //
    // "We scan the permutation from left to right, constructing a bit string
    // of length n, indicating which elements of the permutation we've seen
    // so far. Initially the string is all zeros. As each element of the
    // permutation is encountered, we use it as an index into the bit string
    // and set the corresponding bit to one. When we encounter element k in
    // the permutation, to determine the number of elements less than k to
    // its left, we need to know the number of ones in the first k bits of
    // our bit string. We extract the first k bits by right shifting the
    // string by n − k. This reduces the problem to: given a bit string,
    // count the number of one bits in it.
    // We solve this problem in constant time by using the bit string as an
    // index into a precomputed table, containing the number of ones in the
    // binary representation of each index."
    size_t rank = this->permutation_rank_maker.rank(corners_start_permutation);

    /// Now get the orientation of the corners.
    /// 7 corner orientations dictate the orientation of the 8th, so only 7 need to be stored.
    std::array<uint8_t, 7> corners_start_orientation = {
            cube.GetCornerOrientation(Cube::Corner::ULB),
            cube.GetCornerOrientation(Cube::Corner::URB),
            cube.GetCornerOrientation(Cube::Corner::URF),
            cube.GetCornerOrientation(Cube::Corner::ULF),
            cube.GetCornerOrientation(Cube::Corner::DLF),
            cube.GetCornerOrientation(Cube::Corner::DLB),
            cube.GetCornerOrientation(Cube::Corner::DRB)
    };

    // Treat the orientations as a base-3 number, and convert it to base-10.
    size_t corners_orientation_to_number =
            corners_start_orientation[0] * 729 +
            corners_start_orientation[1] * 243 +
            corners_start_orientation[2] * 81 +
            corners_start_orientation[3] * 27 +
            corners_start_orientation[4] * 9 +
            corners_start_orientation[5] * 3 +
            corners_start_orientation[6];

    /// Combine the permutation and orientation into a single index. p * 3^7 + o;
    return rank * 2187 + corners_orientation_to_number;
}
