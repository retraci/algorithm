#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct Node {
    int p;
    string s;
    int id;
};

const int N = 1010;

int n;
Node va[N];

bool check(string s) {
    int cnt[11] = {0};
    for (char ch : s) {
        cnt[ch - '0']++;
    }
    return cnt[0] >= 1 && cnt[1] >= 1 && cnt[2] >= 2;
}

void solve() {
    sort(va + 1, va + n + 1, [&](auto &a, auto &b) {
        return a.p < b.p;
    });

    for (int i = 1; i <= n; i++) {
        if (check(va[i].s)) {
            cout << va[i].id << endl;
            return;
        }
    }
    cout << 0 << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int p;
        string s;
        cin >> p >> s;
        va[i] = {p, s, i};
    }
    solve();

    return 0;
}