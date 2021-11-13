#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <deque>
#include <bitset>

using namespace std;

#define ll long long

const int N = 4000 * 4 + 10;

string P, x;
unordered_map<char, string> mp;
char X[N];
int tt;

void init() {
    mp['0'] = "0000", mp['1'] = "0001", mp['2'] = "0010", mp['3'] = "0011";
    mp['4'] = "0100", mp['5'] = "0101", mp['6'] = "0110", mp['7'] = "0111";
    mp['8'] = "1000", mp['9'] = "1001", mp['A'] = "1010", mp['B'] = "1011";
    mp['C'] = "1100", mp['D'] = "1101", mp['E'] = "1110", mp['F'] = "1111";
}

void solve() {
    tt = 0;
    for (char ch : x) {
        for (char a : mp[ch]) X[tt++] = a;
    }
    for (int i = 0; i < P.size() - 1; i++) X[tt++] = '0';

    ll p = 0;
    for (int i = 0; i < P.size(); i++) p = (p << 1) + P[i] - '0';

    int start = 0;
    while (start < tt && X[start] == '0') start++;

    ll lim = 1LL << (P.size() - 1);
    ll cur = 0;
    int id = start;
    while (id < tt) {
        while (id < tt && cur < lim) cur = (cur << 1) + X[id++] - '0';
        if (cur < lim) break;

        cur ^= p;
    }

    string ans = "";
    while (cur) {
        ans += (cur & 1) + '0';
        cur >>= 1;
    }
    int c0 = P.size() - 1 - ans.size();
    if (c0 < 0) cout << "sbyl" << endl;
    while (c0--) ans += "0";
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    init();

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> P >> x;
        solve();
    }

    return 0;
}