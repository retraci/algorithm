// POJ 3468 A Simple Problem with Integers
/*
	思路：
	线段树 区间修改，区间查询 
	
	note:
	注意要用 scanf 
*/ 

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define ll long long
#define mid (left + (right-left) / 2)
#define lson ((node<<1) + 1)
#define rson ((node<<1) + 2)

struct Node {
	int left, right;
	ll sum, lz;
	Node(int l_, int r_, ll s_, ll lz_) {
		left = l_, right = r_, sum = s_, lz = lz_;
	}
};

const int maxn = 100010;

int n, q;
vector<Node> tree;
ll nums[maxn];

void push_up(int node) {
	tree[node].sum = tree[lson].sum + tree[rson].sum;
}

void push_down(int node) {
	if(tree[node].lz) {
		int left = tree[node].left;
		int right = tree[node].right;
		
		tree[lson].sum += tree[node].lz*(mid-left+1);
		tree[rson].sum += tree[node].lz*(right-mid);
		tree[lson].lz += tree[node].lz;
		tree[rson].lz += tree[node].lz;
		tree[node].lz = 0;
	}
}

void build(int node, int left, int right) {
	tree[node].left = left;
	tree[node].right = right;
	
	if(left == right) {
		tree[node].sum = nums[left];
		return;
	}
	
	build(lson, left, mid);
	build(rson, mid+1, right);
	
	push_up(node);
	
}

void update_range(int node, int L, int R, ll val) {
	int left = tree[node].left;
	int right = tree[node].right;
	
	if(L>right || R<left) return;
	if(L<=left && R>=right) {
		tree[node].sum += val*(right-left+1);
		tree[node].lz += val;
		return;
	}
	
	push_down(node);
	if(R <= mid) {
		update_range(lson, L, R, val);
	} else if(L >= mid+1) {
		update_range(rson, L, R, val);
	} else {
		update_range(lson, L, R, val);
		update_range(rson, L, R, val);
	}
	push_up(node);
}

ll query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;
	
	if(L>right || R<left) return 0;
	if(L<=left && R>=right) {
		return tree[node].sum;
	}
	
	push_down(node);
	if(R <= mid) {
		return query(lson, L, R);
	} else if(L >= mid+1) {
		return query(rson, L, R);
	} else {
		return query(lson, L, R)+query(rson, L, R);
	}
}

void solve() {
	tree = vector<Node>(n*4, Node(0,0,0,0));
	build(0, 1, n);
	char op;
	int l, r;
	while(q--) {
		cin >> op;
		scanf("%d%d", &l, &r);
		if(op == 'C') {
			ll val;
			scanf("%I64d", &val);
			update_range(0, l, r, val);
		} else {
			ll ans = query(0, l, r);
			cout << ans << endl;
		}		
	}

}

int main() {
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		scanf("%I64d", &nums[i]);
	}
	solve();
	
	return 0;
} 
