#include <iostream>
#include <sstream>
#include "FileManager.h"
using namespace std;

void FileManager::saveFile(string& fileName) {
	fileWriter = new ofstream(fileName.c_str());

	if (fileWriter->good()) {
    list<Student> studentList = studentTable->getList();
    list<Course> courseList = courseTable->getList();
    list<CourseSelection*> selectionList = selectionTable->getList();
    
    *fileWriter << "students" << endl;
    for (list<Student>::iterator it = studentList.begin();
          it != studentList.end();
          ++it) {
      Student s = *it;
      *fileWriter << "\t" << s.getID() << " " << s.getName() << " " << s.getYear() << " " << s.getGender() << endl;
    }
    
    *fileWriter << "courses" << endl;
    for (list<Course>::iterator it = courseList.begin();
          it != courseList.end();
          ++it) {
      Course c = *it;
      *fileWriter << "\t" << c.getCode() << " " << c.getName() << " " << c.getCredit() << endl;
    }
    
    *fileWriter << "selections" << endl;
    for (list<CourseSelection*>::iterator it = selectionList.begin();
          it != selectionList.end();
          ++it) {
      CourseSelection cs = *(*it);
      *fileWriter << "\t" << cs.getID() << " " << cs.getCode() << " " << cs.getMark() << endl;
    }
    
    *fileWriter << "enddata";
    
    fileWriter->flush();
    
    cout << "Saving Successful\n" << endl;
	}
	else {
		cout << "Error: Save File Error (File not exist / File Corrupted / Incorrect Format)\n" << endl;
	}

  (*fileWriter).close();
  delete fileWriter;
}

void FileManager::loadFile(string& fileName) {
	fileReader = new ifstream(fileName.c_str());

	if (fileReader->good()) {
    string mode;
    
    studentTable->clear();
    courseTable->clear();
    selectionTable->clear();

    for (string line; getline(*fileReader, line); ) {
      if (line.at(0) == '\t') {
        istringstream iss(line);
        string sub;
        
        if (mode.compare("students") == 0) {
          string id;
          string name;
          string year;
          string gender;
          
          iss >> sub;
          id = sub;
          sub = "";
          
          iss >> sub;
          name = sub;
          sub = "";
          
          iss >> sub;
          year = sub;
          sub = "";
          
          iss >> sub;
          gender = sub;
          
          Student s(id, name, year, gender);
          studentTable->insert(s);
        }
        else if (mode.compare("courses") == 0) {
          string code;
          string name;
          string credit;
          
          iss >> sub;
          code = sub;
          sub = "";
          
          iss >> sub;
          name = sub;
          sub = "";
          
          iss >> sub;
          credit = sub;
          
          Course c(code, name, credit);
          courseTable->insert(c);
        }
        else if (mode.compare("selections") == 0) {
          string id;
          string code;
          string mark;
          
          iss >> sub;
          id = sub;
          sub = "";
          
          iss >> sub;
          code = sub;
          sub = "";
          
          iss >> sub;
          mark = sub;
          
          selectionTable->addCourse(id, code, mark);
        }
      }
      else {
        mode = line;
      }
    }
    
    cout << "Loading Successful\n" << endl;
	}
	else {
		cout << "Error: Load File Error (File not exist / File Corrupted / Incorrect Format)\n" << endl;
	}
 
  fileReader->close();
}
