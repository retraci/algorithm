#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2510;

typedef pair<int, int> PII;

int n, m;
PII cs[N];
PII fs[N];

void solve() {
    sort(cs, cs+n);
    sort(fs, fs+m);

    int ans = 0;
    for (int i = n - 1; ~i; i--) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (fs[j].second <= 0) continue;
            if (fs[j].first >= cs[i].first && fs[j].first <= cs[i].second) {
                idx = j;
            }
        }
        if (idx == -1) continue;
        fs[idx].second--;
        ans++;
    }

    cout << ans << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> cs[i].first >> cs[i].second;
    }
    for (int i = 0; i < m; i++) {
        cin >> fs[i].first >> fs[i].second;
    }
    solve();

    return 0;
}

