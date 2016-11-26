#include "objects.h"
#include "prototypes.h"

int agregarDatos (Lista **p, Score *jugador) {

	Lista *act, *aux, *ant;
	aux = (Lista *) malloc(sizeof(Lista));
	if (!aux) return -1;
	if (!jugador) return -1;

	aux->dato = (Score *)jugador;

	if (!*p) { // Si no existe la lista
		*p = aux;
		aux->sig = NULL;
		aux->ant = NULL;
		return 0;
	}

	act = *p;
	ant = act->ant;

	// Buscamos al ultimo elemento o hasta encontrar uno con dato menor (agrega nodos ordenadamente, de mayor a menor)
	while(act->sig && (((Score *)act->dato)->puntos > ((Score *)aux->dato)->puntos)) {
		ant = act;
		act = act->sig;
	}

	if ((((Score *)act->dato)->puntos >= ((Score *)aux->dato)->puntos)) { // Si el dato es mayor o igual que el nuevo dato (el aux) (lo ingreso como siguiente)
		if (!act->sig) { // Si estamos en el ultimo nodo
			act->sig = aux;
			aux->ant = act;
			aux->sig = NULL;
		}
		else {
			(act->sig)->ant = aux;
			aux->sig = act->sig;
			act->sig = aux;
			aux->ant = act;
		}
		return 0;
	}

	if ((((Score *)act->dato)->puntos < ((Score *)aux->dato)->puntos)) { // Idem anterior pero cuando es menor (lo ingreso como anterior)
		if (*p == act) { // Si estamos en el primer nodo
			*p = aux;
			aux->sig = act;
			aux->ant = NULL;
			act->ant = aux;
		}
		else {
			ant->sig = aux;
			aux->ant = ant;
			act->ant = aux;
			aux->sig = act;
		}
		return 0;
	}
	return 0;
}

void imprimirDatos(Lista **p, ALLEGRO_FONT *font, CFG *config) {
	int i = 1;
	Lista *aux;
	aux = *p;

	if (!*p) { // Si no existe la lista
	}
	else if (!aux->dato) { // si la lista esta vacia
	}
	else {
		while(aux && i < 11) { // Mientras exista (i < 11 es la cantidad de scores a imprimir)
			al_draw_textf(font, al_map_rgb(255, 255, 255), config->SCREEN_W/12, config->font*i + config->SCREEN_H/4, ALLEGRO_ALIGN_LEFT, "%d°\t", i);
			al_draw_textf(font, al_map_rgb(255, 255, 255), config->SCREEN_W/9, config->font*i + config->SCREEN_H/4, ALLEGRO_ALIGN_LEFT, ": %s", ((Score *)aux->dato)->nombre);
			al_draw_textf(font, al_map_rgb(255, 255, 255), config->SCREEN_W/4, config->font*i + config->SCREEN_H/4, ALLEGRO_ALIGN_RIGHT, "%d\tpts", ((Score *)aux->dato)->puntos);
			aux = aux->sig;
			i++;
		}
	}
}

void eliminarDatos(Lista **p) {
	Lista *aux;
	if(!*p) { // Si no existe la lista
		return;
	}
	aux = *p;
	while (aux->sig) { // Mientras exista el siguiente
		*p = aux->sig;
		free((Score *)aux->dato);
		free(aux);
		aux = *p;
		aux->ant = NULL;
	}
	*p = NULL;
	free((Score *)aux->dato);
	free(aux);
}

int cargarDatos(Lista **p) {
	Score *jugador;
	int x;
	jugador = (Score *) malloc (sizeof(Score));
	if (!jugador) return -1;
	FILE *file = fopen("./assets/highscores.txt", "r");
	if (!file) return -1;
	rewind(file);
	fscanf(file, "%d - %s", &jugador->puntos, jugador->nombre);
	while (!feof(file) && jugador->nombre) {
		x = agregarDatos(p, jugador);
		if (x) return -1;
		jugador = (Score *) malloc (sizeof(Score));
		if (!jugador) return -1;
		fscanf(file, "%d - %s", &jugador->puntos, jugador->nombre);
	}
	free(jugador);
	fclose(file);
	return 0;
}

int guardarDatos(Lista **p) {
	Lista *aux;
	aux = *p;
	FILE *file = fopen("./assets/highscores.txt", "w");
	if (!file) return -1;
	rewind(file);
	while (aux) { // Mientras exista el nodo
		fprintf(file, "%d - %s\n", ((Score *)aux->dato)->puntos, ((Score *)aux->dato)->nombre);
		aux = aux->sig;
	}
	fclose(file);
	return 0;
}
