#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e5 + 10;

int n;
int va[N];

void solve() {
    set<PII> ts;
    ts.insert({va[1], 1});
    for (int i = 2; i <= n; i++) {
        auto it = ts.lower_bound({va[i], i});
        auto ret = it;
        int tmp = 0x3f3f3f3f;
        if (it != ts.end()) {
            if (abs(it->first - va[i]) < tmp) {
                ret = it;
                tmp = abs(it->first - va[i]);
            }
        }
        while (it != ts.begin()) {
            --it;
            if (abs(it->first - va[i]) <= tmp) {
                ret = it;
                tmp = abs(it->first - va[i]);
            } else {
                break;
            }
        }

        cout << tmp << " " << ret->second << endl;

        ts.insert({va[i], i});
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}