# Advanced Technical Interview Preperation Problems and Solutions
Presented by UCLA ACM ICPC   
Questions: https://tinyurl.com/ask-ucla-icpc <br />
ICPC Facebook Group: https://www.facebook.com/groups/ucla.icpc/

<p>Hello there! Welcome to the Advanced Technical Interview Guide presented to you by ACM ICPC. If you are looking to boost your
technical skills, this is a great place to get started. If you have no idea about the types of questions you would ecounter in a technical interview, make sure to checkout our CS31 interview prep guide first and then make sure to come back. If you have already, you're in the right place.</p>

# Table of Contents
1. [Arrays](#arrays)
2. [Searching and Sorting](#searchingandsorting)
3. [Strings](#strings)
4. [Linked Lists](#linkedlists)
5. [Stacks and Queues](#stacksandqueues)
6. [Trees](#trees)
7. [Graphs](#graphs)
8. [Recursion and Dynamic Programming](#recursionanddynamicprogramming)
9. [System Design](#systemdesign)

# Arrays <a name="arrays"></a>
<p>Array questions, often interchangable with string questions are some of the most common questions asked during technical interviews. As we have learnt previously, what makes arrays so popular is their simplicity in storing data. So when dealing with arrays you want to deal with an algorithm that is in the O(N) or O(log(N)) ballpark. This is achieved by the constant time access with indexing. When required to sort, we would be dealing with an O(NlogN) algorithm. We will deal with sorting in the following section. For now, let us take a look at some vanilla array problems.</p>

## Two pointer approach.
<p>Often, we come across problems that may look like an O(N^2) problem when bruteforcing but would make the interviewer unhappy. As the name suggests, it involves two pointer, one that starts at the beginning and one that starts in the end. In each iteration, we move the beggining pointer or the end pointer by some number of indices while searching for an optimal value or finding a maximum/minimum. Consider Leetcode problem <a href="https://leetcode.com/problems/container-with-most-water/">11</a>.</p>
<center><img src="images/pr11.PNG"/></center>
<p>The main idea behind solving this problem is to optimize on the maximum amount of water that can be stored in a container. The amount of water in a container is given by height x width where the height is the minimum of the two walls and the width is the distance between the two walls. How do we keep track of two walls? Simple, two pointers. How do we advance the pointers? we increment the start pointer or decrement the end pointer only if the wall that is pointed to by that pointer is shorter than the wall pointed to by the other. We do this in the hope of finding a higher wall so that we can store more water! We stop once the two pointers meet because we don't want to go out of bounds or double count. In this we solved a potentially O(N^2) time problem in O(N).</p>
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
