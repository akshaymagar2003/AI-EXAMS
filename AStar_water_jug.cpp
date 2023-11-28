#include <bits/stdc++.h>

using namespace std;

struct State
{
    int x, y;            // Current state of the jugs
    int cost;            // Cost of reaching this state
    int heuristic;       // Heuristic value for A* algorithm
    vector<string> path; // Sequence of actions to reach this state

    State(int _x, int _y, int _cost, int _heuristic, const vector<string> &_path)
    {
        x = _x;
        y = _y;
        cost = _cost;
        heuristic = _heuristic;
        path = _path;
    }
    // Define a comparison operator for the priority queue
};

// Function to print the path of actions
void printPath(const vector<string> &path)
{
    for (const auto &action : path)
    {
        cout << action << endl;
    }
}
bool isValid(int x, int y, int xLimit, int yLimit)
{
    return (x >= 0 && y >= 0 && x <= xLimit && y <= yLimit);
}
struct StateComparator
{
    bool operator()(const State &a, const State &b) const
    {
        return (a.cost + a.heuristic) > (b.cost + b.heuristic);
    }
};
// Function to perform A* search for the water jug problem
void solveWaterJug(int xLimit, int yLimit, int target)
{
    priority_queue<State, vector<State>, StateComparator> pq; // Min heap for A* algorithm
    map<pair<int, int>, int> costMap;                         // Map to store the cost of reaching a state

    // Starting state (both jugs are empty)
    State start(0, 0, 0, target, {});

    pq.push(start);
    costMap[{0, 0}] = 0;

    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();

        // Goal check
        if (current.x == target || current.y == target)
        {
            cout << "Solution found! Minimum cost: " << current.cost << endl;
            cout << "Path:" << endl;
            printPath(current.path);
            return;
        }

        // Generate next states
        vector<State> nextStates;

        // Fill jug 1
        // Fill jug 1
        nextStates.push_back(State(xLimit, current.y, current.cost + 1, target - current.x, current.path));

        nextStates.back().path.push_back("Fill jug 1");

        // Fill jug 2
        nextStates.push_back(State(current.x, yLimit, current.cost + 1, target - current.y, current.path));
        nextStates.back().path.push_back("Fill jug 2");

        // Empty jug 1
        nextStates.push_back(State(0, current.y, current.cost + 1, target - current.x, current.path));
        nextStates.back().path.push_back("Empty jug 1");

        // Empty jug 2
        nextStates.push_back(State(current.x, 0, current.cost + 1, target - current.y, current.path));
        nextStates.back().path.push_back("Empty jug 2");

        // Pour water from jug 1 to jug 2
        int pour1_x = max(0, current.x - (yLimit - current.y));
        int pour1_y = min(yLimit, current.y + current.x);
        int pour1_cost = current.cost + 1;
        int pour1_heuristic = target - (current.x - max(0, current.x - (yLimit - current.y)));
        vector<string> pour1_path = current.path;
        pour1_path.push_back("Pour water from jug 1 to jug 2");
        nextStates.push_back(State(pour1_x, pour1_y, pour1_cost, pour1_heuristic, pour1_path));

        // Pour water from jug 2 to jug 1
        int pour2_x = min(xLimit, current.x + current.y);
        int pour2_y = max(0, current.y - (xLimit - current.x));
        int pour2_cost = current.cost + 1;
        int pour2_heuristic = target - (current.y - max(0, current.y - (xLimit - current.x)));
        vector<string> pour2_path = current.path;
        pour2_path.push_back("Pour water from jug 2 to jug 1");
        nextStates.push_back(State(pour2_x, pour2_y, pour2_cost, pour2_heuristic, pour2_path));

        for (const auto &nextState : nextStates)
        {
            if (isValid(nextState.x, nextState.y, xLimit, yLimit))
            {
                int newCost = current.cost + 1;
                if (costMap.find({nextState.x, nextState.y}) == costMap.end() || newCost < costMap[{nextState.x, nextState.y}])
                {
                    costMap[{nextState.x, nextState.y}] = newCost;
                    pq.push(nextState);
                }
            }
        }
    }

    // No solution found
    cout << "No solution exists." << endl;
}

int main()
{
    int xLimit, yLimit, target;

    cout << "Enter the capacity of jug 1: ";
    cin >> xLimit;

    cout << "Enter the capacity of jug 2: ";
    cin >> yLimit;

    cout << "Enter the target amount: ";
    cin >> target;

    solveWaterJug(xLimit, yLimit, target);

    return 0;
}
