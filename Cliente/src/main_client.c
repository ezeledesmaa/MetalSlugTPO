// ./Client "ip del server"
#include "header.h"

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_S, KEY_A
};

void error(const char *msg) {
	perror(msg);
	exit(0);
}

const float FPS = 50;
const int SCREEN_W = 640;
const int SCREEN_H = 410;

int main(int argc, char **argv) {
	/**Variables de Allegro*/
	ALLEGRO_DISPLAY			*display			= NULL;
	ALLEGRO_EVENT_QUEUE	*event_queue	= NULL;
	ALLEGRO_TIMER				*timer				= NULL;
	ALLEGRO_BITMAP			*aImage				= NULL;
	ALLEGRO_BITMAP			*sImage				= NULL;
	ALLEGRO_BITMAP			*escImage			= NULL;
	ALLEGRO_BITMAP			*spaceImage		= NULL;
	ALLEGRO_BITMAP			*arrowImage		= NULL;

	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	/**Variables de Server TCP*/
	int sended = 0;
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[1024];
	char buffer2[1024];
	/**Inicializacion Server TCP*/
	if (argc < 2) {
		fprintf(stderr,"usage %s hostname\n", argv[0]);
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		error("ERROR opening socket");
	}
	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	memset((void *) &serv_addr, '\0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(PUERTO);

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		error("ERROR connecting");
	}

	/**Inicialiación y configuración Allegro*/
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "Error al iniciar al_init_image_addon!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
	al_set_window_title(display, "Cliente - Metal Slug - TPO - R1021 - GRUPO 2 - 2016");	// Titulo del display


	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	aImage = al_load_bitmap("./assets/a.png");
	if(!aImage) {
		fprintf(stderr, "failed to create aImage!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	sImage = al_load_bitmap("./assets/s.png");
	if(!sImage) {
		fprintf(stderr, "failed to create sImage!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(aImage);
		return -1;
	}

	escImage = al_load_bitmap("./assets/esc.png");
	if(!escImage) {
		fprintf(stderr, "failed to create escImage!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(aImage);
		al_destroy_bitmap(sImage);
		return -1;
	}

	spaceImage = al_load_bitmap("./assets/space.png");
	if(!spaceImage) {
		fprintf(stderr, "failed to create spaceImage!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(aImage);
		al_destroy_bitmap(sImage);
		al_destroy_bitmap(escImage);
		return -1;
	}

	arrowImage = al_load_bitmap("./assets/arrow.png");
	if(!arrowImage) {
		fprintf(stderr, "failed to create arrowImage!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(aImage);
		al_destroy_bitmap(sImage);
		al_destroy_bitmap(escImage);
		al_destroy_bitmap(spaceImage);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);

	///Esperar que el server nos indique que podemos empezar///
	printf("Esperando al server\n");
	memset((void *) buffer2, '\0', 1024);
	n = read(sockfd, buffer2, 1023);
	if (n < 0) {
		error("ERROR reading from socket");
	}
	if (!strcmp(buffer2,"START")) {
		doexit = 0;
	}
	else if (!strcmp(buffer2,"EXIT")) {
		doexit = 1;
	}
	///Fin///

	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (sended) {
			memset((void *) buffer2, '\0', 1024);
			n = read(sockfd, buffer2, 1023);
			if (n < 0) {
				error("ERROR reading from socket");
			}
			if (!strcmp(buffer2,"ERROR")) {
				n = write(sockfd,buffer,strlen(buffer));
				if (n < 0) {
					error("ERROR writing to socket");
				}
			}
			else if (!strcmp(buffer2,"CORRECTO")) {
				sended = 0;
			}
			else {
				// DEBUG - printf("Buffer incorrecto\n");
				sended = 0;
			}
			// DEBUG - printf("Mensaje del server: %s\n",buffer);
		}

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			doexit = true;
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN && !sended) {
			switch(ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = true;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_LEFT;TRUE"); buffer[13] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_RIGHT;TRUE"); buffer[14] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = true;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_SPACE;TRUE"); buffer[14] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_S:
			key[KEY_S] = true;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_S;TRUE"); buffer[10] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_A:
			key[KEY_A] = true;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_A;TRUE"); buffer[10] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {


			case ALLEGRO_KEY_LEFT:
			key[KEY_LEFT] = false;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_LEFT;FALSE"); buffer[14] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = false;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_RIGHT;FALSE"); buffer[15] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_ESCAPE:
			doexit = true;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_EXIT;FALSE"); buffer[15] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = false;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_SPACE;FALSE"); buffer[16] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_S:
			key[KEY_S] = false;
			memset((void *) buffer, '\0', 1024);
			strcpy(buffer,"KEY_S;FALSE"); buffer[12] = '\0';
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) error("ERROR writing to socket");
			sended = 1;
			break;

			case ALLEGRO_KEY_A:
			key[KEY_A] = false;
			break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_bitmap(escImage, 5, 5, 0);
			al_draw_bitmap(arrowImage, 305, 155, 0);
			al_draw_bitmap(arrowImage, 405, 155, 0);
			al_draw_bitmap(spaceImage, 5, 305, 0);
			al_draw_bitmap(aImage, 5, 155, 0);
			al_draw_bitmap(sImage, 105, 155, 0);
			if(key[KEY_LEFT]) {
				al_draw_tinted_bitmap(arrowImage, al_map_rgba_f(1,0.5, 0.5, 1), 305, 155, 0);
			}
			if(key[KEY_RIGHT]) {
				al_draw_tinted_bitmap(arrowImage, al_map_rgba_f(1,0.5, 0.5, 1), 405, 155, 0);
			}
			if(key[KEY_SPACE]) {
				al_draw_tinted_bitmap(spaceImage, al_map_rgba_f(1,0.5, 0.5, 1), 5, 305, 0);
			}
			if(key[KEY_A]) {
				al_draw_tinted_bitmap(aImage, al_map_rgba_f(1,0.5, 0.5, 1), 5, 155, 0);
			}
			if(key[KEY_S]) {
				al_draw_tinted_bitmap(sImage, al_map_rgba_f(1,0.5, 0.5, 1), 105, 155, 0);
			}
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(aImage);
	al_destroy_bitmap(sImage);
	al_destroy_bitmap(escImage);
	al_destroy_bitmap(spaceImage);
	al_destroy_bitmap(arrowImage);
	close(sockfd);
	return 0;
}

