all:
	gcc -o semaforo semaforoMain.c -lpthread
	gcc -o monitor monitorMain.c -lpthread
