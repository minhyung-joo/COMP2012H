#include <iostream>
#include <stdlib.h>
#include "RegistrationSystem.h"
using namespace std;

RegistrationSystem::RegistrationSystem() {
  reportGenerator = new ReportGenerator(&studentTable, &courseTable, &selectionTable);
  fileManager = new FileManager(&studentTable, &courseTable, &selectionTable);
}

bool RegistrationSystem::checkID(const string &id) {
	if (id.length() != 8) return false;

	for (int i = 0; i < 8; i++) {
		char c = id.at(i);
		if (c < '0' || c > '9') return false;
	}

	return true;
}

bool RegistrationSystem::checkName(const string &name) {
	return name.length() > 0 && name.length() <= 32;
}

bool RegistrationSystem::checkYear(const string &year) {
	if (year.length() != 1) return false;

	char c = year.at(0);
	if (c < '1' || c > '3') return false;

	return true;
}

bool RegistrationSystem::checkGender(const string &gender) {
	if (gender.length() != 1) return false;

	char c = gender.at(0);
	if (c == 'F' || c == 'M' || c == 'f' || c == 'm') return true;
	else return false;
}

void RegistrationSystem::insertStudent() {
	string id;
	string name;
	string year;
	string gender;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.query(id);
  if (s.getID().compare(id) == 0) {
    cout << "Student already exist" << endl;
  }
  else {
    cout << "Enter the student name: ";
  	getline(cin, name);
  	while (!checkName(name)) {
  		cout << "Invalid input, re-enter again [student name]: ";
  		getline(cin, name);
  	}
   
  	cout << "Enter the student year [1-3]: ";
  	getline(cin, year);
  	while (!checkYear(year)) {
  		cout << "Invalid input, re-enter again [student year]: ";
  		getline(cin, year);
  	}
   
  	cout << "Enter the student gender [M,F]: ";
  	getline(cin, gender);
  	while (!checkGender(gender)) {
  		cout << "Invalid input, re-enter again [M,F]: ";
  		getline(cin, gender);
  	}
    char g = gender.at(0);
    if (g == 'm' || g == 'M') gender = "Male";
    else gender = "Female";
    
    Student s(id, name, year, gender);
    studentTable.insert(s);
    
  	cout << "Creation of student record successful\n" << endl;
  }
	
	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::modifyStudent() {
	string id;
	string name;
	string year;
	string gender;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.remove(id);
  if (s.getID().compare(id) == 0) {
    cout << "Enter the student name [" << s.getName() << "]: ";
  	getline(cin, name);
  	while (!checkName(name)) {
  		cout << "Invalid input, re-enter again [student name]: ";
  		getline(cin, name);
  	}
  
  	cout << "Enter the student year [" << s.getYear() << "]: ";
  	getline(cin, year);
  	while (!checkYear(year)) {
  		cout << "Invalid input, re-enter again [student year]: ";
  		getline(cin, year);
  	}
  
  	cout << "Enter the student gender [" << s.getGender().at(0) << "]: ";
  	getline(cin, gender);
  	while (!checkGender(gender)) {
  		cout << "Invalid input, re-enter again [M,F]: ";
  		getline(cin, gender);
  	}
    char g = gender.at(0);
    if (g == 'm' || g == 'M') gender = "Male";
    else gender = "Female";

    Student modified(id, name, year, gender);
    studentTable.insert(modified);

  	cout << "Modification of student record successful\n" << endl;
  }
  else {
    cout << "Student not exist\n" << endl;
  }

	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::deleteStudent() {
	string id;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.remove(id);
 
	if (s.getID().compare(id) == 0) {
		cout << "Deletion of student record successful\n" << endl;
	}
	else {
		cout << "Student not exist\n" << endl;
	}

	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::queryStudent() {
	string id;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
 
  Student s = studentTable.query(id);
  if (s.getID().compare(id) == 0) {
    cout << endl;
		cout << "ID:\t" << s.getID() << endl;
		cout << "Name:\t" << s.getName() << endl;
		cout << "Year:\t" << s.getYear() << endl;
		cout << "Gender:\t" << s.getGender() << endl;
		cout << endl;
  }
	else {
		cout << "Student not exist\n" << endl;
	}

	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::studentManagement() {
	system("clear");
	string input;
	char choice;

	cout << "HKUST Course Registration System  (Student Menu)" << endl;
	cout << "------------------------------------------------" << endl;
	cout << endl;

	cout << "1. Insert Student Record" << endl;
	cout << "2. Modify Student Record" << endl;
	cout << "3. Delete Student Record" << endl;
	cout << "4. Query Student Record" << endl;
	cout << "5. Go back to main menu" << endl;
	cout << endl;

	cout << "Enter your choice (1-5): ";
	while (true) {
		getline(cin, input);
		if (input.length() == 1) choice = input.at(0);
		else choice = 'x';

		switch (choice) {
			case '1':
				insertStudent();
				return;
			case '2':
				modifyStudent();
				return;
			case '3':
				deleteStudent();
				return;
			case '4':
				queryStudent();
				return;
			case '5':
				return;
			default:
				cout << "Invalid input, re-enter again (1-5): ";
				break;
		}
	}
}

bool RegistrationSystem::checkCode(const string& code) {
	if (code.length() < 7 || code.length() > 8) return false;

	char c;
	for (int i = 0; i < 4; i++) {
		c = code.at(i);

		if (c < 'A' || c > 'Z') return false;
	}

	for (int j = 4; j < code.length(); j++) {
		c = code.at(j);

		if (c < '0') return false;
		else if (c > '9' && c < 'A') return false;
		else if (c > 'Z') return false;
	}

	return true;
}

bool RegistrationSystem::checkCourseName(const string& name) {
	return name.length() > 0 && name.length() <= 50;
}

bool RegistrationSystem::checkCredit(const string& credit) {
	if (credit.length() != 1) return false;

	char c = credit.at(0);
	if (c < '0' || c > '5') return false;

	return true;
}

void RegistrationSystem::insertCourse() {
	string code;
	string name;
	string credit;

	cout << "Enter the course code: ";
	getline(cin, code);
	while (!checkCode(code)) {
		cout << "Invalid input, re-enter again [course code]: ";
		getline(cin, code);
	}
	Course c = courseTable.query(code);
  if (c.getCode().compare(code) == 0) {
    cout << "Course already exist\n" << endl;
  }
  else {
    cout << "Enter the course name: ";
  	getline(cin, name);
  	while (!checkCourseName(name)) {
  		cout << "Invalid input, re-enter again [course name]: ";
  		getline(cin, name);
  	}
  
  	cout << "Enter the course credit [0-5]: ";
  	getline(cin, credit);
  	while (!checkCredit(credit)) {
  		cout << "Invalid input, re-enter again [course credit]: ";
  		getline(cin, credit);
  	}
  
    Course c(code, name, credit);
    courseTable.insert(c);
  
  	cout << "Creation of course record successful\n" << endl;
  }
	
	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::modifyCourse() {
	string code;
	string name;
	string credit;

	cout << "Enter the course code: ";
	getline(cin, code);
	while (!checkCode(code)) {
		cout << "Invalid input, re-enter again [course code]: ";
		getline(cin, code);
	}
 
	Course c = courseTable.remove(code);
  if (c.getCode().compare(code) == 0) {
    cout << "Enter the course name [" << c.getName() << "]: ";
  	getline(cin, name);
  	while (!checkCourseName(name)) {
  		cout << "Invalid input, re-enter again [course name]: ";
  		getline(cin, name);
  	}
  
  	cout << "Enter the course credit [" << c.getCredit() << "]: ";
  	getline(cin, credit);
  	while (!checkCredit(credit)) {
  		cout << "Invalid input, re-enter again [course credit]: ";
  		getline(cin, credit);
  	}
  
    Course modified(code, name, credit);
    courseTable.insert(modified);
  
  	cout << "Modification of course record successful\n" << endl;
  }
  else {
    cout << "Course not exist\n" << endl;
  }

	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::deleteCourse() {
	string code;

	cout << "Enter the course code: ";
	getline(cin, code);
	while (!checkCode(code)) {
		cout << "Invalid input, re-enter again [course code]: ";
		getline(cin, code);
	}
	
  Course c = courseTable.remove(code);
	if (c.getCode().compare(code) == 0) {
		cout << "Deletion of course record successful\n" << endl;
	}
	else {
		cout << "Course not exist\n" << endl;
	}

	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::queryCourse() {
	string code;

	cout << "Enter the course code: ";
	getline(cin, code);
	while (!checkCode(code)) {
		cout << "Invalid input, re-enter again [course code]: ";
		getline(cin, code);
	}
	
  Course c = courseTable.query(code);
  if (c.getCode().compare(code) == 0) {
    cout << endl;
  	cout << "Code:\t" << c.getCode() << endl;
  	cout << "Name:\t" << c.getName() << endl;
  	cout << "Credit:\t" << c.getCredit() << endl;
  	cout << endl;
  }
  else {
    cout << "Course not exist\n" << endl;
  }

	cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::courseManagement() {
	system("clear");
	string input;
	char choice;

	cout << "HKUST Course Registration System  (Course Menu)" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << endl;

	cout << "1. Insert Course Record" << endl;
	cout << "2. Modify Course Record" << endl;
	cout << "3. Delete Course Record" << endl;
	cout << "4. Query Course Record" << endl;
	cout << "5. Go back to main menu" << endl;
	cout << endl;

	cout << "Enter your choice (1-5): ";

	while (true) {
		getline(cin, input);
		if (input.length() == 1) choice = input.at(0);
		else choice = 'x';

		switch (choice) {
			case '1':
				insertCourse();
				return;
			case '2':
				modifyCourse();
				return;
			case '3':
				deleteCourse();
				return;
			case '4':
				queryCourse();
				return;
			case '5':
				return;
			default:
				cout << "Invalid input, re-enter again (1-5): ";
				break;
		}
	}
}

void RegistrationSystem::addCourse() {
	string id;
  string code;
  string mark = "N/A";

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.query(id);
  if (s.getID().compare(id) == 0) {
    cout << "Enter the course code: ";
  	getline(cin, code);
  	while (!checkCode(code)) {
  		cout << "Invalid input, re-enter again [course code]: ";
  		getline(cin, code);
  	}
    Course c = courseTable.query(code);
    if (c.getCode().compare(code) == 0) {
      CourseSelection cs = selectionTable.querySelection(id, code);
      
      if ( (cs.getID() == id) && (cs.getCode() == code) ) {
        cout << "The student already registered the course\n" << endl;
      }
      else {
        selectionTable.addCourse(id, code, mark);
        
        cout << "Add course successful\n" << endl;
      }
    }
    else {
      cout << "Course not exist\n" << endl;
    }
  }
	else {
		cout << "Student not exist\n" << endl;
	}

  cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::dropCourse() {
  string id;
  string code;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.query(id);
  
  if (s.getID() == id) {
		cout << "Enter the course code: ";
  	getline(cin, code);
  	while (!checkCode(code)) {
  		cout << "Invalid input, re-enter again [course code]: ";
  		getline(cin, code);
  	}
    Course c = courseTable.query(code);
    
    if (c.getCode() == code) {
      CourseSelection cs = selectionTable.querySelection(id, code);
      
      if ( (cs.getID() == id) && (cs.getCode() == code) ) {
        selectionTable.dropCourse(id, code);
        cout << "Drop course successful\n" << endl;
      }
      else {
        cout << "The registration record not exist\n" << endl;
      }
    }
    else {
      cout << "Course not exist\n" << endl;
    }
	}
	else {
		cout << "Student not exist\n" << endl;
	}

  cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

bool RegistrationSystem::checkMark(const string &mark) {
  if (mark.length() < 1 || mark.length() > 3) return false;
  
  for (int i = 0; i < mark.length(); i++) {
    char c = mark.at(i);
    if (c < '0' || c > '9') return false;
  }
  
  const char *cstr = mark.c_str();
  int m = atoi(cstr);
  if (m > 100) return false;
  
  return true;
}

void RegistrationSystem::modifyExam() {
  string id;
  string code;
  string mark;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.query(id);
  
  if (s.getID() == id) {
		cout << "Enter the course code: ";
  	getline(cin, code);
  	while (!checkCode(code)) {
  		cout << "Invalid input, re-enter again [course code]: ";
  		getline(cin, code);
  	}
    Course c = courseTable.query(code);
    
    if (c.getCode() == code) {
      CourseSelection cs = selectionTable.querySelection(id, code);
      
      if ( (cs.getID() == id) && (cs.getCode() == code) ) {
        selectionTable.dropCourse(id, code);
        cout << "Enter the exam mark [" << cs.getMark() << "]: "; // Put the exam mark
        getline(cin, mark);
        while (!checkMark(mark)) {
          cout << "Invalid input, re-enter again [exam mark]: ";
          getline(cin, mark);
        }
        selectionTable.addCourse(id, code, mark);
        
        cout << "Modification of exam mark successful\n" << endl;
      }
      else {
        cout << "The registration record not exist\n" << endl;
      }
      
    }
    else {
      cout << "Course not exist\n" << endl;
    }
	}
	else {
		cout << "Student not exist\n" << endl;
	}

  cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::queryRegistration() {
  string id;
  string code;

	cout << "Enter the student ID: ";
	getline(cin, id);
	while (!checkID(id)) {
		cout << "Invalid input, re-enter again [student ID]: ";
		getline(cin, id);
	}
	Student s = studentTable.query(id);
  
  if (s.getID() == id) {
		cout << "Enter the course code: ";
  	getline(cin, code);
  	while (!checkCode(code)) {
  		cout << "Invalid input, re-enter again [course code]: ";
  		getline(cin, code);
  	}
    Course c = courseTable.query(code);
    
    if (c.getCode() == code) {
      CourseSelection cs = selectionTable.querySelection(id, code);
      
      if ( (cs.getID() == id) && (cs.getCode() == code) ) {
        cout << endl;
        cout << "Student ID:\t" << cs.getID() << endl; // Put the information
        cout << "Course Code:\t" << cs.getCode() << endl;
        cout << "Exam mark:\t" << cs.getMark() << endl;
        cout << endl;
      }
      else {
        cout << "The registration record not exist\n" << endl;
      }
    }
    else {
      cout << "Course not exist\n" << endl;
    }
	}
	else {
		cout << "Student not exist\n" << endl;
	}

  cout << "Hit ENTER to continue..." << endl;
	cin.ignore();
}

void RegistrationSystem::courseRegistration() {
	system("clear");
	string input;
	char choice;

	cout << "HKUST Course Registration System  (Registration Menu)" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;

	cout << "1. Add Course" << endl;
	cout << "2. Drop Course" << endl;
	cout << "3. Modify Exam Mark" << endl;
	cout << "4. Query Registration" << endl;
	cout << "5. Go back to main menu" << endl;
	cout << endl;

	cout << "Enter your choice (1-5): ";

	while (true) {
		getline(cin, input);
		if (input.length() == 1) choice = input.at(0);
		else choice = 'x';

		switch (choice) {
      case '1':
        addCourse();
				return;
      case '2':
				dropCourse();
        return;
      case '3':
        modifyExam();
				return;
      case '4':
        queryRegistration();
				return;
			case '5':
				return;
			default:
				cout << "Invalid input, re-enter again (1-5): ";
				break;
		}
	}
}

void RegistrationSystem::listStudent() {
  reportGenerator->listStudents();
  cout << "Output Successful\n" << endl;
  
  cout << "Hit ENTER to continue..." << endl;
  cin.ignore();
}

void RegistrationSystem::listCourse() {
  reportGenerator->listCourses();
  cout << "Output Successful\n" << endl;
  
  cout << "Hit ENTER to continue..." << endl;
  cin.ignore();
}

void RegistrationSystem::listCourseOfStudent() {
  string id;

  cout << "Enter the student ID: ";
  getline(cin, id);
  while (!checkID(id)) {
    cout << "Invalid input, re-enter again [student ID]: ";
    getline(cin, id);
  }

  Student s = studentTable.query(id);

  if (s.getID().compare(id) == 0) {
    reportGenerator->listCourseOfStudent(s);
    cout << "Output Successful\n" << endl;
  }
  else {
    cout << "Student not exist\n" << endl;
  }

  cout << "Hit ENTER to continue..." << endl;
  cin.ignore();
}

void RegistrationSystem::listStudentOfCourse() {
  string code;

  cout << "Enter the course code: ";
  getline(cin, code);
  while (!checkCode(code)) {
    cout << "Invalid input, re-enter again [course code]: ";
    getline(cin, code);
  }

  Course c = courseTable.query(code);

  if (c.getCode().compare(code) == 0) {
    reportGenerator->listStudentOfCourse(c);
    cout << "Output Successful\n" << endl;
  }
  else {
    cout << "Course not exist\n" << endl;
  }
  
  cout << "Hit ENTER to continue..." << endl;
  cin.ignore();
}

void RegistrationSystem::reportManagement() {
	system("clear");
	string input;
	char choice;

	cout << "HKUST Course Registration System  (Report Generation Menu)" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << endl;

	cout << "1. List all student information" << endl;
	cout << "2. List all course information" << endl;
	cout << "3. List all courses of a student" << endl;
	cout << "4. List all students of a course" << endl;
	cout << "5. Go back to main menu" << endl;
	cout << endl;

	cout << "Enter your choice (1-5): ";

	while (true) {
		getline(cin, input);
		if (input.length() == 1) choice = input.at(0);
		else choice = 'x';

		switch(choice) {
      case '1':
        listStudent();
        return;
      case '2':
        listCourse();
        return;
      case '3':
        listCourseOfStudent();
        return;
      case '4':
        listStudentOfCourse();
        return;
			case '5':
				return;
			default:
				cout << "Invalid input, re-enter again (1-5): ";
				break;
		}
	}
}

void RegistrationSystem::saveData() {
  string fileName;
  
  cout << "Enter the filename: ";
  getline(cin, fileName);
  fileManager->saveFile(fileName);
  
  cout << "Hit ENTER to continue..." << endl;
  cin.ignore();
}

void RegistrationSystem::loadData() {
  string fileName;
  
  cout << "Enter the filename: ";
  getline(cin, fileName);
  fileManager->loadFile(fileName);
  
  cout << "Hit ENTER to continue..." << endl;
  cin.ignore();
}

void RegistrationSystem::fileManagement() {
	system("clear");
	string input;
	char choice;

	cout << "HKUST Course Registration System  (File Menu)" << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;

	cout << "1. Save Database" << endl;
	cout << "2. Load Database" << endl;
	cout << "3. Go back to main menu" << endl;
	cout << endl;

	cout << "Enter your choice (1-3): ";

	while (true) {
		getline(cin, input);
		if (input.length() == 1) choice = input.at(0);
		else choice = 'x';

		switch (choice) {
      case '1':
        saveData();
        return;
      case '2':
        loadData();
        return;
			case '3':
				return;
			default:
				cout << "Invalid input, re-enter again (1-3): ";
				break;
		}
	}
}

void RegistrationSystem::exec() {
	while (true) {
		system("clear");
		string input;
		char choice;

		cout << "HKUST Course Registration System" << endl;
		cout << "--------------------------------" << endl;
		cout << endl;

		cout << "1. Student Management" << endl;
		cout << "2. Course Management" << endl;
		cout << "3. Course Registration" << endl;
		cout << "4. Report Management" << endl;
		cout << "5. File Management" << endl;
		cout << "6. Exit" << endl;
		cout << endl;

		cout << "Enter your choice (1-6): ";

		bool chosen = false;
		while (!chosen) {
			getline(cin, input);
			if (input.length() == 1) choice = input.at(0);
			else choice = 'x';
			switch(choice) {
				case '1':
					studentManagement();
					chosen = true;
					break;
				case '2':
					courseManagement();
					chosen = true;
					break;
				case '3':
					courseRegistration();
					chosen = true;
					break;
				case '4':
					reportManagement();
					chosen = true;
					break;
				case '5':
					fileManagement();
					chosen = true;
					break;
				case '6':
					return;
				default:
					cout << "Invalid input, re-enter again (1-6): ";
					break;			
			}
		}
	}
}
