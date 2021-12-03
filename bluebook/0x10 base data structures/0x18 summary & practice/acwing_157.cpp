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

string s1, s2;

string dfs(string &s, int &u) {
    vector<string> sons;
    u++;
    while (s[u] == '0') sons.push_back(dfs(s, u));
    u++;

    sort(sons.begin(), sons.end());
    string res = "";
    for (auto so : sons) res += so;
    return '0' + res + '1';
}

void solve() {
    s1 = '0' + s1 + '1';
    s2 = '0' + s2 + '1';

    int u1 = 0, u2 = 0;
    if (dfs(s1, u1) == dfs(s2, u2)) cout << "same" << "\n";
    else cout << "different" << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> s1 >> s2;
        solve();
    }

    return 0;
}