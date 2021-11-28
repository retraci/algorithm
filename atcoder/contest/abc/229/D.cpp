#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

string str;
int K;

void solve() {
    int ans = 0;
    int left = 0;
    for (int right = 0; right < str.size(); right++) {
        if (str[right] == '.') K--;
        while (K < 0) {
            if (str[left] == '.') K++;
            left++;
        }
        ans = max(ans, right - left + 1);
    }

    cout << ans << endl;
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