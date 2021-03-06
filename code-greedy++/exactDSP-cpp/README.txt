1) Count k cliques using mace http://research.nii.ac.jp/~uno/code/mace.html 
2) Input the resulting output file from mace (one line for each k-clique) to the densest.cpp 



— 
HI_PR is an efficient implementation of the push-relabel method.
See 
  Goldberg and Tarjan, "A New Approach to the Maximum Flow Problem,"
  J. ACM Vol. 35, 921--940, 1988
and 
  Cherkassky and Goldberg, "On Implementing Push-Relabel Method for the
  Maximum Flow Problem," Proc. IPCO-4, 157--171, 1995.

The program is designed to run under UNIX/LINUX.
The program reads from the standard input and writes to the standard
output. Run "make" to compile the program. Program name is "hi_pr".

If the total capacity of arcs out of the source is greater than MAXLONG,
then the flow computed by hi_pr is upper-bounded by MAXLONG and if the
maximum flow value is greater than MAXLONG, then the computed flow is not
maximum. In this case a warning message is printed. To deal with this overflow
problem, edit "types.h" and redefine "excessType" to be "long long int" if 
your compiler supports this type of "double" otherwise.

See makefile for compile-time options.

The program is available on "as is" basis. It is not guaranteed to
be free of bugs, and IG Systems assumes no responsibility for any
potential problems. 

This software comes with NO WARRANTY, expressed or implied. By way 
of example, but not limitation, we make no representations of warranties
of merchantability or fitness for any particular purpose or that the use
of the software components or documentation will not infringe any patents,
copyrights, trademarks, or other rights.
