//
//  training.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"

Training::Training() {
    
}

Training::Training(string file) {
    targetAttribute = "robot";
    extractAttribute();
    extractFile(file);
}

Training::Training(Training& tr) {
    targetAttribute = tr.targetAttribute;
    for (map<string, vector<string> >::const_iterator it=tr.attribute.begin(); it!=tr.attribute.end(); it++) {
        for (int i=0; i<it->second.size(); i++) {
            attribute[it->first].push_back(it->second[i]);
        }
    }
    for (int j=0; j<tr.getNumberData(); j++) {
        map<string, string> content;
        for (map<string, vector<string> >::const_iterator it=attribute.begin(); it!=attribute.end(); it++) {
                content[it->first] = (tr.data)[j][it->first];            
        }
        content[targetAttribute] = (tr.data)[j][targetAttribute];
        data.push_back(content);
    }
    for (int i=0; i<tr.getNumberAttribute(); i++) {
        attributeIndex.push_back(tr.getAttribute(i));
    }
}

Training::~Training() {
    
}

void Training::extractFile(string file) {
    //initiate data
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            getline(readFile, strLine);
            char * token;
            char * cstr = new char[strLine.length()+1];
            strcpy(cstr, strLine.c_str());
            token = strtok(cstr, " ");
            int x = 0;
            map<string, string> content;
            while (token!=NULL && x<7) {
                string tokenStr(token);
                if (x==0) {
                    content[targetAttribute] = tokenStr;
                } else {
                    content[getAttribute(x-1)] = tokenStr;
                }
                token = strtok(NULL, " ");
                x++;
            }
            data.push_back(content);
        }
    }
}

void Training::extractAttribute() {
    attribute["head"].push_back("1");
    attribute["head"].push_back("2");
    attribute["head"].push_back("3");
    attribute["body"].push_back("1");
    attribute["body"].push_back("2");
    attribute["body"].push_back("3");
    attribute["smile"].push_back("1");
    attribute["smile"].push_back("2");
    attribute["hold"].push_back("1");
    attribute["hold"].push_back("2");
    attribute["hold"].push_back("3");
    attribute["jacket"].push_back("1");
    attribute["jacket"].push_back("2");
    attribute["jacket"].push_back("3");
    attribute["jacket"].push_back("4");
    attribute["tie"].push_back("1");
    attribute["tie"].push_back("2");
    
    attributeIndex.push_back("head");
    attributeIndex.push_back("body");
    attributeIndex.push_back("smile");
    attributeIndex.push_back("hold");
    attributeIndex.push_back("jacket");
    attributeIndex.push_back("tie");
}

vector<string> Training::getAttributeValues(string attr){
    return attribute[attr];
}

string Training::getTargetAttribute() {
    return targetAttribute;
}

string Training::getDataValue(int i, string attr) {
    if (i<getNumberData()) {
        return data[i][attr];
    }
}

vector< map<string, string> > Training::getDataVector() {
    return data;
}

string Training::getAttribute(int index) {  
    return attributeIndex[index];
}

int Training::getNumberAttribute() {
    return attributeIndex.size();
}

int Training::getNumberData() {
    return data.size();
}

bool Training::isAll1() {
    for (int i=0; i<getNumberData(); i++) {
        if (getDataValue(i, getTargetAttribute())=="0") {
            return false;
        }
    }
    return true;
}

bool Training::isAll0() {
    for (int i=0; i<getNumberData(); i++) {
        if (getDataValue(i, getTargetAttribute())=="1") {
            return false;
        }
    }
    return true;
}

void Training::deleteAttribute(string attr) {
    attribute.erase(attr);
    int found = 0;
    while (attributeIndex[found]!=attr) {
        found++;
    }
    attributeIndex.erase(attributeIndex.begin()+found);
}

void Training::deleteInstance(int index) {
    data.erase(data.begin()+index);
}






