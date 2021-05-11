#include<iostream>
#include<vector>
#include<map>
#include<iterator>
#include<cstdlib>
#include<time.h>
using namespace std;

class CSMA{
	private:
		int no_of_senders;
		map<int,int> senders;
		
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
			
			vector<int> transmission(no_of_senders);
			vector<bool> completed(no_of_senders,false);
			vector<int> rand_time(no_of_senders);
			vector<int> duration;
			
			map<int,int>::iterator itr=senders.begin();
			    itr++;
				for(;itr!=senders.end();itr++){
					duration.push_back(itr->second);
				}
			
			int cntr=no_of_senders;
			bool cmpl=false;
			
			int temp_duration=senders.begin()->first+senders.begin()->second;
			transmission[0]=senders.begin()->first;
			completed[0]=true;
			cntr--;
			
			while(!cmpl){
				srand(time(0));
				for(int i=0;i<no_of_senders;i++){
					if(!completed[i]){		
						rand_time[i]=rand()%6;
					}
				}
				int min_index,min=1000;
				for(int i=0;i<no_of_senders;i++){
					if(!completed[i]){
						if(rand_time[i]<min){
							min=rand_time[i];
							min_index=i;
						}
					}
				}
				
				temp_duration+=min;
				completed[min_index]=true;
				transmission[min_index]=temp_duration;
				temp_duration+=duration[min_index-1];
				
				for(int i=0;i<no_of_senders;i++){
					if(completed[i]){
						cmpl=true;
					}
					else{
						cmpl=false;
						break;
					}
				}
			}
			
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
}


/*

Enter no of senders
3
Enter the start and duration time
1 4
2 4
4 3
Transmissions begin at:
1 12 5
No collisions


Enter no of senders
4
Enter the start and duration time
1 4
2 4
4 3
6 3
Transmissions begin at:
1 6 11 15
No collisions

*/

