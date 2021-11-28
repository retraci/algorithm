#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

string str;
int K;
map<string, int> mp1;
map<int, string> mp2;

void init() {
    mp1["January"] = 0;
    mp1["February"] = 1;
    mp1["March"] = 2;
    mp1["April"] = 3;
    mp1["May"] = 4;
    mp1["June"] = 5;
    mp1["July"] = 6;
    mp1["August"] = 7;
    mp1["September"] = 8;
    mp1["October"] = 9;
    mp1["November"] = 10;
    mp1["December"] = 11;

    for (auto [a, b] : mp1) {
        mp2[b] = a;
    }
}

void solve() {
    init();

    int cur = mp1[str];
    cur = (cur + K) % 12;
    cout << mp2[cur] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> str >> K;
    solve();

    return 0;
}