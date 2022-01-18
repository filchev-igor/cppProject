**Change import, because versions are differed**

###v0.1
In order to run in main file use next code:

```
Student student;

student.handleInputState();
```

###v0.2
In order to run in main file use next code:

```
clock_t start;
double duration;

start = clock();

SortedStudent student;
```

Time elapsed 0 seconds

**Function creates new file**

`student.createFile();`

Time elapsed ~0.30 seconds
**Function for filling data with some random data**
```
student.fillFileWithRandomData();
```

Lines of codes 1217. Fill name **55**
Change vector to deque or list with CTRL_R command. Use match case and words
Time elapsed in seconds
Deque 0.031
Vector 0.047
**Function reads data from file, sorts and writes to new files with the passed and failed student results**
```
student.exportSortedData();

duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

cout<<"Time elapsed (in seconds): "<< duration <<'\n';
```

###v1.0

In version v0.2 I have used **first** strategy. I think, that it is better strategy, because initial file stays untouched 
by the algorithm and in case of using files for saving data (not any relational databases on the laptop (MySQL, etc.) or NoSQL
one's like MongoDB, etc.) this strategy allows programmer not to lose initial data by some mistake in his code.

**Task to split initial data by marks 5 was done in version v0.2**

Functions for discover:
1. std::find
2. std::find_if
3. std::search
4. std::copy
5. std::remove
6. std::remove_if
7. std::remove_copy
8. std::remove_copy_if
9. std::transform
10. std::partition
11. std::stable_partition

* Only find was used for splitting file data after read procedure by empty spaces and line breaks.
* Find_if is the same as find, but returns boolean value. Here it was not needed.
* Other functions from the list were not uses
* There is no need to use `copy`, because in some cases it is needed to use keys for vectors or something like 
`for (const <type> var: vectorName)` for exact data extraction
* `remove` function for deleting some spaces and line breaks was not used, because initial string was 
split with the `find` function
* It might be better for my code to use `remove_copy` for solving problem with the line breaks, and it could 
make my code shorter
