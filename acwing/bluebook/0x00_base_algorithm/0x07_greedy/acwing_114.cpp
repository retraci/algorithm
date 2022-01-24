#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

const int N = 1010;

int n;
PII va[N];
int idx[N];
vector<int> s, ans;

bool cmp(int a, int b) {
    return va[a].first * va[a].second < va[b].first * va[b].second;
}

vector<int> max_vec(vector<int> a, vector<int> b) {
    if (a.size() > b.size()) return a;
    else return b;

    if (vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend())) return a;
    else return b;
}

vector<int> muilt(vector<int> &a, int b) {
    vector<int> res;
    int tmp = 0;
    for (int i = 0; i < a.size(); i++) {
        tmp += b * a[i];
        res.push_back(tmp % 10);
        tmp /= 10;
    }

    while (tmp) res.push_back(tmp % 10), tmp /= 10;

    return res;
}

vector<int> div(vector<int> &a, int b) {
    vector<int> res;
    int flag = 0;
    int s = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        s = s * 10 + a[i];
        int tmp = s / b;
        if (tmp > 0 || flag) {
            flag = 1;
            res.push_back(tmp);
        }
        s = s % b;
    }

    reverse(res.begin(), res.end());
    return res;
}

void output(vector<int> &a) {
    for (int i = a.size() - 1; ~i; i--) {
        cout << a[i];
    }
    cout << endl;
}

void solve() {
    for (int i = 0; i <= n; i++) idx[i] = i;

    sort(idx + 1, idx + 1 + n, cmp);

    s = vector<int>(1, 1);
    ans = vector<int>(1, 0);
    for (int i = 0; i <= n; i++) {
        int id = idx[i];
        if (i > 0) ans = max_vec(ans, div(s, va[id].second));
        s = muilt(s, va[id].first);
    }

    output(ans);
}

int main() {
    cin >> n;
    for (int i = 0; i <= n; i++) {
        scanf("%d%d", &va[i].first, &va[i].second);
    }
    solve();

    return 0;
}

