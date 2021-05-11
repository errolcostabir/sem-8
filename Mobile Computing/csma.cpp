#include<iostream>
#include<vector>
#include<map>
#include<iterator>
using namespace std;

class CSMA{
	private:
		int no_of_senders;
		map<int,int> senders;
		vector<int> transmission;
	
	public:
		void setSenders(int n){
			no_of_senders=n;
		}
		
		void start_and_duration(){
			int start_time,duration_time;
			for(int i=0;i<no_of_senders;i++){
				cin>>start_time>>duration_time;
				senders.insert(pair<int,int> (start_time,duration_time));
			}
		}
		
		void getSenders(){
			map<int,int>::iterator itr;
			for(itr=senders.begin();itr!=senders.end();itr++){
				cout<<itr->first<<" "<<itr->second<<endl;
			}
		}
		
		void compute(){
			int temp_duration=senders.begin()->first+senders.begin()->second;
			transmission.push_back(senders.begin()->first);
			int start_value=senders.begin()->first;
			map<int,int>::iterator itr=senders.begin();
			itr++;
			for(;itr!=senders.end();itr++){
				if(itr->first<temp_duration){
					transmission.push_back(temp_duration);
				}
				else{
					transmission.push_back(itr->first);
				}
			}
		}
		
		void getAns(){
			for(int i=0;i<transmission.size();i++){
				cout<<transmission[i]<<" ";
			}
			vector<int> collisions;
			for(int i=1;i<transmission.size();i++){
				if(transmission[i]==transmission[i-1]){
					collisions.push_back(i-1);
					collisions.push_back(i);
				}
			}
			cout<<endl;
			if(collisions.size()>0){
				cout<<"Collisions between: "<<endl;
				for(int i=0;i<collisions.size();i++){
					cout<<collisions[i]+1<<" ";
				}
				cout<<"at "<<transmission[collisions[0]];
			}
			else{
				cout<<"No collisions"<<endl;
			}
		}
};

int main(){
	int n;
	CSMA c;
	cout<<"Enter no of senders"<<endl;
	cin>>n;
	cout<<"Enter the start and duration time"<<endl;
	c.setSenders(n);	
	c.start_and_duration();
	cout<<"Transmissions begin at: "<<endl;
	c.compute();
	c.getAns();
}



/*
Enter no of senders
3
Enter the start and duration time
1 4
6 2
5 3
Transmissions begin at:
1 5 6
No collisions



Enter no of senders
3
Enter the start and duration time
1 4
2 4
4 3
Transmissions begin at:
1 5 5
Collisions between:
2 3 at 5

*/
