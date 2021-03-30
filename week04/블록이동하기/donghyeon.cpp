#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// �κ��� ��ǥ���� ����� �����ϴ� ����ü
typedef struct _pos {
	int x1;
	int y1;
	int x2;
	int y2;
	int cost;
}Pos;
queue<Pos> q;
int N;
// dp[x1][y1][x2][y2] -> (x1,y1),(x2,y2)�� �����ִ� �κ��� �ּ� �̵����
// �κ��� ��� �������� �̵��ߵ��� (x2 >= x1) && (y2 >= y1)�� ���
int dp[101][101][101][101];
int minDp; // ������������ �ּҺ��

// ���ο� ��ǥ�� �̵��ϴ� �Լ�
void check(vector<vector<int>>& board, int nx1, int ny1, int nx2, int ny2, int cost) {
	// ��ȿ������ ����� ����
	if (nx1 < 0 || nx1 >= N || ny1 < 0 || ny1 >= N ||
		nx2 < 0 || nx2 >= N || ny2 < 0 || ny2 >= N) {
		return;
	}

	// �̵��Ϸ��� ���� ���̸� ����
	if (board[nx1][ny1] == 1 || board[nx2][ny2] == 1) {
		return;
	}

	// �̵��Ϸ��� ��ǥ�� ó�� �����ϰų� ������ ��뺸�� ���� �̵� ������ ���� ����
	if (dp[nx1][ny1][nx2][ny2] == 0 || dp[nx1][ny1][nx2][ny2] > cost + 1) {
		q.push({ nx1,ny1,nx2,ny2,cost + 1 });

		dp[nx1][ny1][nx2][ny2] = cost + 1;

		if (nx2 == N - 1 && ny2 == N - 1) { // �� ��° ������ �������� �������� ��
			minDp = min(minDp, dp[nx1][ny1][nx2][ny2]); // �ּҰ��̸� ����
		}
	}

	return;
}

// �κ��� ���η� ��ġ�Ǿ����� �� ȸ��
void rotateRow(vector<vector<int>>& board, int x1, int y1, int x2, int y2, int cost) {
	int nx1;
	int ny1;
	int nx2;
	int ny2;

	// ���� �� �������� ȸ��
	if (x1 != 0 && board[x2 - 1][y2] != 1) { // ������ ���� ���� �ƴ� ���� �̵�
		nx1 = x1 - 1;
		ny1 = y1;
		nx2 = x1;
		ny2 = y1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// ������ �� �������� ȸ��
	if (x1 != 0 && board[x1 - 1][y1] != 1) { // ���� ���� ���� �ƴ� ���� �̵�
		nx1 = x2 - 1;
		ny1 = y2;
		nx2 = x2;
		ny2 = y2;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// ���� �Ʒ� �������� ȸ��
	if (x1 != N - 1 && board[x2 + 1][y2] != 1) { // ������ �Ʒ��� ���� �ƴ� ���� �̵�
		nx1 = x1;
		ny1 = y1;
		nx2 = x1 + 1;
		ny2 = y1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// ������ �Ʒ� �������� ȸ��
	if (x1 != N - 1 && board[x1 + 1][y1] != 1) { // ���� �Ʒ��� ���� �ƴ� ���� �̵�
		nx1 = x2;
		ny1 = y2;
		nx2 = x2 + 1;
		ny2 = y2;
		check(board, nx1, ny1, nx2, ny2, cost);
	}
}

// �κ��� ���η� ��ġ�Ǿ����� �� ȸ��
void rotateColumn(vector<vector<int>>& board, int x1, int y1, int x2, int y2, int cost) {
	int nx1;
	int ny1;
	int nx2;
	int ny2;

	// ���� �� �������� ȸ��
	if (y1 != 0 && board[x2][y2 - 1] != 1) { // ���� �Ʒ��� ���� �ƴ� ���� �̵�
		nx1 = x1;
		ny1 = y1 - 1;
		nx2 = x1;
		ny2 = y1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// ������ �� �������� ȸ��
	if (y1 != N - 1 && board[x2][y2 + 1] != 1) { // ������ �Ʒ��� ���� �ƴ� ���� �̵�
		nx1 = x1;
		ny1 = y1;
		nx2 = x1;
		ny2 = y1 + 1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// ���� �Ʒ� �������� ȸ��
	if (y1 != 0 && board[x1][y1 - 1] != 1) { // ���� ���� ���� �ƴ� ���� �̵�
		nx1 = x2;
		ny1 = y2 - 1;
		nx2 = x2;
		ny2 = y2;
		check(board, nx1, ny1, nx2, ny2, cost);
	}

	// ������ �Ʒ� �������� ȸ��
	if (y1 != N - 1 && board[x1][y1 + 1] != 1) { // ������ ���� ���� �ƴ� ���� �̵�
		nx1 = x2;
		ny1 = y2;
		nx2 = x2;
		ny2 = y2 + 1;
		check(board, nx1, ny1, nx2, ny2, cost);
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0;

	N = board.size();
	minDp = INT_MAX;

	int dx1[] = { -1,1,0,0 };
	int dy1[] = { 0,0,-1,1 };
	int dx2[] = { -1,1,0,0 };
	int dy2[] = { 0,0,-1,1 };

	q.push({ 0,0,0,1,0 }); // �ʱⰪ (0,0),(0,1)�� 0�� ������� �����ִ� ���¿��� ���

	while (!q.empty()) {
		int x1 = q.front().x1;
		int y1 = q.front().y1;
		int x2 = q.front().x2;
		int y2 = q.front().y2;
		int cost = q.front().cost;

		q.pop();

		// �����¿� �̵�
		for (int i = 0; i < 4; i++) {
			int nx1 = x1 + dx1[i];
			int ny1 = y1 + dy1[i];
			int nx2 = x2 + dx2[i];
			int ny2 = y2 + dy2[i];

			check(board, nx1, ny1, nx2, ny2, cost);
		}

		// ȸ��
		if (x1 == x2) { // �κ��� ���� ������ ��
			rotateRow(board, x1, y1, x2, y2, cost);
		}
		else { // �κ��� ���� ������ ��
			rotateColumn(board, x1, y1, x2, y2, cost);
		}
	}

	answer = minDp;

	return answer;
}