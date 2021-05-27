#include<iostream>
#include<vector>
using namespace std;

class DualSimplex{
	
	private:
		
		int no_coeff,no_slacks;
		vector< vector<float> > mat1;
		vector< vector<float> > mat2;
		
	public:
		
		void setVariables(int no_coeff,int no_slacks){
			this->no_coeff=no_coeff;
			this->no_slacks=no_slacks;
		}
		
		void getTable(){
			for(int i=0;i<no_coeff+1;i++){
				vector<float> temp_arr;
				for(int j=0;j<(no_coeff+no_slacks+1);j++){
					float temp;
					cin>>temp;
					temp_arr.push_back(temp);
				}
				mat1.push_back(temp_arr);
			}
		}
		
		void compute(){
			
			vector<float> cb(no_coeff,0);
			vector<int> bv(no_coeff,0);			
			bool flag=false;
			int iter=1;
			
			while(!flag){
				mat2=mat1;
				vector<float> zj(no_coeff+no_slacks+1,0);
				vector<float> cjzj(no_coeff+no_slacks);
				
				for(int i=0;i<(no_coeff+no_slacks+1);i++){
					for(int j=1;j<no_coeff+1;j++){
						zj[i]+=mat2[j][i]*cb[j-1];
					}
				}
				
				for(int i=0;i<(no_coeff+no_slacks);i++){
					cjzj[i]= -(mat2[0][i]-zj[i]);
				}
				
				fill(zj.begin(),zj.end(),0);
				
				int leaving,entering; float pivot;
				float smallest_leaving=1000.0;
				float min_ratio=1000.0;
				
				for(int i=1;i<no_coeff+1;i++){
					if(mat2[i][no_coeff+no_slacks]<smallest_leaving){
						smallest_leaving=mat2[i][no_coeff+no_slacks];
						leaving=i;
					}
				}
				
				for(int i=0;i<(no_coeff+no_slacks);i++){
					if(mat2[leaving][i]>=0){
						continue;
					}
					else{
						if(cjzj[i]/mat2[leaving][i]<min_ratio){
							min_ratio=cjzj[i]/mat2[leaving][i];
							entering=i;
						}
					}
				}
				
				bv[leaving-1]=entering+1;
				cb[leaving-1]=mat2[0][entering];
				pivot=mat2[leaving][entering];
				
				for(int i=0;i<(no_coeff+no_slacks+1);i++){
					mat1[leaving][i]=mat2[leaving][i]/pivot;
				}
				
				for(int i=1;i<no_coeff+1;i++){
					for(int j=0;j<(no_coeff+no_slacks+1);j++){
						if(i==leaving){
							continue;
						}
						else{
							mat1[i][j]=mat2[i][j]-(mat2[i][entering]*mat1[leaving][j]);
						}
					}
				}
				cout<<endl;
				cout<<"After Iteration "<<iter<<endl;
				iter++;
					
				for(int i=0;i<no_coeff+1;i++){
					for(int j=0;j<no_coeff+no_slacks+1;j++){
						cout<<mat1[i][j]<<" ";
					}
					cout<<endl;
				}		
				
				
				for(int i=1;i<no_coeff+1;i++){
					if(mat1[i][no_coeff+no_slacks]<0){
						flag=false;
						break;
					}
					else{
						flag=true;
					}
				}
			}
			
			vector<int> ans(no_coeff,0);
			vector<float> zj(no_coeff+no_slacks+1,0);
			
			for(int i=0;i<no_coeff;i++){
				if(bv[i]>0){
					ans[bv[i]-1]=mat1[i+1][no_coeff+no_slacks];
				}
				else{
					ans[i]=0;
				}
			}
			
			for(int i=0;i<(no_coeff+no_slacks+1);i++){
					for(int j=1;j<no_coeff+1;j++){
						zj[i]+=mat1[j][i]*cb[j-1];
					}
				}
			
			cout<<"The solution is: "<<endl;
			cout<<"Z: "<<zj[no_coeff+no_slacks]<<endl;
			for(int i=0;i<no_coeff;i++){
				cout<<"X"<<i+1<<": "<<ans[i]<<" ";	
			}	
		}
};


int main(){
	DualSimplex d;
	int coeff,slacks;
	cout<<"Enter the number of coefficients and slack variables"<<endl;
	cin>>coeff>>slacks;
	d.setVariables(coeff,slacks);
	cout<<"Enter the equations"<<endl;
	d.getTable();
	d.compute();
}


/*

Enter the number of coefficients and slack variables
3 3
Enter the equations
1 2 3 0 0 0 0
-2 1 -1 1 0 0 -4
1 1 2 0 1 0 8
0 -1 1 0 0 1 -2

After Iteration 1
1 2 3 0 0 0 0
1 -0.5 0.5 -0.5 -0 -0 2
0 1.5 1.5 0.5 1 0 6
0 -1 1 0 0 1 -2

After Iteration 2
1 2 3 0 0 0 0
1 0 0 -0.5 -0 -0.5 3
0 0 3 0.5 1 1.5 3
-0 1 -1 -0 -0 -1 2
The solution is:
Z: 7
X1: 3 X2: 2 X3: 0

*/
