#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pai;

void printpath(map<pai, pai> mp, pai u)
{
    if (u.first == 0 && u.second == 0)
    {
        cout << 0 << " " << 0 << endl;
        return;
    }
    printpath(mp, mp[u]);
    cout << u.first << " " << u.second << endl;
}

bool DFS(int a, int b, int target, map<pai, int> &m, map<pai, pai> &mp, pai u)
{
    if (u.first == target || u.second == target)
    {
        printpath(mp, u);
        if (u.first == target)
        {
            if (u.second != 0)
                cout << u.first << " " << 0 << endl;
        }
        else
        {
            if (u.first != 0)
                cout << 0 << " " << u.second << endl;
        }
        return true;
    }

    m[{u.first, u.second}] = 1;

    bool found = false;

    if (!found && m[{a, u.second}] != 1)
    {
        mp[{a, u.second}] = u;
        found = DFS(a, b, target, m, mp, {a, u.second});
    }

    if (!found && m[{u.first, b}] != 1)
    {
        mp[{u.first, b}] = u;
        found = DFS(a, b, target, m, mp, {u.first, b});
    }

    if (!found)
    {
        int d = b - u.second;
        if (u.first >= d)
        {
            int c = u.first - d;
            if (m[{c, b}] != 1)
            {
                mp[{c, b}] = u;
                found = DFS(a, b, target, m, mp, {c, b});
            }
        }
        else
        {
            int c = u.first + u.second;
            if (m[{0, c}] != 1)
            {
                mp[{0, c}] = u;
                found = DFS(a, b, target, m, mp, {0, c});
            }
        }
        // if first one is empty

        d = a - u.first;
        if (u.second >= d)
        {
            int c = u.second - d;
            if (m[{a, c}] != 1)
            {
                mp[{a, c}] = u;
                found = DFS(a, b, target, m, mp, {a, c});
            }
        }
        else
        {
            int c = u.first + u.second;
            if (m[{c, 0}] != 1)
            {
                mp[{c, 0}] = u;
                found = DFS(a, b, target, m, mp, {c, 0});
            }
        }
    }
    if (!found && m[{u.first, 0}] != 1)
    {
        mp[{u.first, 0}] = u;
        found = DFS(a, b, target, m, mp, {u.first, 0});
    }

    if (!found && m[{0, u.second}] != 1)
    {
        mp[{0, u.second}] = u;
        found = DFS(a, b, target, m, mp, {0, u.second});
    }

    return found;
}

int main()
{
    int Jug1 = 4, Jug2 = 3, target = 2;
    cout << "Path from initial state to solution state ::\n";

    map<pai, int> m;
    map<pai, pai> mp;
    pai initial_state = make_pair(0, 0);

    if (!DFS(Jug1, Jug2, target, m, mp, initial_state))
        cout << "No solution";

    return 0;
}
