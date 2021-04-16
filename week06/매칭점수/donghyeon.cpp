#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

typedef struct _pageInfo { // page�� ������ ���� ����ü
	int index; // page�� index
	string content; // page�� content
	vector<string> links; // page�� �ܺθ�ũ���� content
	int baseScore; // page�� �⺻����
	double machingScore = 0.0L; // page�� ��Ī����
}PageInfo;
vector<PageInfo> pageInfoArr; // �������� �������� �����ϴ� �迭

// ���� ���� : ��Ī���� �������� -> �ε��� ��������
bool compare(PageInfo p1, PageInfo p2) {
	return p1.machingScore != p2.machingScore ? p1.machingScore > p2.machingScore : p1.index < p2.index;
}

// ������������ content�� �������� �Լ�
string getContent(string pages) {
	string content = "";
	string pattern = "<meta property=\"og:url\" content="; // ã�ƾ��ϴ� ����ǥ���� ����
	int index = pages.find(pattern); // �ش� ������ ��ġ�� ã��

	index += pattern.length() + 1; // content ���� ���� ��ġ = ���� ��ġ + ���� ���� + 1

	// " " �ȿ� �ִ� content ������ ������
	for (int i = index; i < pages.length(); i++) {
		if (pages[i] == '\"') {
			break;
		}
		content += pages[i];
	}

	return content;
}

// �⺻ ������ ���ϴ� �Լ�
int getBaseScore(string word, string pages) {
	string pattern = "<body>\n"; // ã�ƾ��ϴ� ����ǥ���� ����
	int index = pages.find(pattern); // �ش� ������ ��ġ�� ã��
	index += pattern.length(); // �ܺθ�ũ ���� ���� ��ġ = ���� ��ġ + ���� ����

	string tmp = ""; // body ��ũ�� �ܾ�� �ӽ�����
	int baseScore = 0; // �⺻����

	for (int i = index; i < pages.length(); i++) {
		if (isalpha(pages[i])) { // ���ĺ��� ��쿡�� ����
			tmp += tolower(pages[i]);
		}
		else { // ���ĺ��� �ƴϸ�
			if (tmp == word) { // ������� ������ �ܾ word�� ��ġ�ϴ��� Ȯ��
				baseScore++;
			}
			tmp = ""; // �ӽ����� �ܾ� �ʱ�ȭ
		}
	}

	return baseScore;
}

// �ܺθ�ũ �ּҵ��� �������� �Լ�
vector<string> getLinks(string pages) {
	vector<string> links; // �ܺθ�ũ �ּҸ� ����
	string pattern = "<a href="; // ã�ƾ��ϴ� ����
	int index = 0;

	// index ��ġ���� ������ ��� �߰��� ������ �ݺ�
	while ((index = pages.find("<a href=", index)) != string::npos) {
		string link = "";
		index += pattern.length() + 1; // �ܺθ�ũ �ּ� ���� ���� ��ġ = ���� ��ġ + ���� ���� + 1
		for (int i = index; i < pages.length(); i++) { // " " �ȿ� ���� �ܺθ�ũ�� �ּ� ������ ������
			if (pages[i] == '\"') {
				break;
			}
			link += pages[i];
		}
		links.push_back(link);
	}

	return links;
}

// page -> ���� �ʿ��� ������ �����ؼ� PageInfo ���·� ����
PageInfo getPageInfo(string word, string page, int index) {
	PageInfo pageInfo;
	pageInfo.index = index;
	pageInfo.content = getContent(page);
	pageInfo.baseScore = getBaseScore(word, page);
	pageInfo.links = getLinks(page);

	return pageInfo;
}

int solution(string word, vector<string> pages) {
	int answer = 0;

	transform(word.begin(), word.end(), word.begin(), ::tolower); // �˻�� �ҹ��ڷθ� ����

	for (int i = 0; i < pages.size(); i++) {
		PageInfo pageInfo = getPageInfo(word, pages[i], i); // i��° �������� ���� ������ �����ͼ�	
		pageInfoArr.push_back(pageInfo); // ������ �������� �����ϴ� �迭�� ����
	}

	// �� �������� ��Ī������ ����
	for (int i = 0; i < pageInfoArr.size(); i++) {
		string content = pageInfoArr[i].content;
		pageInfoArr[i].machingScore += (double)pageInfoArr[i].baseScore; // �켱 �⺻������ ������
		for (int j = 0; j < pageInfoArr.size(); j++) { // �ٸ� ���������� ����
			if (i != j) {
				for (int k = 0; k < pageInfoArr[j].links.size(); k++) { // �ٸ� ���������� �ܺθ�ũ ����
					// ���� �ٸ� �������� �ܺθ�ũ�� ���� �����ϴ� ������ �ּҰ� ���ԵǾ��ִٸ�
					if (content == pageInfoArr[j].links[k]) {
						// ���� ������ ��Ī������ �����ϴ� �������� ��ũ������ ������
						pageInfoArr[i].machingScore +=
							(double)pageInfoArr[j].baseScore / pageInfoArr[j].links.size();
						break;
					}
				}
			}
		}
	}

	// ���� �� ù ��° �������� �ε����� ����
	sort(pageInfoArr.begin(), pageInfoArr.end(), compare);
	answer = pageInfoArr[0].index;

	return answer;
}