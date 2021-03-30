#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// map[x][y][0] = true -> x,y�� �������� ���� �������� ��� ��ġ
// map[x][y][1] = true -> x,y�� �������� ������ �������� �� ��ġ
bool map[101][101][2];
int length; // map�� ũ�⸦ ����

// ���� �������� ���¸� �����ϴ� �Լ�
// [x,y,a]���� x��, y��, a�� �������� ����������
bool cmp(vector<int> a1, vector<int> a2) {
	if (a1[0] != a2[0]) {
		return a1[0] < a2[0];
	}
	else {
		if (a1[1] != a2[1]) {
			return a1[1] < a2[1];
		}
		else {
			return a1[2] < a2[2];
		}
	}
}

// return true -> x,y�� ����� ��ġ�ϴ� ���Ǹ���
bool check_gidung(int x, int y) {
	if (x == length) { // �ٴ��̸� ������ ��ġ ����
		return true;
	}
	if (map[x + 1][y][0] == true) { // ��ġ�Ϸ��� ��ġ �Ʒ��� ����� ������ ��ġ ����
		return true;
	}
	// ��ġ�Ϸ��� ��ġ�� ���� ���κ��̸� ��ġ ����
	if (map[x][y][1] == true || (y - 1 >= 0 && map[x][y - 1][1] == true)) {
		return true;
	}

	return false;
}

// return true -> x,y�� ���� ��ġ�ϴ� ���Ǹ���
bool check_bo(int x, int y) {
	// ���� ���κ��� ����� ��ġ�� ������ ��ġ ����
	if (map[x + 1][y][0] == true || map[x + 1][y + 1][0] == true) {
		return true;
	}
	// ���� ���� �ٸ� ���� ����������� ��ġ ����
	if (y - 1 >= 0 && map[x][y - 1][1] == true && y + 1 < length && map[x][y + 1][1] == true) {
		return true;
	}

	return false;
}

// x,y�� a �������� ��ġ�ϴ� �Լ�
// ��ġ ������ �ش� ��ġ�� ��ġ �������� Ȯ�� �۾�
void insert_struct(int x, int y, int a) {
	if (a == 0) {
		if (check_gidung(x, y)) {
			map[x][y][0] = true;
		}
	}
	else {
		if (check_bo(x, y)) {
			map[x][y][1] = true;
		}
	}
}

// x,y�� a �������� �����ϴ� �Լ�
// ���� ������ �ش� ��ġ�� �������� ������ ��� ������ ���������� ������ �����ϴ��� Ȯ��
void delete_struct(int x, int y, int a) {
	if (a == 0) { // ����� �����ϴ� ��Ȳ
		map[x][y][0] = false; // �켱 ����� �����ߴٰ� ����

		if (x - 1 >= 0 && map[x - 1][y][0] == true) { // �����Ϸ��� ��ġ ���� ����� ��ġ���ִٸ�
			if (check_gidung(x - 1, y) == false) { // �ش� ����� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][0] = true; // ����� �ٽ� ��������
				return;
			}
		}
		if (y - 1 >= 0 && map[x - 1][y - 1][1] == true) { // �����Ϸ��� ����� �� ������ ���� �����ϰ� �־��ٸ�
			if (check_bo(x - 1, y - 1) == false) { // �ش� ���� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][0] = true; // ����� �ٽ� ��������
				return;
			}
		}
		if (map[x - 1][y][1] == true) { // �����Ϸ��� ����� ���� ���� �����ϰ� �־��ٸ�
			if (check_bo(x - 1, y) == false) { // �ش� ���� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][0] = true; // ����� �ٽ� ��������
				return;
			}
		}
	}
	else { // ���� �����ϴ� ��Ȳ
		map[x][y][1] = false; // �켱 ���� �����ߴٰ� ����

		if (y - 1 >= 0 && map[x][y - 1][1] == true) { // �����Ϸ��� �� ���ʿ� �ٸ� ���� ����Ǿ��ִٸ�
			if (check_bo(x, y - 1) == false) { // �ش� ���� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][1] = true; // ���� �ٽ� ��������
				return;
			}
		}
		if (y + 1 < length && map[x][y + 1][1] == true) { // �����Ϸ��� �� �����ʿ� �ٸ� ���� ����Ǿ��ִٸ�
			if (check_bo(x, y + 1) == false) { // �ش� ���� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][1] = true; // ���� �ٽ� ��������
				return;
			}
		}
		if (map[x][y][0] == true) { // �����Ϸ��� ���� ���� ���� ����� ��ġ�� �־��ٸ� 
			if (check_gidung(x, y) == false) { // �ش� ����� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][1] = true; // ���� �ٽ� ��������
				return;
			}
		}
		if (y + 1 <= length && map[x][y + 1][0] == true) { // �����Ϸ��� ���� ������ ���� ����� ��ġ�� �־��ٸ�
			if (check_gidung(x, y + 1) == false) { // �ش� ����� ������ �����ϴ��� Ȯ�� �� ������ �������ϸ�
				map[x][y][1] = true; // ���� �ٽ� ��������
				return;
			}
		}
	}
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;

	length = n;

	for (int i = 0; i < build_frame.size(); i++) {
		int x = build_frame[i][0];
		int y = build_frame[i][1];
		int a = build_frame[i][2];
		int b = build_frame[i][3];

		// ���������� ��ǥ���� 2���� �迭 �ε����� ���߱� ���� ��ȯ
		// [x,y] -> map[y][n-x]�� �������� ��ġ Ȥ�� ����
		if (b == 0) {
			delete_struct(length - y, x, a);
		}
		else {
			insert_struct(length - y, x, a);
		}
	}

	// ��� map�� ��ȸ�ϸ鼭 �������� ��ġ�Ǿ��ִ� ��ġ�� ����
	// 2���� �迭 �ε����� ���������� ��ǥ������ ���߱� ���� ��ȯ
	for (int i = 0; i <= length; i++) {
		for (int j = 0; j <= length; j++) {
			if (map[i][j][0]) {
				answer.push_back({ j,n - i,0 });
			}
			if (map[i][j][1]) {
				answer.push_back({ j,n - i,1 });
			}
		}
	}

	sort(answer.begin(), answer.end(), cmp);

	return answer;
}