/*
 * program that outputs the probability of a maximum period prime reciprical (period of p-1)
 */
import java.util.*;
public class redoReciprocals{

    public static Scanner sc = new Scanner(System.in);
    public static int primelim = 2000000;                           //limit on the input to stop a memory error on the array
    public static int low = Integer.parseInt(sc.nextLine());        //start of range
    public static int high = Integer.parseInt(sc.nextLine());       //end of range
    public static int interval = Integer.parseInt(sc.nextLine());   //interval at which it will print out the ratio
    public static boolean [] arr = new boolean[primelim/2];         //a boolean array which tracks if a given index is prime

    public static void removeMult(int n){
        for(int i=n*n; i<=primelim;i+=2*n) arr[i/2]=true;          //sets all multiples of a given n to be non-prime                                 
    }

    public static int reciprocal(int n){         //this method returns the period of a reciprocal, it is tested accurate to ~2x10^6 digits
        Stack<Integer> dig = new Stack<>(); int carry = 1; int zeros = 0; boolean tail;
        while(true){
            tail = false;           //tail keeps track of whether there is currently a tail zero as
            carry*=10;              //shifts carry up a digit
            if(carry<n){            //if the carry is not big enough to divide, shift it up and add a zero
                carry*=10;
                zeros++;
                tail = true;
            }
            carry = carry%n;       //division
            if(dig.contains(carry)){    //if the carry is repeated then the period is finished
                if(tail) zeros-=1;      //get rid of tail zero if it exists
                break;
            } 
            else dig.push(carry);       //else remember carry and move on
        }
        return zeros+dig.size();        //period length
    }

    public static void main(String[]args){ 
        arr[0]=true;                            //1 is not prime
        int sqr =(int) Math.ceil(Math.sqrt(primelim));   //only need to check primes under the sqrt of array size
        for(int i=3; i<=sqr; i+=2) if(!arr[i/2]) removeMult(i); //remove multiples of any primes, using arr[i/2] as this halves the size of the array and we can just ignore any even i's
        int sum_mx = 0; int sum_nmx = 0; String x;
        for(int i=1; i<=high; i++){
            if(i%2!=0){                                 
                if(!arr[i/2]) {                      //if i is odd and marked as prime find its reciprocal
                    int hold = reciprocal(i);
                    if(hold == i-1) sum_mx++;        //if the reciprocal is max period increase respective count
                    else sum_nmx++;
                }
            }
            if(i>low && i%interval==0){
                x = Double.toString((double)sum_mx/(double)(sum_nmx+sum_mx));
                System.out.println(x);
            }
        }
    }
}