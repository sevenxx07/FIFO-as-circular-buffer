# Formulation of the problem
A queue is a data structure that defines element selection and insertion operations. The select-from-queue operation selects the element that we 
inserted into the queue first. When pushing elements into a queue, the inserted item is inserted at the end of the queue.
This structure is also sometimes referred to as FIFO (first-in first-out).

A queue can be implemented as an array, either a static length array with an explicit limitation on the number of inserted elements or a dynamic length array. 
Alternatively, it can also be implemented with a data structure called a linked list.

The simplest implementation of a queue in an array is to store the ith element in the queue at the ith position in the array. Adding a new element is very easy. 
Second, removing elements can take a long time, because in order to preserve the order, it is necessary to first remove the 1st element (from the front) of the queue 
and move all subsequent elements by one position. Such an implementation is quite inefficient for larger queues, so it is usually not used.

A circular queue is an efficient implementation of an array queue in which no elements are moved during the pop() operation. In a circular queue, we can imagine that 
the allocated array is looped. Now we no longer change the position of individual elements, but only move the pointers to the beginning and end of the data area. 
When implementing, I needed to pay special attention to the situation when the first few elements in the queue are at the end of the array and the rest are already at the beginning of the array.

![obrazek](https://github.com/user-attachments/assets/d921f632-177a-49df-b250-99d205417a18)

# Implementation of the problem
I resized the allocated array dynamically so that the queue uses an adequate amount of memory. It is necessary to enlarge and reduce the field. The push_to_queue() function should thus always execute 
successfully and return true unless some exceptional event occurs. I implemented increasing the queue to twice its original size and reducing it to a third when it drops below this limit. 
This way I avoided frequent resizing.
