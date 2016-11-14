/**********************************************************************
 *  Pattern Recognition readme.txt template
 **********************************************************************/

Name: Minhyung Joo
Login: mjoo
Hours to complete assignment (optional): 20+



/**********************************************************************
 *  Step 1.  Explain briefly how you implemented brute force.
 *           What method(s) did you add to the Point data type?
 **********************************************************************/

The brute force algorithm basically compares four points by iterating
through four loops so as to compare every permutation of the set of points.
The comparison happens by picking the leftmost Point as origin and
computing the slopes with three other points. If the slopes are equal,
print the line and continue.
No method was implemented in Point for this algorithm. 


/**********************************************************************
 *  Step 2.  Explain briefly how you implemented the sorting solution.
 *           Did you sort by angle, slope, or something else?
 *           What method(s) did you add to the Point data type?
 *           What steps did you do to print a minimal representation?
 **********************************************************************/

The sort was done by slope. The point picked as origin will be passed to
the sort algorithm, because the Point class itself was implemented as a
functor by overloading the () operator.
For minimal representation, a copy of the original container of Points was
made, then every point that constitutes a line segment was popped from
the container. Not very memory efficient, but accurate.

/**********************************************************************
 *  Empirical    Fill in the table below with actual running times in
 *  Analysis     seconds when reasonable (say 180 seconds or less).
 *               You can round to the nearest tenth of a second.
 **********************************************************************/

      N       brute       sorting
---------------------------------
     10         1ms        < 1ms
     20         2ms        < 1ms
     40         5ms        < 1ms
     80        40ms          2ms
    100       118ms          4ms       
    150       329ms          7ms
    200       930ms         14ms
    400      8000ms         22ms
   1000     37827ms         45ms
   2000      >180s         220ms
   4000      >180s         717ms
  10000      >180s        4065ms
 100000   (for fun!)     82248ms

/**********************************************************************
 *  Estimate how long it would take to solve an instance of size
 *  N = 1,000,000 for each of the two algorithms using your computer.
 **********************************************************************/
Brute: Years...
Sorting: Around 30 minutes


/**********************************************************************
 *  Theoretical   Give the worst-case running time of your programs
 *  Analysis      as a function of N. Justify your answer briefly.
 **********************************************************************/
Brute: O(N^4)
Brute algorithm is simply a 4 for loops with iterations given by:
(N-3)(N-2)(N-1)(N)

Sorting: O(N^3logN)
Outermost loop executes N times. Sorting is assumed to take NlogN. In
worst case, where the three aligning points are in the last of the array,
the search roughly takes N.

/**********************************************************************
 *  Known bugs / limitations. For example, if your program prints
 *  out different representations of the same line segment when there
 *  are 5 or more points on a line segment, indicate that here.
 **********************************************************************/
The Qt GUI cannot handle more than 2000 points. The initial points show
up correctly but once it runs the algorithms the program freezes. I am
guessing this is because of generating too many line objects.


/**********************************************************************
 *  List whatever help (if any) that you received. Be specific with
 *  the names of lab TAs, classmates, or course staff members.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/




/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/

