#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n = 6;
	vector<int> m1{ 3,12,5,2,9,11};
	vector<int> m2{ 8,10,9,6,3,1 };
	vector<int> optimal_sequence(n,0);
	vector<bool> complete(n,false);
	int index,machine,front=0,back=n-1;
	while (true) {
		int min = 1000;
		for (int i = 0; i < n; i++) {
			if (!complete[i] && (m1[i] < min || m2[i] < min)) {
				if (m1[i] < min) {
					machine = 1;
					min = m1[i];
					index = i + 1;
				}
				if (m2[i] < min) {
					machine = 2;
					min = m2[i];
					index = i + 1;
				}
			}
		}
		complete[index - 1] = true;
		if (machine == 1) {
			optimal_sequence[front] = index;
			front++;
		}
		else {
			optimal_sequence[back] = index;
			back--;
		}
		if (front > back) {
			break;
		}
	}

	cout << "Optimal Sequence: ";
	for (int i = 0; i < n; i++) {
		cout << optimal_sequence[i] << " ";
	}
	int m1_time_in = 0, m1_time_out = 0, m2_time_in = 0, m2_time_out = 0,prev_timeout=0;
	int idle_time = 0;
	for (int i = 0; i < n; i++) {
		m1_time_in = m1_time_out;
		m1_time_out = m1_time_in + m1[optimal_sequence[i]-1];
		m2_time_in = max(m1_time_out, m2_time_out);
		m2_time_out = m2_time_in + m2[optimal_sequence[i]-1];
		if (i == 0) {
			idle_time += m1_time_out - m1_time_in;
		}
		else {
			idle_time += m2_time_in - prev_timeout;
		}
		prev_timeout = m2_time_out;
	}

	cout << "\nIdle  time on machine 1: " << m2_time_out - m1_time_out << endl;
	cout << "Idle time on machine 2: " << idle_time << endl;
	cout << "Total elapsed time: " << m2_time_out << endl;
}

/*
Output:
Optimal Sequence: 4 1 3 2 5 6
Idle  time on machine 1: 1
Idle time on machine 2: 6
Total elapsed time: 43
*/