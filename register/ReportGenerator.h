#ifndef REPORT_H
#define REPORT_H

#include <fstream>
#include <sstream>
#include "Records.h"

class ReportGenerator {
public:
  ReportGenerator(StudentTable *stt, CourseTable *ct, SelectionTable *set) : studentTable(stt), courseTable(ct), selectionTable(set) { }  
	void listStudents();
	void listCourses();
	void listCourseOfStudent(const Student&);
	void listStudentOfCourse(const Course&);
private:
	ofstream fileWriter;
	stringstream stringBuilder;
  StudentTable *studentTable;
  CourseTable *courseTable;
  SelectionTable *selectionTable;
};

#endif
