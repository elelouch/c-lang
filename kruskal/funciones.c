#include "kruskal.h"

/* La idea sera unir componentes conexos formando un arbol abarcador.
 * Cada vertice sera un componente conexo por si mismo al comienzo del algoritmo.
 * Para construir componentes conexos mas grandes, se examinan las aristas a partir del conjunto A
 * en orden creciente a partir de los costos (cola prioridad). Si la arista conecta dos vertices que
 * pertenecen a componentes disconexos entonces se agregara la arista en el arbol abarcador T.
 * Se descartara la arista si la misma conecta dos vertices de un mismo componente. */

/*COMBINA (A,B,C) se utiliza para combinar los componentes conexos A y B en el componente C.
 *Hace la union entre A y B en C suponiendo que A y B son disjuntos
 *
 *ENCUENTRA(v,C) retorna el nombre del componente conexo de C, del cual el vertice v es miembro.
 *Esta operacion se utilizara para determinar si dos vertices son del mismo o de distintos componentes.
 *
 *INICIAL(A,v,C) para que A sea el nombre de un componente que pertenece a C y que inicialmente contiene
 *al vertice v
 * */

void inserta(vertice v1,vertice v2, int nuevo_costo, arista **cola){//agrega una arista a la cola
    arista *nueva_arista = malloc(sizeof(arista));
    nueva_arista -> vertice_u = v1;
    nueva_arista -> vertice_v = v2;
    nueva_arista -> costo = nuevo_costo;
    nueva_arista -> sig = NULL;

    if(!*cola){
        *cola = nueva_arista;
        return;
    }
    nueva_arista->sig = *cola;
    *cola = nueva_arista;
}

arista *sacar_min(arista **cola){
    int min;
    arista *pivot;
    arista *menor_arista;
    if(!*cola){ // si la cola esta vacia
        printf("No hay aristas disponibles\n");
        return NULL;
    }
    //inicializo
    menor_arista = *cola;
    min = menor_arista -> costo;
    pivot = menor_arista;

    //encuentro la menor arista
    while(pivot){
        if(pivot->costo < min){
            menor_arista = pivot;
            min = menor_arista->costo;
        }
        pivot = pivot->sig;
    }

    if(*cola == menor_arista){ // si la primer arista de la cola es la menor, apunto la cabeza de la cola al siguiente elemento
        *cola = menor_arista->sig;
        return menor_arista;
    }
    // encuentro la arista previa a la menor, vuelvo a atravesar la cola
    pivot = *cola;
    while(pivot->sig != menor_arista)
        pivot = pivot->sig;

    pivot->sig = pivot->sig->sig; //apunto a la arista previa con la siguiente de la siguiente
    return menor_arista;
}

void inicial(tipo_nombre a, conjunto_CE *ce){// nombre de un componente que pertenece al conjunto ce que inicialmente tiene al vertice tipo_elemento
    ce->nombres[a].nombre_conjunto = a;
    ce->nombres[a].siguiente_elemento = NIL;     // no posee siguiente elemento
    ce->encabezamientos[a].primer_elemento = a;// el primer elemento de un componente conexo es el mismo
    ce->encabezamientos[a].cuenta = 1;         // cada elemento comienza con
}

void combina(tipo_nombre a, tipo_nombre b,conjunto_CE *ce){ // a y b son los conjuntos
    int i;
    if(ce->encabezamientos[a].cuenta >  ce->encabezamientos[b].cuenta){ //si A es el conjunto mas grande, combinar B en A
        i = ce->encabezamientos[b].primer_elemento; // primer elemento del conjunto B
        while(ce->nombres[i].siguiente_elemento != NIL){
            ce->nombres[i].nombre_conjunto = a; // nombre del conjunto que contiene a i pasa a ser a
            i = ce->nombres[i].siguiente_elemento;
        }
        // i ahora es igual al ultimo elemento del conjunto B (ahora unido con A)
        ce->nombres[i].nombre_conjunto = a;
        ce->nombres[i].siguiente_elemento = ce->encabezamientos[a].primer_elemento;
        ce->encabezamientos[a].primer_elemento = ce->encabezamientos[b].primer_elemento;
        ce->encabezamientos[a].cuenta += ce->encabezamientos[b].cuenta;

        ce->encabezamientos[b].cuenta = 0;

    }else{
        i = ce->encabezamientos[a].primer_elemento;
        while(ce->nombres[i].siguiente_elemento != NIL){
            ce->nombres[i].nombre_conjunto = a; // nombre del conjunto que contiene a i pasa a ser a
            i = ce->nombres[i].siguiente_elemento;
        }

        // i ahora es igual al ultimo elemento del conjunto A (ahora unido con B)
        ce->nombres[i].nombre_conjunto = b;
        ce->nombres[i].siguiente_elemento = ce->encabezamientos[b].primer_elemento;
        ce->encabezamientos[b].primer_elemento = ce->encabezamientos[a].primer_elemento;
        ce->encabezamientos[b].cuenta += ce->encabezamientos[a].cuenta;

        ce->encabezamientos[a].cuenta = 0;
    }
}
void lista(arista *cola){
    if(!cola){
        printf("\n");
        return;
    }
    printf("(%d-%d,%d) | ",cola->vertice_u, cola->vertice_v, cola->costo);
    lista(cola->sig);
}

tipo_nombre encuentra(vertice v1,conjunto_CE* ce){
    return ce->nombres[v1].nombre_conjunto;
}

void kruskal(arista **cola){
    int numero_componentes = VERTICES, i;
    arista *arbol = NULL, *menor_arista;
    conjunto_CE combina_encuentra;
    vertice v1,v2;
    tipo_nombre componente1,componente2;

    if(!*cola){
        printf("No hay lados disponibles\n");
        return;
    }

    for(i = 0; i < VERTICES;i++)
        inicial(i,&combina_encuentra); //incializo el conjunto combina-encuentra

    while(numero_componentes > 1){
        menor_arista = sacar_min(cola);
        v1 = menor_arista -> vertice_u; // vertice de cada arista
        v2 = menor_arista -> vertice_v;
        componente1 = encuentra(v1,&combina_encuentra);
        componente2 = encuentra(v2,&combina_encuentra);
        if(componente1 != componente2){ // si las componentes son disconexas, entonces
            combina(v1,v2,&combina_encuentra); // combino las componentes
            menor_arista->sig = arbol; // agrego la arista al arbol abarcador de menor costo
            arbol = menor_arista;
            numero_componentes--; // una componente seguro fue combinada con otra si la arista juntaba dos componentes disconexas, por eso tengo una menos
        }else{
            if(menor_arista)
                free(menor_arista); // descarto la arista si estuvo en un primer momento
        }
    }
    lista(arbol);
}
