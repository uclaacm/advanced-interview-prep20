# Advanced Technical Interview Preperation Problems and Solutions :watch:
Presented by UCLA ACM ICPC   
Questions: https://tinyurl.com/ask-ucla-icpc <br />
ICPC Facebook Group: https://www.facebook.com/groups/ucla.icpc/

<p>Hello there! Welcome to the Advanced Technical Interview Guide presented to you by ACM ICPC. If you are looking to boost your
technical skills, this is a great place to get started. If you have no idea about the types of questions you would encounter in a technical interview, make sure to check out our CS32 interview prep guide first and then make sure to come back. If you have already, you're in the right place.</p>

# Table of Contents :zap:
1. [Arrays](#arrays)
2. [Strings](#strings)
3. [Linked Lists](#linkedlists)
4. [Stacks and Queues](#stacksandqueues)
5. [Trees](#trees)
6. [Graphs](#graphs)
7. [Recursion and Dynamic Programming](#recursionanddynamicprogramming)
8. [System Design](#systemdesign)

# Arrays <a name="arrays"></a> :dolphin:
<p>Array questions, often interchangeable with string questions are some of the most common questions asked during technical interviews. As we have learned previously, what makes arrays so popular is their simplicity in storing data. So when dealing with arrays you want to deal with an algorithm that is in the O(N) or O(log(N)) ballpark. This is achieved by the constant time access with indexing. When required to sort, we would be dealing with an O(NlogN) algorithm. We will deal with sorting in the following section. For now, let us take a look at some vanilla array problems.</p>
<img src="images/arraymeme.jpg" width="50%" height="50%">

## Two pointers approach :earth_asia:
<p>Often, we come across problems that may look like an O(N^2) problem when brute-forcing but would make the interviewer unhappy. As the name suggests, it involves two pointers, one that starts at the beginning and one that starts in the end. In each iteration, we move the beginning pointer or the end pointer by some number of indices while searching for an optimal value or finding a maximum/minimum. Consider Leetcode problem <a href="https://leetcode.com/problems/container-with-most-water/">11</a>.</p>
<center><img src="images/pr11.PNG" align="center" width="50%" height="50%"/></center>
<p>The main idea behind solving this problem is to optimize the maximum amount of water that can be stored in a container. The amount of water in a container is given by height x width where the height is the minimum of the two walls and the width is the distance between the two walls. How do we keep track of the two walls? Simple, two pointers. How do we advance the pointers? we increment the start pointer or decrement the end pointer only if the wall that is pointed to by that pointer is shorter than the wall pointed to by the other. We do this in the hope of finding a higher wall so that we can store more water! We stop once the two pointers meet because we don't want to go out of bounds or the double count. We solved a potentially O(N^2) time problem in O(N)!</p>
<br />

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        //initialize two pointers start and end that point to the start and end of the list.
        int start = 0;
        int end = height.size() - 1;
        //max_water is the value we are optimizing for and 
        //the termination codition is when start equals end.
        int max_water = 0;
        while(start < end){
            //calculate the amount of water that the two walls can hold between them.
            int water_amount = min(*(height.begin() + start), *(height.begin() + end))*(end - start);
            max_water = max(max_water, water_amount);
            //carefully increment start or decrement end (the wall with lesser height) 
            //in the hope of leading to a higher wall.
            if(*(height.begin() + start) > *(height.begin() + end)){
                end -= 1;
            }else{
                start += 1;
            }
        }
        return max_water;
    }
};
```
## Sorting :camel:
<p>Now, sometimes we may not be so lucky when it comes to the order of elements in an array. Sorting, solves a lot of these problems. However, sorting does come at a cost, the fastest algorithm that we can write after performing a sort is of O(Nlog(N)). This is still better than an O(N^2) or O(N^3) solution. Let's demonstrate the value of sorting with leetcode problem <a>15</a>.</p>
<img src="images/p15.PNG" width="50%" height="50%">

<p>This problem adds a layer over our usual two pointer approach. What is that layer? Sorting! What does sorting achieve in this scenario? First off, we notice that there is a simple brute force solution to this problem i.e. forming a triple for loop and finding the triplets that sum up to the given value. But this is ugly and your interviewer will ask you to optimize. Well, since a two pointers approach can only observe two values at a time we won't be able to use that approach. Or can we? We definitely wouldn't be able to find a 3sum in O(N) but what about O(N^2) which is, after all, better than O(N^3). This is where we start thinking along the lines of sorting. Sorting will not disturb the O(N^2) time complexity of our algorithm because we can sort an array in O(Nlog(N)). On sorting, we consider an element centric approach where we move from element to element and check if there exist two greater numbers that sum up to the remaining value using a two pointers approach.</p>

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //First, we sort.
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int pos = 0;
        //iterate throught each number in the sorted list one by one.
        for(int i = 0; i < nums.size(); i++){
            //continue if we have already dealt with this value 
            //of 'it' because we only want unique triplets in our result vector.
            if(i != 0 && nums[i] == nums[i-1]){
                continue;
            }
            //initialize our two pointers
            int start = i+1;
            int end = nums.size() - 1;
            while(start < end){
                //again we only want uniques so we advance 
                //start or end if we have already accounted for the numbers pointed by them.
                if(start != i+1 && nums[start] == nums[start-1]){
                    start += 1;
                    continue;
                }else if(end != nums.size() - 1 && nums[end] == nums[end + 1]){
                    end -= 1;
                    continue;
                }
                //Check three possible cases.
                if(nums[i] + nums[start] + nums[end] == 0){
                    res.push_back({nums[i], nums[start], nums[end]});
                    start += 1;
                    end -= 1;
                }else if (nums[i] + nums[start] + nums[end] < 0){
                    start += 1;
                }else{
                    end -= 1;
                }
            }
        }
        return res;
    }
};
```
## Searching :snowman:
<p>Often, we are presented with one or more sorted arrays or semi-sorted arrays. When the interviewer provides you with this information, you will need to take advantage of it to reduce the time complexity of the solution. The best way to take advantage of this is by using a binary search or some equivalent that yields an O(log(N)) time complexity.</p>
<p>The solution to a problem may not always be direct binary search. You may have to handle a few extra cases or edge cases but the solution is almost always "Binary Search-esque." For example, consider Leetcode problem <a href="https://leetcode.com/problems/search-in-rotated-sorted-array/">33</a>.</p>

<img src="images/p33.PNG">

<p>What would the brute force be in this case? Well, simply searching each element one by one in a simple for loop. But we didn't take advantage of the fact that it is rotated sorted, i.e. the array can be divided into two sorted parts. Now if we want logarithmic time, we could simply perform a binary search on each part of the list to find the target element. So the key to the solution of the problem is finding the pivot i.e. the smallest element (which is also the start of the un-rotated list). We find the pivot using a modified version of binary search.</p>

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        int pivot_index = 0;

        //first we attempt to find the pivot if there exists any.
        while(start <= end){
            int mid = (start + end) / 2;
            if(mid == 0 || mid == nums.size() - 1){
                start = 0;
                end = nums.size() - 1;
                break;
            }else if(nums[mid] > nums[mid+1]){
                if(target <= nums[mid] && target >= nums[0]){
                    start = 0;
                    end = mid;
                }else{
                    start = mid + 1;
                    end = nums.size() - 1;
                }
                break;
            }else if(nums[mid] < nums[mid-1]){
                if(target <= nums[mid-1] && target >= nums[0]){
                    start = 0;
                    end = mid-1;
                }else{
                    start = mid;
                    end = nums.size() - 1;
                }
                break;
            }else{
                if(nums[mid] > nums[start]){
                    start = mid + 1;
                }else{
                    end = mid - 1;
                }
            }
        } 
        //perform binary search
        if(start >= end){
            start = 0;
            end = nums.size() - 1;
        }

        //Now that we know which sorted part of the array consists of the element, we perform binary search on that part.
        while(start <= end){
            if(nums[start] == target){
                return start;
            }else if(nums[end] == target){
                return end;
            }
            int mid = (start + end) / 2;
            if(nums[mid] == target){
                return mid;
            }else if (nums[mid] < target){
                start = mid + 1;
            }else{
                end = mid - 1;
            }
        }
        return -1;
    }
};
```
