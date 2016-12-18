Register: main.o Records.o RegistrationSystem.o ReportGenerator.o FileManager.o
	g++ -o Register main.o Records.o RegistrationSystem.o ReportGenerator.o FileManager.o
main.o: main.cpp RegistrationSystem.h
	g++ -c main.cpp
RegistrationSystem.o: RegistrationSystem.h RegistrationSystem.cpp Records.h ReportGenerator.h FileManager.h
	g++ -c RegistrationSystem.cpp
Records.o: Records.h Records.cpp hashtable.h datatype.h
	g++ -c Records.cpp
ReportGenerator.o: ReportGenerator.h ReportGenerator.cpp datatype.h
	g++ -c ReportGenerator.cpp
FileManager.o: FileManager.h FileManager.cpp
	g++ -c FileManager.cpp
