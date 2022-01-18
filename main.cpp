#include <iostream>
#include "./v0.2/SortedStudent.h"

int main() {
    clock_t start;
    double duration;

    start = clock();



    SortedStudent student;

    //v0.1
    //student.handleInputState();

    //v0.2 Create file and fill with random values by cycle
    //Time elapsed 0 seconds
    //student.createFile();

    //Time elapsed ~0.30 seconds
    //student.fillFileWithRandomData();

    //Lines of codes 1217. Fill name "55"
    //Change vector to deque or list with CTRL_R command. Use match case and words
    //Time elapsed in seconds
    //Deque 0.031
    //Vector 0.047
    student.exportSortedData();

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Time elapsed (in seconds): "<< duration <<'\n';

    return 0;
}
