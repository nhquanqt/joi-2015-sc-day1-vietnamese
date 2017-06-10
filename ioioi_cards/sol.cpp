#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;
const int maxc = 5e5 + 5, maxn = 1e5 + 5;
const ll inf = 1e18;

int Val[5], pos[5];
int N, M;
int L[maxn], R[maxn];
vector<ii> G[maxc];

ll d[maxc][5];

void run_dijkstra(int from, int id) {
	for (int i = 0; i <= M; ++i)
		d[i][id] = inf;
	d[from][id] = 0;
	priority_queue<ii, vector<ii>, greater<ii>> q;
	q.emplace(0, from);
	while (q.size()) {
		ll w; int v; tie(w, v) = q.top(); q.pop();
		if (w != d[v][id])
			continue;
		for (auto edge: G[v]) {
			if (d[edge.y][id] > d[v][id] + edge.x) {
				d[edge.y][id] = d[v][id] + edge.x;
				q.emplace(d[edge.y][id], edge.y);
			}
		}
	}
}

ll cost[1 << 4][1 << 4];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	M = 0;
	for (int i = 0; i < 5; ++i) {
		cin >> Val[i];
		M += Val[i];
	}
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> L[i] >> R[i];
		int cost = R[i] - L[i] + 1;
		G[L[i] - 1].emplace_back(cost, R[i]);
		G[R[i]].emplace_back(cost, L[i] - 1);
	}
	int sum = 0;
	for (int i = 1; i < 5; ++i) {
		sum += Val[i - 1];
		pos[i - 1] = sum;
		run_dijkstra(sum, i - 1);
	}
	#define MAX (1 << 4)
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j)
			cost[i][j] = inf;
	}
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				cost[i][i ^ (1 << j) ^ (1 << k)] = min(cost[i][i ^ (1 << j) ^ (1 << k)], d[pos[k]][j]);
	}
	for (int k = 0; k < MAX; ++k)
		for (int i = 0; i < MAX; ++i)
			for (int j = 0; j < MAX; ++j)
				cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
	cout << (cost[MAX - 1][0] == inf ? -1 : cost[MAX - 1][0]) << endl;
}