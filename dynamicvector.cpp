/**************************************************************************

Templated Dynamic Vector

See header file for documentation.

***************************************************************************/

#include "dynamicvector.h"

template <typename T>
DynamicVector<T>::DynamicVector() : curr_size(0), capacity(0), arr(nullptr)
{
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	this->nullify();
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& copy_vector) : arr(nullptr), curr_size(0), capacity(0)
{
	// Create a deep copy by using the assignment operator.
	*this = copy_vector;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator= (const DynamicVector<T>& copy_vector)
{
	// Do not proceed with invalid self-assignment.
	if (this != &copy_vector)
	{
		// Clear existing array.
		this->nullify();

		// Copy values for current size and capacity.
		curr_size = copy_vector.curr_size;
		capacity = copy_vector.capacity;

		// Allocate new memory to copy elements in.
		arr = new T[capacity];
		if (arr == nullptr)
		{
			throw string("Error: DynamicVector memory allocation failure.");
		}

		// If there are elements in the vector, copy elements from the copy list to the new list.
		if (curr_size >= 1)
		{
			memcpy(arr, copy_vector.arr, curr_size * sizeof(T));
		}
	}

	return *this;
}

template <typename T>
void DynamicVector<T>::push(const T& value)
{
	// Must allocate more space if the size would exceed the current capacity, or if there is no capacity.
	if(curr_size >= capacity)
	{
		if(capacity == 0)
		{			
			capacity = 1; // Choose an arbitrary starting size if this is the first insertion.
		}
		else
		{			
			capacity = capacity * 2; // Double the size if the vector would run out of its currently allocated space.
		}

		// Reallocate the array.
		T* new_arr = nullptr;

		// Allocate a new dynamic array with n elements.
		new_arr = new T[capacity];
		if (new_arr == nullptr)
		{
			throw string("Error: DynamicVector memory allocation failure.");
		}

		// If there were elements in the vector, copy elements from the old list to the new list.
		if (curr_size >= 1)
		{
			memcpy(new_arr, arr, curr_size * sizeof(T));
		}

		// Delete original dynamic array. if arr is NULL, the vector was
		// originally empty and there is no memory to delete.
		if (arr != nullptr)
		{
			delete [] arr;
		}

		// Save new array.
		arr = new_arr;	

		// Insert the new element and update vector size.
		arr[curr_size] = value;
		curr_size++;
	}
	else	// Did not exceed size, so just insert.
	{
		arr[curr_size] = value;
		curr_size++;
	}
}

template <typename T>
void DynamicVector<T>::erase(const unsigned int erase_index)
{
	// Only delete an element within the bounds of the array.
	if(erase_index >= 0 && erase_index < curr_size)
	{
		// Erase value at erase_index and shift elements left.
		for(unsigned i = (erase_index + 1); i < curr_size; i++)
		{
			arr[i - 1] = arr[i];
		}

		curr_size--;

		// Shrink the dynamic array if it becomes too small.
		if (curr_size < (capacity / 2))
		{
			// Reallocate the array.
			T* new_arr = nullptr;

			// Allocate a new dynamic array with n / 2 elements.
			new_arr = new T[capacity / 2];
			if (new_arr == nullptr)
			{
				throw string("Error: DynamicVector memory allocation failure.");
			}

			// If there were elements in the vector, copy elements from the old list to the new list.
			if (curr_size >= 1)
			{
				memcpy(new_arr, arr, curr_size * sizeof(T));
			}

			// Delete original dynamic array. if arr is NULL, the vector was
			// originally empty and there is no memory to delete.
			if (arr != nullptr)
			{
				delete[] arr;
			}

			// Save the new array.
			arr = new_arr;

			// Update capacity.
			capacity = capacity / 2;
		}
	}
}

template <typename T>
void DynamicVector<T>::insert(const T& value, const unsigned int insert_index)
{
	// If inserting into the middle of the array...
	if(insert_index >= 0 && insert_index <= curr_size)
	{
		// Check we have enough room to insert a new element. If not, allocate more space and copy over the array.
		if(curr_size >= capacity)
		{
			if(capacity == 0)
			{				
				capacity = 1; // Choose an arbitrary size.
			}
			else
			{				
				capacity = capacity * 2; // Double the size.
			}

			// Reallocate the array
			T* new_arr = nullptr;

			// Allocate a new dynamic array with n elements.
			new_arr = new T[capacity];
			if (new_arr == nullptr)
			{
				throw string("Error: DynamicVector memory allocation failure.");
			}

			// If there were elements in the vector, copy elements from the old list to the new list
			if (curr_size >= 1)
			{
				// Copy the first half of the array, insert_index number of values.
				memcpy(new_arr, arr, insert_index * sizeof(T));

				// Insert the new value.
				new_arr[insert_index] = value;			

				// Starting after the new value, copy over the remainder of the array.
				memcpy(	&new_arr[insert_index + 1],
					&arr[insert_index],
					(curr_size - insert_index)* sizeof(T));
			}
			else // else curr_size == 0. We insert the first element.
			{
				new_arr[0] = value;
			}

			curr_size++;

			// Delete original dynamic array. if vArr is NULL, the vector was
			// originally empty and there is no memory to delete.
			if (arr != nullptr)
			{
				delete [] arr;
			}

			// Save the new array.
			arr = new_arr;	
		}
		else
		{
			// Put the new element at insert_index and shift the other elements right.
			curr_size++;
			for(unsigned i = (curr_size - 1); i > insert_index; i--)
			{
				arr[i] = arr[i - 1];
			}
			arr[insert_index] = value;
		}
	}
	else if (insert_index >= 0 && insert_index == curr_size) // Insert at the end of the array.
	{
		this->push(value);
	}
}

template <typename T>
unsigned DynamicVector<T>::size() const
{
	return curr_size;
}

template <typename T>
T& DynamicVector<T>::operator [ ] (const unsigned int i) const
{
	if (i > (curr_size - 1))	// Abort if array out of bounds.
	{
		throw string("Error: Array out of bounds.");
	}
	return arr[i];
}

template <typename T>
void DynamicVector<T>::nullify()
{
	// Delete the memory of the array, if any.
	if (capacity > 0)
		delete [] arr;
	
	// Reinitialize.
	curr_size	= 0;
	capacity	= 0;
	arr		= nullptr;
}

template class DynamicVector<string>;
template class DynamicVector<int>;
