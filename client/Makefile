
all:
	g++ -o mychat \
	  my_text_ctrl.cpp \
	  my_panel.cpp \
	  my_frame.cpp \
	  my_chat.cpp \
	  -I../include \
	  -I/home/hum/local/include \
	  `wx-config --cxxflags` \
	  `wx-config --libs` \
	  /home/hum/local/lib/libboost_system.a \
	  /home/hum/local/lib/libboost_thread.a \
	  -lpthread \
	  -lrt

clean:
	rm -rf mychat

