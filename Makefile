default:
	gcc `pkg-config --cflags gtk+-3.0` -o oh-my-corners main.c my_view.c `pkg-config --libs gtk+-3.0`
