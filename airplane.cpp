#ifndef Included_NameModel_H
#define Included_NameModel_H
#include <iostream>


class airplane{
	private:
	int flightnum;
	int** seat;
	int availableSeats;
	int row;
	int col;
	public:
/*	
	airplane(){
		seat = new int*[0];
		
	}	
*//*
	~airplane(){
		for(int i=0; i<row;i++)
			delete seat[i];
		delete seat;
	}
	*/
	void setFlightNum(int num){
		flightnum = num;

	}

	void setSeat(int a, int b){
		delete seat;
		seat = new int*[a];
		for(int i =0; i<a; i++)
			seat[i] = new int[b];

		for(int i = 0; i<a; i++)
			for(int j =0; j<b; j++)
				seat[i][j] = 0;

		row=a;
		col = b;
		availableSeats=a*b;
	}

	int getFlightNum(){
		return flightnum;
	}

	void reserveSeat(int a, char b){
		//int col = 0;
		if(seat[a-1][b-65]==1);
			//std::cout<<"Seat is taken"<<std::endl;
		else{
			//std::cout<<a<<" "<<b<<" has been reserved"<<std::endl;
			seat[a-1][b-65] = 1;
			availableSeats--;
		}
	}

	void showFlightDetails(){

		std::cout<<"Flight: "<<flightnum<<" ("<<availableSeats<<" available seats)"<<std::endl;

	}

	void showFlightSeats(){


		for(int i=0; i<=row;i++)
        {

			for(int j=0;j<col;j++)
            {
				if(i==0)
				{
					std::cout<<static_cast<char>(65+j)<<" ";

				}
				if(j==0 && i!=0)
				std::cout<<i;
				if(i!=0 && seat[i-1][j]==0)
				std::cout<<" O";
				if(i!=0 && seat[i-1][j]==1)
				std::cout<<" X";


			}
			std::cout<<std::endl;

		}

	}

	void cancelSeat(int a, int b){
		seat[a-1][b-65] = 0;
		availableSeats++;

	}

};
#endif // Included_NameModel_H
