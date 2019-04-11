template <typename T>

System<T> :: System(){

  root = new T("\\", NULL);

}


template <typename T>

System<T> :: ~System(){

    delete root;

}


template <typename T>

bool System<T> :: isValidPath(string path){



string subpath = "";

subpath = path.substr(0,1);

if(((subpath.length()) >= 1) &&  (subpath[0] == '\\'))

  return true;

else

  return false;

}


template <typename T>

Directory* System<T> :: getRoot(){ return root;}


template <typename T>

Directory* System<T> :: getDirectory(string path){

	 {

	              Directory* retDir = NULL;
	              Directory* iterate = root;
	              string str;
				  string tempath = path;

	              if(isValidPath(path) == false){return NULL;}

	              if(path == "\\"){return iterate;}

	              while(tempath.length()>0){

	                           tempath = tempath.substr(1,tempath.length()-1);

	                           int num = tempath.find("\\");

	                           if(num == -1){
	                           str = tempath;
	                           FSObject* tempoint = iterate->getChild(str);
	                           if(tempoint == nullptr)
	                        	   return NULL;
	                           retDir = dynamic_cast<Directory*>(tempoint);

	                            return retDir;

	                           }

	                           str = tempath.substr(0,num);

	                           FSObject* temp = iterate->getChild(str);
                               if(temp == nullptr)
                               return NULL;
	                           retDir = dynamic_cast<Directory*>(temp);

	                           iterate = retDir;

	                           tempath = tempath.erase(0,num);

	              }

	return retDir;

	}
      /* if(isValidPath(path) == false)
           return NULL;
       Directory* iterate = NULL;
       iterate = root;
       string tempath = path;
       while(path != ""){
           int found =0;
           int firstfound = 0;
           int secondfound = 0;

       for(int i = 0; i<(tempath.length()); ++i){
           if((path[i] == '\\') && (found==0)){
               found++;
               firstfound = i;
           }

           if((path[i] == '\\') && (found==1)){
               found++;
               secondfound = i;
           }
       }

           if(found == 2){

           if((typeid(*iterate)!=typeid(T)))
		return NULL;

          string findChild = tempath.substr(firstfound + 1, secondfound - (firstfound+1));
		
          if(iterate->getChild(findChild))
                   iterate = dynamic_cast<Directory*>(iterate->getChild(findChild));
           }


           if(secondfound == 0){

           if(typeid(*iterate)!=typeid(T))

           return NULL;

               string findChild = tempath.substr(firstfound + 1);

               if(iterate->getChild(findChild))

                   iterate = dynamic_cast<Directory*>(iterate->getChild(findChild));

                 return iterate;

           }

           tempath = tempath.substr(secondfound,tempath.length()-secondfound + 1);


       }

       return iterate;
      */
   }


template <typename T>

File* System<T> :: getFile(string path, string name){

        if(isValidPath(path) == false)

           return NULL;

        if(getDirectory(path)==NULL)

        return NULL;

       Directory * temp = getDirectory(path);

        if(temp->getChild(name) == NULL)

           return NULL;

        if(typeid(*(temp->getChild(name))) != typeid(File))

           return NULL;


        File* tempFile;

        tempFile = dynamic_cast<File*>(temp->getChild(name));

           return tempFile;

    }


template <typename T>

int System<T> :: addDir(string path, string name){

        if(isValidPath(path) == false)

           return -1;

        //Do statement for if the given path does not indicate an existing directory

        if(getDirectory(path) == NULL)

           return -2;

        T* temp = dynamic_cast<T*>(getDirectory(path));

        if(temp->addChild(true, name) == false)

           return -3;

           else{

           //Do we delete temp here?

           return 0;

           }

        return 0;

  }


template <typename T>

int System<T> :: addFile(string path, string name, string content){

        if(isValidPath(path) == false)

           return -1;

        if(getDirectory(path) == NULL)

           return -2;

         T* temp = dynamic_cast<T*>(getDirectory(path));

        if(temp->addChild(false, name) == false)

           return -3;

           else{

               File * filepoint = dynamic_cast<File*>(temp->getChild(name));

               filepoint->setContent(content);//is this setting conent right

               return 0;

           }

        return 0;

    }


template <typename T>

string System<T> :: list(string path){

       if(isValidPath(path) == false)

          return "";

       if(getDirectory(path) == NULL)

          return "<nope>";

       if((getDirectory(path)->getCount())==0)

          return "<empty>";

           Directory * pointPath = getDirectory(path);

           string retPath = "";

           retPath = pointPath->list();

          // int numChild = getDirectory(path)->getCount();

  // FSObject * togetPath = getDirectory(path)->getChild(numChild-1);

          //retPath = togetPath->getPath();

          //what about directory name?

          return retPath;



   }


template <typename T>

int System<T> :: del(string path, string name){

       if(isValidPath(path) == false)

          return -1;

       if(getDirectory(path) == NULL)

          return -2;

       Directory * temp = getDirectory(path);
       bool result = temp->removeChild(name);
       if( result== false)

          return -3;

       else

          return 0;

  }


template <typename T>

int System<T> :: move(string fromPath, string fromName, string toPath, string toName){

    /*if(isValidPath(fromPath) == false || isValidPath(toPath) == false)

           return -1;

    if(getDirectory(fromPath) == NULL || getDirectory(toPath) == NULL)

           return -2;

    T* pointto = dynamic_cast<T*>(getDirectory(toPath));

    T* pointfrom = dynamic_cast<T*>(getDirectory(fromPath));

  // Directory * pointto = getDirectory(toPath);


 // Directory* pointfrom = getDirectory(fromPath);

    //Do we not consider that the directory doesnt have a child?

    FSObject * toBeMoved = pointfrom->getChild(fromName);

           if(typeid(*toBeMoved) == typeid(T)){
        	  // Directory * temp = dynamic_cast<Directory*>(toBeMoved);
               cout<<"Entered directory check"<<endl;
              // pointto->addChild(true,toName);

               pointto = dynamic_cast<T*>(pointto->getChild(toName));

               pointfrom = dynamic_cast<T*>(pointfrom->getChild(fromName));

               int numChild = pointfrom->getCount();


               if(numChild==0){
            	   cout<<"Entered child = 0 check"<<endl;
            	   pointfrom->removeChild(fromName);
            	   pointto->addChild(true,toName);
                   //del(fromPath,fromName);

                   return 0;

               }

               else{

            	   cout<<"Entered child != 0 check"<<endl;
            	   pointto->addChild(true,toName);
            	   cout<<"cleareed add child"<<endl;
                   while(numChild!=0){
                	   cout<<"Entered recursive check"<<endl;
                       move(pointfrom->getPath(), pointfrom->getChild(0)->getName(), pointto->getChild(toName)->getPath(), pointto->getChild(0)->getName());

                       //numChild = pointfrom->getCount();

                   }

                   //del(fromPath, fromName);
                   pointfrom->removeChild(fromName);

                   return 0;

               }

           }

           else{

        	   cout<<"Entered file check"<<endl;
               pointto->addChild(false, toName);

               del(fromPath, fromName);

               return 0;

           }*/

	 if(isValidPath(fromPath) == false||isValidPath(toPath) == false)
		 return -1;

	   if(getDirectory(fromPath)==nullptr||getDirectory(toPath)==nullptr)
	     return -2;
	   Directory* pointfrom = getDirectory(fromPath);
       Directory* pointto = getDirectory(toPath);

	   FSObject* toBeMoved = pointfrom->getChild(fromName);


	   if (typeid(*toBeMoved)!=typeid(File)){
	   Directory* temp = dynamic_cast<Directory*>(toBeMoved);

	    if  (temp->getCount()==0){


	         pointfrom->removeChild(fromName);
	         pointto->addChild(true, toName);

	         return 0;
	    }
	     else{

	    	 pointto->addChild(true, toName);

	          while(temp->getCount()!=0){
                      move(temp->getPath(), temp->getChild(0)->getName(), pointto->getChild(toName)->getPath(),temp->getChild(0)->getName() );
                }
              pointfrom->removeChild(fromName);
              return 0;
	     }
	   }

	      if(typeid(*toBeMoved)==typeid(File)){
	    	  File* temp = dynamic_cast<File*>(toBeMoved);
	    	  string tempContent=temp->getContent();
	    	  pointfrom->removeChild(fromName);
	    	  pointto->addChild(false, toName);
	    	  return 0;

	      }

}










