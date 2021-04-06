#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// bits ������ Unique ������ �����ϴ��� Ȯ��
bool checkUnique(vector<vector<string>>& relation, string bits) {
	set<string> set; // ���ڿ� ������ ����
	int flag = 1; // 1 : Unique ������ ����, 0 : Unique ������ ����X

	for (int i = 0; i < relation.size(); i++) {
		string str = "";
		for (int j = 0; j < bits.length(); j++) {
			if (bits[j] == '1') { // üũ���ִ� ��Ʈ�� �Ӽ��� �߰�
				str += relation[i][j];
			}
		}

		if (set.find(str) == set.end()) { // ó�� �����ϴ� ���ڿ� ���� -> ���ϼ� ����
			set.insert(str);
		}
		else { // �̹� ������ ���ڿ� ���� -> �ش� ��Ʈ ������ ���ϼ� ����X
			flag = 0;
			break;
		}
	}

	return flag;
}

// ���ڷ� ���� ���� ��Ʈ�� ��ȯ���� �� 1�� ���� count
int count_bit(int n) {
	int ret = 0;

	while (n) {
		if (n & 1) {
			ret++;
		}
		n = n >> 1;
	}

	return ret;
}

// ��Ʈ ��ȯ �� 1�� ������ ���� �������� ����
bool comp(int& a, int& b) {
	return count_bit(a) < count_bit(b);
}

int solution(vector<vector<string>> relation) {
	int answer = 0;
	int n = relation[0].size();
	vector<int> uniqueComb; // ���ϼ��� �����ϴ� ������ ���� ����, 0011 -> ���ϼ� ���� -> 3 ����

	// ��� ������ ���� ��Ʈ�� ǥ��
	// 0000 ~ 1111
	for (int i = 0; i < (1 << (n)); i++) {
		string bits = "";
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) {
				bits += "1";
			}
			else {
				bits += "0";
			}
		}

		if (checkUnique(relation, bits)) { // �ش� ������ ���ϼ��� �����ϸ� �ش� ������ ����� ���� ����
			uniqueComb.push_back(i);
		}
	}

	vector<int> checkMinimal(uniqueComb.size(), 1); // 1 : �ش� ������ �ּҼ��� ����, 0 : �ּҼ� ����X

	sort(uniqueComb.begin(), uniqueComb.end(), comp);

	for (int i = 0; i < uniqueComb.size() - 1; i++) {
		int n = uniqueComb[i]; // ���ϼ��� ������Ű�� i��° ���� ��������

		for (int j = i + 1; j < uniqueComb.size(); j++) { // ������ ��� ����� ���ϸ� �ּҼ��� �����ϴ��� Ȯ��
			if (checkMinimal[j] == 0) { // �̹� �ּҼ��� ������Ű�� ���ϴ� ������ �Ѿ
				continue;
			}

			if ((n & uniqueComb[j]) == n) { // �����ϰ� �ִ� ��Ʈ�� �ִٸ� -> ����� �Ӽ��� �ִٸ�
				checkMinimal[j] = 0; // �ش� ������ �ּҼ� ����X
			}
		}
	}

	for (int i = 0; i < uniqueComb.size(); i++) { // ���ϼ��� �����ϴ� ��� ���� ��
		if (checkMinimal[i]) { // �ּҼ��� �����ϴ� ������ count
			answer++;
		}
	}

	return answer;
}