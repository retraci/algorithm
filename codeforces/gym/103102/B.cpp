#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 1e6 + 10;

string s;
int vs[N];

ll get_sum() {
    for (int i = 1; i <= s.size(); i++) {
        vs[i] = vs[i - 1] + s[i - 1] - '0';
    }

    ll res = 0;
    for (int i = 1; i <= s.size(); i++) {
        if (s[i - 1] == '0') res += vs[i - 1];
    }

    return res;
}

void solve()  {
    ll sum = get_sum();

    cout << (sum % 3 != 0 ? "Alice" : "Bob") << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s;
    solve();

    return 0;
}