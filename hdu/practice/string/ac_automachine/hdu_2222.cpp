// HDU 2222 Keywords Search
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

struct node {
	node* nxt[26];
	node* fail;
	int cnt;
	node() {
		memset(nxt,NULL,sizeof nxt);
		fail = NULL;
		cnt = 0;
	}
};

node* root;
char tar[1000010];

void init() {
	root = new node;
}

// 铺路，无节点就造节点
void insert(char* str) {
	int len = strlen(str);
	node* p = root;
	int ch;
	for(int i=0; i<len; i++) {
		ch = str[i]-'a';
		if(p->nxt[ch] == NULL) {
			p->nxt[ch] = new node;
		}
		p = p->nxt[ch];
	}
	p->cnt++;
}

// bfs + get_nxt
void get_fail() {
	queue<node*> q;
	q.push(root);
	while(!q.empty()) {
		node* fa = q.front();
		q.pop();
		for(int i=0; i<26; i++) {
			if(fa->nxt[i] != NULL) {
				node* p = fa->fail;
				// 不断找后缀 
				while(p != NULL) {
					if(p->nxt[i] != NULL) {		// 有相同的 
						fa->nxt[i]->fail = p->nxt[i];
						break;
					} else {					// 无相同的就继续找短一些的后缀 
						p = p->fail;
					}
				}
				
				if(p == NULL)
					fa->nxt[i]->fail = root;
					
				q.push(fa->nxt[i]);
			}
		}
	}
}

int query(char* tar) {
	int len = strlen(tar);
	int ans = 0;
	int ch;
	node* p = root;
	for(int i=0; i<len; i++) {
		ch = tar[i]-'a';
		// 不相同 且 能继续退 
		while(p->nxt[ch]==NULL && p!=root) 
			p = p->fail;

		p = p->nxt[ch];
		// 退到 root了 
		if(p == NULL) 
			p = root;	// 设置成 root 可以跳过记数且进行下一步的搜索 
		
		// 找后缀并记数 
		node* temp = p;
		while(temp!=root && temp->cnt!=-1) {
			ans += temp->cnt;
			temp->cnt = -1;
			temp = temp->fail;
		}
	}
	return ans;
}

int main() {
	int t;
	char s[60];
	cin >> t;
	while(t--) {
		init();
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			scanf("%s",s);
			insert(s);
		}
		get_fail();
		scanf("%s",tar);
		cout << query(tar) << endl;
	}

	return 0;
}
