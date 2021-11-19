# luna date
## convert normal calendar to an easier date system

### compile
```g++ convert.cpp -o lunaConvert```
### run
```lunaConvert <args> <date>```
```lunaConvert n 19-12-2008```
the n stands for normal operation




### features:
* convert normal calendar to the other system
* leap years work
* show day of the week
* convert back


## how the system works
instead of 12 months, with each one having different amount of days (31 28 31 30 31 30 31 31 30 31 30 31)
it has 13 months, each with exactly 28 days
13 * 28 = 364
there is one day left, at the end of the year, this day is not a normal day like monday or thursday, this day is an unnamed day
the reason for this is so that every year, every date will have the same day

### the system is synchronized at 1 january 1970 (normal calendar), on a thursday




