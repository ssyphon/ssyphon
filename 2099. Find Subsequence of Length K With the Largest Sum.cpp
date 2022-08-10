/*
You are given an integer array nums and an integer k. 
You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or 
no elements without changing the order of the remaining elements.
*/

/* 
The O(n) solution is actually slower because it's 2*n which matter on these smaller datasets. 
Also, making my n + k^2 solution O(n) would require creating unordered_set/maps and that is also just slower. 
I've learned that repeatedly calling find ends up being faster than creating those data structures for smaller data leetcode problems. 
PS: stable_partition says worst case O(nlogn) if it can't allocate enough memory, but I'm assuming it could.
*/

class Solution {
public:
    //best time 3ms, 99% runtime/memory, O(n + k^2)
    //my second attempt. I figured I may get faster times just using the nth_element result as my answer and 
    //sorting it using nums in place. unordered_maps, while O(n), are often slower than searching when working with smaller vectors
    
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> temp(begin(nums), end(nums));
        auto it = prev(end(temp), k);
        nth_element(begin(temp), it, end(temp));
        temp.assign(it, end(temp));
        
        int start = 0;
      
        //keep swapping the beginning of temp with the next element found in nums if it exists in temp
        for (int &i: nums) {
            if ((it = find(begin(temp) + start, end(temp), i)) != end(temp))
                swap(temp[start++], *it);
            if (start == k) break;
        }
        
        return temp;
    }
    
    //best time 8ms, 98% runtime/memory, O(n)
    //we need to count the number of pivots to the right of nth element because stable_sort is agnostic 
    //regardless of policy. it will either put all pivots or 1 pivot into bucket used for answer
    
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> temp(begin(nums), end(nums));
        auto it = prev(end(temp), k);
        nth_element(begin(temp), it, end(temp));
        
        int pivot = *it, n = count(it, end(temp), pivot);
        
        stable_partition(begin(nums), end(nums), [&](int &i) {return i >= pivot;});
        temp.resize(k);
      
        //only add pivot elements if below the count of them that existed to the right of pivot after calling nth element (inclusive)
        for (int i = 0, j = 0, l = 0; l < k; i++) {
            if (nums[i] != pivot) 
                temp[l++] = nums[i];
            else if (j < n) 
                temp[l++] = pivot, j++;
        }
        
        return temp;
    }
};
