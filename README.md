# Algorithms for DSP

To read more about the project please see the project_report.pdf

This project consisted of 4 different approaches:
1) To get the approximation through Greedy++ algorithm read the README in code-greedy++ folder. This algorithm takes a list of edges as its input. The enumeration of nodes starts with one, and the first line of the input file should consist of the number of nodes and the number of edges.

2) To compile the arboricity approximation algorithm change the folder to arb_testing and run 
g++ arb\_algo.cpp -o arb\_algo

To run it run
./arb\_algo 

It expects an adjacency list as its input, where the first line is the number of nodes, and the next lines start with the degree of the corresponding node and then the list of neighbors. The enumeration of nodes starts with zero.

3) To get the exact solution read the README in code-greedy++ folder. This algorithm takes a list of edges as its input. The enumeration of nodes starts with one, and the first line of the input file should consist of the number of nodes and the number of edges.

4) To use the sampling technique it's necessary to run the input_convertion.ipynb script, and then run the exact solution on the output of the corresponding sampling procedure. The script takes just a list of edges with no additional information, the enumeration of nodes starts with 0.


input_convertion.ipynb can be used to convert from the list of edges with no additional information (starting at 0) to all other needed formats.

Also, there are test generators for complete graphs in the data folder. They take the number of nodes as the input and output edge\_list/adj\_list for the complete graph.
