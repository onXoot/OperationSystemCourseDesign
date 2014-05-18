CXX = clang++
CPPFLAGS =  -std=c++11 
LDFLAGS  =  -pthread

server:  cal.o stack.o server.o
	$(CXX) -o $@ $^ $(LDFLAGS)
server.o: server.cpp
	$(CXX) -c $^ $(CPPFLAGS)
cal.o : cal.c 
	$(CXX) -c $^ $(CPPFLAGS)
stack.o: stack.c
	$(CXX) -c $^ $(CPPFLAGS)

client :client.o
	$(CXX) -o client client.o -pthread
client.o: client.cpp
	$(CXX) -c client.cpp -std=c++11

.PHONY : clean
clean:
	-rm cal.o  stack.o server.o client.o client server
