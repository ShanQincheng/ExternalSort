# include <iostream>	 // cout, endl
# include <vector>
# include <fstream>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <cfloat>


using namespace std;

typedef struct stuPairs // define a struct, it will be read from file
{
    char sid_one[16] = {}; // information of sid1
    char sid_two[16] = {}; // information of sid2
    float weight = -1.0;   // the weight between student sid1 and sid2
}StuPairs;

//int ReadBinaryFile(StuPairs* stuPairStructArray, string, int, int); // read node pairs from binary file
int ReadBinaryFile(StuPairs* stuPairStructArray, string, int, int); // read node pairs from binary file
StuPairs* QuickSort(StuPairs* elementArray, int left, int right);  // QuickSort algorithm sorts StuPairs Array by weight. internal sort
bool OutPutBinaryFile(StuPairs* elementArray, int arraySize, string outPutFileName); // output StuPairs structure to file with binary format
void MergeSort(StuPairs* elementArray, int p, int r);  // merge sort main function
void Merge(StuPairs* elementArray, int p, int q, int r); // merge sort core function
void ExternalSort(string inputFile1, string inputFile2, string outputFile); // external sort first generation
void DeepExternalSort(string inputFile1, string inputFile2, string outputFile, int memorySize); // external sort deeper generation
void print_head(string fileName); // 
void play(string fileName);
