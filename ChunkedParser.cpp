#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
    int pos;
    unsigned long int iSize = 0;

    if (argc != 2) {
        cout << "Usage: ./a.out filename" << endl;
        return 1;
    }

    ifstream inputFile (argv[1]);
    // inputFile.open(argv[1],ios::in);

    if (inputFile.is_open()) {
        cout << "File openned successfully!" << endl;
		// inputFile.close(); 
	}
	else {
		cout << "File not opened successfully! Please try again!" << endl;
        return 1;
	}

    string inputLine, sChunkSize, outputLine;
    getline (inputFile, inputLine);

    cout << "Line Read from file is: \n" << inputLine << endl;

    pos = inputLine.find_first_of("\\r\\n");
    if (pos != string::npos) {
        inputLine = inputLine.substr (pos + 4);
    }
    else {
        cout << "Expected delimiters not found!" << endl;
        return 1;
    }

    cout << "New Line output: \n" << inputLine << endl;

    do {

        sChunkSize = inputLine.substr(4 , inputLine.find_first_of("\\r\\n", 4) - 4);
        cout << "ChunkSize in hex value: " << sChunkSize << endl;
        iSize = strtoul (sChunkSize.c_str(), NULL, 16);
        cout << "ChunkSize in integer value: " << iSize << endl;
        outputLine += inputLine.substr(sChunkSize.length() + 8, iSize);
        inputLine = inputLine.substr(iSize + sChunkSize.length() + 8);
        cout << "Input line: " << inputLine << endl;

        cout << "Output line: " << outputLine << endl;
    } while (iSize);



    inputFile.close(); 
    return 0;

}