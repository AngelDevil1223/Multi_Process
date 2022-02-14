# Multi_Process

Project specification


You are required to process several data sets and calculate certain values based on their content. Each data sample is a floating-point number. Each data set consists of many data samples and each data set is stored in a file. The file format is that all data samples in this data set are separated by whitespace in the file. As an example, we have posted three data sets on the course site: dataset1, dataset2, and dataset3, for your reference. However, your program should be able to process any number of data sets.

•	Write a C program, called process.c, to do the calculation concurrently with multiple processes. The program first reads the file names of all data sets from the command line. For each data set, it creates a child process. Each child process reads the data samples from its file and calculates: i) the sum of all data sample values in the dataset (sum); ii) the number of the data sample values in the dataset (num). Then the child process sends the calculated sum and num values to the main process via a Unix pipe. The main process will print to the standard output the file name of the data set followed by the received sum and num values and the average of the values in the dataset (avg) derived from the sum and num values in the main process. The output of one data set occupies one line as shown below. You may structure your code either as i) waiting for all child processes to finish then processing their data in the order the children were created or ii) waiting for any child to finish and processing its data then repeating this until all children are finished (more difficult but may earn you some extra credit). Finally the main program, based on the received values, calculates the average (just 1 value) for all samples in all datasets and prints it to the standard output. The output of the main program should be as follows:

Filenamei SUM=sumi NUM=numi AVG=avgi Filenamej SUM=sumj NUM=numj AVG=avgj
… AVERAGE=average
 


•	Write a Pthread C program, called thread.c, to repeat the above calculation concurrently with multiple threads. The program creates a thread to process each data set. Each thread does the calculations for its data set and passes the results to the main program. The main program waits for all threads to finish and, based on the obtained values, calculates and prints the final results to the standard output in the same format as above.

Your programs should compile as follows:

gcc -o prs process.c
gcc -o thr thread.c -lpthread

And the programs should run as follows (all datasets are provided as command line arguments):

./prs dataset1 dataset2 dataset3
./thr dataset1 dataset2 dataset3
