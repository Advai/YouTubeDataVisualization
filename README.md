# Setup
  1. Download the repository. NOTE: do not use the ofxDatGui online. I have made changes to it for this specific project and it will not compile with any other  version. 
  2. Go to your addons folder in openframeworks and paste the folders inside this repository's addons folder
  3. add the ofxbraitsch folder in to the bin/data folder of your project and add the json.hpp file to your src directory
  4. replace the ofApp.h and ofApp.cpp that was generated with the respective files in this repository
  5. Add the python script and text files into your src folder. Inside the ofApp.h files, replace the path variable strings with the paths to these files in your project. 
  6. Set the Python path variable. Go to Project -> Options -> C/C++ -> General -> Additional Include Directories and add the path to your Python include folder and the libs folder. Do the same thing in the Project -> Options -> Linker -> General -> Additional Library Directories
  7. Any machine attempting to access Google accounts and data needs to sign up its project and obtain their own API keys and credentials. Once you receive those, go into the client_secret.json and update it with your project specific API keys and credentials.  
  
# Features
Once you log into your Google account: <br>
* Compare how many views, likes, and topics your liked videos range from 
* Compare views, subscribers and categories of your subscriptions
* Works with any Google account
    
  
  
