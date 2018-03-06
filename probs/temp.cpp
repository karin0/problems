#include <bits/stdc++.h>
#define Rep(i, a, b) for (int i = (a), i##_ = (b); i < i##_; ++i)
#define For(i, a, b) for (int i = (a), i##_ = (b); i <= i##_; ++i)
#define Down(i, a, b) for (int i = (a), i##_ = (b); i >= i##_; --i)
#define bin(x, k) ((x)>>(k)&1)
using namespace std;
const int D = 24, MAX_N = 3e5, MAX_M = 3e5;
struct Node {
	Node* ch[2];
} nodes[(D+1)*(MAX_N+MAX_M+1)+1], * nil = nodes, * root[MAX_N + MAX_M + 1];
inline Node* new_node(const Node& x)
{
	static Node* cur = nodes + 1;
	*cur = x;
	return cur++;
}
void insert(Node* &o, Node* p, int x, int k)
{
	o = new_node(*p);
	if (k < 0) return;
	int b = bin(x, k);
	insert(o->ch[b], p->ch[b], x, k-1);
}
int query(Node* o, Node* p, int x, int k)
{
	if (k < 0) return 0;
	int b = !bin(x, k);
	return o->ch[b] - p->ch[b] ? 1 << k | query(o->ch[b], p->ch[b], x, k-1)
		: query(o->ch[!b], p->ch[!b], x, k-1);
}
inline void init()
{
	*nil = (Node){nil, nil};
}
int main()
{
	int n, m, S = 0;
	scanf("%d%d", &n, &m);
	init();
	insert(root[0], nil, 0, D-1);
	For (i, 1, n) {
		int a;
		scanf("%d", &a);
		insert(root[i], root[i-1], S ^= a, D-1);
	}
	while (m--) {
		char c;
		int l, r, x;
		scanf(" %c", &c);
		if (c == 'A') {
			scanf("%d", &x);
			insert(root[n+1], root[n], S ^= x, D-1);
			++n;
		} else {
			scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", query(root[r-1], l > 1 ? root[l-2] : nil, x^S, D-1));
		}
	}
	return 0;
}
