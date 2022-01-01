#include <vector>
#include <queue>
#include <limits.h>
#include <cstdio>

using namespace std;

vector<pair<int, int>> adj[201]; // adj[i][j] -> i���� j���� ���

// num��ġ�� �������� �� ������ ������ �ִܰŸ� �迭 vector<int> dist�� ��ȯ
vector<int> dijkstra(int num, int V) {
	vector<int> dist(V + 1, INT_MAX); // dist[i] -> x�������� i���� ������ �ּҺ��
	priority_queue<pair<int, int> > pq;

	dist[num] = 0;
	pq.push(make_pair(0, num));

	// �켱���� ť -> ���ͽ�Ʈ��
	while (!pq.empty()) {
		int cost = -pq.top().first; 
		int near = pq.top().second;

		pq.pop();

		if (dist[near] < cost)
			continue;

		for (int i = 0; i < adj[near].size(); i++) {
			int nextNum = adj[near][i].first;
			int nextDist = cost + adj[near][i].second;

			if (dist[nextNum] > nextDist) {
				dist[nextNum] = nextDist;
				pq.push(make_pair(-nextDist, nextNum)); // ����� �������� �������� ������ ���� -�� ����
			}
		}
	}

	return dist;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
	int answer = 0;

	for (int i = 0; i < fares.size(); i++) {
		int a = fares[i][0];
		int b = fares[i][1];
		int w = fares[i][2];

		adj[a].push_back(make_pair(b, w));
		adj[b].push_back(make_pair(a, w));
	}

	vector<int> distS = dijkstra(s, n); // ������� s���� �� ���� ������ �ִ� �Ÿ�
	vector<int> distA = dijkstra(a, n); // �������� a���� �� ���� ������ �ִ� �Ÿ�
	vector<int> distB = dijkstra(b, n); // �������� b���� �� ���� ������ �ִ� �Ÿ�

	answer = INT_MAX;
	for (int i = 1; i <= n; i++) { // ��� ��带 ��������
		if (answer > distS[i] + distA[i] + distB[i]) { // (s���� -> i���� -> a,b���� �����)�� �ּҰ�
			answer = distS[i] + distA[i] + distB[i];  
		}
	}

	return answer;
}