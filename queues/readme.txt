/**********************************************************************
 *  Randomized Queues and Deques
 **********************************************************************/

Name: Joo, Minhyung
ID: 20173164
Login: mjoo
Hours to complete assignment (optional): 10+


/**********************************************************************
 *  Explain briefly how you implemented the randomized queue and deque.
 *  Which data structure did you choose (array, linked list, etc.)
 *  and why?
 **********************************************************************/
 
 Randomized queue implements singly-linked list while deque implements
 doubly-linked list. The double and single link choice was quite obvious,
 because deque must support adding and removing from both front and back
 in constant time while randomized queue does not.

/**********************************************************************
 *  Briefly describe why any sequence of N randomized queue operations,
 *  starting from an empty randomized queue, takes O(N) time.
 **********************************************************************/

  Randomly accessing an item in the queue will have varying time cost.
  Assuming the process is completely random, the time cost of accessing
  front elements and that of accessing back elements will be evened out
  in the long run.

/**********************************************************************
 *  Briefly describe why each Deque operation takes O(1) time.
 **********************************************************************/

  Since deque is designed using doubly-linked list, accessing the first
  and last elements of the list takes constant time, as the pointers are
  stored. For the size() function to be constant, deque class also keeps
  a int _size variable.

/**********************************************************************
 *  How much memory (in bytes) does your data type use to store N items.
 *  Use tilde notation to simplify your answer. Use the memory requirements
 *  for a "typical machine" given in Lecture. In your analysis, don't include
 *  the memory for the items themselves (as this memory is allocated by
 *  the client and depends on the item type.
 *  For a typical machine, refer to page 11 of 
 *  https://www.cs.princeton.edu/courses/archive/spr10/cos226/lectures/02-14Analysis-2x2.pdf
 **********************************************************************/

RandomizedQueue: ~ 12N

Dequeue: ~ 16N

Assuming object overhead is 8 bytes and a pointer is 4 bytes.
The difference comes from single vs double link.

/**********************************************************************
 *  Known bugs / limitations.
 **********************************************************************/
  The Iterator classes support the bare minimum of operators. So, many STL
  techniques such as "iterators - v.begin();" cannot be performed. Only
  a straight traversal of the list is possible. 

/**********************************************************************
 *  List whatever help (if any) that you received and from whom,
 *  including help from staff members or lab TAs.
 **********************************************************************/
  
  Had to contact professor Tang on various points of the project, including
  library choice and exception handling.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

  Probably not serious, but I think writing codes for correctly handling
  standard input took as long as desigining the data structures. I still
  think standard input system is so arbitrary.

/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/
