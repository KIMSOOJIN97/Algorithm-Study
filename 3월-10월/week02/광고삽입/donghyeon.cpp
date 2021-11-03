#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// delimeter �������� ���ڿ� �и�
vector<string> splitStr(string str, char delimeter) {
	vector<string> split_str;
	string tmp = "";

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == delimeter) {
			split_str.push_back(tmp);
			tmp = "";
		}
		else {
			tmp += str[i];
		}
	}
	split_str.push_back(tmp);

	return split_str;
}

// �ð� -> int�� ������
int getTime(vector<string> time) {
	int hour = stoi(time[0]) * 60 * 60;
	int minute = stoi(time[1]) * 60;
	int second = stoi(time[2]);

	return hour + minute + second;
}

string solution(string play_time, string adv_time, vector<string> logs) {
	string answer = "";
	int end_time = getTime(splitStr(play_time, ':')); // ������ ��� �ð�
	int adv_playing_time = getTime(splitStr(adv_time, ':')); // ���� ��� �ð�
	vector<int> cnt(360001, 0); // 0�� ~ 360000�ʱ��� ��û�� ��� Ƚ���� ����
	                            // cnt[i] -> i�ʿ� �������� ����� ��û�� ��

	// ������ ��� �ð����� ���� �ð��� ��� ���� ���� �ð��� �� ó���� ���� 
	if (end_time <= adv_playing_time) {
		answer = "00:00:00";
		return answer;
	}

	for (int i = 0; i < logs.size(); i++) {
		// �α� ��� -> ��û�� ��� ���� �ð�, �� �ð�
		vector<string> splited = splitStr(logs[i], '-');
		int st = getTime(splitStr(splited[0], ':'));
		int et = getTime(splitStr(splited[1], ':'));

		// ��û�� ��� ���� �ð� ~ �� �ð����� ��� Ƚ���� ����
		for (int j = st; j < et; j++) {
			cnt[j]++;
		}
	}

	int start_time = 0; // ���� ���� ���� �ð�
	long long total_cnt = 0; // ���� ��� �ð�
	long long max_total_cnt = 0; // �ִ� ���� ��� �ð�
	for (int i = start_time; i < adv_playing_time; i++) {
		total_cnt += cnt[i]; // �ð� �ð����� ���� ����ð� ���� ���� ��� Ƚ���� ����
	}
	max_total_cnt = total_cnt;

	int i = start_time;
	while (1) {
		// i ~ (i + adv_playing_time)���� ���� -> (i + 1) ~ (i + adv_playing_time + 1)���� ������ ����
		// (a+1 ~ b+1)���� ������ = (a~b)������ ������ - a���� �� + (b+1)���� ��
		total_cnt -= cnt[i];
		total_cnt += cnt[i + adv_playing_time];
		i++;

		// �κ� �������� ���� ū ���� ����
		if (total_cnt > max_total_cnt) {
			max_total_cnt = total_cnt;
			start_time = i;
		}

		// ������ ���۽ð� + ����ð� -> ������ ����ð����� ũ�� ����
		if (i + adv_playing_time > end_time) {
			break;
		}
	}



	// ���� �ð� ���ڿ� -> �ð�, ��, �ʴ����� ����
	string hour = to_string(start_time / 3600);
	string minute = to_string((start_time % 3600) / 60);
	string second = to_string(start_time % 60);

	// "X" -> "0X"�� ����� ����
	if (hour.length() == 1) {
		hour = "0" + hour;
	}
	if (minute.length() == 1) {
		minute = "0" + minute;
	}
	if (second.length() == 1) {
		second = "0" + second;
	}

	answer = hour + ":" + minute + ":" + second;

	return answer;
}