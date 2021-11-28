#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e4 + 10;

int n;
int tt;
string mp1[N];
unordered_map<string, int> mp2;

int du[N];
vector<int> g[N];

void add(int u, int v) {
    g[u].push_back(v);
    du[v]++;
}

int get_id(string x) {
    if (!mp2.count(x)) {
        mp1[++tt] = x;
        mp2[x] = tt;
    }

    return mp2[x];
}

void solve() {
    vector<string> ans;
    queue<int> que;
    for (int i = 1; i <= tt; i++) {
        if (mp1[i] == "@") {
            que.push(i);
            break;
        }
    }
    for (int i = 1; i <= tt; i++) {
        if (du[i] == 0 && mp1[i] != "@") que.push(i);
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();
        ans.push_back(mp1[u]);

        for (auto v : g[u]) {
            if (--du[v] == 0) que.push(v);
        }
    }

    for (string &x : ans) {
        if (x == "@" || x == "#") continue;
        cout << x << " ";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    while (n--) {
        string a, b;
        cin >> a >> b;
        if (a == "#") a = "@";

        int id1 = get_id(a);
        int id2 = get_id(b);
        add(id1, id2);
    }
    solve();

    return 0;
}