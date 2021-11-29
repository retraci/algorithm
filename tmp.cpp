#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e5 + 10;

int arr[5];

struct Node {
    int id;
    bool operator<(const Node &that) const {
        return arr[id] > arr[that.id];
    }
};

void solve() {
    set<Node> st;
    st.insert({1});
    st.insert({2});
    st.insert({3});

    arr[1] = 100;
    arr[2] = 200;
    st.insert({2});
    cout << (*st.begin()).id;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();

    return 0;
}