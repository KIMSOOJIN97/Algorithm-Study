#include <string>
#include <vector>
#include <stack>

using namespace std;

// �ùٸ� ���ڿ����� üũ
bool checkRightStr(string u) {
	if (u.length() == 0) {
		return true;
	}

	// ���� -> ¦�� �´��� Ȯ��
	stack<char> s;
	s.push(u[0]);

	for (int i = 1; i < u.length(); i++) {
		if (u[i] == '(') {
			s.push(u[i]);
		}
		else {
			if (s.top() == '(') {
				s.pop();
			}
			else {
				s.push(u[i]);
			}
		}
	}

	if (!s.empty()) {
		return false;
	}
	return true;
}

// �ùٸ� ���ڿ��� ����
string makeRightStr(string w) {
	// 1�ܰ� : �� ���ڿ� -> ��ȯ
	if (w.length() == 0) {
		return "";
	}

	string u = "";
	string v = "";
	string rightStr = ""; // ��� ���ڿ�
	int cnt1 = 0; // ���� '('�� ����
	int cnt2 = 0; // ���� ')'�� ����

	// 2�ܰ� : ���ڿ� w�� �������� ���ڿ� u, v�� �и�
	for (int i = 0; i < w.length(); i++) {
		// ���� '('�� ')'�� ������ ī��Ʈ
		if (w[i] == '(') {
			cnt1++;
		}
		else {
			cnt2++;
		}
		u += w[i];

		if (cnt1 == cnt2) { // ���� '('�� ')'�� ������ ���� ���� u�� �������� ���ڿ� Ȯ��
			for (int j = i + 1; j < w.length(); j++) { // ������ ���ڿ��� v�� 
				v += w[j];
			}
			break;
		}
	}

	if (checkRightStr(u)) { // 3�ܰ� : u�� �ùٸ� ���ڿ��̶�� v�� ���� 1�ܰ� �ٽ� ����
		rightStr = u + makeRightStr(v); // 3-1�ܰ� : ������ ��� ���ڿ��� u�� �̾���̰� ��ȯ
	}
	else { // 4�ܰ� : u�� �ùٸ� ���ڿ��� �ƴϸ�
		rightStr += '('; // 4-1�ܰ� : ù ���ڷ� '(' ����
		rightStr += makeRightStr(v); // 4-2�ܰ� : ���ڿ� v�� ���� 1�ܰ���� ��������� ������ ����� ����
		rightStr += ')'; // 4-3�ܰ� : ')'�� �ٽ� ����

		// 4-4�ܰ� : �� ��°���� ������-1 ���ڿ����� ��ȣ ������ ����� ���� 
		for (int i = 1; i < u.length() - 1; i++) {
			if (u[i] == '(') {
				rightStr += ')';
			}
			else {
				rightStr += '(';
			}
		}
	}

	return rightStr; // ���� ��� ���ڿ��� ��ȯ
}

string solution(string p) {
	string answer = "";

	return makeRightStr(p);
}