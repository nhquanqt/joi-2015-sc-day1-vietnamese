#include <bits/stdc++.h>
using namespace std;

const int MAXN = (1 << 20) + 5;
const char C[3] = {'J', 'O', 'I'};

int K, N;
string S;
int four[15];
int cnt[MAXN][3];

int get_cnt(int i, int j, int type) {
	if (i <= j)
		return cnt[j][type] - (i == 0 ? 0 : cnt[i - 1][type]);
	return cnt[N - 1][type] - cnt[i - 1][type] + cnt[j][type];
}

int get_len(int i, int j) {
	if (i <= j)
		return j - i + 1;
	return N - i + j + 1;
}

int end(int start, int len) {
	return (start + len - 1) % N;
}

int f[MAXN][11];
int c[MAXN][11];

int dp(int start, int level) {
	if (!level)
		return 0;
	if (c[start][level])
		return f[start][level];
	c[start][level] = 1;
	int &ans = f[start][level] = 0;
	int cur = start;
	for (int i = 0; i < 3; ++i) {
		int ed = end(cur, four[level - 1]);
		ans += get_len(cur, ed) - get_cnt(cur, ed, i);
		cur = (ed + 1) % N;
	}
	return ans += dp(cur, level - 1);
}

int main() {
	four[0] = 1;
	for (int i = 1; i <= 10; ++i)
		four[i] = four[i - 1] * 4;
	cin >> K;
	N = four[K];
	cin >> S;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 3; ++j) {
			cnt[i][j] = S[i] == C[j];
			if (i)
				cnt[i][j] += cnt[i - 1][j];
		}
	}
	int ans = N;
	for (int i = 0; i < N; ++i)
		ans = min(ans, dp(i, K));
	cout << ans << endl;
}