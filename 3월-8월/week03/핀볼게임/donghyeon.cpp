#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int maze[101][101];
vector<pair<int, int>> bh;
vector<pair<int, int>> wh[6]; // �� ��ȣ�� ��Ȧ ��ġ�� ����
// i�������� ���� �ְ� (j + 1)�� ������ nextD[i][j] �������� �ٲ�
int nextD[4][5] = { {1,3,2,1,1},{3,0,0,2,0},{0,1,3,3,3},{2,2,1,0,2} };
int N;
int maxScore;

// return 0 -> ��Ȧ ����, return 1 -> �� �� 
int check(int& x, int& y, int& d, int& score) {
	// ���� �հ� ���Դٸ� ���� �ε��� �ݴ� �������� ������ �ٲ�
	// ���� ����
	if (x < 0 || x >= N || y < 0 || y >= N) {
		if (x < 0) {
			d = 1;
		}
		else if (x >= N) {
			d = 0;
		}
		else if (y < 0) {
			d = 3;
		}
		else {
			d = 2;
		}
		score++;

		return 1;
	}

	if (maze[x][y] == -1) { // ��Ȧ�̸� ����
		return 0;
	}

	if (maze[x][y] >= 1 && maze[x][y] <= 5) { // ��Ͽ� �ε�������
		d = nextD[d][maze[x][y] - 1]; // ���� ����
		score++;
	}
	else if (maze[x][y] >= 6) { // ��Ȧ�� ��������
		// �ش� ������ ��Ȧ �� ���� ��ġ�� �ƴ� �ٸ� ��ġ�� ��Ȧ�� �̵�
		for (int i = 0; i < 2; i++) {
			if (x == wh[maze[x][y] - 6][i].first && y == wh[maze[x][y] - 6][i].second) {
				continue;
			}
			int nx = wh[maze[x][y] - 6][i].first;
			int ny = wh[maze[x][y] - 6][i].second;
			x = nx;
			y = ny;
			break;
		}
	}

	return 1;
}

void dfs(int x, int y, int d) {
	int sx = x;
	int sy = y;
	int score = 0;

	while (1) {
		// �����¿� ���⿡ ���� ��ǥ �̵�
		if (d == 0) {
			x--;
		}
		else if (d == 1) {
			x++;
		}
		else if (d == 2) {
			y--;
		}
		else {
			y++;
		}

		// �̵��� ��ǥ���� ó�� ��ġ�� ��Ȧ�̸� ����
		if ((x == sx && y == sy) || check(x, y, d, score) == 0) {
			maxScore = max(maxScore, score);
			break;
		}
	}

	return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;

		// ��Ȧ, ��Ȧ, �ִ����� �ʱ�ȭ
		bh.clear();
		for (int i = 0; i < 5; i++) {
			wh[i].clear();
		}
		maxScore = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> maze[i][j];
				if (maze[i][j] == -1) {
					bh.push_back(make_pair(i, j));
				}
				else if (maze[i][j] >= 6) {
					// wh[idx] -> (idx + 6)�� ��Ȧ
					wh[maze[i][j] - 6].push_back(make_pair(i, j));
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (maze[i][j] == 0) {
					for (int k = 0; k < 4; k++) { // �����¿� ���⸶�� ���
						dfs(i, j, k);
					}
				}
			}
		}

		cout << "#" << test_case << " " << maxScore << endl;
	}
	return 0;
}