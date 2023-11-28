#include <iostream>
#include <vector>

using namespace std;

const int MAX_MISSIONARIES = 3;
const int MAX_CANNIBALS = 3;

struct State
{
    int missionariesLeft;
    int cannibalsLeft;
    int boat;
    int missionariesRight;
    int cannibalsRight;
};

bool is_valid(const State &state)
{
    if (state.missionariesLeft < 0 || state.cannibalsLeft < 0 ||
        state.missionariesRight < 0 || state.cannibalsRight < 0)
    {
        return false;
    }
    if ((state.missionariesLeft < state.cannibalsLeft && state.missionariesLeft > 0) ||
        (state.missionariesRight < state.cannibalsRight && state.missionariesRight > 0))
    {
        return false;
    }
    return true;
}

bool is_goal(const State &state)
{
    return state.missionariesLeft == 0 && state.cannibalsLeft == 0;
}

void print_state(const State &state)
{
    cout << "Left: " << state.missionariesLeft << " " << state.cannibalsLeft << "\tright: " << state.missionariesRight << " " << state.cannibalsRight << "\n";
}

void move(State &state, int missionaries, int cannibals)
{
    state.missionariesLeft -= missionaries;
    state.cannibalsLeft -= cannibals;
    state.boat = 1 - state.boat; // Flip the boat side
    state.missionariesRight += missionaries;
    state.cannibalsRight += cannibals;
}

void undo_move(State &state, int missionaries, int cannibals)
{
    state.missionariesRight -= missionaries;
    state.cannibalsRight -= cannibals;
    state.boat = 1 - state.boat; // Flip the boat side
    state.missionariesLeft += missionaries;
    state.cannibalsLeft += cannibals;
}

bool dfs(State &state, vector<State> &path)
{
    if (!is_valid(state))
    {
        return false;
    }

    path.push_back(state);
    if (is_goal(state))
    {
        return true;
    }

    // Generate possible moves
    for (int m = 0; m <= 2; ++m)
    {
        for (int c = 0; c <= 2; ++c)
        {
            if (m + c >= 1 && m + c <= 2)
            {
                if (state.boat == 0)
                {
                    move(state, m, c);
                    if (dfs(state, path))
                    {
                        return true;
                    }
                    undo_move(state, m, c);
                }
                else
                {
                    move(state, m, c);
                    if (dfs(state, path))
                    {
                        return true;
                    }
                    undo_move(state, m, c);
                }
            }
        }
    }

    path.pop_back();
    return false;
}

int main()
{
    State initial_state = {3, 3, 0, 0, 0};
    vector<State> path;

    if (dfs(initial_state, path))
    {
        for (const auto &state : path)
        {
            print_state(state);
        }
    }
    else
    {
        cout << "No solution found.\n";
    }

    return 0;
}
