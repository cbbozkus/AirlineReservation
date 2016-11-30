
#define PLANE_NUM 100
#include "airplane.cpp"
#include <iostream>

class ReservationSystem {

/*ReservationSystem();
~ReservationSystem();
void addFlight( const int flightNo, const int rowNo, const int seatNo );
void cancelFlight( const int flightNo );
void showAllFlights();
void showFlight( const int flightNo );
int makeReservation( const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol );
void cancelReservation( const int resCode );
void showReservation( const int resCode );
*/
private:
airplane *planes;
int countP;
int resCount;
int*** resCodes;

public:

ReservationSystem(){
	countP=0;
	resCount=0;
	planes= new airplane[0];
	resCodes = new int**[PLANE_NUM];
	for(int i=0; i<PLANE_NUM;i++)
    {
		resCodes[i] = new int*[4];
    }
}

~ReservationSystem(){
	delete []planes;
	for(int i=0; i<PLANE_NUM;i++){
		//for(int a =0; a<4; a++){
			//if(a==2 || a==3)
			//	delete res
			//delete resCodes[i][a];
		//}
		delete resCodes[i];
	}
	delete resCodes;
	
}

void showAllFlights(){
    if(countP == 0)
    {
        std::cout << "No flights exist" << std::endl;
        std::cout<<std::endl;
    }
    else
    {
        std::cout<<std::endl;
        std::cout << "Flights currently operated: " << std::endl;

        for(int i=0; i<countP; i++)
        {
            planes[i].showFlightDetails();
        }
        std::cout<<std::endl;
	}
}

void addFlight( const int flightNo, const int rowNo, const int seatNo ){
	for(int i= 0; i<countP; i++)
		if(planes[i].getFlightNum() == flightNo){
			std::cout<<"Flight "<<flightNo<<" already exists"<<std::endl;
			return;
		}

	airplane *a = new airplane();
	(*a).setFlightNum(flightNo);
	(*a).setSeat(rowNo, seatNo);
	airplane *temp = new airplane[countP+1];
	for(int i = 0; i<countP; i++){
		temp[i] = planes[i];
	}
	//for(int i=0; i<countP ;i++)
		//delete planes[i];
	delete []planes;
	planes = temp;
	planes[countP] = *a;
	delete a;
	countP++;
    std::cout << "Flight " << flightNo << " has been added" << std::endl;
}

void showFlight( const int flightNo )
{
	for(int i=0; i<countP; i++){
		if(planes[i].getFlightNum()==flightNo)
        {
			planes[i].showFlightDetails();
			planes[i].showFlightSeats();
		}

	}
	std::cout << std::endl;

}

int makeReservation( const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol ){
	bool e = false;
	for(int i=0; i<countP; i++)
		if(planes[i].getFlightNum() == flightNo)
			e = true;
	if(!e){
		std::cout<<"Flight "<<flightNo<<" does not exist"<<std::endl;
		return -1;
	}
    else{
	bool q = false;
	int *rowTemp= new int[numPassengers];
	char *colTemp = new char[numPassengers];
	int tempPassengers=0;
	for(int a =0; a<resCount;a++){
			for(int c=0; c<numPassengers; c++)
            {
				for(int d = 0; d<*(resCodes[a][1]); d++)
                {
					if(resCodes[a][2][d] == seatRow[c] && static_cast<char>(resCodes[a][3][d]) == seatCol[c])
                    {
						rowTemp[tempPassengers] = seatRow[c];
						colTemp[tempPassengers] = seatCol[c];
						tempPassengers++;
						q = true;
					}
                }
            }
	}
	if(q){
		for(int i=0; i<tempPassengers; i++)
			std::cout<<rowTemp[i]<<colTemp[i]<<" ";
		std::cout<<"is not available"<<std::endl;
	}
 	else{

	for(int i=0; i<countP; i++){
		if(flightNo==planes[i].getFlightNum())
			for(int j=0; j<numPassengers; j++){
				if(rowTemp[j] == seatRow[j] && colTemp[j] == seatCol[j]);
				else
				planes[i].reserveSeat(seatRow[j], seatCol[j]);
			}
	}


    int* tempNo = new int(flightNo);
    int *tempPass = new int (numPassengers);
	resCodes[resCount][0] = tempNo;
	resCodes[resCount][1] = tempPass;
	int *col = new int[numPassengers];
	int *row = new int[numPassengers];
	for(int a =0;a<numPassengers;a++){
		col[a] = static_cast<int>(seatCol[a]);
		row[a] = seatRow[a];
	}
	resCodes[resCount][2] = row;
	resCodes[resCount][3] = col;
	resCount++;
	//std::cout << "Your reservation code is " << resCount << std::endl;
	delete []rowTemp;
	delete []colTemp;
	return resCount;
    }
	delete []rowTemp;
	delete []colTemp;
    return -1;
    }
    return -1;

}


void showReservation( const int resCode ){
    int actualResCode = resCode-1;
	if( resCode<resCount && resCodes[actualResCode] != NULL ){
		std::cout<<"Reservations under Code "<<resCode<<" in Flight "<<*resCodes[actualResCode][0]<<": ";
		for(int i=0; i<*(resCodes[actualResCode][1]);i++){
			std::cout<<resCodes[actualResCode][2][i]<<static_cast<char>(resCodes[actualResCode][3][i])<<" ";
		}
		std::cout<<std::endl;
	}
	else{
	//save given res codes
		std::cout<<"No reservation found under Code "<<resCode<<std::endl;
	}

}


void cancelFlight( const int flightNo ){
	bool x = false;
	for(int i=0; i<countP; i++){
		if(flightNo == planes[i].getFlightNum()){
			for(int a=i; a<countP; a++)
				planes[a] = planes[a+1];
			countP--;
			airplane *temp = new airplane[countP];
			for(int j =0; j<countP; j++)
				temp[j] = planes[j];
			delete []planes;
			planes = temp;
			x =true;
		}

	}

	if(x == false)
		std::cout<<"Flight "<<flightNo<<" does not exist"<<std::endl;


	bool t=false;
	for(int i =0; i<resCount; i++)
    {
		if(resCodes[i] != NULL && (*resCodes[i][0]) == flightNo)
		{
			//cancelReservation(i+1);
	    for(int x=0; x<countP; x++)
			{
                if(*(resCodes[i][0]) == planes[x].getFlightNum())
                {

                    for(int j=0; j<*(resCodes[i][1]); j++)
                    {
                        planes[i].cancelSeat(resCodes[i][2][j], resCodes[i][3][j]);
                    }
                }
            }
	    /*
		for(int b =0; b<*resCodes[i][1]; b++){
			delete resCodes[i][2][b];
			delete resCodes[i][3][b];
		}
		*/
            delete resCodes[i][0];
            delete resCodes[i][1];
            delete[] resCodes[i][2];
            delete[] resCodes[i][3];
            //delete resCodes[actualResCode];
            resCodes[i]=NULL;

			t =true;
		}
	}
	if(t==true)
		std::cout<<"Flight "<<flightNo<<" and all it's reservations have been canceled"<<std::endl;


}


void cancelReservation( const int resCode ){
    int actualResCode = resCode-1;
	if(actualResCode>=resCount)
		std::cout<<"No reservations are found under code "<<resCode<<std::endl;
	else{
	std::cout<<"Reservation for seats ";

	for(int i=0; i<countP; i++){
		if(*(resCodes[actualResCode][0]) == planes[i].getFlightNum())
			for(int j=0; j<*(resCodes[actualResCode][1]); j++){
				std::cout<<resCodes[actualResCode][2][j]<<static_cast<char>(resCodes[actualResCode][3][j])<<" ";
				planes[i].cancelSeat(resCodes[actualResCode][2][j], resCodes[actualResCode][3][j]);
			}

	}
	std::cout<<"is canceled in Flight "<<*resCodes[actualResCode][0]<<std::endl;
	/*for(int b=0; b<resCodes[actualResCode][1];b++){
		delete resCodes[actualResCode][2][b];
		delete resCodes[actualResCode][3][b];
	}
*/
	delete resCodes[actualResCode][0];
	delete resCodes[actualResCode][1];
	delete[] resCodes[actualResCode][2];
	delete[] resCodes[actualResCode][3];
	//delete resCodes[actualResCode];
	resCodes[actualResCode]=NULL;

	}
}


// ...
// you may define additional member functions and data members, if necessary.

};

