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

int n, q;
string str;
int f[N];

void solve() {
    str = ' ' + str;
    int ans = 0;
    for (int i = 3; i <= n; i++) {
        if (str[i - 2] == 'a' && str[i - 1] == 'b' && str[i] == 'c') {
            f[i - 2] = f[i - 1] = f[i] = 1;
            ans++;
        }
    }

    while (q--) {
        int pos;
        char ch;
        cin >> pos >> ch;

        if (ch == str[pos]) {
            cout << ans << endl;
            continue;
        }
        if (f[pos]) {
            if (str[pos] == 'a') f[pos + 1] = f[pos + 2] = f[pos] = 0;
            else if (str[pos] == 'b') f[pos] = f[pos - 1] = f[pos + 1] = 0;
            else f[pos] = f[pos - 1] = f[pos - 2] = 0;
            ans--;
        }

        str[pos] = ch;
        for (int j = pos; j <= pos + 2; j++) {
            if (f[j] == 1 || f[j - 1] == 1 || f[j - 2] == 1) continue;

            if (str[j - 2] == 'a' && str[j - 1] == 'b' && str[j] == 'c') {
                f[j - 2] = f[j - 1] = f[j] = 1;
                ans++;
            }
        }

        cout << ans << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    cin >> str;
    solve();

    return 0;
}