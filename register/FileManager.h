#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include "Records.h"

class FileManager {
public:
  FileManager(StudentTable *sst, CourseTable *ct, SelectionTable *set) : studentTable(sst), courseTable(ct), selectionTable(set) { }
	void saveFile(std::string& name);
	void loadFile(std::string& name);
private:
	std::ofstream* fileWriter;
	std::ifstream* fileReader;
  StudentTable *studentTable;
  CourseTable *courseTable;
  SelectionTable *selectionTable;
};

#endif
