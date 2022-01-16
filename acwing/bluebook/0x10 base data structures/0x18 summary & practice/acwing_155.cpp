#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <queue>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int n;
set<pii> mem;
priority_queue<pii, vector<pii>, greater<>> edts;
queue<pii> que;
int cnt, ti;

bool mac(int t, int m, int p) {
    for (auto it1 = mem.begin(); it1 != mem.end(); it1++) {
        auto it2 = next(it1);
        if (it1 == mem.end()) break;

        int start = it1->first + it1->second;
        int rem = it2->first - start;
        if (rem >= m) {
            mem.insert({start, m});
            edts.push({t + p, start});
            return true;
        }
    }

    return false;
}

void work(int t) {
    while (!edts.empty() && edts.top().first <= t) {
        int cur = edts.top().first;
        while (!edts.empty() && edts.top().first == cur) {
            auto [_, start] = edts.top(); edts.pop();
            auto it = mem.lower_bound({start, 0});
            mem.erase(it);
        }
        ti = max(ti, cur);

        while (!que.empty()) {
            auto [m, p] = que.front();
            if (!mac(cur, m, p)) break;
            que.pop();
        }
    }
}

void solve() {
    mem.insert({-1, 1});
    mem.insert({n, 1});

    int t, m, p;
    while (cin >> t >> m >> p, t || m || p) {
        work(t);
        if (!mac(t, m, p)) {
            que.push({m, p});
            cnt++;
        }
    }

    work(2e9);
    cout << ti << '\n';
    cout << cnt << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    solve();

    return 0;
}