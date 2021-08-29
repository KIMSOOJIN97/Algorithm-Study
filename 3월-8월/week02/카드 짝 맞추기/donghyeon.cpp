#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>>

using namespace std;

vector<vector<int>> tmp; // board�� �ӽ�����
vector<int> cardNum; // ī���ȣ ����
vector<pair<int, int>> cardPos[7]; // cardPos[n] -> n�� ī���� ��ġ1,2
int cardCnt;
int minCost;
int dr[] = { 1,0,-1,0 };
int dc[] = { 0,1,0,-1 };

// ��ǥ���� �����ȿ� �ִ��� üũ
bool check(int x, int y) {
	if (x >= 0 && y >= 0 && x < 4 && y < 4) {
		return true;
	}
	else {
		return false;
	}
}

// (sr,sc) -> (er, ec)�� ���� �ִܰ��
int bfs(int sr, int sc, int er, int ec) {
	queue<pair<pair<int, int>, int>> q; // {ī�� ��ġ, ���}
	vector<vector<bool>> visited(4, vector<bool>(4, false)); // ��ġ �湮 üũ

	q.push({ make_pair(sr,sc),0 });
	visited[sr][sc] = true;

	while (!q.empty()) {
		int r = q.front().first.first;
		int c = q.front().first.second;
		int cost = q.front().second;
		q.pop();

		for (int i = 0; i < 8; i++) {
			int nr = r;
			int nc = c;

			if (i < 4) { // �����¿�
				nr += dr[i];
				nc += dc[i];
			}
			else { // ctrl ���� ���¿��� �̵�
				int j = i - 4;
				while (check(nr + dr[j], nc + dc[j])) {
					nr += dr[j];
					nc += dc[j];
					if (tmp[nr][nc] != 0)
						break;
				}
			}

			// ���� �湮 ���� ��ġ�� ť�� ����
			if (check(nr, nc) && visited[nr][nc] == 0) {
				visited[nr][nc] = 1;
				q.push({ {nr, nc}, cost + 1 });
				if (nr == er && nc == ec) { // �̵��� ��ġ�� ���� ��ġ�� ����
					return cost + 1;
				}
			}
		}
	}

	return 0;
}

// (r, c)���� idx��° ī�� �����
void dfs(int idx, int r, int c, int cost) {
	if (cost > minCost) { // ������� ����� ���� ��뺸�� ũ�ٸ� �ߴ�
		return;
	}

	// ��� ī�带 �������� ��� Ȯ��
	if (idx == cardCnt) {
		if (minCost > cost) {
			minCost = cost;
		}
		return;
	}

	int num = cardNum[idx]; // �����ؾ� �� ī�� ��ȣ
	pair<int, int> cardA = cardPos[num][0]; // num�� ī�� ��ġ1
	pair<int, int> cardB = cardPos[num][1]; // num�� ī�� ��ġ2


	// ���� ��ġ -> numA -> numB
	int costAB = bfs(r, c, cardA.first, cardA.second)
		+ bfs(cardA.first, cardA.second, cardB.first, cardB.second) + 2;
	// ���� ��ġ -> numB -> numA
	int costBA = bfs(r, c, cardB.first, cardB.second)
		+ bfs(cardB.first, cardB.second, cardA.first, cardA.second) + 2;

	// num�� ī�带 �����ٰ� ǥ��
	tmp[cardA.first][cardA.second] = 0;
	tmp[cardB.first][cardB.second] = 0;

	dfs(idx + 1, cardB.first, cardB.second, cost + costAB); // numA -> numB ������ ����
	dfs(idx + 1, cardA.first, cardA.second, cost + costBA); // numB -> numA ������ ����

	// ��Ϳ��� �������� �� �ٽ� ī�带 ǥ��
	tmp[cardA.first][cardA.second] = num;
	tmp[cardB.first][cardB.second] = num;

	return;
}

int solution(vector<vector<int>> board, int r, int c) {
	int answer = 0;
	vector<int> numCheck(7, 0);
	minCost = INT_MAX;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] != 0) {
				if (numCheck[board[i][j]] == 0) { // ���ο� ������ ī��� ī���ȣ������ ����
					cardNum.push_back(board[i][j]);
					numCheck[board[i][j]] = 1;
					cardCnt++;
				}
				cardPos[board[i][j]].push_back(make_pair(i, j)); // ī�� ��ġ ����
			}
		}
	}

	sort(cardNum.begin(), cardNum.end()); // ī�� ��ȣ ����

	// ī�带 �����ϴ� ������ ��� ��츦 ���ϰ� ���� dfsŽ��
	do {
		tmp = board; // ī�� ��ġ ����
		dfs(0, r, c, 0); // r,c���� ���
	} while (next_permutation(cardNum.begin(), cardNum.end())); // ��� ���� ���

	answer = minCost;

	return answer;
}

/*
*{1,2,3} ī��
-1 -> 2 -> 3
-1 -> 3 -> 2
-2 -> 1 -> 3
-2 -> 3 -> 1
-3 -> 1 -> 2
-3 -> 2 -> 1

*ī�� ��ġ
-ī��1A : (1ar, 1ac)
-ī��1B : (1br, 1bc)
-ī��2A : (2ar, 2ac)
-ī��2B : (2br, 2bc)
-ī��3A : (3ar, 3ac)
-ī��3B : (3br, 3bc)

*1 -> 2 -> 3 ����
					   [1�� ī��]                       [2�� ī��]                       [3�� ī��]
(r, c) -->	(1ar, 1ac) -> (1br, 1bc) --> (2ar, 2ac) -> (2br, 2bc) --> (3ar, 3ac) -> (3br, 3bc)

																				 --> (3br, 3bc) -> (3ar, 3ac)

											--> (2br, 2bc) -> (2ar, 2ac) --> (3ar, 3ac) -> (3br, 3bc)

																				 --> (3br, 3bc) -> (3ar, 3ac)


	   -->	(1br, 1bc) -> (1ar, 1ac) --> (2ar, 2ac) -> (2br, 2bc) --> (3ar, 3ac) -> (3br, 3bc)

																				 --> (3br, 3bc) -> (3ar, 3ac)

											--> (2br, 2bc) -> (2ar, 2ac) --> (3ar, 3ac) -> (3br, 3bc)

																				--> (3br, 3bc) -> (3ar, 3ac)
*/

