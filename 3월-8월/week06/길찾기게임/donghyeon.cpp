#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct _node { // ����� ������ ���� ����ü
	int x;
	int y;
	int num;
	int left;
	int right;
}Node;
vector<Node> nodes; // ������ ������ ���� ����
vector<int> preorder; // ���� ��ȸ���� ���� �湮 ����
vector<int> postorder; // ���� ��ȸ���� ���� �湮 ����

// ���� ���� : y�� ���� �������� -> x�� ���� ��������
bool comp(Node n1, Node n2) {
	return n1.y != n2.y ? n1.y > n2.y : n1.x < n2.x;
}

// ����Ʈ���� ����� �Լ�
// �� ��忡 �θ� ��Ī������
void make_binary_tree(int nodeNum, int parent) {
	if (nodes[nodeNum].x < nodes[parent].x) { // �θ� ��庸�� x���� ���� ���
		if (nodes[parent].left == -1) { // �θ� ����� ���� �ڽ��� ������ ����
			nodes[parent].left = nodeNum;
		}
		else { // ���� �ڽ��� �ִٸ� ���� �ڽ��� �θ� ���� ���
			make_binary_tree(nodeNum, nodes[parent].left);
		}
	}
	else { // �θ� ��庸�� x���� ū ���
		if (nodes[parent].right == -1) { // �θ� ����� ������ �ڽ��� ������ ����
			nodes[parent].right = nodeNum;
		}
		else { // ������ �ڽ��� �ִٸ� ������ �ڽ��� �θ� ���� ���
			make_binary_tree(nodeNum, nodes[parent].right);
		}
	}

	return;
}

// ���� ��ȸ
// ���� ��尪 ���� -> ���� �ڽ� �湮 -> ������ �ڽ� �湮
void dfs_pre(int idx) {
	preorder.push_back(nodes[idx].num + 1);

	if (nodes[idx].left != -1) {
		dfs_pre(nodes[idx].left);
	}
	if (nodes[idx].right != -1) {
		dfs_pre(nodes[idx].right);
	}
}

// ���� ��ȸ
// ���� �ڽ� �湮 -> ������ �ڽ� �湮 -> ���� ��尪 ����
void dfs_post(int idx) {
	if (nodes[idx].left != -1) {
		dfs_post(nodes[idx].left);
	}
	if (nodes[idx].right != -1) {
		dfs_post(nodes[idx].right);
	}
	postorder.push_back(nodes[idx].num + 1);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer;

	// ��� ���� ����
	for (int i = 0; i < nodeinfo.size(); i++) {
		Node node;
		node.x = nodeinfo[i][0];
		node.y = nodeinfo[i][1];
		node.num = i;
		node.left = -1;
		node.right = -1;
		nodes.push_back(node);
	}

	sort(nodes.begin(), nodes.end(), comp); // ��� ����

	// ����Ʈ���� ����
	for (int i = 1; i < nodes.size(); i++) {
		make_binary_tree(i, 0);
	}

	dfs_pre(0);
	dfs_post(0);

	answer.push_back(preorder);
	answer.push_back(postorder);

	return answer;
}