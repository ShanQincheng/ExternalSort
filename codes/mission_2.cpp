# include "headFile.h"

void print_head(string fileName) {
	//string fileName = "outout29.dat";
    fstream     inFile, outfile;                                           
	StuPairs oneSt;                                            		
    int         stNo = 0;
    float num = -1;
	int count = 0, number = 0;
    
inFile.open(fileName.c_str(), fstream::in | fstream::binary);
	fileName = "headData.txt";
	outfile.open( fileName.c_str(), fstream::out );
    if (!inFile.is_open()) {   
	    cout << endl << fileName << " does not exist!!!" << endl;
        return;
    }
    inFile.seekg (0, inFile.end);
    stNo = inFile.tellg() / sizeof(stuPairs);			               
    inFile.seekg (0, inFile.beg);
    for (int i = 0; i < stNo; i++) { 
	    inFile.read((char *)&oneSt, sizeof(oneSt));
	    number++;                  
 		if ( num < oneSt.weight ) {
 			num = oneSt.weight;
 			count++;
 			outfile << num << "  " << inFile.tellg() - sizeof(stuPairs) << endl ;
 			cout << "[ " << number << " ] " << num  << endl;//<< " " << number << endl;
		}                                  
	}   //end for
    inFile.close();
	outfile.close();
}

int find_site( float command ) {
	fstream infile;
	string filename = "headData.txt";
	infile.open(filename.c_str(), fstream::in);
	float value;
	int ans;
	while( true ) {
		infile >> value;
		infile >> ans;
		if ( value == command ) {
			infile.close();
			return ans;
		}
	}
	return -1;
}

void play(string fileName) {
	fstream infile, outfile;
	clock_t c0, c1;
	stuPairs oneSt;
	int count = 0, num = 0;
	int         stNo = 0;
	double time;
    string filename = "time.txt";
	outfile.open( filename.c_str(), fstream::out);
	float command ;
//	fileName = "outout29.dat";
	string order;
	cout << "Pleas input a number in the range 0~1 or input -1 to quit" << endl;
	cin >> command;
	while ( command != -1 ) {
		c0 = clock();
		if ( command <=1 && command >=0 ) {
			num++;
			infile.open(fileName.c_str(), fstream::in | fstream::binary);
			infile.seekg (0, infile.end);
    		stNo = ( infile.tellg() - find_site(command) ) / sizeof(stuPairs);			               
			infile.seekg (find_site(command), infile.beg);
			//infile.seekg (0, infile.end);
			for ( int i = 0 ; i < stNo ; i++ ) {
				//infile.seekg (0, infile.beg);
				count++;
				infile.read((char *)&oneSt, sizeof(oneSt));
				//infile.read((char *)&oneSt, sizeof(oneSt));
				cout << "[ " << count << " ]  " << oneSt.sid_one << "  " << oneSt.sid_two << "  " << oneSt.weight << endl;
			}
			c1 = clock();
		    time = c1 - c0;
            outfile << "value " << command << " Quantity " << count << " time " << time << endl;
 	    }
		else cout << "error input , please try again";
		count = 0;
		cout << "Pleas input a number in the range 0~1 or input -1 to quit" << endl;
		cin >> command;
		infile.close();
	}
	outfile.close();


	
}


