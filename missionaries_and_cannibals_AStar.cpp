#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>

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
    int depth;     // Cost function: depth of the current state
    int heuristic; // Heuristic function: Manhattan distance to the goal state
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

int manhattan_distance(const State &a, const State &b)
{
    return abs(a.missionariesLeft - b.missionariesLeft) +
           abs(a.cannibalsLeft - b.cannibalsLeft) +
           abs(a.missionariesRight - b.missionariesRight) +
           abs(a.cannibalsRight - b.cannibalsRight);
}

struct CompareStates
{
    bool operator()(const State &a, const State &b) const
    {
        // f(n) = g(n) + h(n)
        int f_a = a.depth + a.heuristic;
        int f_b = b.depth + b.heuristic;
        return f_a > f_b; // Priority queue is a max heap, so we use > to make it act like a min heap
    }
};

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

bool a_star(State &initial_state)
{
    priority_queue<State, vector<State>, CompareStates> pq;
    set<State, StateComparator> visited;
    vector<State> path;

    initial_state.depth = 0;
    initial_state.heuristic = manhattan_distance(initial_state, State{0, 0, 0, 3, 3});

    pq.push(initial_state);
    visited.insert(initial_state);

    while (!pq.empty())
    {
        State current_state = pq.top();
        pq.pop();

        path.push_back(current_state);

        if (is_goal(current_state))
        {
            // Print the entire sequence of states
            for (const auto &state : path)
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

                    next_state.depth = current_state.depth + 1;
                    next_state.heuristic = manhattan_distance(next_state, State{0, 0, 0, 3, 3});

                    if (is_valid(next_state) && visited.find(next_state) == visited.end())
                    {
                        pq.push(next_state);
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

    if (!a_star(initial_state))
    {
        cout << "No solution found.\n";
    }

    return 0;
}
