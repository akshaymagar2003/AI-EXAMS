#include <iostream>
#include <vector>
#include <queue>
#include <set>

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

struct StateComparator
{
    bool operator()(const State &a, const State &b) const
    {
        if (a.missionariesLeft != b.missionariesLeft)
            return a.missionariesLeft < b.missionariesLeft;
        if (a.cannibalsLeft != b.cannibalsLeft)
            return a.cannibalsLeft < b.cannibalsLeft;
        if (a.boat != b.boat)
            return a.boat < b.boat;
        if (a.missionariesRight != b.missionariesRight)
            return a.missionariesRight < b.missionariesRight;
        return a.cannibalsRight < b.cannibalsRight;
    }
};

bool bfs(State &initial_state)
{
    queue<State> q;
    set<State, StateComparator> visited;

    q.push(initial_state);
    visited.insert(initial_state);

    while (!q.empty())
    {
        State current_state = q.front();
        q.pop();

        print_state(current_state);

        if (is_goal(current_state))
        {
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
                        q.push(next_state);
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
