#include "airplane.cpp"

class ReservationSystem{

public:
ReservationSystem();
~ReservationSystem();
void addFlight( const int flightNo, const int rowNo, const int seatNo );
void cancelFlight( const int flightNo );
void showAllFlights();
void showFlight( const int flightNo );
int makeReservation( const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol );
void cancelReservation( const int resCode );
void showReservation( const int resCode );
airplane *planes;
int countP;
int resCount;
int*** resCodes;


};
