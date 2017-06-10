#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 5;

int N;
int H[maxn], P[maxn], C[maxn];
int pos[maxn];

struct IT {
	ll T[4 * maxn], lz[4 * maxn];
	IT() {
		reset();
	}
	void reset() {
		for (int i = 0; i < 4 * maxn; ++i) {
			T[i] = -1e18;
			lz[i] = 0;
		}
	}
	void lazy(int v, int l, int r) {
		if (!lz[v])
			return;
		if (l != r) {
			lz[2 * v] += lz[v];
			lz[2 * v + 1] += lz[v];
		}
		T[v] += lz[v];
		lz[v] = 0;
	}
	#define mid ((l + r) >> 1)
	void up(int v, int l, int r, int i, int j, ll val) {
		lazy(v, l, r);
		if (l > j || r < i)
			return;
		if (i <= l && r <= j) {
			lz[v] += val;
			lazy(v, l, r);
			return;
		}
		up(2 * v, l, mid, i, j, val);
		up(2 * v + 1, mid + 1, r, i, j, val);
		T[v] = max(T[2 * v], T[2 * v + 1]);
	}
	void set(int v, int l, int r, int pos, ll val) {
		lazy(v, l, r);
		if (l > pos || r < pos)
			return;
		if (l == r) {
			T[v] = max(T[v], val);
			return;
		}
		set(2 * v, l, mid, pos, val);
		set(2 * v + 1, mid + 1, r, pos, val);
		T[v] = max(T[2 * v], T[2 * v + 1]);
	}
	ll get(int v, int l, int r, int i, int j) {
		lazy(v, l, r);
		if (l > j || r < i)
			return -1e18;
		if (i <= l && r <= j)
			return T[v];
		return max(get(2 * v, l, mid, i, j), 
			get(2 * v + 1, mid + 1, r, i, j));
	}
	#undef mid
} T;

ll pre[maxn], suf[maxn];

void upd(int i) {
	int p = lower_bound(pos + 1, pos + N + 2, H[i]) - pos;
		T.set(1, 1, N + 1, p, T.get(1, 1, N + 1, 1, p) + P[i]);
		T.up(1, 1, N + 1, 1, p - 1, -C[i]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> H[i] >> P[i] >> C[i];
		pos[i] = H[i];
	}
	pos[N + 1] = 0;
	sort(pos + 1, pos + N + 2);
	T.set(1, 1, N + 1, 1, 0);
	for (int i = 1; i <= N; ++i)
	{
		upd(i);
		pre[i] = T.get(1, 1, N + 1, 1, N + 1);
	}
	T.reset();
	T.set(1, 1, N + 1, 1, 0);
	for (int i = N; i >= 1; --i) {
		upd(i);
		suf[i] = T.get(1, 1, N + 1, 1, N + 1);
	}
	ll ans = 0;
	for (int i = 1; i <= N + 1; ++i) {
		// cout << i << ' ' << pre[i] << ' ' << pre[i - 1] << ' ' << suf[i] << endl;
		ans = max(ans, pre[i - 1] + suf[i]);
	}
	cout << ans << endl;
}