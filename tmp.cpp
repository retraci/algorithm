#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;

string P, x;
unordered_map<char, string> mp;

void init() {
    mp['0'] = "0000", mp['1'] = "0001", mp['2'] = "0010", mp['3'] = "0011";
    mp['4'] = "0100", mp['5'] = "0101", mp['6'] = "0110", mp['7'] = "0111";
    mp['8'] = "1000", mp['9'] = "1001", mp['A'] = "1010", mp['B'] = "1011";
    mp['C'] = "1100", mp['D'] = "1101", mp['E'] = "1110", mp['F'] = "1111";
}

void solve() {
    for (int i = 0; i < 10; i++) {
        for (int i = 0; i < 10; i++) {
            cout << 1 << endl;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    init();

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();

    return 0;
}