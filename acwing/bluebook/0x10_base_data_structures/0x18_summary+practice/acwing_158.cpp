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

int n;
string s1, s2;

string get(string &s) {
    int i = 0, j = 1;

    while (i < n && j < n) {
        int k = 0;
        while (k < n && s[i + k] == s[j + k]) k++;
        if (s[i + k] > s[j + k]) i = i + k + 1;
        else j = j + k + 1;
        if (i == j) j++;
    }

    int pos = min(i, j);
    return s.substr(pos, n);
}

void solve() {
    n = s1.size();
    s1 += s1, s2 += s2;

    s1 = get(s1), s2 = get(s2);

    if (s1 != s2) {
        cout << "No" << "\n";
        return;
    }
    cout << "Yes" << "\n";
    cout << s1 << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s1 >> s2;
    solve();

    return 0;
}