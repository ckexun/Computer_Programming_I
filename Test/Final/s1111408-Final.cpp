#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

struct Date
{
   int year;
   int month;
   int day;
   int hour;
};

struct MemberRecord
{
   char idNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

struct ReservationRecord
{
   char idNumber[ 12 ]; // account number
   int branchCode;      // branch code
   Date date;           // reservation date
   int numCustomers;    // number of customers
};

char branchNames[ 19 ][ 24 ] = { "", "Taipei Dunhua South",   "Taipei Zhongxiao",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New",
                                     "Kaohsiung Jianxing",  "Pingtung Kending" };

// read all memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// read all reservations that are not out of date, from the file Reservations.dat
void loadReservations( vector< ReservationRecord > &reservations );

// compute the current date
Date compCurrentDate();

// return true if and only if date1 <= date2
bool lessEqual( const Date &date1, const Date &date2 );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login and display the submenu
void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations );

// there exists a member with specified idNumber and password
bool valid( char idNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new reservation for the member with specified IDnumber
void reservation( char idNumber[], vector< ReservationRecord > &reservations );

// compute 7 dates which is starting from the current date
void compAvailableDates( Date availableDates[] );

// display all fields of reservation
void output( ReservationRecord reservation );

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete( char idNumber[], vector< ReservationRecord > &reservations );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if idNumber is a legal ID number
//bool legalID( char idNumber[] );

// return true if idNumber belongs to memberDetails
bool existingID( char idNumber[], const vector< MemberRecord > &memberDetails );

// write all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

// write all reservations that are not out of date, into the file Reservations.dat
void saveReservations( const vector< ReservationRecord > &reservations );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   vector< ReservationRecord > reservations; // all reservations

   loadMemberDetails( memberDetails );
   loadReservations( reservations );

   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;
   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails, reservations );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         saveReservations( reservations );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

void loadMemberDetails( vector< MemberRecord > &memberDetails )
{
    ifstream load("Members.dat", ios::in | ios::binary);
    MemberRecord tmp{};
    while( load.read(reinterpret_cast<char*>(&tmp), sizeof(MemberRecord)))
        memberDetails.push_back(tmp);
    load.close();
}

void loadReservations( vector< ReservationRecord > &reservations )
{
    ifstream load("Reservations.dat", ios::in | ios::binary);
    MemberRecord reser{};
    while (!load.eof())
        load.read(reinterpret_cast<char*>(&reservations), sizeof(ReservationRecord));
    load.close();
}

Date compCurrentDate()
{
   Date currentDate;
   tm structuredTime;
   time_t rawTime = time( 0 );
   localtime_s( &structuredTime, &rawTime );

   currentDate.year = structuredTime.tm_year + 1900;
   currentDate.month = structuredTime.tm_mon + 1;
   currentDate.day = structuredTime.tm_mday;
   currentDate.hour = structuredTime.tm_hour;

   return currentDate;
}

bool lessEqual( const Date &date1, const Date &date2 )
{
    if (date1.year > date2.year)
        return false;
    else if (date1.year < date2.year)
        return true;
    else if (date1.month > date2.month)
        return false;
    else if (date1.month < date2.month)
        return true;
    else if (date1.day > date2.day)
        return false;
    else if (date1.day < date2.day)
        return true;
    else if (date1.hour > date2.hour)
        return false;
    else
        return true;
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );
   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations )
{
   char idNumber[ 12 ] = "";
   char password[ 24 ] = "";

   do {
      cout << "Please enter your ID number: ";
      cin >> idNumber;
      cout << "Enter your password: ";
      cin >> password;
   } while( !valid( idNumber, password, memberDetails ) );

   cin.ignore();

   int choice;

   while( true )
   {      
      cout << "\n1 - Make Reservation\n";
      cout << "2 - Reservation Enquiry/Canceling\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         reservation( idNumber, reservations );
         break;

      case 2:
         queryDelete( idNumber, reservations );
         break;

      case 3:
         return;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }
}

bool valid( char idNumber[], char password[], const vector< MemberRecord > &memberDetails )
{
    bool corret = false;
    for (int i = 0; i < memberDetails.size(); i++) {
        if (strcmp(idNumber, memberDetails[i].idNumber) == 0 && strcmp(password, memberDetails[i].password) == 0)
            corret = true;
    }
    if (!corret)
        cout << endl << "Invalid account number or password. Please try again." << endl << endl;
    return corret;
}

void reservation( char idNumber[], vector< ReservationRecord > &reservations )
{
   ReservationRecord newReservation{};
   
   strcpy_s(newReservation.idNumber,idNumber);
   for (int i = 1; i <= 18; i++) 
       cout << i << ". " << branchNames[i] << endl;

   int choice;
   do {
       cout << "\nEnter your choice (0 to end):";
       cin >> newReservation.branchCode;
   } while (newReservation.branchCode > 18);
   if (newReservation.branchCode == 0) {
       cin.ignore();
       return;
   }


   Date availableDates[7]{};
   compAvailableDates(availableDates);
   cout << endl << "Available days:" << endl << endl;
   for (int i = 0; i < 7; i++){
       cout << i + 1 << ". " << availableDates[i].year << "/" << availableDates[i].month << "/" << availableDates[i].day << endl;
   }

   int choise;
   do {
       cout << endl << "Enter your choice (0 to end):";
       cin >> choise;
   } while (choise > 7);
   if (choise == 0) {
       cin.ignore();
       return;
   }
    newReservation.date.year = availableDates[choise - 1].year;
    newReservation.date.month = availableDates[choise - 1].month;
    newReservation.date.day = availableDates[choise - 1].day;

    int firstHour = availableDates[choise - 1].hour;
    do {
        cout << "\n\nEnter hour (" << firstHour << "~23):";
        cin >> newReservation.date.hour;
    } while (newReservation.date.hour < firstHour || newReservation.date.hour > 23);

    do {
        cout << "\n\nEnter the number of customers (1~30, 0 to end):";
        cin >> newReservation.numCustomers;
    } while (newReservation.numCustomers > 30);

    cin.ignore();
    if (newReservation.numCustomers == 0) {
        cin.ignore();
        return;
    }

   cout << endl << setw( 26 ) << "Branch"
                << setw( 14 ) << "Date" << setw( 8 ) << "Hour"
                << setw( 19 ) << "No of Customers" << endl;

   output( newReservation );

   cout << "\nReservation Completed!\n";

   reservations.push_back( newReservation );
}

void compAvailableDates( Date availableDates[] )
{
   Date currentDate = compCurrentDate();
   cout << endl << "The current hour is "<< currentDate.year << "/" << currentDate.month << "/" << currentDate.day <<":"<<currentDate.hour << endl;

   availableDates[0].hour = currentDate.hour + 1;
   for (int i = 0; i < 7; i++) { // put date in array
       availableDates[i].day = currentDate.day + i;
       if (currentDate.hour == 23) {
           availableDates[0].day = currentDate.day + 1;
           availableDates[0].hour = 0;
       }
       availableDates[i].month = currentDate.month;
       availableDates[i].year = currentDate.year;

       if (availableDates[i].month == 1 || availableDates[i].month == 3 || availableDates[i].month == 5 || availableDates[i].month == 7
           || availableDates[i].month == 8 || availableDates[i].month == 10 || availableDates[i].month == 12) {
           if (availableDates[i].day > 31) {
               availableDates[i].day -= 31;
               availableDates[i].month++;
           }
       }
       else if (availableDates[i].month == 2) {
           if ((availableDates[i].year % 4 == 0 && availableDates[i].year % 100 != 0) || availableDates[i].year % 400 == 0) {
               if (availableDates[i].day > 29) {
                   availableDates[i].day -= 29;
                   availableDates[i].month++;
               }
           }
           else {
               if (availableDates[i].day > 28) {
                   availableDates[i].day -= 28;
                   availableDates[i].month++;
               }
           }

       }
       else
           if (availableDates[i].day > 30) {
               availableDates[i].day -= 30;
               availableDates[i].month++;
           }
   }
}

void output( ReservationRecord reservation )
{
   cout << setw( 26 ) << branchNames[ reservation.branchCode ]
        << setw( 8 ) << reservation.date.year << '-'
        << setw( 2 ) << setfill( '0' ) << reservation.date.month << '-'
        << setw( 2 ) << setfill( '0' ) << reservation.date.day
        << setw( 8 ) << setfill( ' ' ) << reservation.date.hour
        << setw( 19 ) << reservation.numCustomers << endl;
}

void queryDelete( char idNumber[], vector< ReservationRecord > &reservations )
{
   Date currentDate = compCurrentDate();
   bool have = false;
   int j = 0;
   
   for (int i = 0; i < reservations.size(); i++) { //add
       if (strcmp(idNumber, reservations[i].idNumber) == 0) {//add
           if (lessEqual(currentDate, reservations[i].date)) { //add
               cout << endl << setw(26) << "Branch"
                   << setw(14) << "Date" << setw(8) << "Hour"
                   << setw(19) << "No of Customers" << endl;
               for (int i = 0; i < reservations.size(); i++) {
                   if (strcmp(idNumber, reservations[i].idNumber) == 0) {
                       if (lessEqual(currentDate, reservations[i].date)) {
                           have = true;
                           j++;
                           cout << j << ". ";
                           output(reservations[i]);
                       }
                   }
               }
               break; //add
           }
       }
   }
   
   if (!have) {
       cout << "No reservations!\n";
       return;
   }


   int choice = 0;
   do {
       cout << "\n\nChoose a reservation to cancel (0: keep all reservations):";
       cin >> choice;
   } while (choice > j);
   cin.ignore();
   if (choice == 0) 
       return;  

   vector< ReservationRecord > tmp;
   int k = 0;
   for (int i = 0; i < reservations.size(); i++) {
       bool in = true;    
       if (strcmp(idNumber, reservations[i].idNumber) == 0) {
           k++;
           if (k == choice) {
               in = false;
           }
       }
       if (in)
           tmp.push_back(reservations[i]);
   }

   reservations.clear();
   reservations = tmp;
   cin.ignore();
}

void registration( vector< MemberRecord > &memberDetails )
{
   MemberRecord newMember;

   cout << "Input your ID Number: ";
   cin >> newMember.idNumber;
   cin.ignore();

   if( existingID( newMember.idNumber, memberDetails ) )
   {
      cout << "\nYou are already a member!\n\n";
      return;
   }

   cout << "Input your Name: ";
   cin >> newMember.name;

   cout << "Choose a password: ";
   cin >> newMember.password;

   cin.ignore();

   memberDetails.push_back( newMember );

   cout << "\nRegistration Completed!\n\n";
}

bool existingID( char idNumber[], const vector< MemberRecord > &memberDetails )
{
    for (int i = 0; i < memberDetails.size(); i++) {
        if (strcmp(idNumber, memberDetails[i].idNumber) == 0)
            return true;
    }
    return false;
}

void saveMemberDetails( const vector< MemberRecord > &memberDetails )
{
    ofstream save("Members.dat", ios::out | ios::binary);
    MemberRecord tmp{};
    for (int i = 0; i < memberDetails.size(); i++) {
        tmp = memberDetails[i];
        save.write(reinterpret_cast<char*>(&tmp), sizeof(MemberRecord));
    }
    save.close();
}

void saveReservations( const vector< ReservationRecord > &reservations )
{
    ofstream save("Reservations.dat", ios::out | ios::binary);//modify
    ReservationRecord tmp{};
    for (int i = 0; i < reservations.size(); i++) {
        tmp = reservations[i];
        save.write(reinterpret_cast<char*>(&tmp), sizeof(ReservationRecord));
    }
    save.close();
}