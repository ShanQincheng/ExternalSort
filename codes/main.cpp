// T07
// 10427124 ¬_ªÃ¼e  04106034 ¦ó¬FÀM

# include "headFile.h"

int main(int argc, char** argv) {
    StuPairs* stuPairStructArray = NULL;
    StuPairs stuPair;
    string filename;
    string filenameHead = "pairs";
    string filenameEnd = ".dat";
    string outputFileHead = "outout";
    string outputFilename;
    string oddLastFileName;
    int i = 0; // iterator variable
    int fileSerialNumber = -1;
    int continueFlag = 0;  // The variable used to determine whether the program continues execution
    int readPosition = -1;
    int memorySize = 5;
    int filesNumber = -1;  // record how many files are created
    int fileLength = -1;
    int singleStuPairsLength = -1;
    int totalPairs = -1;
    clock_t startTime, finishTime;
    double internalSortTime, externalSortTime = 0.0;
    vector<string> filenameVector;
    //vector<string> filenameSecondVector;
    bool oddFlag = false; 

    cout << "*******************************************###****" << endl;
    cout << " On-machine Exercise 08                          *" << endl;
    cout << " Mission 1: External Merge Sort on a Binary File *" << endl;
    cout << " Mission 2: Threshold search on Primary Index    *" << endl;
    cout << "*******************************************###****" << endl;
    cout << "##############################################################" << endl;
    cout << "Mission 1: External Merge Sort on a Binary File" << endl;
    cout << "##############################################################" << endl << endl;

    cout << "Input the file name (e.g., 801, 802, 803): [0]Quit" << endl;
    cin >> filename ;
	
	
	/*
		Pre-processing before program work, not important
	*/
    while ( filename != "0")
    {
        ifstream inF;
        //stuPairStructArray = (StuPairs*)calloc(memorySize, sizeof(StuPairs));
        inF.open(filenameHead + filename + filenameEnd, std::ifstream::binary);
        if(!inF)
            exit(1);
        inF.seekg(0, inF.end);
        fileLength = inF.tellg();
        inF.seekg(0, inF.beg);
        inF.read(reinterpret_cast<char*>(&stuPair), sizeof(StuPairs) * 1);
        singleStuPairsLength = inF.tellg();
        totalPairs = fileLength / singleStuPairsLength;
        inF.close();
        printf("\"Please input a number in the range [20, %d]:\n", totalPairs / 2);
        //cout << "Please input a number in the range [20, 390]:" << endl;
        cin >> memorySize;
        printf("Number of initial runs = number of pairs / buffer size = %d / %d = %d\n", totalPairs, memorySize, totalPairs / memorySize);

        /*
            Read the student information file, split each single student information
            and then store each single student information into a stuInfo Structre.
            push_back each stu info structure into the stuInfoVector
        */
		startTime = clock();  // Timing starts
        stuPairStructArray = (StuPairs*)calloc(memorySize, sizeof(StuPairs));
        while( (readPosition = ReadBinaryFile(stuPairStructArray, filenameHead + filename + filenameEnd, memorySize, readPosition) ) == -1) // generate the input .txt file name
        {
            cout << filenameHead + filename + filenameEnd << " does not exist!!!" << endl << endl;
            cout <<"Input the file name (e.g., 801, 802, 803): [0]Quit" << endl;
            cin >> filename;
            if(filename == "0")
                return 0;
            ifstream inF;
            //stuPairStructArray = (StuPairs*)calloc(memorySize, sizeof(StuPairs));
            inF.open(filenameHead + filename + filenameEnd, std::ifstream::binary);
            if(!inF)
                exit(1);
            inF.seekg(0, inF.end);
            fileLength = inF.tellg();
            inF.seekg(0, inF.beg);
            inF.read(reinterpret_cast<char*>(&stuPair), sizeof(StuPairs) * 1);
            singleStuPairsLength = inF.tellg();
            totalPairs = fileLength / singleStuPairsLength;
            inF.close();
            printf("\"Please input a number in the range [20, %d]:\n", totalPairs / 2);
            //cout << "Please input a number in the range [20, 390]:" << endl;
            cin >> memorySize;
            printf("Number of initial runs = number of pairs / buffer size = %d / %d = %d\n", totalPairs, memorySize, totalPairs / memorySize);
        }
        
        /*
			core program start from here
		*/

        outputFilename = outputFileHead + "1.dat";	// generate first file     
        MergeSort(stuPairStructArray, 0, memorySize - 1); // merge sort array by weight
        OutPutBinaryFile(stuPairStructArray, memorySize, outputFilename);	// 
        filenameVector.push_back(outputFilename);
        free(stuPairStructArray);

		
        for(fileSerialNumber = 2; readPosition != -2; fileSerialNumber++)
        {
            stuPairStructArray = (StuPairs*)calloc(memorySize, sizeof(StuPairs));
            readPosition = ReadBinaryFile(stuPairStructArray, filenameHead + filename + filenameEnd, memorySize, readPosition);
           // QuickSort(stuPairStructArray, 0, memorySize - 1);
            
            MergeSort(stuPairStructArray, 0, memorySize - 1);
            
            outputFilename = outputFileHead + to_string(fileSerialNumber) + filenameEnd;
            OutPutBinaryFile(stuPairStructArray, memorySize, outputFilename);
            filenameVector.push_back(outputFilename);
            free(stuPairStructArray);
            //printf("return out\n");
        }
		finishTime = clock();
        filesNumber = fileSerialNumber;

		
        internalSortTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
        //printf( "%lf seconds\n", duration );

        startTime = clock();
        
        printf("%d\n", filenameVector.size());
        system("pause");
        if(filenameVector.size() % 2 != 0)
        {
        	oddFlag = true;
        	oddLastFileName = filenameVector.at(filenameVector.size() - 1 );
        	filenameVector.pop_back();
		}
		
	//	system("pause");
        
        while(filenameVector.size() > 1)
        {
            //ExternalSort(filenameVector.at(0), filenameVector.at(1), (outputFileHead + to_string(fileSerialNumber) + filenameEnd) );
            DeepExternalSort(filenameVector.at(0), filenameVector.at(1), (outputFileHead + to_string(fileSerialNumber) + filenameEnd), memorySize);
            //DeepExternalSort(filenameVector.at(1), filenameVector.at(0), (outputFileHead + to_string(fileSerialNumber) + filenameEnd), memorySize);
            filenameVector.push_back(outputFileHead + to_string(fileSerialNumber) + filenameEnd);
            fileSerialNumber++;
            remove(filenameVector.at(0).c_str());
            remove(filenameVector.at(1).c_str());
            vector<string>::iterator iter = filenameVector.begin();
            filenameVector.erase(iter);
            iter = filenameVector.begin();
            filenameVector.erase(iter);
        }
        
        if(oddFlag)
        {
        	DeepExternalSort(filenameVector.at(0), oddLastFileName, (outputFileHead + to_string(fileSerialNumber) + filenameEnd), memorySize);
        //	DeepExternalSort(oddLastFileName, filenameVector.at(0), (outputFileHead + to_string(fileSerialNumber) + filenameEnd), memorySize);
        	remove(filenameVector.at(0).c_str());
        	remove(oddLastFileName.c_str());
        	filenameVector.pop_back();
        	filenameVector.push_back(outputFileHead + to_string(fileSerialNumber) + filenameEnd);
		}
		
        finishTime = clock();
        externalSortTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC;
        printf("\n\nThe execution time ...\n");
        printf("Internal Sort = %lf\n", internalSortTime);
        printf("External Sort = %lf\n", externalSortTime);
        printf("Total Execution Time = %lf\n", internalSortTime + externalSortTime);

        cout << endl << endl << "##############################################################" << endl;
        cout << "Mission 2: Threshold search on Primary Index" << endl;
        cout << "##############################################################" << endl << endl;
        /**/
  //  	cout <<     filenameVector.at(0) << endl;
  		cout << filenameVector.at(0);
		print_head(filenameVector.at(0));
		cout << filenameVector.at(0);
  	 	play(filenameVector.at(0));
		
        
        readPosition = -1;
        /*
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
           printf( "%lf seconds\n", duration );
         */
        cin.clear();
        free(stuPairStructArray);
        filenameVector.clear();
        cout << "[0]Quit or [Any other key]continue?" << endl;
        scanf("%d", &continueFlag);

        if(continueFlag == 0)
        {
            return 0;
        }else{
            cout << "Input the file name (e.g., 801, 802, 803): [0]Quit" << endl;
            cin >> filename ;
        }

    }

    //print_head();

    return 0;
}
