#include <iostream>

/*
                    Q. find the first & last occurrences of x

                explanation -  we will be given a sorted array and have to find out the first and last
                                occurrences of our given nmbr

                                    arr[] = {2, 4, 6, 8, 8, 8, 11, 13}
                                    index =  0  1  2  3  4  5   6   7

                                    if  x = 8,  then occurences = {3, 5}    <- index
                                    if  x = 10, then occurences = {-1, -1}    <- returning false
                                    if  x = 11, then occurences = {6, 6}    <- bcz there is only one occurrence of 11


                        we will find occurences by linear search. firstly we assign first & last as '-1', then linear search
                        the array. when we find our 'x' we will assign its index to our 'first' & 'last'. then again do the
                        linear search the index of next 'x' will be assigned to our 'last', there is no need to change our
                        'first'. then again we search for the next 'x' for our 'last'

    code
first = -1, last = -1
for(i=0->n-1)
{
    if(arr[i] == x)
    {
        if(first == -1)
            first = i
        
        last = i
    }
}

            TC - O(N)


            to get low time complexity (like O(log)), we will optimize the above code
            for that we will use the concept of lower_bound & upper_bound
                                                a[ind] >= x    a[ind] > x
                                                   lb(8)        ub(8) - 1

                        to find our 'first' & 'last' we lower_bound 'x' for our first
                        and upper_bound minus '1' for our 'last'

                some things that we have to take into our consideration
                                        if we take x = 10 then the lower_bound will point to element 11 (index 6)
                                        if we take x = 14 then the lower_bound will point to hypothetical index 'n'
                            considering them
                                            (lb(14) == n || arr[lb] != n)


    Actual code
int lowerBound(vector<int> arr, int n, int x) {
    int low = 0, high = n - 1;
    int ans = n;

    while (low <= high) {
        int mid = (low + high) / 2;
        // maybe an answer
        if (arr[mid] >= x) {
            ans = mid;
            //look for smaller index on the left
            high = mid - 1;
        }
        else {
            low = mid + 1; // look on the right
        }
    }
    return ans;
}

int upperBound(vector<int> &arr, int n, int x) {
    int low = 0, high = n - 1;
    int ans = n;

    while (low <= high) {
        int mid = (low + high) / 2;
        // maybe an answer
        if (arr[mid] > x) {
            ans = mid;
            //look for smaller index on the left
            high = mid - 1;
        }
        else {
            low = mid + 1; // look on the right
        }
    }
    return ans;
}

pair<int, int> firstAndLastPosition(vector<int> &arr, int n, int k)
{
    int lb = lowerBound(arr, n, k);
    if(lb == n || arr[lb] != k)
        return {-1, -1};

    return {lb, upperBound(arr, n, k) -1};
}

        
            TC - 2 * O(log 'base 2' N)
            SC - O(1)



                now we will be solving this problem by using binary search
                    we will use binary search to find 'first' occurrence
                    then we will use binary search to find 'last' occurrence

            arr = {2, 8, 8, 8, 8, 8, 11, 13}    x = 8

            lets apply binary search on above array
            we will get,  low = index 0,    high = index 7
                      then  mid = 3.5 = 3 index,  we got our 'first' as index 3 (element 8) but we search on the left side of
                                                  the array bcz we have to find the 'first' occurrence which
                                                  should be on starting of the array

            we will get,  low = index 0,    high = index 2
                      then  mid = 1 index,  we got our 'first' as index 1 (element 8) but we search on the left side of
                                                  the array bcz we have to find the 'first' occurrence which
                                                  should be on starting of the array

            we will get,  low = index 0,    high = index 0
                      then  mid = 0 index,  at index 0, we got and 2 is not x
                                                2 < 8 so we have to go to the right
                                            so 'low' will move 1 step fwd by doing that it (low) crossess 'high'
                                            so we stop and we got our 'first' as index 1 (from 2nd iteration)


            now for the 'last'
            lets apply binary search on above array
            we will get,  low = index 0,    high = index 7
                      then  mid = 3.5 = 3 index,  we got our 'last' as index 3 (element 8) but we search on the right side of
                                                  the array bcz we have to find the 'last' occurrence which
                                                  should be on ending of the array

            we will get,  low = index 4,    high = index 7
                      then  mid = 5 index,  we got our 'last' as index 5 (element 8) but we search on the right side of
                                                  the array bcz we have to find the 'last' occurrence which
                                                  should be on ening of the array

            we will get,  low = index 6,    high = index 7
                      then  mid = 6 index,  at index 6 we got 11 which is greater than x
                                                8 < 11 so we have to go to the left
                                            so 'high' will move 1 step before 'mid' by doing that it (high) crossess 'low'
                                            so we stop and we got our 'last' as index 5 (from 2nd iteration)

        Pseudo code
// for first occurrence
fn(arr, n, x)
{
    low = 0, high = n-1
    first = -1

    while(low <= high)
    {
        mid = (low + high)/2
        if(a[mid] == x)
            first = mid, high = mid - 1
        else if(a[mid] < x)
            low = mid + 1
        else
            high = mid - 1
    }
}

// for last occurrence
fn(arr, n, x)
{
    low = 0, high = n-1
    last = -1

    while(low <= high)
    {
        mid = (low + high)/2
        if(a[mid] == x)
            last = mid, low = mid + 1
        else if(a[mid < x])
            low = mid + 1
        else
            high = mid - 1
    }
}


        Actual Code
int firstOccurrence(vector<int> &arr, int n, int k)
{
    int low = 0, high = n-1;
    int first = -1;

    while(low <= high)
    {
        int mid = (low + high)/2;
        if(arr[mid] == k)
        {
            first = mid; 
            high = mid - 1;
        }
        else if(arr[mid] < k)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return first;
}

int lastOccurrence(vector<int> &arr, int n, int k)
{
    int low = 0, high = n-1;
    int last = -1

    while(low <= high)
    {
        int mid = (low + high)/2;
        if(arr[mid] == x)
        {
            last = mid;
            low = mid + 1:
        }
        else if(a[mid < x])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return last;
}

pair<int, int> firstAndLastPosition(vector<int> &arr, int n, int k)
{
    int first = firstOccurrence(arr, n, k);
    if(first == -1)
        return {-1, -1};                    // if nmbr doesnt exist first and last both are false

    int last = lastOccurrence(arr, n, k);
    return {first, last};
}

int count(vector<int> & arr, int n, int k);
{
    pair<int, int> ans = firstAndLastOccurrence(arr, n, k);
    if(ans.first == -1)
        return 0;
    
    return ans.second - ans.first + 1;
}
*/

int main()
{
    std::cout << "Hello World!\n";
}