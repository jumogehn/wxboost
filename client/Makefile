
all:
	g++ -o chat_client \
	  chat_client.cpp \
	  -I../include \
	  -I/home/hum/local/include \
	  /home/hum/local/lib/libboost_system.a \
	  /home/hum/local/lib/libboost_thread.a \
	  -lpthread \
	  -lrt

clean:
	rm -rf chat_client 

