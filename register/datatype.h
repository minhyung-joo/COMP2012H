#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;

class Student {
public:
	Student() {
		studentID = "";
		name = "";
		year = "";
		gender = "";
	}
	Student(string id, string n, string y, string g) : studentID(id), name(n), year(y), gender(g) { }
	string getID() const { return studentID; }
	void setID(string id) { studentID = id; }
	string getName() const { return name; }
	void setName(string n) { name = n; }
	string getYear() const { return year; }
	void setYear(string y) { year = y; }
	string getGender() const { return gender; }
	void setGender(string g) { gender = g; }
	bool operator<(const Student &s) {
		return studentID.compare(s.getID()) < 0;
	}
  bool operator==(const Student &s) {
    return studentID == s.getID();
  }
  bool operator=(const Student &s) {
    studentID = s.getID();
    name = s.getName();
    year = s.getYear();
    gender = s.getGender();
  }
	string getKey() { return getID(); }
private:
	string studentID;
	string name;
	string year;
	string gender;
};

class Course {
public:
	Course() { 
		courseCode = "";
		name = "";
		credit = "";
	}
	Course(string code, string n, string c) : courseCode(code), name(n), credit(c) { }
	string getCode() const { return courseCode; }
	void setCode(string code) { courseCode = code; }
	string getName() const { return name; }
	void setName(string n) { name = n; }
	string getCredit() const { return credit; }
	void setCredit(string c) { credit = c; }
	bool operator<(const Course &c) {
		return courseCode.compare(c.getCode()) < 0;
	}
  bool operator==(const Course &c) {
    return courseCode == c.getCode();
  }
	string getKey() { return getCode(); }
private:
	string courseCode;
	string name;
	string credit;
};

class CourseSelection {
public:
	CourseSelection() {
    studentID = "";
    courseCode = "";
    examMark = ""; 
  }
  CourseSelection(string id, string code) : studentID(id), courseCode(code) { 
    examMark = "";
  }
  CourseSelection(string id, string code, string mark) : studentID(id), courseCode(code), examMark(mark) { }
	string getID() const { return studentID; }
	void setID(string id) { studentID = id; }
	string getCode() const { return courseCode; }
	void setCode(string code) { courseCode = code; }
	string getMark() const { return examMark; }
	void setMark(int mark) { examMark = mark; }
  bool operator<(const CourseSelection &cs) {
    if (studentID.compare(cs.getID()) == 0) {
      return courseCode.compare(cs.getCode()) < 0;
    }
    else {
      return studentID.compare(cs.getID()) < 0;
    }
  }
  bool operator==(const CourseSelection &cs) {
    return (studentID == cs.getID()) && (courseCode == cs.getCode());
  }
  bool operator==(const string &s) {
    return (studentID == s) || (courseCode == s);
  }
private:
	string studentID;
	string courseCode;
	string examMark;
};

#endif
