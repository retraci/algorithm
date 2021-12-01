#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e5 + 10;

int n;
string str;
int va[N];
int nex[N];

void solve() {
    for (int i = 1; i <= n; i++) va[i] = str[i - 1] - '0';

    int last = n + 1;
    for (int i = n; i >= 1; i--) {
        nex[i] = last;
        if (va[i] != 1) last = i;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int sum = 1;
        for (int j = i; j <= n && sum <= n; j = nex[j]) {
            int rb = nex[j] - 1;
            sum *= va[j];
            if (sum >= j - i + 1 && sum <= rb - i + 1) ans++;
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> str;
    solve();

    return 0;
}