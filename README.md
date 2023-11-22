# Reciprocals
Collecting data on prime reciprocals with a period of exactly p-1.\n
So after figuring out that all max period prime reciprocals>10 have 10 as a primitive root. (duh)\n
I used some optimised modulused exponentiation to calculate the reciprocals instead of the dynamic division used in MaxReciprocals.c\n
This program both runs far faster and scales much better, which is why the newer .csv is a little over 200mb. (it contains all mpr primes under 10^9)
