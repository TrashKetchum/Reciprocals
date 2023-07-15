#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool* primegen(long high){
    long size = (high+1)/2;

    bool* primeArr = malloc((size)*sizeof(bool));
    primeArr[0] = true;
    long sqr = (long)sqrt((double)size);

    for(int i=3; i<=sqr; i+=2){
        if(!primeArr[i/2]){
            for(long j = i*i; j<=high; j+=(2*i)){
                primeArr[j/2] = true;
            }
        }
    }
    return primeArr;
}

long reciprocalPeriod(long prime){
    bool first = true;
    long halfway = (prime-1)/2;
    long position = 0;
    long carry = 1;
    long period = 0;
    bool tail = false;
    while(true){
        tail = false;
        carry*=10;
        if(carry<prime){
            carry*=10;
            position++;
            tail=true;
        }
        carry = carry%prime;
        if(period==carry){
            if(tail) position--;
            break;
        }
        else{
            if(first) period = carry;
            position++;
            if(position>halfway){
                position = prime-1;
                break;
            }
        }
        first = false;
    }
    return position;
}

void reciprocalScan(bool* primeArr, long high){
    FILE *fp;
    fp = fopen ("MaxReciprocalOutput.csv", "w+");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    fprintf(fp, "%s\n", "Prime");
    long period = 0;
    double ratio = 0;
    for(long i=3; i<=high; i++){
        if(i%2!=0){
            if(!primeArr[i/2]){
                period = reciprocalPeriod(i);
                if(period==i-1){
                    fprintf(fp, "%lu\n", i);
                }
            }
        }
    }
    fclose(fp);
    free(primeArr);
}

int main(){
    long high;
    scanf("%lu", &high);
    bool* primeArr = primegen(high);
    reciprocalScan(primeArr, high);
}