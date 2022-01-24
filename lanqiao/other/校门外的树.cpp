// 莞工OJ 校门外的树
/*
	思路：
	1<<0 表示树
	1<<1 表示树苗
	1<<2 表示空
	
	node:
	二进制记录状态 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

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

const int maxn = 1000010;

int n, m;
vector<Node> tree;
ll ans1, ans2;

void push_up(int node) {
	tree[node].sum = tree[lson].sum | tree[rson].sum;
}

void push_down(int node) {
	if(tree[node].lz) {
		tree[lson].sum = tree[lson].lz = tree[node].lz;
		tree[rson].sum = tree[rson].lz = tree[node].lz;
		tree[node].lz = 0;
	}
}

void build(int node, int left, int right) {
	tree[node].left = left;
	tree[node].right = right;

	if(left == right) return;

	build(lson, left, mid);
	build(rson, mid+1, right);
}

void update(int node, int L, int R, int val) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right<L || left>R) return;
	if(L<=left && right<=R) {
		int s = tree[node].sum;

		if(val == (1<<2)) {
			// s 区间全是树苗
			if(s == (1<<1)) {
				ans2 += right-left+1;
				tree[node].sum = (1<<2);
				tree[node].lz = (1<<2);
				// s区间部分含有树苗
			} else if((1<<1) & s) {
				push_down(node);
				update(lson, L, R, val);
				update(rson, L, R, val);
				push_up(node);
			} else {
				tree[node].sum = (1<<2);
				tree[node].lz = (1<<2);
			}
		} else {
			// s区间全是空位
			if(s == (1<<2)) {
				tree[node].sum = val;
				tree[node].lz = val;
				// s区间部分是空位
			} else if((1<<2) & s) {
				push_down(node);
				update(lson, L, R, val);
				update(rson, L, R, val);
				push_up(node);
			}
		}

		return;
	}

	push_down(node);
	update(lson, L, R, val);
	update(rson, L, R, val);
	push_up(node);
}

void query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;

	if(right<L || left>R) return;
	if(L<=left && right<=R) {
		int s = tree[node].sum;

		if(s == (1<<1)) {
			ans1 += right-left+1;
		} else if((1<<1) & s) {
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

/*
3 3
0 1 2
1 1 3
0 2 3
*/

void print_tree() {
	cout << endl;
	for(int i = 0; i < tree.size(); i++) {
		printf("%d %d %d\n", tree[i].left, tree[i].right, tree[i].sum);
	}
	cout << endl;
}

void solve() {
	tree = vector<Node>((n+1)*4, Node(0,0,1,0));
	build(0, 0, n);

	int op, a, b;
	while(m--) {
		scanf("%d%d%d", &op, &a, &b);
		if(op == 0) {
			update(0, a, b, 1<<2);
		} else {
			update(0, a, b, 1<<1);
		}
//		print_tree();
	}

	query(0, 0, n);
	cout << ans1 << endl << ans2 << endl;
}

int main() {
	cin >> n >> m;
	solve();

	return 0;
}
