#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

string str;

void solve() {
    int flag = 0;
    for (char ch : str) {
        if (!(ch & 1)) flag = 1;
    }
    if (!flag) {
        cout << -1 << endl;
        return;
    }

    if (!(str.back() & 1)) {
        cout << 0 << endl;
    } else if (!(str.front() & 1)) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }
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
        cin >> str;
        solve();
    }

    return 0;
}