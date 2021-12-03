#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

string s;

void solve() {
    string t = "";
    for (int i = 0; i < 100; i++) t += "oxx";

    int n = t.size(), sz = s.size();
    for (int i = 0; i + sz <= n; i++) {
        string tmp = t.substr(i, sz);
        if (tmp == s) {
            cout << "Yes" << "\n";
            return;
        }
    }
    cout << "No" << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s;
    solve();

    return 0;
}