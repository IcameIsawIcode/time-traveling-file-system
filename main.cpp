#include "file.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    FileSystem fs;
    string line;

    while(getline(cin, line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if(cmd =="CREATE") {
            string filename;            // only the first word after create will be considered for filename
            ss>>filename;

            if (filename == "") {
                cout<<"Format: CREATE <Filename>"<<endl;
            }
            else if (fs.getFile(filename)) {
                cout << "File already exists" << filename << "\n";
            }
            else {
                fs.createFile(filename);
                fs.updateHeaps(filename);
            }


        }
        else if (cmd=="READ") {
            string filename; //strictly follows the input format
            ss>>filename;
            if (filename == "") {
                cout<<"Format: READ <Filename>"<<endl;
            }
            else {
                File* f = fs.getFile(filename);
                if (f) {
                    cout << f->read() << "\n";
                }
                else {
                    cout << "File not found"<<"\n";
                }
            }

        }
        else if (cmd =="INSERT") {
            string filename, content; // refer README for sanitisation
            ss>>filename;
            if (filename == "") {
                cout<<"Format: INSERT <Filename> <content>"<<endl;
            }
            else {
                getline(ss, content);
                if(content == "") {
                    cout << "Format: INSERT <Filename> <content>"<<"\n";
                }

                else {
                    content = content.substr(1,content.length()-1);
                    File* f = fs.getFile(filename);
                    if(f) {
                        f->insert(content);
                        fs.updateHeaps(filename);
                    }
                    else {
                        cout << "File not found"<<"\n";
                    }
                }

            }


        }
        else if (cmd =="UPDATE") {
            string filename, content; // here replace the content
            ss>>filename;
            if (filename == "") {
                cout<<"Format: UPDATE <Filename> <content>"<<endl;
            }
            else {
                getline(ss, content);
                if(content == "") {
                    cout << "Format: UPDATE <Filename> <content>"<<"\n";
                }
                else {
                    content = content.substr(1,content.length()-1);
                    File* f = fs.getFile(filename);
                    if(f) {
                        f->update(content);
                        fs.updateHeaps(filename); // updates heaps in real time, refer file.cpp
                    }
                    else {
                        cout << "File not found"<<"\n";
                    }
                }

            }

        }
        else if (cmd=="SNAPSHOT") {
            string filename, message;
            ss>>filename;
            if (filename == "") {
                cout<<"Format: SNAPSHOT <Filename> <message>"<<endl;
            }
            else {
                getline(ss, message); // message = empty is considered valid

                File* f = fs.getFile(filename);
                if(f){
                    if (!(f->snapshot(message))) {
                        cout<<"Already snapshotted this version"<<"\n";
                    }

                }
                else {
                    cout << "File not found"<<"\n";
                }

            }


        }
        else if (cmd=="ROLLBACK") {
            string filename;
            string id;
            ss>>filename; // refer README for assumptions
            ss>>id;
            if (filename == "") {
                cout<<"Format: ROLLBACK <Filename> <ID/empty>"<<endl;
            }
            else {
                if (id=="") {
                    File* f = fs.getFile(filename);
                    if(f) {
                        f->rollback(-1); // checking if f exists
                    }
                    else {
                        cout<< "File not found"<<"\n";
                    }
                }
                else {
                    try {
                        int ho = stoi(id); // converting string to integer to check validity
                        if (ho>=0) {
                            File* f = fs.getFile(filename);
                            if(f){
                                f->rollback(ho);
                            }
                            else {
                                cout<<"File not found"<<"\n";
                            }
                        }
                        else {
                            cout<<"Invalid ID"<<"\n";
                        }

                    }
                    catch(...) {
                        cout<<"Format: ROLLBACK <Filename> <ID/empty>"<<endl;
                    }
                }
            }



        }
        else if (cmd =="HISTORY") {
            string filename;
            ss>>filename;
            if (filename == "") {
                cout<<"Format: HISTORY <Filename>"<<endl;
            }
            else {
                File* f = fs.getFile(filename);
                if(f){
                    f->history();
                }
                else {
                    cout<<"File not found"<<"\n";
                }
            }

        }
        else if (cmd =="RECENT_FILES") {
            int num;
            if (ss>>num) {
                if (num <= 0) {
                    cout << "Number must be positive"<<endl;
                }
                else {
                    fs.recentFiles(num);
                }

            }
            else {
                cout<<"Format: RECENT_FILES <num>"<<"\n";
            }
        }
        else if (cmd =="BIGGEST_TREES") {
            int num;
            if (ss>>num) {
                if (num <= 0) {
                    cout << "Number must be positive"<<endl;
                }
                else {
                    fs.biggestTrees(num);
                }

            }
            else {
                cout<<"Format: BIGGEST_TREES <num>"<<"\n";
            }
        }
        else {
            cout << "Unknown command: " << cmd << "\n"; // any other command is ignored
        }
    }


    return 0;
}
