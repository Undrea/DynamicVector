/**************************************************************************

Templated Dynamic Vector 

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

***************************************************************************/


#ifndef __DYNAMIC_VECTOR__
#define __DYNAMIC_VECTOR__

#include <iostream>
#include <string>

using namespace std;

template <typename T> 
class DynamicVector {
private:
	size_t curr_size;
	size_t capacity;
	T* arr;
public:
	/*	Constructors	***************************************************/
	DynamicVector();
	DynamicVector(const DynamicVector<T>& copy_vector);

	/*	Deconstructor	***************************************************/
	~DynamicVector();

	/*	Overloaded Operators	*******************************************/
	DynamicVector<T>& operator= (const DynamicVector<T>& copy_vector);

	/*	Manipulators	***************************************************/
	//
	// push
	// 
	// Push the passed value to the end of the vector.
	//
	// Preconditions:	value is initialized
	// Postconditions:	pushes value onto the end of the vector
	// Inputs:			value: the value to push onto the vector
	// Outputs:			none
	//
	void push(const T& value);

	//
	// erase
	// 
	// Erase value at erase_index and shift elements left to fill that space.
	//
	// Preconditions:	erase_index is initialized
	//					erase_index < curr_size
	// Postconditions:  erases value at erase_index and shift elements left into space
	// Inputs:			erase_index: the index at which to remove the element from the vector
	// Outputs:			none
	//
	void erase(const unsigned int erase_index);

	//
	// insert
	// 
	// Inserts an element into the vector at insert_index.
	//
	// Preconditions:	value and insert_index are initialized
	//					insert_index <= curr_size
	// Postconditions:	value is added to the vector at the index and the elements at a larger index are shifted right
	// Inputs:			value: the value to insert to the vector
	//					insert_index: the index at which to insert the element to the vector
	// Outputs:			none
	//
	void insert(const T& value, const unsigned int insert_index);

	/*	Getters		*******************************************************/
	//
	// size
	// 
	// Return the current size of the vector.
	//
	// Preconditions:	none
	// Postconditions:	returns the unsigned corresponding to the size of the vector
	// Inputs:			none
	// Outputs:			the size of the vector
	//
	unsigned size() const;

	//
	// operator [ ]
	// 
	// Returns the object at index i in the vector.
	//
	// Preconditions:	i is initialized
	// Postconditions:	returns the object at position i in the vector
	// Inputs:			i: the index requested
	// Outputs:			the object at that position in the vector
	//
	T& operator [ ] (const unsigned int i) const;
	
	//
	// nullify
	// 
	// Deletes all elements in the vector.
	//
	// Preconditions:	
	// Postconditions:	vector class is initialized to its starting settings
	// Inputs:			
	// Outputs:			
	//
	void nullify();
};

#endif