#include<iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int map[21][21];
bool buildChk[21]; // buildChk[i] = true -> ����or���� Ư�� ���ο��� i��°�� Ȱ�ַΰ� �Ǽ��Ǿ�����
int N, X;

// �ε��� ��ȿ���� üũ
bool checkRange(int idx) {
	if (idx < 0 || idx >= N) {
		return false;
	}
	return true;
}

// �� ���� �� ���� ���̸� ���ϴ� �Լ�
int checkHeightDiff(int height1, int height2) {
	if (abs(height1 - height2) >= 2) { // ���� ���̰� 2 �̻��̸� Ȱ�ַ� �Ǽ� �Ұ�
		return -1;
	}

	if (abs(height1 - height2) == 0) { // ���̰� ���ٸ� �Ѿ
		return 0;
	}

	if (height1 > height2) { // ���� ������ ���̰� 1��ŭ �� ŭ
		return 1;
	}
	else { // ������ ������ ���̰� 1��ŭ �� ŭ
		return 2;
	}
}

// map[x][y]�� �������� ���� ���� �������� Ȱ�ַ� �Ǽ�
bool buildLeft(int x, int y) {
	int height = map[x][y]; // ���� ����
	buildChk[y] = true; // y�� ������ Ȱ�ַ� �Ǽ�

	// (x,y)�� �������� �������� X��ŭ ������ ������ Ž���ϸ� Ȱ�ַ� �Ǽ�
	for (int i = 1; i < X; i++) {
		// �Ǽ��Ϸ��� ��ġ�� �������� ����ų�, ���� ���̿� ���̰� �ٸ��ų�, �̹� Ȱ�ַΰ� �Ǽ��Ǿ� �ִٸ� 
		// return false
		if (checkRange(y - i) == false || map[x][y - i] != height || buildChk[y - i] == true) {
			return false;
		}
		buildChk[y - i] = true;
	}

	return true;
}

// map[x][y]�� �������� ������ ���� �������� Ȱ�ַ� �Ǽ�
bool buildRight(int x, int y) {
	int height = map[x][y]; // ���� ����
	buildChk[y] = true; // y�� ������ Ȱ�ַ� �Ǽ�

	// (x,y)�� �������� ���������� X��ŭ ������ ������ Ž���ϸ� Ȱ�ַ� �Ǽ�
	for (int i = 1; i < X; i++) {
		// �Ǽ��Ϸ��� ��ġ�� �������� ����ų�, ���� ���̿� ���̰� �ٸ��ų�, �̹� Ȱ�ַΰ� �Ǽ��Ǿ� �ִٸ� 
		// return false
		if (checkRange(y + i) == false || map[x][y + i] != height || buildChk[y + i] == true) {
			return false;
		}
		buildChk[y + i] = true;
	}

	return true;
}

// map[x][y]�� �������� ���� ���� �������� Ȱ�ַ� �Ǽ�
bool buildUp(int x, int y) {
	int height = map[x][y];
	buildChk[x] = true;

	// (x,y)�� �������� �������� X��ŭ ������ ������ Ž���ϸ� Ȱ�ַ� �Ǽ�
	for (int i = 1; i < X; i++) {
		// �Ǽ��Ϸ��� ��ġ�� �������� ����ų�, ���� ���̿� ���̰� �ٸ��ų�, �̹� Ȱ�ַΰ� �Ǽ��Ǿ� �ִٸ� 
		// return false
		if (checkRange(x - i) == false || map[x - i][y] != height || buildChk[x - i] == true) {
			return false;
		}
		buildChk[x - i] = true;
	}

	return true;
}

// map[x][y]�� �������� �Ʒ��� ���� �������� Ȱ�ַ� �Ǽ�
bool buildDown(int x, int y) {
	int height = map[x][y];
	buildChk[x] = true;

	// (x,y)�� �������� �Ʒ������� X��ŭ ������ ������ Ž���ϸ� Ȱ�ַ� �Ǽ�
	for (int i = 1; i < X; i++) {
		// �Ǽ��Ϸ��� ��ġ�� �������� ����ų�, ���� ���̿� ���̰� �ٸ��ų�, �̹� Ȱ�ַΰ� �Ǽ��Ǿ� �ִٸ� 
		// return false
		if (checkRange(x + i) == false || map[x + i][y] != height || buildChk[x + i] == true) {
			return false;
		}
		buildChk[x + i] = true;
	}

	return true;
}

// ���� ���� ���� -> ���� ���� ���ڰ����� ����
bool checkRow(int x) {
	int flag = true; // �⺻������ Ȱ�ַ� �Ǽ� ����
	int y;

	// ��� ���� Ž���ϸ鼭 
	for (int i = 0; i < N; i++) {
		y = i + 1; // ������ ������ �ε��� ����
		if (checkRange(y)) { // ��ȿ������ ����
			int height_diff = checkHeightDiff(map[x][i], map[x][y]); // �������� �������� ����

			if (height_diff < 0) { // ���� �� �������� 2�̻��̸� Ȱ�ַ� �Ǽ� �Ұ�
				flag = false;
				break;
			}
			else if (height_diff == 1) { // ���� ������ ���̰� 1��ŭ �� ū ���
				if (buildRight(x, y) == false) { // ������ �������� Ȱ�ַ� �Ǽ��� �Ұ����ϸ� false ����
					flag = false;
					break;
				}
			}
			else if (height_diff == 2) { // ������ ������ ���̰� 1��ŭ �� ū ���
				if (buildLeft(x, i) == false) { // ���� �������� Ȱ�ַ� �Ǽ��� �Ұ����ϸ� false ����
					flag = false;
					break;
				}
			}
		}
	}

	// Ȱ�ַ� �Ǽ� ǥ�� �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		buildChk[i] = 0;
	}

	return flag;
}

// ���� ���� ���� -> ���� ���� ���ڰ����� ����
bool checkColumn(int y) {
	int flag = true; // �⺻������ Ȱ�ַ� �Ǽ� ����
	int x;

	// ��� ���� Ž���ϸ鼭 
	for (int i = 0; i < N; i++) {
		x = i + 1; // �Ʒ� ������ �ε��� ����
		if (checkRange(x)) { // ��ȿ������ ����
			int height_diff = checkHeightDiff(map[i][y], map[x][y]); // �������� �������� ����

			if (height_diff < 0) { // ���� �� �������� 2�̻��̸� Ȱ�ַ� �Ǽ� �Ұ�
				flag = false;
				break;
			}
			else if (height_diff == 1) { // ���� ������ ���̰� 1��ŭ �� ū ���
				if (buildDown(x, y) == false) { // �Ʒ��� �������� Ȱ�ַ� �Ǽ��� �Ұ����ϸ� false ����
					flag = false;
					break;
				}
			}
			else if (height_diff == 2) { // �Ʒ��� ������ ���̰� 1��ŭ �� ū ���
				if (buildUp(i, y) == false) { // ���� �������� Ȱ�ַ� �Ǽ��� �Ұ����ϸ� false ����
					flag = false;
					break;
				}
			}
		}
	}

	// Ȱ�ַ� �Ǽ� ǥ�� �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		buildChk[i] = 0;
	}

	return flag;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int answer = 0;
		cin >> N >> X;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		// 0 ~ N-1���� ��� ��� ���� Ž��
		for (int i = 0; i < N; i++) {
			if (checkRow(i)) { // i�� �࿡ Ȱ�ַ� �Ǽ� �����ϸ� count++
				answer++;
			}
			if (checkColumn(i)) { // i�� ���� Ȱ�ַ� �Ǽ� �����ϸ� count++
				answer++;
			}
		}

		cout << "#" << test_case << " " << answer << endl;
	}

	return 0;
}