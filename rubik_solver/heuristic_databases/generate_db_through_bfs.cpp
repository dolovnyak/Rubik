#include "generate_db_through_bfs.hpp"

void generate_db_through_bfs(HeuristicDB *db) {
    if (db->IsFull()) {
        throw std::logic_error("call db generate on full db");
    }

    /// default cube constructor has solved cube, so first not visited cube is solved cube.
    Cube solved_state;
    db->SetMovesNumberByState(solved_state, 0);

    std::queue<StateWithDepth> not_visited_states;
    not_visited_states.emplace(solved_state, 0);
    if (db->IsFull()) { return; }

    while (!not_visited_states.empty()) {
        StateWithDepth current_state = not_visited_states.front();
        not_visited_states.pop();

        for (auto rotation : kAllRotations) {
            Cube new_cube_state = Cube::Rotate(current_state.cube, rotation);
            if (db->IsMovesNumbersBetter(new_cube_state, current_state.depth + 1)) {
                db->SetMovesNumberByState(new_cube_state, current_state.depth + 1);
                not_visited_states.emplace(new_cube_state, current_state.depth + 1);
            }
        }
        if (db->IsFull()) { return; }
    }

    throw std::logic_error("Nodes are empty but db doesn't full.\n"
                           "Filled db elements: " + std::to_string(db->GetFilledNumber()));
}