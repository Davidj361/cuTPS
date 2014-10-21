server:	serverEx
# Add files here
serverEx:	Server.o Controller.o Connection.o Serializer.o DBManager.o
	g++ Server.o Controller.o Connection.o Serializer.o DBManager.o -o serverEx
Server.o:	Server.cc
	g++ -c Server.cc
Controller.o:	Controller.cc
	g++ -c Controller.cc
Connection.o:	Connection.cc
	g++ -c Connection.cc
Serializer.o:	Serializer.cc
	g++ -c Serializer.cc
DBManager.o:	DBManager.cc
	g++ -c DBManager.cc
