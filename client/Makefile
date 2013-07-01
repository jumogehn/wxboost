
all:
	g++ -g -o mychat \
	  my_text_ctrl.cpp \
	  my_panel.cpp \
	  my_frame.cpp \
	  my_chat.cpp \
	  -I../include \
	  -I/home/hum/local/include \
	  -I/usr/lib/x86_64-linux-gnu/wx/include/gtk2-unicode-release-2.8 \
	  -I/usr/include/wx-2.8 \
	  -D_FILE_OFFSET_BITS=64 \
	  -D_LARGE_FILES \
	  -D__WXGTK__ \
	  -pthread \
	  -L/usr/lib/x86_64-linux-gnu \
	  -Wl,-Bsymbolic-functions \
	  -Wl,-z,relro \
	  -lwx_gtk2u_core-2.8 \
	  -lwx_baseu-2.8 \
	  /home/hum/local/lib/libboost_system.a \
	  /home/hum/local/lib/libboost_thread.a \
	  -lpthread \
	  -lrt

clean:
	rm -rf mychat
