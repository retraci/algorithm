// 201709-5 除法
/*
	思路：
	线段树 单点修改，区间查询 
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mid (left+(right-left) / 2)
#define lson ((node<<1) + 1)
#define rson ((node<<1) + 2)

struct Node {
	int left, right;
	ll sum;
	Node(int l_, int r_, ll s_) {
		left = l_, right = r_, sum = s_;
	}
};

int n, m;
vector<Node> tree;
vector<ll> nums;

void push_up(int node) {
	tree[node].sum = tree[lson].sum + tree[rson].sum;
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

void update(int node, int idx, ll val) {
	int left = tree[node].left;
	int right = tree[node].right;
	
	if(left == right) {
		tree[node].sum = val;
		nums[idx] = val;
		return;
	}
	
	if(idx>=left && idx<=mid) {
		update(lson, idx, val);
	} else if(idx>mid && idx<=right) {
		update(rson, idx, val);
	}
	
	push_up(node);
}

ll query(int node, int L, int R) {
	int left = tree[node].left;
	int right = tree[node].right;
	
	if(right<L || left>R) return 0;
	if(L<=left && right<=R) return tree[node].sum;
	
	return query(lson, L, R) + query(rson, L, R);
}

void solve() {
	tree = vector<Node>(n*4, Node(0,0,0));
	build(0, 0, n-1);
	
	int op, a, b;
	while(m--) {
		scanf("%d%d%d", &op, &a, &b);
		if(op == 1) {
			ll v;
			scanf("%I64d", &v);
			
			if(v == 1) continue;
			for(int i = a-1; i <= b-1; i++) {
				if(nums[i] >= v && nums[i]%v == 0) {
					ll val = nums[i] / v;
					update(0, i, val);
				}
			}
			
		} else {
			printf("%I64d\n", query(0, a-1, b-1));
		}
	}
}

int main() {
	cin >> n >> m;
	
	int temp;
	for(int i = 0; i < n; i++) {
		scanf("%I64d", &temp);
		nums.push_back(temp);
	}
	solve();
	
} 
