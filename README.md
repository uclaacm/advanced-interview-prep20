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
<p>Array questions, often interchangeable with string questions are some of the most common questions asked during technical interviews. As we have learned previously, what makes arrays so popular is their simplicity in storing data. When dealing with arrays you want to deal with an algorithm that is in the O(N) or O(log(N)) ballpark. This is achieved by the constant time access with indexing. When required to sort, we would be dealing with an O(NlogN) algorithm. Let us take a look at some vanilla array problems.</p>
<p align="center"><img src="images/arraymeme.jpg" width="50%" height="50%"></p>

## Two pointers approach :earth_asia:
<p>Often, we come across problems that may have an O(N^2) solution on first glance. The two pointer approach allows us to solve such problems in O(N) or 
O(Nlog(N)) if sorting is involved. As the name suggests, it involves two pointers, one that starts at the beginning and one that starts in the end. In each iteration, we move the beginning pointer or the end pointer by some number of indices while searching for an optimal value or finding a maximum/minimum. Consider Leetcode problem <a href="https://leetcode.com/problems/container-with-most-water/">11</a>.</p>
<p align="center"><img src="images/pr11.PNG" align="center" width="50%" height="50%"/></p>
<p>The main idea behind solving this problem is to optimize the maximum amount of water that can be stored in a container. The amount of water in a container is given by height * width where the height is the minimum of the two walls and the width is the distance between the two walls. How do we keep track of the two walls? Simple, two pointers. How do we advance the pointers? we increment the start pointer or decrement the end pointer only if the wall that is pointed to by that pointer is shorter than the wall pointed to by the other. We do this in the hope of finding a higher wall so that we can store more water! We stop once the two pointers meet because we don't want to go out of bounds or double count. We solved a potentially O(N^2) time problem in 
O(N)!</p>

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
<p>Now, sometimes we may not be so lucky when it comes to the order of elements in an array. Sorting, solves a lot of these problems. However, sorting does come at a cost, the fastest algorithm that we can write after performing a sort is of O(Nlog(N)) as sorting is bounded by this time complexity. This, however, is still better than an O(N^2) or O(N^3) solution. Let's demonstrate the importance of sorting in certain scenarios with leetcode problem <a>15</a>.</p>
<p align="center"><img src="images/p15.PNG" width="50%" height="50%"></p>

<p>This problem adds a layer over our usual two pointer approach. What is that layer? Sorting! What does sorting achieve in this scenario? First off, we notice that there is a simple brute force solution to this problem i.e. forming a triple for loop and finding the triplets that sum up to the given value. But this is ugly and your interviewer will ask you to optimize. Well, since a two pointers approach can only observe two values at a time we won't be able to use that approach. Or could we? We definitely wouldn't be able to find a 3sum in O(N) but what about O(N^2) which is, after all, better than O(N^3). This is where we start thinking along the lines of sorting. Sorting will not disturb the O(N^2) time complexity of our algorithm because we can sort an array in O(Nlog(N)). On sorting, we consider an element centric approach where we move from element to element and check if there exist two greater numbers that sum up to the remaining value using a two pointers approach. We also have to account for unique triplets so we skip values if we have already encountered them.</p>

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

<p align="center"><img src="images/p33.PNG" width="50%" height="50%"></p>

<p>What would the brute force solution be in this case? Well, simply searching each element one by one in a simple for loop. But we didn't take advantage of the fact that it is rotated sorted, i.e. the array can be divided into two sorted parts. Now if we want logarithmic time, we could simply perform a binary search on each part of the list to find the target element. So the key to the solution of the problem is finding the pivot i.e. the smallest element which divides the array into the two sorted parts. We find the pivot using a modified version of binary search.</p>

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        //Note that we use start and end twice, once to find the pivot
        //and again to find the target element.
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
            }else if(nums[mid] > nums[mid+1]){ //discrepency in increasing order of sort indicates
                                               //we have found the pivot. 
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
        //if start has crossed end then there is no rotations and we can perform a single binary
        //search on the entire array.
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
## Logical Problems :lock:
<p>Some array problems are simply math-based problems where we have to summon our math/logic skills. Sadly, there is no definite approach that we can use to solve such problems. The only way that we stand a good chance at solving such problems is solving more problems! Consider Leetcode problem <a href="https://leetcode.com/problems/rotate-image/">48</a>.</p>

<p align="center"><img src="images/p48.PNG" width="50%" height="50%"></p>

<p>At first glance, this problem seems rather simple. You pull out a pen and work through an example, you see a definite pattern where each element, on rotation, is taking the place of another element which is located at a definite number of places away in the matrix. However, while it seems like a definite pattern, coming up with an element-wise algorithm is tedious. Moreover, since we have to do it in place, swapping two elements will make us lose track of the element that already exists at the position we are swapping into. This is where we need to apply some kind of logic to the problem. We do this by breaking down the rotation into two predictable operations, i.e. a reflection about the middle row followed by a reflection about the diagonal. Note that swapping is not a problem here because when we swap, both elements are being swapped into their final positions.</p>

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        //first we reflect about the middle row.
        reverse(matrix.begin(), matrix.end());
        //now we reflect about the diagonal.
        for(int i = 0; i < matrix.size(); i++){
            for(int j = i+1; j < matrix.size(); j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};
```
## Practice :muscle:
<p>These are some of the techniques that we use when solving array problems. While most of these techniques seem rather abstract, knowing them will allow us to nudge ourselves towards the right solution. Now that you have been equipped with these techniques, attempt to solve the following problems. If you get stuck, don't worry, we've got your back. Feel free to peek at the solution in the solutions directory or if you don't want to, zoom into office hours!</p>
1. <a href="https://leetcode.com/problems/first-missing-positive/">Leetcode Problem 41: First Missing Number</a><br>
2. <a href="https://leetcode.com/problems/trapping-rain-water/">Leetcode Problem 42: Trapping Rain Water</a><br>
3. <a href="https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/">Leetcode Problem 448: Find All Numbers Disappeared In An Array</a><br>
4. <a href="https://leetcode.com/problems/beautiful-arrangement-ii/">Leetcode Problem 667: Beautiful Arrangement ii</a><br>
5. <a href="https://leetcode.com/problems/fruit-into-baskets/">Leetcode Problem 904: Fruit Into Baskets</a>

# Strings <a name="strings"></a> :ramen:
<p>Array problems are often interchangable with string problems. After all, a string is an array of characters! When solving string problems, we might have to employ the two pointers approach that we discussed and sometimes even sorting (where alphabetical ordering matters). But there are a few new tricks that we could employ to solve string problems. Remember! if we can solve string problems using array techniques, we can solve array problems with string techniques.</p>

<p align="center"><img src="https://i.imgflip.com/3wxtdy.jpg"></p>

## Using A Hashtable :rocket:
<p>What's so cool about strings and characters is that they are hashable. We can associate a character, sub-string or string with a certain value that we would like to keep track of for each character, sub-string or string respectively. This could be the number of times it appears or even the position of the character in a string or string in an array. Let us illustrate the use of a hashtable with Leetcode problem <a href="https://leetcode.com/problems/longest-substring-without-repeating-characters/">3</a>.</p>

<p align="center"><img src="images/p3.PNG" height="50%" width="50%"></p>

<p>In order to find the longest substring with non-repeating characters, we keep track of the last seen position of each character in the string. This way we know that the next sub-string that we observe has to begin at the next position of the last seen position.</p>

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> seen;
        int start = 0;
        int end = 0;
        int longest_len = 0;
        while(start != s.length() && end != s.length()){
            if(seen.find(s[end]) == seen.end() || seen[s[end]] < start){
                seen[s[end]] = end;
                if(end - start + 1 > longest_len)
                    longest_len = end - start + 1;
                end += 1;
            }
            else{
                start = seen[s[end]] + 1;
                seen[s[end]] = end;
                end += 1;
            }
        }
        return longest_len;
    }
};
```
## Sliding Window :running:
<p>Another greedy approach to solving string problems is using a sliding window of a fixed size to slide across our string while we check constraints and keep track of some values. A sliding window is essentially a range of characters in our string that starts from the beginning and terminates a fixed-length before the end of the string. The concept is better illustrated in this figure from <a href="https://tinyfool.org/2019/04/the-sliding-window-algorithm/">TinyFool's blog.</a></p>

<p align="center"><img src="images/slidingwindow.png" width="50%" height="50%"></p>

<p>In the above figure, the window is three characters wide and slides across from the beginning to the end. We need to make sure to check edge cases and not slide out of bounds. Let us work through a problem that makes use of the sliding window technique. Consider Leetcode problem <a href="https://leetcode.com/problems/substring-with-concatenation-of-all-words/">30</a>.</p>

<p align="center"><img src="images/p30.PNG" width="50%" height="50%"></p>

<p>The above problem requires using both the techniques that we just learned. A hash table to keep track of the which words are present in the words vector and the number of times each one occurs, and a sliding window of some length to slide across all possible candidate substrings that are of that length. On close observation, we notice that the length of the window is going to be the total number of characters in the words vector. This is because every concatenation of all words will be of that fixed length. Now we just slide our window across the string. For each candidate, we check if all the individual words in the words vector are present. We do this by counting backward, decrementing the count of a word in a copy of the previously constructed hash table every time we encounter a valid word. We also count the number of words encountered to ensure that we account for exactly the right number of words. The time complexity of the above algorithm is going to be O((N-K) * K) where K is the length of the concatenated string and N is the length of the given string.</p>

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        //result we are going to return
        vector<int> result;
        //handle edge cases
        if(s == "" || words.size() == 0) 
            return result;
        //we obtain the length of each word in words vector and the size of the window
        //we will be considering.
        int word_len = words[0].length();
        int window_len = words.size() * word_len;
        //handle invalid case where our window is bigger than our string.
        if(window_len > s.size())
            return result;
        //create a hash table to keep track of words in the words vector and the number
        //of times each word appears. This will be used to check if a given window over 
        //the string s has a combination of any of these words
        unordered_map<string, int> word_counts;
        for(auto it : words){
            if(word_counts.find(it) == word_counts.end()){
                word_counts[it] = 1; 
            }else{
                word_counts[it] += 1;
            }
        }
        //iterate through all windows
        for(int i = 0; i <= s.size() - window_len; i++){
            //create a temporary hash map that will keep track of the words encountered
            //in this window.
            unordered_map<string, int> temp_words_counts(word_counts);
            int j = i;
            //number of words that are in the words vector which must be zero if we have
            //encountered all the words in our window.
            int count = words.size();
            while(j < i + window_len){
                //check every substring of length 'word_len'
                string temp = s.substr(j, word_len);
                //if the word is not in our words vector or even if it is but there are too many
                //break out of this window.
                if(word_counts.find(temp) == word_counts.end() || temp_words_counts[temp] == 0){
                    break;
                }else{
                    //else we decrement the count of that particular word and count, moving us
                    //closer to the result.
                    temp_words_counts[temp] -= 1;
                    count -= 1;
                }
                j += word_len;
            }
            //we have encountered all the words in this window in some permutation.
            //we add the starting index to our result vector.
            if(count == 0)
                result.push_back(i);
            
        }
        
        return result;
    }
};
```
## Practice :muscle:
<p>There are a few more types of string questions that one may encounter in technical interviews. These include Dynamic Programming, BFS/DFS, Topological Sort, etc. Don't worry, we'll cover these concepts when we get there. But for now, we will just work with the above problem-solving techniques. Remember to use the skills that you employed when solving array questions because they can come in handy as well.</p>

1. [Leetcode Problem 6: ZigZag Conversion](https://leetcode.com/problems/zigzag-conversion/)
2. [Leetcode Problem 32: Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
3. [Leetcode Problem 49: Group Anagrams](https://leetcode.com/problems/group-anagrams/)
4. [Leetcode Problem 767: Reorganize String](https://leetcode.com/problems/reorganize-string/)