// HDU 3065 病毒侵入持续中
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct node {
	node *next[26];
	node *fail;
	int id;
	node() {
		memset(next,NULL,sizeof(next));
		fail = NULL;
		id = 0;
	}
};

node *root;
char pat[1010][55];
int mark[1010];
int n;
char str[2000010];

void init() {
	root = new node;
}

void insert(char *str,int id) {
	node *p = root;
	int ch;
	int len = strlen(str);
	for(int i=0; i<len; i++) {
		ch = str[i]-'A';
		if(p->next[ch] == NULL)
			p->next[ch] = new node;
		p = p->next[ch];
	}
	p->id = id;
}

void get_fail() {
	node *fa;
	queue<node*> q;
	q.push(root);
	while(!q.empty()) {
		fa = q.front();
		q.pop();
		for(int i=0; i<26; i++) {
			if(fa->next[i]) {
				node *p = fa->fail;
				while(p && p->next[i]==NULL) p = p->fail;
				fa->next[i]->fail = p?p->next[i]:root;
				q.push(fa->next[i]);
			}
		}
	}
}

void query(char *str) {
	node *p = root;
	int len = strlen(str);
	int ch;
	for(int i=0; i<len; i++) {
		ch = str[i]-'A';
		if(ch>=26 || ch<0) {
			p = root;
			continue;
		}
		while(p && p->next[ch]==NULL) p = p->fail;
		p = p?p->next[ch]:root;
		node *temp = p;
		while(temp) {
			if(temp->id != 0) 
				mark[temp->id]++;
			temp = temp->fail;
		}
	}
}

int main() {
	while(~scanf("%d",&n)) {
		init();
		memset(mark,0,sizeof(mark));
		for(int i=1; i<=n; i++) {
			scanf("%s",pat[i]);
			insert(pat[i],i);
		}
		get_fail();
		scanf("%s",str);
		query(str);
		for(int i=1; i<=n; i++) {
			if(mark[i]) {
				printf("%s: %d\n",pat[i],mark[i]);
			}
		}
		delete(root);
	}

	return 0;
}
