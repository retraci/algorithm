#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
string str;

void solve() {
    int p1 = 0, p2 = n - 1;
    int mc = 0, tc = 0;
    while (p1 < n) {
        if (str[p1] == 'T') {
            if (mc) break;
        }
        if (str[p1] == 'M') mc++;
        p1++;
    }

    while (p2) {
        if (str[p2] == 'M') {
            if (tc) break;
        }
        if (str[p2] == 'T') tc++;
        p2--;
    }

    cout << str.substr(p1 + 1, p2 - p1 - 1) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> str;
    solve();

    return 0;
}