#include<iostream>
#include<vector>
#define M 100
using namespace std;

class BigM {

private:
	int no_coeff, no_surplus, no_artificial;
	vector<vector<float> > mat1;
	vector<vector<float> > mat2;

public:
	void getValues(int no_coeff,int no_surplus,int no_artificial) {
		this->no_coeff = no_coeff;
		this->no_surplus = no_surplus;
		this->no_artificial = no_artificial;
	}

	void getMatrix() {
		for (int i = 0; i < no_surplus+1; i++) {
			vector<float> temp1;
			for (int j = 0; j < no_coeff + no_surplus + no_artificial + 1; j++) {
				float temp2;
				cin >> temp2;
				temp1.push_back(temp2);
			}
			mat1.push_back(temp1);
		}
	}

	void compute() {
		vector<float> cb(no_surplus,M);
		vector<int> bv(no_surplus,0);
		bool flag = false;
		int iter = 1;
		while (!flag) {
			vector<float> Zj(no_artificial + no_coeff + no_surplus + 1, 0);
			vector<float> cjzj(no_artificial + no_coeff + no_surplus);
			mat2 = mat1;
			for (int i = 0; i < no_artificial + no_coeff + no_surplus + 1; i++) {
				for (int j = 1; j < no_surplus + 1; j++) {
					Zj[i] += cb[j - 1] * mat2[j][i];
				}
			}
			for (int i = 0; i < no_artificial + no_coeff + no_surplus; i++) {
				cjzj[i] = mat2[0][i] - Zj[i];
			}
			fill(Zj.begin(), Zj.end(), 0);
			int leaving, entering; float vertex;
			float smallest = 9000.0;
			for (int i = 0; i < no_artificial + no_coeff + no_surplus; i++) {
				if (cjzj[i] < smallest) {
					smallest = cjzj[i];
					entering = i;
				}
			}
			float smallest_row = 9000.0;
			for (int i = 1; i < no_surplus + 1; i++) {
				float temp = mat1[i][no_artificial + no_coeff + no_surplus] / mat2[i][entering];
				if (temp < smallest_row) {
					smallest_row = temp;
					leaving = i;
				}
			}
			vertex = mat2[leaving][entering];
			bv[leaving - 1] = entering + 1;
			cb[leaving - 1] = mat2[0][entering];
			for (int i = 0; i < no_artificial + no_coeff + no_surplus + 1; i++) {
				mat1[leaving][i] = mat2[leaving][i] / vertex;
			}
			for (int i = 1; i < no_surplus + 1; i++) {
				for (int j = 0; j < no_artificial + no_coeff + no_surplus + 1; j++) {
					if (i == leaving) {
						continue;
					}
					else {
						mat1[i][j] = mat2[i][j] - (mat2[i][entering] * mat1[leaving][j]);
					}
				}
			}
			cout << "Iteration " << iter<<": "<< endl;
			iter++;
			for (int i = 0; i < no_surplus + 1; i++) {
				for (int j = 0; j < no_coeff + no_surplus + no_artificial + 1; j++) {
					cout << mat1[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
			for (int i = 0; i < no_surplus; i++) {
				if (bv[i] == 0) {
					flag = false;
					break;
				}
				else {
					flag = true;
				}
			}
		}
		vector<float> Z(no_artificial + no_coeff + no_surplus + 1, 0);
		for (int i = 0; i < no_artificial + no_coeff + no_surplus + 1; i++) {
			for (int j = 1; j < no_surplus + 1; j++) {
				Z[i] += cb[j - 1] * mat1[j][i];
			}
		}
		vector<int> soln(no_coeff,0);
		for (int i = 0; i < no_surplus; i++) {
			soln[bv[i]-1] = cb[i];
		}
		cout << "The soln is: " << endl;
		cout << "Z: " << Z[no_artificial + no_coeff + no_surplus] << endl;
		for (int i = 0; i < no_coeff; i++) {
			cout << "X" << i + 1 << ": " << soln[i] <<" ";
		}
	}
};

int main() {
	BigM b;
	int coeff, surplus, artificial;
	cout << "Enter the number of coefficients, surplus variables and artificial variables" << endl;
	cin >> coeff >> surplus >> artificial;
	b.getValues(coeff, surplus, artificial);
	cout << "Enter the matrix (1000 for M)" << endl;
	b.getMatrix();
	b.compute();
}

/*

Output:

Enter the number of coefficients, surplus variables and artificial variables
3 2 2
Enter the matrix (1000 for M)
7 15 20 0 0 100 100 0
2 4 6 -1 0 1 0 24
3 9 6 0 -1 0 1 30
Iteration 1:
7 15 20 0 0 100 100 0
0.666667 0 3.33333 -1 0.444444 1 -0.444444 10.6667
0.333333 1 0.666667 0 -0.111111 0 0.111111 3.33333

Iteration 2:
7 15 20 0 0 100 100 0
0.2 0 1 -0.3 0.133333 0.3 -0.133333 3.2
0.2 1 0 0.2 -0.2 -0.2 0.2 1.2

The soln is:
Z: 82
X1: 0 X2: 15 X3: 20

*/