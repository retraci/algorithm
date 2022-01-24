// 绿化
/*

*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mid (left+(right-left) / 2)
#define lson ((node<<1) + 1)
#define rson ((node<<1) + 2)

struct Node {
	int left, right, sum, lz;
	Node(int l_, int r_, int s_, int lz_) {
		left = l_, right = r_, sum = s_, lz = lz_;
	}
};

const int maxn = 5e5+5;

int n, m;
vector<Node> tree;

void push_up(int node) {
	tree[node].sum = tree[lson].sum + tree[rson].sum;
}

void push_down(int node) {
	if(tree[node].lz) {
		tree[lson].sum += tree[node].lz;
		tree[rson].sum += tree[node].lz;
		tree[lson].lz = tree[node].lz;
		tree[rson].lz = tree[node].lz;
		tree[node].lz = 0;
	}
}

void build(int node, int left, int right) {
	tree[node].left = left;
	tree[node].right = right;
	tree[node].sum = tree[node].lz = 0;

	if(left == right) return;

	build(lson, left, mid);
	build(rson, mid+1, right);
}

void update(int node, int L, int R, int val) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right<L || left>R) return;
	if(L<=left && right<=R) {
		tree[node].sum += val;
		tree[node].lz += val;
		return;
	}

	push_down(node);
	update(lson, L, R, val);
	update(rson, L, R, val);
	push_up(node);
}

int query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right < L || left > R) return 0;
	if(L <= left && right <= R) {
		return tree[node].sum;
	}
	
	push_down(node);
	return query(lson, L, R) + query(rson, L, R);
}

void print_tree() {
	cout << endl;
	for(int i = 0; i < tree.size(); i++) {
		printf("%d %d %d\n", tree[i].left, tree[i].right, tree[i].sum);
	}
	cout << endl;
}

void solve() {
	tree = vector<Node>((n+1)*4, Node(0,0,0,0));
	build(0, 0, n);

	int a, b;
	while (m--) {
		scanf("%d%d", &a, &b);
		update(0, a, b, 1);
	}
	
	for (int i = 1; i <= n; i++) {
		int cnt = query(0, i, i);
		if (cnt != 1) {
			printf("%d %d\n", i, cnt);
			return;
		} 
	}
	cout << "yes!" << endl;
}

int main() {
	cin >> n >> m;
	solve();

	return 0;
}
