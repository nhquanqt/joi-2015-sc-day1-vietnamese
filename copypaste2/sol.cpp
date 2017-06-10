#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

int K, M;
int N;
string S;
int A[maxn], B[maxn], C[maxn];

char solve(int pos, int query) {
	if (query == 0)
		return S[pos];
	int len = B[query] - A[query];
	if (pos < C[query])
		return solve(pos, query - 1);
	else if (pos < C[query] + len)
		return solve(A[query] + pos - C[query], query - 1);
	else
		return solve(pos - len, query - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> K >> M;
	cin >> S;
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i] >> B[i] >> C[i];
	}
	for (int i = 0; i < K; ++i)
		printf("%c", solve(i, N));
	printf("\n");
}