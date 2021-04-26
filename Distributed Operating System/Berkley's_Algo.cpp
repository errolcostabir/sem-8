#include<iostream>
#include<vector>
using namespace std;

class Berkley {
private:
	int slaves;
	vector<int> hours;
	vector<int> minutes;

public:

	void setSlaves(int n) {
		slaves = n;
	}

	int getSlaves() {
		return slaves;
	}

	void setHours(int n) {
		hours.push_back(n);
	}

	void setMinutes(int n) {
		minutes.push_back(n);
	}

	void display() {
		for (int i = 0; i < slaves + 1; i++) {
			cout << hours[i] << " ";
		}
		for (int i = 0; i < slaves + 1; i++) {
			cout << minutes[i] << " ";
		}
	}

	void compute() {
		int sum=0;
		for (int i = 1; i < slaves + 1; i++) {
			int diff;
			if (hours[i]>=hours[0]) {
				diff = (minutes[i] - minutes[0]) % 60;
				sum += diff;
			}
			else {
				diff = (minutes[i] - minutes[0] - 60) % 60;
				sum += diff;
			}
		}
		sum = sum / (slaves + 1);
		if (sum > 0) {
			minutes[0] = (minutes[0] + sum);
			if (minutes[0] > 59) {
				minutes[0] = minutes[0] % 60;
				hours[0] = hours[0] + 1;
			}
		}
		else {
			minutes[0] = (minutes[0] + sum);
			if (minutes[0]<0) {
				minutes[0] = (minutes[0]+60) % 60;
				hours[0] = hours[0] - 1;
			}
		}
		cout << "Time on Master Clock becomes:: " << hours[0] << ": " << minutes[0] << endl;
		cout << "The change in Slave clocks to synchronize are: " << endl;
		for (int i = 1; i < slaves + 1; i++) {
			int diff;
			if (hours[i]>=hours[0]) {
				diff = minutes[i] - minutes[0];
				cout << "Slave " << i << " clock should decrease by " << diff << " minutes" << endl;
			}
			else {
				diff = (minutes[0] - minutes[i] + 60) % 60;
				cout << "Slave " << i << " clock should increase by " << diff << " minutes" << endl;
			}
		}
	}
};

int main() {
	int h, m, n;
	Berkley b;
	cout << "Enter the number of slave nodes" << endl;
	cin >> n;
	b.setSlaves(n);
	cout << "Enter the times on master and slaves in hrs and mins" << endl;
	for (int i = 0; i < b.getSlaves() + 1; i++) {
		cin >> h >> m;
		b.setHours(h);
		b.setMinutes(m);
	}
	b.compute();
}


/*

Enter the number of slave nodes
2
Enter the times on master and slaves in hrs and mins
3 00 
3 25 
2 50 
Time on Master Clock becomes:: 3: 5
The change in Slave clocks to synchronize are:
Slave 1 clock should decrease by 20 minutes
Slave 2 clock should increase by 15 minutes


Enter the number of slave nodes
2
Enter the times on master and slaves in hrs and mins
14 00
13 46
14 20
Time on Master Clock becomes:: 14: 2
The change in Slave clocks to synchronize are:
Slave 1 clock should increase by 16 minutes
Slave 2 clock should decrease by 18 minutes

*/