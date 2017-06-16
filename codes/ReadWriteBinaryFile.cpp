//
// Created by 入山 on 6/6/2017.
//
# include "headFile.h"

int ReadBinaryFile(StuPairs* stuPairStructArray, string inputFileName, int memorySize, int readPosition)
{
    int i = 0; // vector size
    //StuPairs* stuPairStructArray = NULL;
    ifstream inF;
    int fileLength = -1;

    //stuPairStructArray = (StuPairs*)calloc(memorySize, sizeof(StuPairs));
    inF.open(inputFileName, std::ifstream::binary);
    if(!inF)
    {
        return -1;
    }else{
        inF.seekg(0, inF.end);
        fileLength = inF.tellg();
    //    printf("INF END == %d\n", fileLength);
     //   printf("current position == %d\n", readPosition);
        if(readPosition == -1)
        {
            inF.seekg(0, inF.beg);

        }/*else if(readPosition == fileLength){
            readPosition = -2;
            return  readPosition; // the file has all been read
        }*/else{
            inF.seekg(readPosition);
        }

        inF.read(reinterpret_cast<char*>(stuPairStructArray), sizeof(StuPairs) * memorySize);

        if(inF.tellg() >= fileLength || readPosition >= inF.tellg())
        {
            //readPosition = fileLength;
            readPosition = -2;
            for(i = memorySize - 1; i >= 0; i-- )
            {
                if(stuPairStructArray[i].weight <= 0.0 || stuPairStructArray[i].weight > 1.0)
                    stuPairStructArray[i].weight = FLT_MAX;
                else
                    break;
            }
        }else{
            readPosition = inF.tellg();
        }
   //     printf("current position == %d\n", inF.tellg());
/*
        for(i = 0; i < memorySize; i++)
        {
            printf("sid1 == %s, sid2 == %s, weight == %f\n", stuPairStructArray[i].sid_one, stuPairStructArray[i].sid_two, stuPairStructArray[i].weight);
        }
        */
        inF.close();

        return readPosition;
    }
}

bool OutPutBinaryFile(StuPairs* elementArray, int arraySize, string outPutFileName)
{
    int i =0;
    /*
    for(i = 0; i < arraySize; i++)
    {
        printf("sid1 == %s, sid2 == %s, weight == %f\n", elementArray[i].sid_one, elementArray[i].sid_two, elementArray[i].weight);
    }
    */

    int len = 0; // vector size
    ofstream fout;
    fout.open(outPutFileName, ios::binary);

    if(elementArray)
    {
        //	wFp = fopen(outPutFileName.c_str(), "w+");
        for(int i = 0; i < arraySize; i++)
        {
            //	fwrite(&stuInfoVector[i], sizeof(StuInfo), 1, wFp);
            if(elementArray[i].weight == FLT_MAX)
                break;
            fout.write((char *)(&elementArray[i]), sizeof(StuPairs));
        }
//		fclose(wFp);

    //    cout << "~~ A binary file has been created! ~~" << endl;

        return true;
    }else{
        return false;
    }
}