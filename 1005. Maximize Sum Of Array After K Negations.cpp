/*
Given an integer array nums and an integer k, modify the array in the following way:

choose an index i and replace nums[i] with -nums[i].
You should apply this process exactly k times. You may choose the same index i multiple times.

Return the largest possible sum of the array after modifying it in this way.
*/

class Solution {
public:
    //0ms, O(n) with no sort, counting sort, bucket sort, etc
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        
        int neg = 0, small = INT_MAX;
        
        //only the abs minimum is needed because k >= neg will mean we can make everything positive at first,
        //then if k - neg is odd, flip the minimum until its negative and add it to result (*2 to cancel out)
        
        for (auto &i: nums) small = min(abs(i), small),  neg += i < 0;
        
        if (k >= neg) 
            return reduce(begin(nums), end(nums), 0, [](int &a, int &b) {return abs(a) + abs(b);}) 
                   + (((k - neg) % 2) ? -2 * small : 0);
        
        //if k < neg, the pivot of the array is begin(nums) + k - 1, so we can make the largest magnitude negative numbers
        //postive and add the rest as is
        
        nth_element(begin(nums), begin(nums) + k - 1, end(nums));
        
        return reduce(begin(nums), begin(nums) + k, 0, [](int &a, int &b) {return abs(a) + abs(b);})
               + reduce(begin(nums) + k, end(nums));
    }
};
