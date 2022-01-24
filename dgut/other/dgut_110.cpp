#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e6 + 10;

vector<ll> va;

void solve() {
    sort(va.begin(), va.end());

    for (int i = 0; i < 4; i++) cout << va[i] << " ";
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ll tmp;
    while (cin >> tmp) {
        va.push_back(tmp);
    }
    solve();

    return 0;
}