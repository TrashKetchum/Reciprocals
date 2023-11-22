#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>

long long powmod(long long a, long long b, long long p) {
    long long res = 1;
    while (b){
        if(b&1){
            res= (long long)( res*1ll*a%p );
            b--;
        }
        else{
            a = (long long)(a*1ll*a%p);
            b >>= 1;
        }
    }
    return res;
}

bool checker(long long p){
    std::vector<int> fact;
    long long phi = p-1;
    long long n = phi;
    for(int i=2; i*i<=n; i++){
        if(n%i==0){
            fact.push_back(i);
            while(n%i==0) n/=i;
        }
    }
    if(n>1){
        fact.push_back(n);
    }
    bool ok = true;
    for(std::size_t i=0; i<fact.size() && ok; i++){
        ok &= powmod(10, phi/fact[i], p) != 1;
    }
    return ok;
}

std::vector<long long> primegen(long long high){
    long long size = (high+1)/2;
    bool* primeArr = (bool*)calloc(size, sizeof(bool));
    primeArr[0]=true;
    for(long long i=3; i*i<=size; i+=2){
        if(!primeArr[i/2]){
            for(long long j = i*i; j<=high; j+=(2*i)){
                primeArr[j/2] = true;
            }
        }
    }
    std::vector<long long> primes;
    for(long long i=9; i<=high; i+=2){
        if(!primeArr[i/2]){
            primes.push_back(i);
        }
    }
    free(primeArr);
    return primes;
}

int main(){
    FILE* maxp;
    maxp = fopen("newMaxPeriod.csv","w+"); 
    auto start = std::chrono::high_resolution_clock::now();
    long long lim = 1000000000;
    std::vector<long long> primes = primegen(lim);
    fprintf(maxp, "7\n");
    for(int i=0; i<primes.size(); i++){
        if(checker(primes[i])){
            fprintf(maxp, "%lld\n", primes[i]);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    fclose(maxp);
}