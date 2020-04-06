/*
    The main idea behind this solution is that it is guaranteed that the 
    first missing element will lie between 1 and n inclusive where n is
    the size of the vector nums. We iterate through the array and swap the
    the number i into the index i-1 if and only if the number i is between
    1 and n inclusive. We are guaranteed that the inner while loop will not
    run infinitely because there can be at most n-1 swaps until the we encounter
    an element in nums[i] which is already in the index nums[nums[i] - 1].
*/
class Solution
{
public:
    int firstMissingPositive(vector<int>& nums)
    {
        int curr = 1;
        for(int i = 0; i < nums.size(); i++){
            while(nums[i] <= nums.size() && nums[i] > 0 && nums[i] != nums[nums[i] - 1]){
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != i+1){
                return i + 1;
            }    
        }
        
        return nums.size() + 1;
    }
};