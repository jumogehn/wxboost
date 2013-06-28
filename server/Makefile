
all:
	g++ -o chat_server \
	  chat_server.cpp \
	  -I../include \
	  -I/home/hum/local/include \
	  /home/hum/local/lib/libboost_system.a \
	  /home/hum/local/lib/libboost_thread.a \
	  -lpthread \
	  -lrt

clean:
	rm -rf chat_server

