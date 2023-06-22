#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

/* function to convert a character into its digit; 'A' converts into 10; 'B' into 11, etc.
*/
unsigned int hexa_to_number(char ch) {
    unsigned int temp = 0;
    // TODO: implement this function
  int a = 1;
  if (ch >= '0' && ch <= '9') {
            temp += (int(ch) - 48) * a;
             a = a * 16;
        }
        else if (ch >= 'A' && ch <= 'F') {
            temp += (int(ch) - 55) * a;
             a = a * 16;
        }    
  return temp;
}

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int nic) {
  // TODO: implement this function, then delete the return statement below
    unsigned int a;
    a = nic / 100000;
    return a; 
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
    unsigned int a;
    a = nic / 10000;
    a = a % 10;
    return a;    
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
    unsigned int a;
    a = nic / 1000;
    a = a % 10;
    return a; 
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
    unsigned int a;
    a = nic / 100;
    a = a % 10;
    return a;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below
    unsigned int a;
    a = nic/ 10;
    a = a % 10;
    return a;
}

// function to return the hash value based on the sixth digit
unsigned int hashfct6(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below
    unsigned int a;
    a = nic % 10;
    return a;
}

// Constructor for struct Item
Item::Item(string itemName, string nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    string nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

// function that adds the specified NIC to the sensor network (i.e., to all hash tables)
void SensorNIC::addItem(string itemName, string nic) {
  // TO DO: implement this function, then delete the return statement below
  Item r;
  r.nic_ = nic;
  r.itemName_ = itemName;  
    hT1.insert({ nic ,r });
    hT2.insert({ nic ,r });
    hT3.insert({ nic ,r });
    hT4.insert({ nic ,r });
    hT5.insert({ nic ,r });
    hT6.insert({ nic ,r });
}

// function that removes the sensor specified by the nic value from the network
// if sensor is found, then it is removed and the function returns true
// else returns false
bool SensorNIC::removeItem(string nic) {
   // TODO: implement this function, then delete the return statement below   
    hT1.erase(nic);
    hT2.erase(nic);
    hT3.erase(nic);
    hT4.erase(nic);
    hT5.erase(nic);
    hT6.erase(nic);
    return true;
}

// function that decides the best hash function, i.e. the ones among
// fct1-fct6 that creates the most balanced sensor network for the current
// set of NIC addresses, i.e. data member allItems

// Hints:
// Calculate the balance of each hashtable, one by one.
unsigned int SensorNIC::bestHashing() {
  // TODO: implement this function, then delete the return statement below
    unsigned int balance[6];
    unsigned int min_loc;

    int min = hT1.bucket_size(1), max = hT1.bucket_size(1);
    for (unsigned i = 0; i < 10; ++i)
    {
        if (hT1.bucket_size(i) <= min)
            min = hT1.bucket_size(i);
        if (hT1.bucket_size(i) >= max)
            max = hT1.bucket_size(i);
    }
    balance[0] = max - min;
    min = hT2.bucket_size(1), max = hT2.bucket_size(1);
    for (unsigned i = 0; i < 10; ++i)
    {
        if (hT2.bucket_size(i) <= min)
            min = hT2.bucket_size(i);
        if (hT2.bucket_size(i) >= max)
            max = hT2.bucket_size(i);
    }
    balance[1] = max - min;
    min = hT3.bucket_size(1), max = hT3.bucket_size(1);
    for (unsigned i = 0; i < 10; ++i)
    {
        if (hT3.bucket_size(i) <= min)
            min = hT3.bucket_size(i);
        if (hT3.bucket_size(i) >= max)
            max = hT3.bucket_size(i);
    }
    balance[2] = max - min;
    min = hT4.bucket_size(1), max = hT4.bucket_size(1);
    for (unsigned i = 0; i < 10; ++i)
    {
        if (hT4.bucket_size(i) <= min)
            min = hT4.bucket_size(i);
        if (hT4.bucket_size(i) > max)
            max = hT4.bucket_size(i);
    }
    balance[3] = max - min;
    min = hT5.bucket_size(1), max = hT5.bucket_size(1);
    for (unsigned i = 0; i < 10; ++i)
    {
        if (hT5.bucket_size(i) <= min)
            min = hT5.bucket_size(i);
        if (hT5.bucket_size(i) >= max)
            max = hT5.bucket_size(i);
    }
    balance[4] = max - min;
    min = hT6.bucket_size(1), max = hT6.bucket_size(1);
    for (unsigned i = 0; i < 10; ++i)
    {
        if (hT6.bucket_size(i) <= min)
            min = hT6.bucket_size(i);
        if (hT6.bucket_size(i) >= max)
            max = hT6.bucket_size(i);
        // Call bucket_size() to get the size of each bucket
    }
    balance[5] = max - min;
    min_loc = balance[0];
    int a;
    for (int i = 0; i < 6; i++)
    {
        if (balance[i] <= min_loc)
            min_loc = balance[i];

    }
    for (int i = 0; i < 6; i++)
    {
        if (balance[i] == min_loc)
            return i + 1;

    }
return true;
}


// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
