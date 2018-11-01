/*
* FILENAME : 
*       RotateLeft.cpp  
*
* DESCRIPTION :
*       Reads parameters from a supplied file and prints the left rotation of an array to the console
*
* 
* AUTHOR :    
*       Daniel Caplan 2018-11-1
*
*
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void printUsage(const char*);

int main(int argc, char *argv[])
{
    std::ifstream inputFile;
    std::string line;
    std::vector<unsigned int> uintArray;
    std::vector<unsigned int>::iterator it;
    unsigned int numIntegers = 0, numRotations = 0, value = 0, index = 0;
    
    if(argc < 2)
    {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string inputArg(argv[1]);
    
    //Display file format in response to help arg
    if((inputArg.compare("-h") == 0) || ((inputArg.compare("--help") == 0)))
    {
        std::cerr << argv[0] << " rotates an array of integers to the left"         << std::endl
                  << "<input file> format is a text file with the following format" << std::endl
                  << "\t(Line 1) <Number of Integers> <Number of Left Rotations>"   << std::endl
                  << "\t(Line 2) <Initial Integer Array Delimited by Spaces>" 
                  << std::endl;
                  
       return 0;
    }
        
    //Try and open file
    inputFile.open(inputArg.c_str());
    
    if(inputFile.is_open())
    {
        //First get num integers and num rotations
        getline(inputFile, line);
        
        std::stringstream ss(line);
        ss >> numIntegers >> numRotations;
        
        uintArray.resize(numIntegers, 0);
        
        //Read in line of integers
        
        getline(inputFile, line);
        
        ss.clear();
        ss.str(std::string());
        ss.str(line);
        
        while((ss >> value) && (index < numIntegers))
        {
            uintArray[index] = value;
            ++index;
        }
        
        inputFile.close();
        
        if(index != numIntegers)
        {
            std::cout << "Warning: " << index << " values found when " << numIntegers << " were indicated in file" << std::endl << std::endl;
        }
        
        numRotations = (numRotations % numIntegers); //TO prevent repeating rotations
        
        for(it = uintArray.begin() + numRotations; it != uintArray.end(); ++it)
        {
            std::cout << *it << " ";
        }
        
        //If we didn't just print out the original array, go back to beginning and start from there
        if(numRotations > 0)
        {
            for(it = uintArray.begin(); it != (uintArray.begin() + numRotations); ++it)
            {
                std::cout << *it << " ";
            }
            
        }
        
        std::cout << std::endl;
        
    }
    else
    {
        std::cerr << "Can't open file " << inputArg << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    
    return 0;
}

void printUsage(const char* name)
{
    std::cerr << "Usage: " << name << " <input file> OR -h,--help" << std::endl;
}