// POJ 2777 Count Color
/*
	思路：
	线段树，染色问题
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define mid (left+(right-left) / 2)
#define lson ((node<<1) + 1)
#define rson ((node<<1) + 2)

struct Node {
	int left, right, sum, lz;
	Node(int l_, int r_, int s_, int lz_) {
		left = l_, right = r_, sum = s_, lz = lz_;
	}
};

int n, m;
int ans;
int vis[35];
vector<Node> tree;

void push_up(int node) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(tree[lson].sum == tree[rson].sum) tree[node].sum = tree[lson].sum;
	else tree[node].sum = -1;
}

void push_down(int node) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(tree[node].lz) {
		tree[lson].sum = tree[node].lz;
		tree[rson].sum = tree[node].lz;
		tree[lson].lz = tree[node].lz;
		tree[rson].lz = tree[node].lz;
		tree[node].lz = 0;
	}
}

void build(int node, int left, int right) {
	tree[node].left = left;
	tree[node].right = right;

	if(left == right) {
		tree[node].sum = 1;
		return;
	}

	build(lson, left, mid);
	build(rson, mid+1, right);
	push_up(node);
}

void update_range(int node, int L, int R, int val) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right<L || left>R) return;
	if(L<=left && right<=R) {
		tree[node].sum = val;
		tree[node].lz = val;
		return;
	}

	push_down(node);
	update_range(lson, L, R, val);
	update_range(rson, L, R, val);
	push_up(node);
}

void query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right<L || left>R) return;
	if(L<=left && right<=R) {
		int color = tree[node].sum;
		if(color != -1) {
			if(!vis[color]) {
				ans++;
				vis[color] = 1;
			}
		} else {
			push_down(node);
			query(lson, L, R);
			query(rson, L, R);
		}
		return;
	}

	push_down(node);
	query(lson, L, R);
	query(rson, L, R);
}

void print_tree() {
	cout << endl;
	for(int i = 0; i < tree.size(); i++) {
		printf("%d %d %d\n", tree[i].left, tree[i].right, tree[i].sum);
	}
	cout << endl;
}

void solve() {
	tree = vector<Node> (n*4, Node(0,0,1,0));
	build(0, 1, n);

	char op;
	int a, b;
	while(m--) {
		cin >> op;
		scanf("%d%d", &a, &b);
		if(a > b) swap(a, b);
		if(op == 'C') {
			int c;
			scanf("%d", &c);
			update_range(0, a, b, c);
//			print_tree();
		} else {
			ans = 0;
			memset(vis, 0, sizeof(vis));
			query(0, a, b);
			cout << ans << endl;
		}
	}
}

int main() {
	cin >> n >> m >> m;
	solve();

	return 0;
}
