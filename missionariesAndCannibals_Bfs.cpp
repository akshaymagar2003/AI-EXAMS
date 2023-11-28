#include <bits/stdc++.h>

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

bool operator==(const State &a, const State &b)
{
    return a.missionariesLeft == b.missionariesLeft &&
           a.cannibalsLeft == b.cannibalsLeft &&
           a.boat == b.boat &&
           a.missionariesRight == b.missionariesRight &&
           a.cannibalsRight == b.cannibalsRight;
}

namespace std
{
    template <>
    struct hash<State>
    {
        size_t operator()(const State &s) const
        {
            return hash<int>()(s.missionariesLeft) ^
                   hash<int>()(s.cannibalsLeft) ^
                   hash<int>()(s.boat) ^
                   hash<int>()(s.missionariesRight) ^
                   hash<int>()(s.cannibalsRight);
        }
    };
}

bool bfs(State &initial_state)
{
    queue<vector<State>> q;
    unordered_set<State> visited;

    q.push({initial_state});
    visited.insert(initial_state);

    while (!q.empty())
    {
        vector<State> current_path = q.front();
        State current_state = current_path.back();
        q.pop();

        if (is_goal(current_state))
        {
            for (const auto &state : current_path)
            {
                print_state(state);
            }
            return true;
        }

        for (int m = 0; m <= 2; ++m)
        {
            for (int c = 0; c <= 2; ++c)
            {
                if (m + c >= 1 && m + c <= 2)
                {
                    State next_state = current_state;
                    if (current_state.boat == 0)
                    {
                        next_state.missionariesLeft -= m;
                        next_state.cannibalsLeft -= c;
                        next_state.boat = 1;
                        next_state.missionariesRight += m;
                        next_state.cannibalsRight += c;
                    }
                    else
                    {
                        next_state.missionariesRight -= m;
                        next_state.cannibalsRight -= c;
                        next_state.boat = 0;
                        next_state.missionariesLeft += m;
                        next_state.cannibalsLeft += c;
                    }

                    if (is_valid(next_state) && visited.find(next_state) == visited.end())
                    {
                        vector<State> next_path = current_path;
                        next_path.push_back(next_state);
                        q.push(next_path);
                        visited.insert(next_state);
                    }
                }
            }
        }
    }

    return false;
}

int main()
{
    State initial_state = {3, 3, 0, 0, 0};

    if (!bfs(initial_state))
    {
        cout << "No solution found.\n";
    }

    return 0;
}
