#include "objects.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_LEFT_U, KEY_RIGHT, KEY_RIGHT_U, KEY_EXIT, KEY_SPACE, KEY_SPACE_U, KEY_S, KEY_S_U, KEY_A
};

void error(const char *msg) {
	perror(msg);
	exit(0);
}

int get_network_data(int sockfd, char *buffer, int *s, int *k) {
	int n;
	char *key, *status;
	// Me fijo si llegó via red
	memset((void *) buffer, '\0', 1024);
	n = recv(sockfd,buffer,1023,MSG_DONTWAIT);
	//DBG - printf("Buffer: %s / n: %d",buffer,n);

	if(n>0) {
		key = strtok(buffer,";");
		status = strtok(NULL,";");
		//DBG -printf("1 - key: %s / status: %s\n",key,status);

		if(!strcmp(status,"TRUE")) {
			*s=1;
		} else if(!strcmp(status,"FALSE")) {
			*s=0;
		} else {
			printf("Error recepción *s. Buffer: %s\n",buffer);
			n = write(sockfd,"ERROR",5);
			if (n < 0) {
				error("ERROR writing to socket");
			}
			return 0;
		}

		if(!strcmp(key,"KEY_UP")) {
			*k=KEY_UP;
		}
		else if(!strcmp(key,"KEY_DOWN")) {
			*k=KEY_DOWN;
		}
		else if(!strcmp(key,"KEY_LEFT")) {
			*k=KEY_LEFT;
		}
		else if(!strcmp(key,"KEY_LEFT_U")) {
			*k=KEY_LEFT_U;
		}
		else if(!strcmp(key,"KEY_RIGHT")) {
			*k=KEY_RIGHT;
		}
		else if(!strcmp(key,"KEY_RIGHT_U")) {
			*k=KEY_RIGHT_U;
		}
		else if(!strcmp(key,"KEY_EXIT")) {
			*k=KEY_EXIT;
		}
		else if(!strcmp(key,"KEY_SPACE")) {
			*k=KEY_SPACE;
		}
		else if(!strcmp(key,"KEY_SPACE_U")) {
			*k=KEY_SPACE_U;
		}
		else if(!strcmp(key,"KEY_S")) {
			*k=KEY_S;
		}
		else if(!strcmp(key,"KEY_S_U")) {
			*k=KEY_S_U;
		}
		else if(!strcmp(key,"KEY_A")) {
			*k=KEY_A;
		}
		else {
			printf("Error recepción *k. Buffer: %s\n",buffer);
			n = write(sockfd,"ERROR",5);
			if (n < 0) {
				error("ERROR writing to socket");
			}
			return 0;
		}

		// Data saved (s+k), can return
		// DBG - printf("2 - key: %d / status: %d\n",*k,*s);
		n = write(sockfd,"CORRECTO",8);
		if (n < 0) {
			error("ERROR writing to socket");
		}
		return 1;

	} else {
		return 0;
	}
}

void InitServer(CFG *config, ALLEGRO_FONT	*font, int *sockfd, int *newsockfd) {
	/**Variables de Server TCP*/
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	/** Inicializacion Server TCP*/
	// Inicializo sockets
	*sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (*sockfd < 0) {
		error("ERROR opening socket");
	}
	// Armando la estructura "sockaddr_in"
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PUERTO);
	memset((void *) &(serv_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura

	if (bind(*sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}

	listen(*sockfd,5);
	clilen = sizeof(cli_addr);
	printf("Esperando jugador en red...\n");
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_textf(font, al_map_rgb(255, 255, 255), config->SCREEN_W/2, config->SCREEN_H/2, 1, "Esperando jugador en red...");
	al_flip_display();
	// Llamado bloqueante a accept()
	*newsockfd = accept(*sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (*newsockfd < 0) {
		error("ERROR on accept");
	}
	printf("Conexion jugador aceptada!\n");
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_textf(font, al_map_rgb(255, 255, 255), config->SCREEN_W/2, config->SCREEN_H/2, 1, "Conexion aceptada!");
	al_flip_display();
	al_rest(0.2);
	/** Fin Server TCP*/
}
