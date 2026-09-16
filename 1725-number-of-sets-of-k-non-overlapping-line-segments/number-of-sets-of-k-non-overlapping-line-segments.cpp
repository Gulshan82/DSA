class Solution {
    long long power(long long base, long long exp) {
        long long res = 1;
        base %= 1000000007;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % 1000000007;
            base = (base * base) % 1000000007;
            exp /= 2;
        }
        return res;
    }
    
    long long modInverse(long long n) {
        return power(n, 1000000007 - 2);
    }

public:
    int numberOfSets(int n, int k) {
        // We need 2k points to form k segments.
        // We can map the overlapping segments problem to a strictly non-overlapping one 
        // by adding k - 1 "spaces" between the segments. 
        // Thus, we are choosing 2k distinct points from a total of n + k - 1 points.
        int N = n + k - 1;
        int K = 2 * k;
        
        if (K > N) return 0;
        
        long long num = 1;
        long long den = 1;
        
        for (int i = 1; i <= K; ++i) {
            num = (num * (N - i + 1)) % 1000000007;
            den = (den * i) % 1000000007;
        }
        
        return (num * modInverse(den)) % 1000000007;
    }
};