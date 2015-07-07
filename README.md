# DynamicVector
A templated C++ vector class, implemented using a dynamic array.

A vector functions similarily to an array. However, unlike an array, a
vector's size may change dynamically, with the storage automatically 
handled by the vector container. This class also provides indexing, 
insertion, and deletion of elements.

This dynamic vector implementation uses a dynamic array that grows and
shrinks as elements are added to and removed.

Elements may be accessed as efficiently as with an array, in O(1) time.
Pushing a new elements takes an amortized O(1) time, with the worst-case 
being O(N) time in the case needing reallocating the dynamic storage due 
to list growth. Inserting and deleting elements from the middle of the
vector take O(N) time in the worst case as elements must be shifted into
their proper places. It takes O(N) in the worse case to reallocate
memory when the array is exhausted or to reclaim significant unused space.

An array implementation (as opposed to linked list) for a dynamic vector
has better overall performance if the time per operation is not important 
(the cost of O(N) is amortized over N/2 actions). While a linked list is 
faster in the worst-case scenario, it may overall have a slower runtime 
because of the number of allocations performed.
