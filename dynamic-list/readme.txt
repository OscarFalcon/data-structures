Generalized Dynamic List 

This is a dynamic list implementation. Most dynamic lists out there are hard
coded to represent arrays of a fixed data type, with the most common being a 
list of ints. Unfortunately, this method of hard coding to a specific type
is not very helpfull in terms of reuseability. Here, a generalized type dynamic
list is implemented that allows arbitrary data types as elements of the array. 
Elements can be ints, doubles, longs, arrays of chars, structs, etc. The 
specific type (actually size of the type in bytes) is specified at run time, 
and all other operations are carried out as a normal dynamic list. 


This code has five functions described as follows:

dlist_init - This initializes a list, and takes as arguments the initial length
the list should be, the size of the element in the list, and the growth factor,
which is an integer indicating by how much the array should grow by when
reallocation is needed.

dlist_free - Frees all memory associated with the list

dlist_insert - Inserts a value into the list. The value is specific as an 
argument by providing a pointer to a void. The data pointed to by this pointer
is copied into the array.

dlist_get - a convenience function for retriving an element in the list

dlist_set - a convenience function for setting an element in the list. 