/*
	converts a date from normal to a luna time, and returns the t

*/



#include <iostream>
// std::stoi and std::string are defined here in microsoft ISO c++ 14
#include <string>
#include <string.h>
#include <stdio.h>

// function declarations
void print_luna(int ddi, int mmi, int yyyyi, int args);
// picture of greg = uggc://vzntrf2.jvxvn.abpbbxvr.arg/__po20110717141238/qbnjx/vzntrf/4/4p/Qvnel-bs-n-jvzcl-xvq-Tert.wct
void print_greg(int ddi, int mmi, int yyyyi, int args);




void getStrings(std::string in, std::string& day, std::string& month, std::string& year){
	day = in.substr(0, 2);
	month = in.substr(3, 2);
	year = in.substr(6, in.find("-", 6));
	return;
}




/*
	usage: lunaconvert <args> <date>
*/
int main(int argc, char *argv[]){
	// handle args
	if (argc < 3){
		// help does not require a third argument, this is the only exception there currently is
		if (argc > 1 && strcmp(argv[1], "h") == 0){
			std::cout << "use `lunaconvert <OPTIONS> dd-mm-yyyy'\ndates MUST be zero padded\n";
			std::cout << "multiple options are allowed\npossible options:\nh\tshow help\nd\tshows what day it is on the output date\ni\tinverted operation, converts dates backs\n";
			return 0;
		}
		std::cout << "error: not enough arguments provided\nuse lunaconvert h to show a list of arguments\n";
		return 0;
	}
	

	bool printday = false, operateInverted = false;

	// get input opts
	while (*(argv[1]) != 0){
		 if (*argv[1] == 'd'){
			// print day
			printday = true;
		}
		else if (*argv[1] == 'i'){
			// operate inverted, instead of greg -> luna, do luna -> gegr
			operateInverted = true;
		}
		*(argv[1])++;
	}












	// tokenize string by dashes
	// string would DD-MM-YYYY
	// WITH ZERO PADDING
	std::string dd, mm, yyyy;
	
	
	// after the 13th month the day/days come, these are stored with month being 14 even thogh it's not a real month
	// all things but as integers instead of strings
	long long ddi, mmi, yyyyi;


	// get strings from the 3rd argument
	getStrings(argv[2], dd, mm, yyyy);


	/* debug output
	std::cout << dd << "\n";
	std::cout << mm << "\n";
	std::cout << yyyy << "\n";
	*/

	ddi = std::stoi(dd);
	mmi = std::stoi(mm);
	yyyyi = std::stoi(yyyy);


	if (operateInverted){
		print_greg(ddi, mmi, yyyyi, (printday & 1));
	}	
	else {
		print_luna(ddi, mmi, yyyyi, (printday & 1));
	}

}


int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 1 1 1970 is on a thursday
char* daysOfWeek[] = {"thursday", "friday", "saturday", "sunday", "monday", "tuesday", "wednesday", "h"}; 
void print_luna(int ddi, int mmi, int yyyyi, int args){

// declaration of some later used variables
	int lunaDays = 0;
	int lunaMonths = 0;
	// lunaYears is the same as the input



	// check how much days where in the year (sometimes 366 instead of 365)
	bool leapYear = false;
	
	// pain
	if (
		// leap year happens once every 4 years
		((yyyyi % 4 == 0) && 
		// but not every 100 years
		(yyyyi % 100 != 0)) || 
		// but it does again every 400 years
		(yyyyi % 400 == 0))
		leapYear = true;
	

	// now we need to find the Nth day of the year using magic
	
	// using a sum, we can find the days in whole months
	while (mmi > 1){
		if (mmi != 3){
			lunaDays += daysPerMonth[mmi - 1];
		}
		else {
			// if leapyear, add 29, else 28
			lunaDays += leapYear ? 29 : 28;
		}
		mmi--;
	}
	


	// add rest of days
	lunaDays += ddi;


	// debug output
	//std::cout << "nday: " << lunaDays << "\n";
	
    


	// now we have the Nth day of the year, do some tricky maths to make it work

	lunaMonths = (lunaDays / 28) + 1;

	// remove the first month's amount of days, but add one
	// modulo
	lunaDays = lunaDays % 28;
    
    // if the date is somehow zero, set it to 28
    if (lunaDays == 0){
        lunaDays = 28;
        lunaMonths--;
    }


	//std::cout << lunaDays << "-" << lunaMonths<< "-" << yyyyi << std::endl; 
	printf("%02d-%02d-%4d\n", lunaDays, lunaMonths, yyyyi);


	// if argument is 1
	if (args & 1){
		// find day
		if (lunaMonths == 14){
			printf("%s\n", daysOfWeek[7]);
		}
		else {
			printf("%s\n", daysOfWeek[(lunaDays -1) % 7]);
		}

	}
}


void print_greg(int ddi, int mmi, int yyyyi, int args){
	

	// leapyear check stage 1: check if the year is a leapyear
	bool leapYear;
	if (
		// leap year happens once every 4 years
		((yyyyi % 4 == 0) && 
		// but not every 100 years
		(yyyyi % 100 != 0)) || 
		// but it does again every 400 years
		(yyyyi % 400 == 0))
		leapYear = true;
	
	

	
	int greg_days = (mmi -1) * 28 + ddi;
	// will be used later
	int diffs = greg_days;
	int greg_months = 1;



	// turn days into months 
	// 
	while (greg_days > daysPerMonth[greg_months]){
		 {
			// take months from the days until days are smaller than the time there is
			greg_days -= daysPerMonth[greg_months];
			if (greg_months == 2 && leapYear){
				greg_days--;
			}
			greg_months++;
		}
	}
	// the code block here above has one date that will make an exception and it will be harder to fix that inside of the block than to fix it here
	if (greg_months == 3 && greg_days == 0){
		greg_months--;
		greg_days = 29;
	}
	

	// year is alays the same
	printf("%02d-%02d-%4d\n", greg_days, greg_months, yyyyi);


	// print day
	if (args & 1){
		yyyyi--;
		// january first on a thursday will be january second a year later, in a leap year this will be 2 years
		while (yyyyi > 1970){
			if (
			// leap year happens once every 4 years
			((yyyyi % 4 == 0) && 
			// but not every 100 years
			(yyyyi % 100 != 0)) || 
			// but it does again every 400 years
			(yyyyi % 400 == 0))
			diffs += 2;
			else diffs += 1;

			yyyyi--;
		}
		// get normal day of week
		// now apply the diffs to the thing
		printf("%s\n", daysOfWeek[diffs % 7]);
	}

}