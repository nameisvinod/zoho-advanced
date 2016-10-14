#include "iostream"
#include "map"
#include "vector"
// #include "priorityqueue"
using namespace std;
#define n 4
#define dist 15
// #define duration 1
#define minCharge 100
#define ChargePerKm 10
enum points {A, B, C, D, E, F};

class Taxi
{
	public:
		int id;
		int nextFreeTime;
		int currentLocation;
		int totalFare;
		Taxi(){
			this->nextFreeTime = 0;
			this->currentLocation = 0;
			this->totalFare = 0;
		};
		Taxi(int id){
			this->id = id;
			this->nextFreeTime = 0;
			this->currentLocation = 0;
			this->totalFare = 0;
		}
		void details(){
			cout<<"\nTaxi id: "<< id+1;
			cout<<"\nNext free time: "<< nextFreeTime;
			char ch = 'A'+currentLocation;
			cout<<"\nCurrent Location : "<< ch;
			cout<<"\nTotal Fare : "<< totalFare;
			cout<<"\n\n";
		}
};
struct myComparator
{
	bool operator()(const Taxi& lhs, const Taxi& rhs)
	{
	  return lhs.nextFreeTime < rhs.nextFreeTime;
	}
};
class Journey{
	public:
		int custId;
		int pickUpPoint;
		int dropPoint;
		int startTime;
		int endTime;
		int fare;
		
		Journey(){};
		// Journey(int custId, int pickUpPoint, int dropPoint, int startTime, int endTime){
		// 	this->custId = custId;
		// 	this->pickUpPoint = pickUpPoint;
		// 	this->dropPoint = dropPoint;
		// 	this->startTime = startTime;
		// 	this->endTime = endTime;
		// }
		void getJourneyDetails(){
			cout<<"Customer id : ";
			cin>> this->custId;
			cout<<"pickUpPoint : ";
			char ch;
			cin>> ch;
			this->pickUpPoint = ch - 'A';
			cout<<"dropPoint : ";
			cin>> ch;
			this->dropPoint = ch - 'A';
			cout<<"startTime : ";
			cin>> this->startTime;
		}
		void setFare(int fare){
			this->fare = fare;
		}
		void journeyDetails(){
			cout<<"CustomerID"<<custId<<endl;
			char ch = pickUpPoint+ 'A';
			cout<<"pickUpPoint : "<<ch<<endl;
			ch = dropPoint + 'A';
			cout<<"dropPoint : "<<ch<<endl;
			cout<<"startTime : "<<startTime;
			cout<<"fare : "<<fare<<endl;
		}
};
class TaxiStation{
	public:
		Taxi taxis[n];
		map<int, vector<Journey> > taxiJourney;
		
		TaxiStation(){};
		int isFree(Taxi t, Journey j){
			return(t.nextFreeTime<=j.startTime);
		}
		void initialise(){
			for (int i = 0; i < n; ++i){
				taxis[i].id = i;
			}
		}
		Taxi getBestTaxi(Journey journey){
			Taxi bestTaxi;
			int i;
			bool done = false;
			for (i = 0; i < n; ++i)
				if(isFree(taxis[i], journey)){
					done = true;
					bestTaxi = taxis[i];
					break;
				}
			int distance = abs(journey.pickUpPoint - bestTaxi.currentLocation);
			for(;i<n;i++){
				if(isFree(taxis[i], journey) && abs(journey.pickUpPoint - taxis[i].currentLocation) < distance){
					cout<<i<<endl;
					distance = abs(journey.pickUpPoint - taxis[i].currentLocation);
					bestTaxi = taxis[i];
				}
			}
			if(!done){
				return Taxi(-1);
			}
			return bestTaxi;
		}
		void taxiJourneySetUp(int id, Journey journey){
			int duration = abs(journey.dropPoint - journey.pickUpPoint);
			taxis[id].nextFreeTime = journey.startTime + duration;
			int fare = (abs(journey.dropPoint - journey.pickUpPoint)*15 - 5)*10 + 100;
			taxis[id].totalFare+=fare;
			taxis[id].currentLocation = journey.dropPoint;
			journey.fare = fare;
			journey.endTime = journey.startTime + duration;
			taxis[id].details();
			taxiJourney[id].push_back(journey);
		}
		void assignTaxi(Journey journey){
			// Taxi bestTaxi = taxisQueue.top(); taxisQueue.pop();
			Taxi bestTaxi = getBestTaxi(journey);
			// cout<< bestTaxi.id<<endl; 
			int id = bestTaxi.id;
			if(id==-1){
				cout<<"No taxis available at the moment "<<endl;
				return;	
			}else{
				cout<<"Taxi can be allotted."<<endl;
				cout<<"Taxi- " << id+1 <<"is allotted "<<endl;
			}
			//map taxi to journey
			taxiJourneySetUp(id, journey);
		}
		void getJourneyDetails(){
			Journey journey;
			journey.getJourneyDetails();
			assignTaxi(journey);
		}
		void taxiDetails(){
			for(map<int, vector<Journey> >::iterator it = taxiJourney.begin();it!=taxiJourney.end();it++){
				taxis[it->first].details();
				for(vector<Journey>::iterator i = (it->second).begin();i!=(it->second).end();i++)
					(*i).journeyDetails();
			}
		}
};

int main(int argc, char const *argv[])
{
	TaxiStation ts;
	ts.initialise();
	ts.taxiDetails();
	int i = 3;
	while(i--){
		ts.getJourneyDetails();
	}
	ts.taxiDetails();
	return 0;
}