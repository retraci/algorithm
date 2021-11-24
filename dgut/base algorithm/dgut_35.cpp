#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n;
string s1 = "*3+1=", s2 = "/2=";

void solve() {
    while (n != 1) {
        if (n & 1) {
            cout << n << s1;
            n = n * 3 + 1;
            cout << n << endl;
        } else {
            cout << n << s2;
            n /= 2;
            cout << n << endl;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    solve();

    return 0;
}