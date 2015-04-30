Allen Tung
Anthony Wong

#Malloc
Compilation Instructions
make test1 Test Basic test cases
make testf Test Fragmentation 
make testsl Test Sorted List with mymalloc


Functionality & Design
For this assignment we were required to implement error checking and functionality from the algorithm presented in CS214's lecture.  Firstly, to improve and decrease fragmentation errors, we changed the memory allocation algorithm's first fit policy, wherein the first available free block is chosen, to a best fit policy, where we locate the block that is the smallest acceptable size for the block.  Our range set is between the size of the block to 1.5 times the size of the block.  If that cannot be found, we choose the smallest block that is available.  We do not check for leaks in our malloc and assume that the programmer will follow good practice and always clean up allocated memory.  

Error Checks
In all our error checks, we output both the file name and line number where the error was triggered.  In malloc we had implemented several simple error checks.  If the user were to input a negative value we return an NULL pointer and an error message.  Secondly, we have a variable that keeps track of the total available free space regardless of whether they are adjacent blocks or not.  If the user inputs a value that is larger than the free space we output an error and return null.  In the free implementation we needed safeguards against freeing of non-dynamic memory, memory not allocated by malloc, as well as redundant calls to free.  To solve this we added in a simple loop that would locate the pointer to memory that matched the pointer we wanted to free.  If it is not found then we throw an error, solving the first two problems.  Also, if it is found but the flag isFree has already been raised then, we throw an error as well solving the redundant free error.

Efficiency
The malloc algorithm takes in worst case O(n^2) time, where n represents the total blocks in memory.  This occurs if the memory block only has block sizes smaller than the requested size.  Since it takes big O(n) time to search for the best fit block.  Failing that the malloc algorithm starts from root and traverses through the list again with a worst case time of O(n).  Thus combined the worst case time would be O(n^2).  
For the free algorithm worst case would be O(n).  The error check loop will take up to O(n) time to complete and throw an error if it fails to find a pointer match.  The actual freeing algorithm takes a constant time.  Thus giving the worst case of O(n).
