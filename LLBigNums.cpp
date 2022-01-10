/**
 * @file LLBigNums.cpp
 * @author Samuel Bazinet (bazinet.samuel1@gmail.com)
 * @brief This program is meant to represent big numbers in c++
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include"LLBigNum.h"

/**
 * @brief add is a function to add numbers to a slice and format the slice to remain under 1000
 * 
 * @param slice slice is the NumSlice to which a number will be added
 * @param number number is the number to be added to the slice 
 */
void add(NumSlice* slice, int number) {

    // we add the number to the value of the slice
    slice->value += number;

    // if the value is greater than or equal to 1000, we correct it and add the remainder to the next slice
    if (slice->value >= 1000) {

        // we adjust the value of the slice and store the modified difference
        int toAdd = slice->value/1000;
        slice->value -= toAdd*1000;

        // a new slice is created if needed
        if (nullptr == slice->next) {

            NumSlice *newSlice = new NumSlice;
            newSlice->prev = slice;
            newSlice->value = 0;
            newSlice->next = nullptr;
            slice->next = newSlice;

        }

        // we recursively call add to apply the remainder to the next slice
        add(slice->next, toAdd);
        
    }

}

/**
 * @brief multiply multiplies the value of a slice by a number
 * 
 * @param slice slice is the NumSlice which will be multiplied
 * @param number number is the number that will multiply the slice
 */
void multiply(NumSlice* slice, int number) {


    // we multiply the value of the slice
    slice->value *= number;

    // if there is a next node, the multiply function is called to multiply it
    if (nullptr != slice->next) {
        multiply(slice->next, number);
    }

    // if the multiplied value is greater than or equal to 1000
    // we adjust the value of the slice (see add for details)
    if (slice->value >= 1000) {

        int toAdd = slice->value/1000;
        slice->value -= toAdd*1000;

        if (nullptr == slice->next) {

            NumSlice *newSlice = new NumSlice;
            newSlice->prev = slice;
            newSlice->value = 0;
            newSlice->next = nullptr;
            slice->next = newSlice;

        }

        add(slice->next, toAdd);
        
    }
    
}

/**
 * @brief deepCopy deep copies a NumSlice 
 * 
 * @param thisSlice the target of the copy
 * @param otherSlice the NumSlice to be copied
 */
void deepCopy(NumSlice* thisSlice, NumSlice* otherSlice) {

    // copy the value of the base Slice
    thisSlice->value = otherSlice->value;

    // set temporary pointers to interate through the slices
    NumSlice* temp1 = thisSlice;
    NumSlice* temp2 = otherSlice;

    // copy the next slices
    while (nullptr != temp2->next) {

        temp2 = temp2->next;

        // make new slices if necessary
        if (nullptr == temp1->next) {

            NumSlice* newSlice = new NumSlice;

            newSlice->prev = temp1;
            newSlice->next = nullptr;
            temp1->next = newSlice;

        }

        temp1 = temp1->next;

        temp1->value = temp2->value;

    }
    
    // delete the extra slices
    if (nullptr != temp1->next) {

        temp1 = temp1->next;

        while (nullptr != temp1->next) {

            temp1 = temp1->next;
            delete temp1->prev;

        }

        delete temp1;

    }

    // reset the pointers
    temp1 = thisSlice;
    temp2 = otherSlice;

    // copy the previous slices
    while (nullptr != temp2->prev) {

        temp2 = temp2->prev;

        // create new slices if necessary
        if (nullptr == temp1->prev) {

            NumSlice* newSlice = new NumSlice;

            newSlice->next = temp1;
            newSlice->prev = nullptr;
            temp1->prev = newSlice;

        }

        temp1 = temp1->prev;

        temp1->value = temp1->value;

    }

    // delete extra slices
    if (nullptr != temp1->prev) {

        temp1 = temp1->prev;

        while (nullptr != temp1->prev) {

            temp1 = temp1->prev;
            delete temp1->next;

        }

        delete temp1;

    }
    
}

/**
 * @brief Construct a new Big Num:: Big Num object
 */
BigNum::BigNum() {

    // everything is initialized to null or 0
    base = new NumSlice;
    base->next = nullptr;
    base->prev = nullptr;
    base->value = 0;

}

/**
 * @brief Construct a new Big Num:: Big Num object from an integer
 * 
 * @param num integer to be converted into a BigNum
 */
BigNum::BigNum(int num) {

    // the pointers are set to null
    base = new NumSlice;
    base->prev = nullptr;
    base->next = nullptr;
    // the value of the int is assigned to the value fo the slice
    base->value = num;

    // if the value of the slice is greater than or equal to 1000, it gets ajusted
    if (base->value >= 1000) {

        // the adjusted remainder is stored
        int toAdd = base->value/1000;
        // the slice value is ajusted
        base->value -= toAdd*1000;

        // a new slice is created to take in the remainder
        NumSlice *newSlice = new NumSlice;
        newSlice->prev = base;
        newSlice->value = 0;
        newSlice->next = nullptr;

        // the new slice is appended to the list of slices
        base->next = newSlice;
        // the remainder is added to the new slice using the add function
        add(newSlice, toAdd);

    }

}

/**
 * @brief Construct a new Big Num:: Big Num object from a NumSlice
 * 
 * @param ns ns is a pointer to a NumSlice which will be copied into a BigNum
 */
BigNum::BigNum(NumSlice *ns) {

    // the base slice is initialized
    base = new NumSlice;
    base->prev = nullptr;
    base->next = nullptr;
    // the value from the slice is copied into the base NumSlice's
    base->value = ns->value;

    // temporary pointers are made to copy the rest of the linked structure into the new BigNum
    NumSlice *temp1 = base;
    NumSlice *temp2 = ns;

    // any previous value is added
    while (nullptr != temp2->prev) {

        temp1->prev = new NumSlice;

        temp1->prev->next = temp1;
        temp1 = temp1->prev;
        temp2 = temp2->prev;
        temp1->value = temp2->value;

    }

    // the last element points to a nullptr    
    temp1->prev = nullptr;
    // the temporary pointers are reset
    temp1 = base;
    temp2 = ns;

    // any next value is added
    while(nullptr != temp2->next) {

        temp1->next = new NumSlice;

        temp1->next->prev = temp1;
        temp1 = temp1->next;
        temp2 = temp2->next;
        temp1->value = temp2->value;

    }

    // the last element points to a nullptr
    temp1->next = nullptr;

}

/**
 * @brief Construct a new Big Num:: Big Num object from a BigNum pointer
 * 
 * @param bn is a pointer to a BigNum to be deep copied
 */
BigNum::BigNum(const BigNum* bn) {

    // a pointer is made to point to the base NumSlice of the other BigNum
    NumSlice *temp2 = bn->base;

    // base is initialized
    base = new NumSlice;
    base->prev = nullptr;
    base->next = nullptr;

    // the value of the other's base is assigned to this base
    base->value = temp2->value;

    // a temporary pointer pointing to this base
    NumSlice *temp1 = base;

    // copying any previous slices from the other's to this
    while (nullptr != temp2->prev) {

        temp1->prev = new NumSlice;

        temp1->prev->next = temp1;
        temp1 = temp1->prev;
        temp2 = temp2->prev;
        temp1->value = temp2->value;

    }

    // last pointer points to null
    temp1->prev = nullptr;

    // the temporary pointers are reset to the bases
    temp1 = base;
    temp2 = bn->base;

    // copy all the next pointers
    while(nullptr != temp2->next) {

        temp1->next = new NumSlice;

        temp1->next->prev = temp1;
        temp1 = temp1->next;
        temp2 = temp2->next;
        temp1->value = temp2->value;

    }

    // the last is set to nullptr
    temp1->next = nullptr;

}

/**
 * @brief Construct a new Big Num:: Big Num object from a BigNum pass-by-reference
 * 
 * @param bn the BigNum to be deep copied
 */
BigNum::BigNum(const BigNum& bn) {

    // a pointer is made to point to the base NumSlice of the other BigNum
    NumSlice *temp2 = bn.base;

    // base is initialized
    base = new NumSlice;
    base->prev = nullptr;
    base->next = nullptr;

    // the value of the other's base is assigned to this base
    base->value = temp2->value;

    // a temporary pointer pointing to this base
    NumSlice *temp1 = base;

    // copying any previous slices from the other's to this
    while (nullptr != temp2->prev) {

        temp1->prev = new NumSlice;

        temp1->prev->next = temp1;
        temp1 = temp1->prev;
        temp2 = temp2->prev;
        temp1->value = temp2->value;

    }

    // last pointer points to null
    temp1->prev = nullptr;

    // the temporary pointers are reset to the bases
    temp1 = base;
    temp2 = bn.base;

    // copy all the next pointers
    while(nullptr != temp2->next) {

        temp1->next = new NumSlice;

        temp1->next->prev = temp1;
        temp1 = temp1->next;
        temp2 = temp2->next;
        temp1->value = temp2->value;

    }

    // the last is set to nullptr
    temp1->next = nullptr;

}

/**
 * @brief Destroy the Big Num:: Big Num object
 * 
 */
BigNum::~BigNum() {

    // a temporary pointer is pointing to the base
    NumSlice *current = base;
    
    // we traverse to the top of the slice list
    while (nullptr != current->next) {
        current = current->next;
    }

    // we delete the slices
    while (nullptr != current->prev) {

        current = current->prev;
        delete current->next;

    }

    // we delete the remaining slice
    delete current;
}

/**
 * @brief operator+ lets integers be added to BigNums
 * 
 * @param number the number to be added
 * @return BigNum - the BigNum after the addition
 */
BigNum BigNum::operator+(const int number) {
    
    // a new BigNum is made from this
    BigNum returnNum(this);
    
    // we use the add function to perfom the addition
    add(returnNum.base, number);

    // the new BigNum is returned
    return returnNum;
    
}

/**
 * @brief operator+ lets BigNum be added together
 * 
 * @param bn a BigNum to be added to another
 * @return BigNum - The BigNum after the addition
 */
BigNum BigNum::operator+(const BigNum& number) {

    // a new BigNum is created from this
    BigNum returnNum(this);
    // pointers are made for the slice list from both BigNums
    NumSlice *leftSlice = returnNum.base;
    NumSlice *rightSlice = number.base;

    // We iterate through the other's slice lise and add each to the equivalent this slice
    while (nullptr != rightSlice->next) {

        // the values are added
        add(leftSlice, rightSlice->value);

        // if required, a new slice is added to the this slice list
        if (nullptr == leftSlice->next) {

            NumSlice *newSlice = new NumSlice;
            newSlice->prev = leftSlice;
            newSlice->value = 0;
            newSlice->next = nullptr;
            leftSlice->next = newSlice;

        }

        leftSlice = leftSlice->next;
        rightSlice = rightSlice->next;

    }

    // the last values are added
    add(leftSlice, rightSlice->value);

    // the new BigNum is returned
    return returnNum;

}

/**
 * @brief operator += performs an addition and assignment
 * 
 * @param number the number to be added
 */
void BigNum::operator+=(const int number) {
    
    // we use the add function to perfom the addition on this base
    add(this->base, number);

}

/**
 * @brief operator += performs an addition and assignment
 * 
 * @param number the number to be added
 */
void BigNum::operator+=(const BigNum& number) {

    NumSlice *leftSlice = this->base;
    NumSlice *rightSlice = number.base;

    // We iterate through the other's slice lise and add each to the equivalent this slice
    while (nullptr != rightSlice->next) {

        // the values are added
        add(leftSlice, rightSlice->value);

        // if required, a new slice is added to the this slice list
        if (nullptr == leftSlice->next) {

            NumSlice *newSlice = new NumSlice;
            newSlice->prev = leftSlice;
            newSlice->value = 0;
            newSlice->next = nullptr;
            leftSlice->next = newSlice;

        }

        leftSlice = leftSlice->next;
        rightSlice = rightSlice->next;

    }

    // the last values are added
    add(leftSlice, rightSlice->value);

}

/**
 * @brief operator* lets a BigNum be multiplied by an int
 * 
 * @param number the number that will multiply the BigNum
 * @return BigNum - the resulting BigNum
 */
BigNum BigNum::operator *(const int number) {

    // a new BigNum is copied from this
    BigNum returnNum(this);

    // we use the multiply function to perform the multiplication
    multiply(returnNum.base, number);

    // the new BigNum is returned
    return returnNum;

}

/**
 * @brief operator* lets BigNum be multiplied by another BigNum
 * 
 * @param number the BigNum that will multiply the other
 * @return BigNum - the resulting BigNum
 */
BigNum BigNum::operator *(const BigNum& number) {
    
    // multiplyHelper is returned, performing the multiplication
    return this->multiplyHelper(number.base, 0);

}

/**
 * @brief operator*= performs a multiplication and assignment
 * 
 * @param number the number that will multiply the BigNum
 */
void BigNum::operator*=(const int number) {

    // we use the multiply function to perform the multiplication
    multiply(this->base, number);
    
}

/**
 * @brief operator*= performs a multiplication and assignment
 * 
 * @param number the number that will multiply the BigNum
 */
void BigNum::operator*=(const BigNum& number) {

    deepCopy(base, multiplyHelper(number.base, 0).base);

}

/**
 * @brief multiplyHelper facilitates the multiplication of BigNums by recursively adding slices 
 * 
 * @param ns the slice that multiplies the BigNum
 * @param counter the slice in 1000th where the slice is located
 * @return BigNum the resulting BigNum
 */
BigNum BigNum::multiplyHelper(NumSlice* ns, int counter) {

    // a new BigNum is created from this
    BigNum returnNum(this);

    // multiplied is used to multiply the BigNum by the slice
    multiply(returnNum.base, ns->value);


    // slices of 1000s are added to the BigNum compensate for the position of the slice being multiplied
    for (int i = 0; i < counter; i++) {

        NumSlice *newSlice = new NumSlice;
        newSlice->prev = returnNum.base->prev;
        newSlice->next = returnNum.base;
        newSlice->value = 0;
        returnNum.base->prev = newSlice;
        returnNum.base = newSlice;

    }

    // if more slices of the other BigNum exist, they get added to the resulting BigNum
    if (nullptr != ns->next) {
        return returnNum + this->multiplyHelper(ns->next, counter+1);
    } else {
        // the completed BigNum is returned
        return returnNum;
    }

}

/**
 * @brief operator= deep copies BigNums
 * 
 * @param toAss the BigNum to be copied
 */
void BigNum::operator =(const BigNum &toAss) {

    // base is initialized
    base = new NumSlice;

    // the pointers are set to null as default
    base->prev = nullptr;
    base->next = nullptr;

    // the value from toAss gets assigned to this' base
    base->value = toAss.base->value;

    // temporary pointers are created for iterating
    NumSlice *temp1 = base;
    NumSlice *temp2 = toAss.base;

    // the next slices are copied
    while (nullptr != temp2->next) {

        NumSlice *temp3 = new NumSlice;

        temp2 = temp2->next;

        temp3->prev = temp1;
        temp3->value = temp2->value;
        temp3->next = nullptr;

        temp1->next = temp3;
        temp1 = temp1->next;
    }

    // the pointers are reset
    temp1 = base;
    temp2 = toAss.base;

    // the preceding slices are copied
    while (nullptr != temp2->prev) {

        NumSlice *temp3 = new NumSlice;
        
        temp2 = temp2->prev;

        temp3->next = temp1;
        temp3->value = temp2->value;
        temp3->prev = nullptr;

        temp1->prev = temp3;
        temp1 = temp1->prev;

    }

}

/**
 * @brief toString converts a BigNum to a string
 * 
 * @return std::string - the resulting string
 */
std::string BigNum::toString() {

    // a temporary pointer is created
    NumSlice *current = base;
    // the string is initialized
    std::string out = "";

    // we go to the end of the slice list
    while (nullptr != current->next) {
        current = current->next;
    }

    // each slice is formatted to be 3 digits long
    while (nullptr != current) {

        if (current->value < 10)
            out += "00" + std::to_string(current->value) + " ";

        else if (current->value < 100)
            out += "0" + std::to_string(current->value) + " ";

        else 
            out += std::to_string(current->value) + ' ';

        current = current->prev;
    }

    // the string is returned
    return out;

}

/**
 * @brief operator<< lets the BigNum be used by the outstream
 * 
 * @param os the outstream
 * @param number the number to be outputted
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const BigNum& number) {

    // a temporary pointer is pointing to the base slice of a BigNum
    NumSlice *current = number.base;
    // a string is initialized
    std::string out = "";
    
    // we go to the end of the slice list
    while (nullptr != current->next) {
        current = current->next;
    }

    // the output slices are formatted to be 3-digit long
    while (nullptr != current) {

        if (current->value < 10)
            out += "00" + std::to_string(current->value) + " ";

        else if (current->value < 100)
            out += "0" + std::to_string(current->value) + " ";

        else 
            out += std::to_string(current->value) + ' ';

        current = current->prev;

    }

    // the string is outputted
    os << out;
    return os;

}

/**
 * @brief factorial calculates a factorial and returns it as a BigNum
 * 
 * @param n the factorial to be calculated (n!)
 * @return BigNum - the resulting Factorial as a BigNum
 */
BigNum factorial(int n) {

    // a BigNum is created
    BigNum out(1);

    // we loop through every number until we reach n
    for (int i = 1; i <= n; i++) {

        // the BigNum is multiplied by i to calculate the factorial
        out = out*i;

    }

    // we return the BigNum
    return out;

}

int main(int argc, char* argv[]) {
    using namespace std;
    /*
    int fac = 100;
    if (argc == 2) {
        fac = atoi(argv[1]);
    }
    */

    // testing the int constructor
    BigNum test(123456789);
    cout << "Pre changes: " << test << endl;

    // testing the adition by integer
    test = test+2345678;
    cout << "After addition with int(2345678): " << test << endl;

    // testing the adition by BigNum
    test = BigNum(1000000) + test;
    cout << "After addition with BigNum(1000): " << test << endl;

    // testing the multiplication by integer
    test = test*11;
    cout << "After multiplication by int(11): " << test << endl;

    // testing the multiplication by BigNum
    cout << "Multiplying BigNum(1010) by BigNum(5500300): " << BigNum(1010)*BigNum(5500300) << endl;

    // testing the += and *= operators
    BigNum test2(2340);
    test2 += 5;
    test2 *= 10;

    cout << "Adding 5 then multiplying by 10: " << test2 << endl;

    test2 += BigNum(2340);

    cout << "Adding BigNum(2340): " << test2 << endl;

    test2 *= BigNum(1000);

    cout << "Multiplying by BigNum(1000): " << test2 << endl << endl;

    // Testing factorial and multiplication by BigNum
    BigNum ohf = factorial(100);
    BigNum tfac = factorial(20);
    
    cout << "100! = " << ohf << endl;
    cout << "20! = " << tfac << endl;

    cout << "Multiplying 100! by 20! = " << ohf*tfac << endl;

    return 0;
    
}