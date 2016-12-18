#include <string>
#include <iostream>
#include "ReportGenerator.h"
using namespace std;

void ReportGenerator::listStudents() {

	fileWriter.open("Students.html");

	stringBuilder << "<HTML>\n";
	stringBuilder << "<HEAD>\n";
	stringBuilder << "<TITLE>All Students List</TITLE>\n";
  stringBuilder << "</HEAD>\n";
	stringBuilder << "<BODY bgColor=#ffffcc>\n";
  stringBuilder << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n";
  stringBuilder << "<H2>All Students List</H2>\n";
  stringBuilder << "<P>\n";
  if (!studentTable->empty()) {
    list<Student> students = studentTable->getList();
    list<Student>::iterator sit = students.begin();
    
    stringBuilder << "<TABLE cellSpacing=1 cellPadding=1 border=1>\n";
    stringBuilder << "\n";
    stringBuilder << "<TR>\n";
    stringBuilder << "<TD>Student ID</TD>\n";
    stringBuilder << "<TD>Student Name</TD>\n";
    stringBuilder << "<TD>Year</TD>\n";
    stringBuilder << "<TD>Gender</TD>\n";
    stringBuilder << "</TR>\n";
    stringBuilder << "\n";
    
    for ( ; sit != students.end(); ++sit) {
      Student s = *sit;
      
      stringBuilder << "<TR>\n";
      stringBuilder << "<TD>" << s.getID() << "</TD>\n";
      stringBuilder << "<TD>" << s.getName() << "</TD>\n";
      stringBuilder << "<TD>" << s.getYear() << "</TD>\n";
      stringBuilder << "<TD>" << s.getGender() << "</TD>\n";
      stringBuilder << "</TR>\n";
      stringBuilder << "\n";
    }
    
    stringBuilder << "</TABLE>\n";
  }
  else {
    stringBuilder << "No student found\n";
  }
  stringBuilder << "</P>\n";
  stringBuilder << "</BODY>\n";
  stringBuilder << "</HTML>";
  
  fileWriter << stringBuilder.str();
  fileWriter.flush();
  fileWriter.close();
  
  stringBuilder.str("");
  stringBuilder.clear();
}

void ReportGenerator::listCourses() {

	fileWriter.open("Courses.html");

	stringBuilder << "<HTML>\n";
	stringBuilder << "<HEAD>\n";
	stringBuilder << "<TITLE>All Course List</TITLE>\n";
  stringBuilder << "</HEAD>\n";
	stringBuilder << "<BODY bgColor=#ffffcc>\n";
  stringBuilder << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n";
  stringBuilder << "<H2>All Course List</H2>\n";
  stringBuilder << "<P>\n";
  if (!courseTable->empty()) {
    list<Course> courses = courseTable->getList();
    list<Course>::iterator cit = courses.begin();
    
    stringBuilder << "<TABLE cellSpacing=1 cellPadding=1 border=1>\n";
    stringBuilder << "\n";
    stringBuilder << "<TR>\n";
    stringBuilder << "<TD>Course Code</TD>\n";
    stringBuilder << "<TD>Course Name</TD>\n";
    stringBuilder << "<TD>Credit</TD>\n";
    stringBuilder << "</TR>\n";
    stringBuilder << "\n";
    
    for ( ; cit != courses.end(); ++cit) {
      Course c = *cit;
      
      stringBuilder << "<TR>\n";
      stringBuilder << "<TD>" << c.getCode() << "</TD>\n";
      stringBuilder << "<TD>" << c.getName() << "</TD>\n";
      stringBuilder << "<TD>" << c.getCredit() << "</TD>\n";
      stringBuilder << "</TR>\n";
      stringBuilder << "\n";
    }
    
    stringBuilder << "</TABLE>\n";
  }
  else {
    stringBuilder << "No course found\n";
  }
  stringBuilder << "</P>\n";
  stringBuilder << "</BODY>\n";
  stringBuilder << "</HTML>";
  
  fileWriter << stringBuilder.str();
  fileWriter.flush();
  fileWriter.close();
  
  stringBuilder.str("");
  stringBuilder.clear();
}

void ReportGenerator::listCourseOfStudent(const Student& s) {
  bool hasCourse = false;
  string id = s.getID();
  string fileName = id + ".html";
  
	fileWriter.open(fileName.c_str());

	stringBuilder << "<HTML>\n";
	stringBuilder << "<HEAD>\n";
	stringBuilder << "<TITLE>Course Records for Student ";
  stringBuilder << s.getID();
  stringBuilder << "</TITLE>\n";
  stringBuilder << "</HEAD>\n";
	stringBuilder << "<BODY bgColor=#ffffcc>\n";
  stringBuilder << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n";
  stringBuilder << "<H2>Course Records for Student: ";
  stringBuilder << s.getName();
  stringBuilder << " (";
  stringBuilder << s.getID();
  stringBuilder << ")</H2>\n";
  stringBuilder << "<P>\n";
  list<CourseSelection*> sl = selectionTable->querySelectionByID(id);
  if (sl.size() > 0) {
    stringBuilder << "<TABLE cellSpacing=1 cellPadding=1 border=1>\n";
    stringBuilder << "\n";
    stringBuilder << "<TR>\n";
    stringBuilder << "<TD>Course Code</TD>\n";
    stringBuilder << "<TD>Course Name</TD>\n";
    stringBuilder << "<TD>Credit</TD>\n";
    stringBuilder << "<TD>Exam Mark</TD>\n";
    stringBuilder << "</TR>\n";
    stringBuilder << "\n";

    list<CourseSelection*>::iterator sit = sl.begin();

    for ( ; sit != sl.end(); ++sit) {
      CourseSelection *cs = *sit;
      string code = cs->getCode();
      Course c = courseTable->query(code);

      stringBuilder << "<TR>\n";
      stringBuilder << "<TD>" << c.getCode() << "</TD>\n";
      stringBuilder << "<TD>" << c.getName() << "</TD>\n";
      stringBuilder << "<TD>" << c.getCredit() << "</TD>\n";
      stringBuilder << "<TD>" << cs->getMark() << "</TD>\n";
      stringBuilder << "</TR>\n";
      stringBuilder << "\n";
    }
  }
  else {
    stringBuilder << "No course taken\n";
  }
  stringBuilder << "</P>\n";
  stringBuilder << "</BODY>\n";
  stringBuilder << "</HTML>";
  
  fileWriter << stringBuilder.str();
  fileWriter.flush();
  fileWriter.close();
  
  stringBuilder.str("");
  stringBuilder.clear();
}

void ReportGenerator::listStudentOfCourse(const Course& c) {
  bool hasCourse = false;
  string code = c.getCode();
  string fileName = code + ".html";
  
	fileWriter.open(fileName.c_str());

	stringBuilder << "<HTML>\n";
	stringBuilder << "<HEAD>\n";
	stringBuilder << "<TITLE>Student Records for Course ";
  stringBuilder << c.getCode();
  stringBuilder << "</TITLE>\n";
  stringBuilder << "</HEAD>\n";
	stringBuilder << "<BODY bgColor=#ffffcc>\n";
  stringBuilder << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n";
  stringBuilder << "<H2>Student Records for Course: ";
  stringBuilder << c.getName();
  stringBuilder << " (";
  stringBuilder << c.getCode();
  stringBuilder << ")</H2>\n";
  stringBuilder << "<P>\n";

  list<CourseSelection*> sl = selectionTable->querySelectionByCode(code);
  if (sl.size() > 0) {
    stringBuilder << "<TABLE cellSpacing=1 cellPadding=1 border=1>\n";
    stringBuilder << "\n";
    stringBuilder << "<TR>\n";
    stringBuilder << "<TD>Student ID</TD>\n";
    stringBuilder << "<TD>Student Name</TD>\n";
    stringBuilder << "<TD>Year</TD>\n";
    stringBuilder << "<TD>Gender</TD>\n";
    stringBuilder << "<TD>Exam Mark</TD>\n";
    stringBuilder << "</TR>\n";
    stringBuilder << "\n";

    list<CourseSelection*>::iterator sit = sl.begin();
    for ( ; sit != sl.end(); ++sit) {
      CourseSelection *cs = *sit;
      string id = cs->getID();
      Student s = studentTable->query(id);

      stringBuilder << "<TR>\n";
      stringBuilder << "<TD>" << s.getID() << "</TD>\n";
      stringBuilder << "<TD>" << s.getName() << "</TD>\n";
      stringBuilder << "<TD>" << s.getYear() << "</TD>\n";
      stringBuilder << "<TD>" << s.getGender() << "</TD>\n";
      stringBuilder << "<TD>" << cs->getMark() << "</TD>\n";
      stringBuilder << "</TR>\n";
      stringBuilder << "\n";
    }
  }
  else {
    stringBuilder << "No student takes this course\n";
  }
  stringBuilder << "</P>\n";
  stringBuilder << "</BODY>\n";
  stringBuilder << "</HTML>";
  
  fileWriter << stringBuilder.str();
  fileWriter.flush();
  fileWriter.close();
  
  stringBuilder.str("");
  stringBuilder.clear();
}
