//
//  main.cpp
//  long-incr-subseq
//
//  Created by mndx on 09/04/2022.
//

#include <chrono>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX = 2501;
int ops = 0;

map<int, int> dp[MAX];

int len_max;

int max(int a, int b) {
    int res = 0;
    
    if(a > b) res = a;
    else res = b;
    
    return res;
}

void len_lis(vector<int> & nums, vector<bool> route) {
    
    int n = (int) nums.size();
    int m = (int) route.size();
    
    if(m < n ) {
        vector<bool> route1_loc = route;
        route1_loc.push_back(true);
        vector<bool> route2_loc = route;
        route2_loc.push_back(false);
        
        len_lis(nums, route1_loc);
        len_lis(nums, route2_loc);
    }
    
    if(m == n) {
        bool is_strict = true;
        int curr = -1;
        int count = 0;
        for(int i = 0; i < n; ++i) {
            if(route[i]) {
                count++;
                if(curr < nums[i]) {
                    curr = nums[i];
                }
                else {
                    is_strict = false;
                }
            }
        }
        
        if(is_strict) {
            len_max = max(len_max, count);
        }
    }
}

int len_rec(vector<int> & nums, int d, int min) {
    int n = (int) nums.size();
    
    ops++;
    
    int len = 0;
    
    if(dp[d][min] != 0) {
        return dp[d][min];
    }
    
    if(d < n - 1) {
        int sum1 = 0;
        if(nums[d + 1] > min) {
            sum1 = 1 + len_rec(nums, d + 1, nums[d + 1]);
        }
        int sum2 = len_rec(nums, d + 1, min);
        
        len = max(sum1, sum2);
    }
    
    if(d == n - 1) {
        if(nums[d] > min) {
            return 1;
        }
        else {
            return 0;
        }
    }
    
    dp[d][min] = len;
    
    return len;
}

int ops_ref = 0;

int len_of_lis(vector<int> & nums) {
    int n = (int) nums.size();
    
    vector<int> dp(n, 1);
    
    int len = 1;

    for(int i = 0; i < n; i++){
        for(int j = i - 1; j >= 0; j--){
            ops_ref++;
            if(nums[i] > nums[j]){
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        
        len = max(len, dp[i]);
    }
    
    return len;
}

int length_of_lis(vector<int> & nums) {
    
    int n = (int) nums.size();
    
    int max_sum = -1;
    
    for(int s = 0; s < n; ++s) {
        if(max_sum <= (n - 1 - s)) {
            int sum_loc = len_rec(nums, s, nums[s]);
            max_sum = max(max_sum, sum_loc);
        }
    }
    
    return max_sum + 1;
}

int main(int argc, const char * argv[]) {
    
    // Input data
    vector<int> nums = {10,9,2,5,3,7,101,18,45,56,67,78,1,2,3,4,301,3,6,1,8,1024,31};
    
    // Size input
    int n = (int) nums.size();
    
    // Compute length of longest increasing subsequence
    int max_sum = length_of_lis(nums);
    
    // Print results
    cout << "max_sum: " << max_sum << endl;
    cout << "ops : " << ops << endl;
    cout << "O(n^2) : " << n * n << endl;
    
    return 0;
}
