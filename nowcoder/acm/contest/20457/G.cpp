#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

ll x, y;

void solve() {
    vector<int> va, vb;
    while (x) va.push_back(x & 1), x >>= 1;
    while (y) vb.push_back(y & 1), y >>= 1;
    while (vb.size() < va.size()) vb.push_back(0);

    cout << 2 << endl;
    ll num = 0;
    for (int i = va.size() - 1; i >= 0; i--) {
        num <<= 1;
        num += 1 ^ va[i];
    }
    cout << num << " ";

    num = 0;
    for (int i = vb.size() - 1; i >= 0; i--) {
        num <<= 1;
        num += 1 ^ vb[i];
    }
    cout << num << " ";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> x >> y;
    solve();

    return 0;
}