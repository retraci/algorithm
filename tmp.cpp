#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 2000, M = 60;

int n;
vector<pair<int, PII>> routes;
int bus[M];

bool is_route(int a, int d)
{
    for (int i = a; i < 60; i += d)
        if (!bus[i])
            return false;
    return true;
}

bool dfs(int depth, int u, int sum, int start)
{
    if (u == depth) return sum == n;

    for (int i = start; i < routes.size(); i ++ )
    {
        auto r = routes[i];
        if (routes[i].first * (depth - u) + sum < n) return false;
        int a = r.second.first, d = r.second.second;
        if (!is_route(a, d)) continue;
        for (int j = a; j < 60; j += d) bus[j] -- ;
        if (dfs(depth, u + 1, sum + r.first, i)) return true;
        for (int j = a; j < 60; j += d) bus[j] ++ ;
    }


    return false;
}

int main()
{
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
    {
        int t;
        scanf("%d", &t);
        bus[t] ++ ;
    }

    for (int i = 0; i < 60; i ++ )
        for (int j = i + 1; i + j < 60; j ++ )
            if (is_route(i, j))
                routes.push_back({(59 - i) / j + 1, {i, j}});

    sort(routes.begin(), routes.end(), greater<pair<int, PII>>());
    for (auto &[c, p] : routes) {
        auto &[s, d] = p;
        cout << c << " " << s << " " << d << "\n";
    }


    int depth = 0;
    while (!dfs(depth, 0, 0, 0)) depth ++ ;

    printf("%d\n", depth);
    return 0;
}