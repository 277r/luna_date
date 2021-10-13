/*
	converts a date from normal to a luna time, and returns the t

*/



#include <iostream>

void getStrings(std::string in, std::string& day, std::string& month, std::string& year){
	day = in.substr(0, 2);
	month = in.substr(3, 2);
	year = in.substr(6, in.find("-", 6));
	return;
}


int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/*
	usage: lunaconvert <args> <date>
*/
int main(int argc, char *argv[]){
	// handle args
	if (argc < 3){
		std::cout << "error: not enough arguments provided";
		return 0;
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

}