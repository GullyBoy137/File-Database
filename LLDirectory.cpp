//SUBMIT this file
//complete all the missing LLDirectory implementations here
//remember to put in dummy/empty implentation of all functions here even if you cannot finish them
//it is very important for you to make sure your submitted code can be compiled with the unmodified version of the header files and main.cpp

#include "LLDirectory.h"
LLDirectory :: LLDirectory(string name, FSObject* parent): Directory(name,parent){
    head = NULL;
    
}

LLDirectory :: ~LLDirectory(){


	LLNode*current = head;
    LLNode*prev = nullptr;
    //delete head;
   // head = NULL;
    while(current!=nullptr){
        prev = current;
        current = current->next;
        delete prev->data;
        delete prev;
    }
   // delete head;
    current = nullptr;
    prev = nullptr;
}

bool LLDirectory :: addChild(bool isDir, string name){
    for( LLNode*p = head; p!=NULL; p=p->next){
        if((p->data)->getName()== name)
            return false;
    }
    if(isDir == true){
        LLNode* newDirectory = new LLNode;
        newDirectory->data = new LLDirectory(name, this);
        newDirectory->next = NULL;
        
        if(head == NULL){
            newDirectory->next = NULL;
            head = newDirectory;
            return true;
        }
            
        for(LLNode* insert = head; insert!=NULL; insert = insert->next){
            if(insert->next == NULL){
                insert->next = newDirectory;
                newDirectory->next = NULL;
             	return true; 
            }
            if(((insert->data)->getName()<name) && (((insert->next)->data)->getName()>name)){
                newDirectory->next = insert->next;
                insert->next =  newDirectory;
		return true;
            }
                
        }
        
    }
    else if(isDir == false){
        LLNode*newFile = new LLNode;
        File* tempFile = new File(name, this);
        tempFile->setContent("");
        newFile->data = tempFile;
        newFile->next = NULL;
       // delete tempFile;
       // tempFile = NULL;
        
        if(head == NULL){
            newFile->next = NULL;
            head = newFile;
            return true;
        }
        
        for(LLNode* insert = head; insert!=NULL; insert = insert->next){
            if(insert->next == NULL){
                insert->next = newFile;
                newFile->next = NULL;
                return true; 
            }
            if(((insert->data)->getName()<name) && (((insert->next)->data)->getName()>name)){
		newFile->next = insert->next;
                insert->next =  newFile;
		return true;
	    }
            
        }
    }
    return true;
    
}

bool LLDirectory :: removeChild(string name){
    LLNode*prev = NULL;
    LLNode*current = head;
    
    while ((current != nullptr) && ((current->data)->getName()!=name))
    {
        prev = current;
        current = current->next;
    }
    
    if(current == NULL)
        return false;
    else{
        if(current == head)
            head = head->next;
        else
            prev->next = current->next;
        delete current;
        return true;
    }
      //??Does anything else need to be done to avoid memory leak?
}

FSObject* LLDirectory :: getChild(string name){
    for(LLNode*p = head; p!=NULL; p=p->next){
        if((p->data)->getName() == name)
            return p->data;
    }
    return NULL;
}

FSObject* LLDirectory :: getChild(int i){
    int length = 0;
    for (const LLNode* s = head; s != nullptr; s = s->next)
        ++length;
    if(i>length-1)
        return NULL;
    
    int j = 0;
    LLNode*p = head;
    while( p!=NULL && j!=i){
        ++j;
        p=p->next;
    }
    return p->data;
}

string LLDirectory :: list(){
	/*string SAname = "";
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
	    return SAname;*/

   /* if(head == NULL)
        return "<empty>";
    else{
    string LList = "";
    for( int i=0; i<getCount(); i++){
    	if(typeid(getChild(i)) == typeid(LLDirectory))
    		LList =LList + "[" + (getChild(i))->getName() + "]" + " ";
       // LList = (s->data)->getName() + LList;
    	if(typeid(getChild(i)) == typeid(File))
    	 LList =  LList + (getChild(i))->getName() + " ";
      }
    LList.pop_back();
    return LList;
    }
   return "";*/
	if(head == NULL)
	        return "<empty>";
	LLNode* curr = head;
	string LList = "";


	  while(curr!= NULL){

		  if(typeid(*(curr->data)) == typeid(LLDirectory))
			  LList+= "[" + curr->data->getName() + "]" + " ";
		  else
			 // if (typeid(*(curr->data)) == typeid(File))
			  LList+=(curr->data)->getName() + " ";

		  curr = curr->next;
	  }
	  LList.pop_back();
	  return LList;
}

int LLDirectory :: getCount(){
    int length = 0;
    for (const LLNode* s = head; s != nullptr; s = s->next)
        ++length;
    return length;
}
