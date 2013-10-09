//
//  training.h
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#ifndef ____training__
#define ____training__

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Training {
public:
    Training();
    Training(string, int); // paramater file: string, maxIteration: int
    Training(Training&);
    Training& operator=(Training&);
    ~Training();
    
    vector<string> getAttributeValues(string); //menampilkan value2 atribut tertentu
    void setAttributeValues(string, vector<string>);
    string getTargetAttribute();
    string getDataValue(int, string); // index ke berapa, atribut apa
    int getDataValueConverted(int, string);
    vector< map<string, string> > getDataVector();
    
    string getAttribute(int); //
    int getNumberAttribute();
    int getNumberData();
    bool isAll1();
    bool isAll0();
    
    void deleteAttribute(string);
    void deleteInstance(int);
    
    int getMaxIteration();
    
private:
    map<string, vector<string> > attribute;
    vector<string> attributeIndex;
    string targetAttribute;
    vector< map<string, string> > data;
    int maxIteration;
    map<string, int> convertValues;
    
    void extractData(string);
    void extractAttribute(string);
    void convert(); //convert values dari attribute menjadi int
};

#endif /* defined(____training__) */
