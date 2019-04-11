;//SUBMIT this file
//complete all the missing SADirectory implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "SADirectory.h"
SADirectory :: SADirectory(string name, FSObject* parent): Directory(name,parent){
    count = 0;
    for(int i = 0; i<DIR_SIZE; ++i)
        children[i] = NULL;
}

SADirectory :: ~SADirectory(){
    for(int i = 0; i<count; ++i){
       // if(children[i] != NULL)
            delete children[i];
    }
}

bool SADirectory :: addChild(bool isDir, string name){
    
    if(count == DIR_SIZE)
        return false;
    for(int i = 0; i<count ; ++i){
        if(children[i]->getName() == name)
            return false;
    }
    if(isDir == true){
        children[count] = new SADirectory(name, this);
        ++count;
        return true;
    }
    else{
        File* tempFile = new File(name, this);
        tempFile->setContent("");
        children[count] = tempFile;
        ++count;
        //delete tempFile;
        tempFile = NULL;
        return true;
    }
   // return true;

}

bool SADirectory :: removeChild(string name){
    for(int i=0; i<count; ++i){
        if(children[i]->getName() == name){
            delete children[i];
            for(int j = i; j<count-1; ++j){
                children[j]=children[j+1];
            }
            --count;
            return true;
        }
    }
    return false;
}

FSObject* SADirectory :: getChild(string name){
    for(int i=0; i<count; ++i){
        if(children[i]->getName() == name){
            return children[i];
        }
    }
    return NULL;//??Do we have to?
}

FSObject* SADirectory :: getChild(int i){
    if(i>DIR_SIZE - 1)
        return NULL;
    else
        return children[i];
}

string SADirectory :: list(){
    string SAname = "";
    if(children[0] == NULL)
        return "<empty>";
    for(int i = 0; i<count; ++i){
    	if(typeid(*(children[i])) == typeid(SADirectory))
        SAname = SAname + "[" + children[i]->getName() + "]" + " ";
    	if(typeid(*(children[i])) == typeid(File))
        SAname =  SAname + children[i]->getName()
		+ " ";
    }
    SAname.pop_back();
    return SAname;

}

int SADirectory :: getCount(){ return count;}
