#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long s64;

const int MaxN = 1000005;
const int MaxLogN = 21;
const int INF = 0x3f3f3f3f;

inline int getint()
{
	static char c;
	while ((c = getchar()) < '0' || c > '9');

	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

int n, nQ;

int anc[MaxLogN][MaxN];
int dep[MaxN];

int dfsCur = 0;
int dfnL[MaxN], dfnR[MaxN];

struct halfEdge
{
	int v, w;
	halfEdge *next;
};
halfEdge adj_pool[MaxN * 2], *adj_tail = adj_pool;
halfEdge *adj[MaxN];

inline void addEdge(const int &u, const int &v)
{
	adj_tail->v = v, adj_tail->next = adj[u];
	adj_tail->w = dep[v] - dep[u];
	adj[u] = adj_tail++;
}

inline bool under(const int &u, const int &v)
{
	return dfnL[u] <= dfnL[v] && dfnL[v] <= dfnR[u];
}

void dfs(const int &u)
{
	for (int i = 0; anc[i][u]; ++i)
		anc[i + 1][u] = anc[i][anc[i][u]];

	dfnL[u] = ++dfsCur;
	for (halfEdge *e = adj[u]; e; e = e->next)
		if (e->v != anc[0][u])
		{
			anc[0][e->v] = u;
			dep[e->v] = dep[u] + 1;
			dfs(e->v);
		}
	dfnR[u] = dfsCur;
}

inline int get_lca(int u, int v)
{
	if (dep[u] < dep[v])
		swap(u, v);
	if (under(v, u))
		return v;

	int delta = dep[u] - dep[v];
	while (delta > 0)
	{
		int l = __builtin_ctz(delta);
		u = anc[l][u];
		delta ^= 1 << l;
	}

	for (int i = 19; anc[0][u] != anc[0][v]; --i)
		if (anc[i][u] != anc[i][v])
		{
			u = anc[i][u];
			v = anc[i][v];
		}
	return anc[0][u];
}

int sta[MaxN];

int li[MaxN];

inline bool cmpByDfn(const int &u, const int &v)
{
	return dfnL[u] < dfnL[v];
}

bool key[MaxN];

inline void build(const int &n)
{
	adj_tail = adj_pool;

	for (int i = 1; i <= n; ++i)
		key[li[i] = getint()] = true;
	sort(li + 1, li + n + 1, cmpByDfn);

	int sta_n = 1;
	sta[sta_n] = 1;
	for (int i = 1; i <= n; ++i)
	{
		int u = li[i];
		int lca = get_lca(u, sta[sta_n]);
		while (sta_n > 0)
		{
			if (dep[lca] >= dep[sta[sta_n - 1]])
			{
				if (sta[sta_n] != lca)
					addEdge(lca, sta[sta_n]);
				if (sta[--sta_n] != lca)
					sta[++sta_n] = lca;
				break;
			}
			addEdge(sta[sta_n - 1], sta[sta_n]);
			--sta_n;
		}
		if (sta[sta_n] != u)
			sta[++sta_n] = u;
	}
	while (sta_n > 1)
	{
		addEdge(sta[sta_n - 1], sta[sta_n]);
		--sta_n;
	}
}

s64 t_path, path_t[MaxN];
int s_path, path_s[MaxN];
int l_path, path_l[MaxN];
int size[MaxN];

void get_path_info(const int &u)
{
	path_t[u] = 0;
	path_s[u] = key[u] ? 0 : INF;
	path_l[u] = key[u] ? 0 : -INF;
	size[u] = key[u];
	for (halfEdge *&e = adj[u]; e; e = e->next)
	{
		get_path_info(e->v);
		t_path += size[e->v] * (path_t[u] + (s64)size[u] * e->w) + size[u] * path_t[e->v];
		s_path = min(s_path, path_s[u] + e->w + path_s[e->v]);
		l_path = max(l_path, path_l[u] + e->w + path_l[e->v]);
		path_t[u] += path_t[e->v] + (s64)size[e->v] * e->w;
		path_s[u] = min(path_s[u], path_s[e->v] + e->w);
		path_l[u] = max(path_l[u], path_l[e->v] + e->w);
		size[u] += size[e->v];
	}
}

inline void solve(const int &n)
{
	t_path = 0, s_path = INF, l_path = -INF;
	get_path_info(1);
	printf("%lld %d %d\n", t_path, s_path, l_path);
	for (int i = 1; i <= n; ++i)
		key[li[i]] = false;
}

int main()
{
	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		int u = getint(), v = getint();
		addEdge(u, v);
		addEdge(v, u);
	}

	dfs(1);

	for (int u = 1; u <= n; ++u)
		adj[u] = NULL;

	cin >> nQ;
	while (nQ--)
	{
		int m = getint();
		build(m);
		solve(m);
	}

	return 0;
}
