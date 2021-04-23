#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct _atom {
	double x;
	double y;
	int d;
	int energy;
}Atom;
Atom atoms[1001]; // ���ڵ��� ������ ���� �迭
int map[4002][4002]; // Ư�� ��ġ�� ���� ������ ���� �迭
bool outed[1001]; // ���ڰ� �Ҹ�Ǿ������� ǥ��

// ���� ��ġ�� ��ȿ���� �˻�
bool check(double x, double y) {
	if (abs(x) > 1000 || abs(y) > 1000) {
		return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	int N;
	int totalEnergy;
	int outCnt; // �Ҹ�� ���� ����
	// 0.5�� �� ������ ��ġ�� �����ϱ� ���� �迭
	double dx[] = { 0.0,0.0,-0.5,0.5 };
	double dy[] = { 0.5,-0.5,0.0,0.0 };

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// �ʱ�ȭ
		totalEnergy = 0;
		outCnt = 0;
		memset(outed, false, sizeof(outed));
		cin >> N;

		for (int i = 0; i < N; i++) {
			cin >> atoms[i].x >> atoms[i].y >> atoms[i].d >> atoms[i].energy;
		}

		// ��� ���ڰ� ���������� ������ �ִ�ð� = �뷫 2001��
		// 0.5�� ������ ������ �������� �����ϹǷ� �ִ� 2001 x 2 = 4002�� ����
		for (int i = 0; i <= 4002; i++) {
			for (int j = 0; j < N; j++) {
				if (outed[j] == true) { // �Ҹ�� ���ڴ� ����
					continue;
				}
				// �����̴� ���⿡ ���� 0.5�� ���� ��ġ�� ����
				atoms[j].x += dx[atoms[j].d];
				atoms[j].y += dy[atoms[j].d];

				// ������ ��ġ�� ��ȿ���� �� �ʰ� -> ���� �ٸ� ���ڿ� �������� �����Ƿ� �Ҹ�Ǿ��ٰ� ����
				if (check(atoms[j].x, atoms[j].y) == false) {
					outed[j] = true;
					outCnt++;
					continue;
				}

				// ������ ��ġ�� map�� ǥ���ϱ� ���� ��ȯ
				int mx = (atoms[j].x + 1000) * 2;
				int my = (atoms[j].y + 1000) * 2;
				map[mx][my]++; // (mx,my) ��ġ�� ���� ������ �ø�
			}

			for (int j = 0; j < N; j++) {
				int mx = (atoms[j].x + 1000) * 2;
				int my = (atoms[j].y + 1000) * 2;

				if (map[mx][my] >= 2) { // ���� ��ġ�� ������ ������ 2�� �̻� -> �浹
					for (int k = 0; k < N; k++) {
						// ���� �Ҹ���� ���� ���ڵ鿡 ���� �������� ���� �� �Ҹ� ǥ��
						if (outed[k] == false && atoms[j].x == atoms[k].x && atoms[j].y == atoms[k].y) {
							totalEnergy += atoms[k].energy;
							outed[k] = true;
							outCnt++;
						}
					}
				}
				map[mx][my] = 0; // Ư�� ��ġ �˻� ���� �� �ٽ� 0���� �ʱ�ȭ
			}

			if (outCnt == N) { // �Ҹ�� ���� ������ ��ü ���� ���� ���ٸ� ����
				break;
			}

		}

		cout << "#" << test_case << " " << totalEnergy << endl;
	}

	return 0;
}