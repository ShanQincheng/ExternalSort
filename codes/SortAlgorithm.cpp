//
// Created by ÈëÉ½ on 6/6/2017.
//


#include "headFile.h"

StuPairs* QuickSort(StuPairs* elementArray, int left, int right) // Quick sort code but not use in this program
{
    int i, j;
    i = left + 1;
    j = right;
    float pivot;
    pivot = elementArray[left].weight;
    StuPairs tempStuPair;

    if(left >= right)
        return elementArray;
    while(true)
    {
        while(i < right)
        {
            if(elementArray[i].weight < pivot)
                i++;
            else
                break;
        }
        while(j > left)
        {
            if(elementArray[j].weight > pivot)
                j--;
            else
                break;
        }
        if(i >= j)
        {
            break;
        }else{
            tempStuPair = elementArray[i];
            elementArray[i] = elementArray[j];
            elementArray[j] = tempStuPair;
        }
    }
    tempStuPair = elementArray[left];
    elementArray[left] = elementArray[j];
    elementArray[j] = tempStuPair;

    QuickSort(elementArray,left, j - 1);
    QuickSort(elementArray,j + 1, right);
}

void MergeSort(StuPairs* elementArray, int p, int r) // p: start index r: end index q: middle index
{
    if(p < r)
    {
        int q = (p + r) / 2;		

        MergeSort(elementArray, p, q);  // sort the left part of the array
        MergeSort(elementArray, q + 1, r);  // sort the right part of the array
        Merge(elementArray, p, q, r);	// merge left part and right part sorting result
    }
    return ;
}

void Merge(StuPairs* elementArray, int p, int q, int r)  
{
    int n1 = q - p + 1;	// n1: the number of left part
    int n2 = r - q; // n2: the number of right part
    int i, j, k = 0; // iterator variable
    StuPairs* leftArray = (StuPairs*)calloc( (n1 + 1), sizeof(StuPairs));	// calloc left array
    StuPairs* rightArray = (StuPairs*)calloc( (n2 + 1), sizeof(StuPairs));	// calloc right array

    for(i = 0; i < n1; i++)	//	assign left part array
    {
        leftArray[i] = elementArray[p + i];
    }
    leftArray[i].weight = FLT_MAX;
    for(i = 0; i < n2; i++)	//	assign right part array
    {
        rightArray[i] = elementArray[q + 1 + i];
    }
    rightArray[i].weight = FLT_MAX;

    i = 0;	//	i: point to L part
    j = 0;	// j: poinrt to R part
    for(k = p; k <= r; k++)	
    {
        if(leftArray[i].weight <= rightArray[j].weight)	//	if leftArray[i].weight <= rightArray[j].weight
        {
            elementArray[k] = leftArray[i];
            i++;
        }else{	// if leftArray[i].weight > rightArray[j].weight
            elementArray[k] = rightArray[j];
            j++;
        }
    }

    return;
}

void ExternalSort(string inputFile1, string inputFile2, string outputFile)
{
    int i, j,  k = 0; // vector size
    //StuPairs* stuPairStructArray = NULL;
    ifstream finStream1;
    ifstream finStream2;
    ofstream foutStream;
    StuPairs fileStuPairs1, fileStuPairs2;

    int inputFileLength1, inputFileLength2, outputFileLength = -1;

    //stuPairStructArray = (StuPairs*)calloc(memorySize, sizeof(StuPairs));
    finStream1.open(inputFile1, ios::binary);
    finStream2.open(inputFile2, ios::binary);
    foutStream.open(outputFile, ios::binary);

    if(!finStream1 || !finStream2)
    {
        return;
    }else{
        finStream1.seekg(0, finStream1.end);
        inputFileLength1 = finStream1.tellg();
        finStream2.seekg(0, finStream2.end);
        inputFileLength2 = finStream2.tellg();
        outputFileLength = inputFileLength1 + inputFileLength2;
        /*
        printf("File 1  END == %d\n", inputFileLength1);
        printf("File 2  END == %d\n", inputFileLength2);
        printf("OutFile   END == %d\n", outputFileLength);
        //printf("current position == %d\n", readPosition);
         */
        finStream1.seekg(0, finStream1.beg);
        finStream2.seekg(0, finStream1.beg);
        foutStream.seekp(0, foutStream.beg);
        finStream1.read(reinterpret_cast<char*>(&fileStuPairs1), sizeof(StuPairs) * 1);
        finStream2.read(reinterpret_cast<char*>(&fileStuPairs2), sizeof(StuPairs) * 1);

        for(k = foutStream.tellp(); k < outputFileLength; k = foutStream.tellp()) {
            if (fileStuPairs1.weight <= fileStuPairs2.weight) {
                foutStream.write(reinterpret_cast<char *>(&fileStuPairs1), sizeof(StuPairs) * 1);
                if (finStream1.tellg() >= inputFileLength1) {
                    foutStream.write(reinterpret_cast<char *>(&fileStuPairs2), sizeof(StuPairs) * 1);
                    while (finStream2.tellg() < inputFileLength2) {
                        finStream2.read(reinterpret_cast<char *>(&fileStuPairs2), sizeof(StuPairs) * 1);
                        foutStream.write(reinterpret_cast<char *>(&fileStuPairs2), sizeof(StuPairs) * 1);
                    }
                    continue;
                }
                finStream1.read(reinterpret_cast<char *>(&fileStuPairs1), sizeof(StuPairs) * 1);
            } else {
                foutStream.write(reinterpret_cast<char *>(&fileStuPairs2), sizeof(StuPairs) * 1);
                if (finStream2.tellg() >= inputFileLength2) {
                    foutStream.write(reinterpret_cast<char *>(&fileStuPairs1), sizeof(StuPairs) * 1);
                    while (finStream1.tellg() < inputFileLength1) {
                        finStream1.read(reinterpret_cast<char *>(&fileStuPairs1), sizeof(StuPairs) * 1);
                        foutStream.write(reinterpret_cast<char *>(&fileStuPairs1), sizeof(StuPairs) * 1);
                    }
                    continue;
                }
                finStream2.read(reinterpret_cast<char *>(&fileStuPairs2), sizeof(StuPairs) * 1);
            }
        }

        finStream1.close();
        finStream2.close();

        return;
    }
}

void DeepExternalSort(string inputFile1, string inputFile2, string outputFile, int memorySize)
{
    //StuPairs* stuPairStructArray = NULL;
    /*
    ifstream finStream1;
    ifstream finStream2;
    ofstream foutStream;
     */
    FILE * pFile1 = NULL;	// pFile1 point to file 1
    FILE * pFile2 = NULL;	// pFile2 point to file 2
    FILE * pOutFile = NULL;	// pOutFile point to output file
    StuPairs* fileStuPairsBuffer1 = NULL;	//	store stu pairs read from file 1  
    StuPairs* fileStuPairsBuffer2 = NULL;	// store stu parirs read from file 2
    unsigned int fileResult1 = -1;	//	the number of stu pairs stored in fileStuPairsBuffer1
    unsigned int fileResult2 = -1;	// the number of stu pairs stored in fileStuPairsBuffer2
    unsigned int i, j,  k = 0; // vector size
    bool fileDone1 = false;	// file 1 finished
    bool fileDone2 = false;  // file 2 finished

    fileStuPairsBuffer1 = (StuPairs*)calloc(memorySize / 2, sizeof(StuPairs));	// calloc for fileStuPairsBuffer1
    fileStuPairsBuffer2 = (StuPairs*)calloc(memorySize / 2, sizeof(StuPairs));	// calloc for fileStuPairsBuffer1
    pFile1 = fopen(inputFile1.c_str(), "rb");	// open and read file1 with binary format
    pFile2 = fopen(inputFile2.c_str(), "rb");	// open and read file2 with binary format
    pOutFile = fopen(outputFile.c_str(), "wb");	// write stu pairs with binary format
    if(pFile1 == NULL || pFile2 == NULL) { printf("Read files error", stderr); exit(1); }
    if(pOutFile == NULL) { printf("Write file error", stderr);}

    /*
     *   size_t fread( void *buffer, size_t size, size_t count, FILE *stream);
     * */
    fileResult1 = fread(fileStuPairsBuffer1, sizeof(StuPairs), memorySize / 2, pFile1);	// read stu paris in fileBuffer1 with the size of half memorySize
    fileResult2 = fread(fileStuPairsBuffer2, sizeof(StuPairs), memorySize / 2, pFile2);	// read stu paris in fileBuffer2 with the size of half memorySize
    i = 0, j= 0;	// i point to fileStuPairsBuffer1, j point to fileStuPairsBuffer2
    while(true)
    {
        if(fileStuPairsBuffer1[i].weight <= fileStuPairsBuffer2[j].weight && fileDone1 == false && fileDone2 == false) // if fileBuffer1[i] <= fileBuffer2[j] 
        {
            //fputs(&fileStuPairsBuffer1[i], pOutFile);
            fwrite(&fileStuPairsBuffer1[i], sizeof(StuPairs), 1, pOutFile);
            i++;
            //if(i >= fileResult1 / 2 && j < fileResult2)
            if(i >= fileResult1)
            {
                fileResult1 = fread(fileStuPairsBuffer1, sizeof(StuPairs), memorySize / 2, pFile1);
                if(fileResult1 == 0)
                {
                    fileDone1 = true;
                }
                i = 0;
            }
        }else if(fileStuPairsBuffer1[i].weight > fileStuPairsBuffer2[j].weight && fileDone1 == false && fileDone2 == false){  // if fileBuffer1[i] > fileBuffer2[j]
            //fputs(&fileStuPairsBuffer2[j], pOutFile);
            fwrite(&fileStuPairsBuffer2[j], sizeof(StuPairs), 1, pOutFile);
            j++;
            //if(j >= fileResult2 && i < fileResult1)
            if(j >= fileResult2)
            {
                fileResult2 = fread(fileStuPairsBuffer2, sizeof(StuPairs), memorySize / 2, pFile2);
                if(fileResult2 == 0)
                {
                    fileDone2 = true;
                }
                j = 0;
            }
        }else if( fileDone1 && (!fileDone2) ){	//	if file 1 finished
            //fputs(&fileStuPairsBuffer2[j], pOutFile);
            fwrite(&fileStuPairsBuffer2[j], sizeof(StuPairs), 1, pOutFile);
            j++;
            if(j >= fileResult2)
            {
                fileResult2 = fread(fileStuPairsBuffer2, sizeof(StuPairs), memorySize / 2, pFile2);
//                if(fileResult2 == 0)
                if(fileResult2 == 0)
                {
                    fileDone2 = true;
                    //cout<<"aaa"<<endl;
                }
                j = 0;
            }
        }else if( (!fileDone1) && fileDone2 ){	// if file 2 finished
            //fputs(&fileStuPairsBuffer1[i], pOutFile);
            fwrite(&fileStuPairsBuffer1[i], sizeof(StuPairs), 1, pOutFile);
            i++;
            if(i >= fileResult1)
            {
                fileResult1 = fread(fileStuPairsBuffer1, sizeof(StuPairs), memorySize / 2, pFile1);
                if(fileResult1 == 0)
                {
                    fileDone1 = true;
                }
                i = 0;
            }
        }else{ // both file1 file2 finished
            break;
        }
    }

    fclose(pFile1);
    fclose(pFile2);
    fclose(pOutFile);
    free(fileStuPairsBuffer1);
    free(fileStuPairsBuffer2);

    return ;
}



