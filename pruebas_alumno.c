#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include "heap.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
int strcmp_heap(const void *a, const void *b) {
	return strcmp(a, b);
}

int intcmp_heap(const void *a, const void *b) {
    const int *x = a;
    const int *y = b;

    if (*x < *y)
        return -1;
    return *x > *y;
}
 
void heap_vacio(){
	printf("\n PRUEBAS HEAP VACIO \n");
	heap_t* heap = heap_crear(strcmp_heap);
	print_test("Se creo heap", heap_esta_vacio(heap) == true);
	print_test("Ver maximo es NULL", heap_ver_max(heap) == NULL);
	print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
	print_test("Desencolo devuelve NULL", heap_desencolar(heap) == NULL);
	print_test("No se puede encolar el elemento NULL", heap_encolar(heap, NULL) == false);
	heap_destruir(heap, NULL);
}
 
void heap_encolar_desencolar(){
	printf("\n PRUEBAS HEAP ENCOLAR Y DESENCOLAR \n");
	heap_t* heap = heap_crear(strcmp_heap);
	print_test("Se creo heap", heap_esta_vacio(heap) == true);
	void* clave = "sol";
	void* clave2 = "luna";
	void* clave3 = "aire";
	print_test("Encolo primer clave", heap_encolar(heap, clave));
	print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
	print_test("Heap esta vacio es false", heap_esta_vacio(heap) == false);
	print_test("Heap ver maximo es igual a la clave", heap_ver_max(heap) == clave);
	print_test("Heap desencolar devuelve la clave", heap_desencolar(heap) == clave);
	print_test("Heap esta vacio es true", heap_esta_vacio(heap) == true);
	print_test("Encolo clave2", heap_encolar(heap, clave2));
	print_test("Heap esta vacio es false", heap_esta_vacio(heap) == false);
	print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
	print_test("Heap ver maximo es igual a la clave2", heap_ver_max(heap) == clave2);
	print_test("Encolo clave3", heap_encolar(heap, clave3));
	print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
	print_test("Heap desencolar devuelve el maximo", heap_desencolar(heap) == clave2);
	heap_destruir(heap, NULL);
}
 
void heap_volumen(size_t n){
	printf("\n PRUEBAS HEAP VOLUMEN CON %ld ELEMENTOS\n",n);
	heap_t* heap = heap_crear(intcmp_heap);
	print_test("Se creo el heap", heap);
	int* arreglo = malloc(sizeof(int)*n);
	if(!arreglo){
		printf("Hubo un problema al crear el arreglo para la prueba\n");
		return;
	}
	bool ok = true;
	for(int i = 0 ; i < n ; i++){
		arreglo[i] = i;
		if(heap_encolar(heap, arreglo + i) == false){
			ok = false;
		}
		if(*(int*)heap_ver_max(heap) != i){
			ok = false;
		}  
	}
	print_test("Se encolaron una gran cantidad de elementos correctamente", ok);
	for(size_t i = n - 1 ; i > 0; i--){
		if(*(int*)heap_desencolar(heap) != i){
			ok = false;
		}
		if((*(int*)heap_ver_max(heap) != i - 1) && (i != 0)){
			ok = false;
		}    
	}
	print_test("Se desencolaron una gran cantidad de elementos correctamente", ok);
	heap_destruir(heap,NULL);
	free(arreglo);
}
 
void heap_arr(){
	printf("\n PRUEBAS HEAP ARR \n");
	void* arreglo[7] = {"agua", "fuego", "aire", "tierra", "hielo", "metal", "rayo"};
	heap_t *heap = heap_crear_arr(arreglo, 7, strcmp_heap);
	print_test("Se creo el heap", heap);
	print_test("Heap ver max es tierra", heap_ver_max(heap) == arreglo[3]);
	print_test("Prueba heap la cantidad de elementos es 7", heap_cantidad(heap) == 7);
	heap_destruir(heap, NULL);
}

void heapsort(){
	printf("\n PRUEBAS HEAP SORT \n");
	int uno = 1, dos = 2, once = 11, diez = 10, cien = 100, cuarenta = 40, cincuenta = 50, veinticinco = 25, nueve = 9, catorce = 14;
	bool ok = true;
	size_t longitud = 10;
	void* arreglo[10] = {&uno, &dos, &once, &diez, &cien, &cuarenta, &cincuenta, &veinticinco, &nueve, &catorce};
	heap_sort(arreglo, longitud, strcmp_heap);
	int* anterior = arreglo[0];
	int* actual;
	for(int i = 0; i < 10; i++){
		actual = arreglo[i]	;	
		if(*actual < *anterior){			
			ok = false;
		 	break;

		}
		anterior = actual;
	}
	print_test("Los numeros se ordenaron correctamente", ok);
}

void heapsort_volumen(size_t n){
	printf("\n PRUEBAS HEAP SORT ORDENANDO UN ARREGLO DE N NUMEROS \n");
	int* numeros = malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++){
		numeros[i] = i;
	}
	void** arreglo = malloc(sizeof(void*)*n);
	if(!arreglo){
		printf("Hubo un problema en la creacion del arreglo para la prueba\n");
		return;
	}
	for(int i = 0 ; i < n ; i++){
		arreglo[i] = &numeros[n - i - 1];
	}
	bool ok = true;
	size_t longitud = n;
	heap_sort(arreglo, longitud, intcmp_heap);
	int* anterior = arreglo[0];
	int* actual;
	for(int i = 0; i < n; i++){
		actual = arreglo[i]	;	
		if(*actual < *anterior){			
			ok = false;
		 	break;

		}
		anterior = actual;
	}
	print_test("Los n numeros se ordenaron correctamente", ok);
	free(arreglo);
	free(numeros);

}
 
void pruebas_heap_alumno(){
	heap_vacio();
	heap_encolar_desencolar();
	heap_arr();
	heapsort();
	heap_volumen(1000);
	heapsort_volumen(1000);
}
	print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
	print_test("Heap desencolar devuelve el maximo", heap_desencolar(heap) == clave2);
	heap_destruir(heap, NULL);
}
 
void heap_volumen(int volumen){
	printf("\n PRUEBAS HEAP VOLUMEN CON %d ELEMENTOS\n",volumen);
	heap_t* heap = heap_crear(intcmp_heap);
	print_test("Se creo el heap", heap);
	int arreglo[volumen];
	bool ok = true;
	for(int i = 0 ; i < volumen ; i++){
		arreglo[i] = i;
		if(heap_encolar(heap, arreglo + i) == false){
			ok = false;
		}
		if(*(int*)heap_ver_max(heap) != i){
			ok = false;
		}  
	}
	print_test("Se encolaron una gran cantidad de elementos correctamente", ok);
	for(int i = volumen - 1 ; i > 0; i--){
		if(*(int*)heap_desencolar(heap) != i){
			ok = false;
		}
		if((*(int*)heap_ver_max(heap) != i - 1) && (i != 0)){
			ok = false;
		}    
	}
	print_test("Se desencolaron una gran cantidad de elementos correctamente", ok);
	heap_destruir(heap,NULL);
}
 
void heap_arr(){
	printf("\n PRUEBAS HEAP ARR \n");
	void* arreglo[7] = {"agua", "fuego", "aire", "tierra", "hielo", "metal", "rayo"};
	heap_t *heap = heap_crear_arr(arreglo, 7, strcmp_heap);
	print_test("Se creo el heap", heap);
	print_test("Heap ver max es tierra", heap_ver_max(heap) == arreglo[3]);
	print_test("Prueba heap la cantidad de elementos es 7", heap_cantidad(heap) == 7);
	heap_destruir(heap, NULL);
}

void heapsort(){
	printf("\n PRUEBAS HEAP SORT \n");
	int uno = 1, dos = 2, once = 11, diez = 10, cien = 100, cuarenta = 40, cincuenta = 50, veinticinco = 25, nueve = 9, catorce = 14;
	bool ok = true;
	size_t longitud = 10;
	void* arreglo[10] = {&uno, &dos, &once, &diez, &cien, &cuarenta, &cincuenta, &veinticinco, &nueve, &catorce};
	heap_sort(arreglo, longitud, strcmp_heap);
	int* anterior = arreglo[0];
	int* actual;
	for(int i = 0; i < 10; i++){
		actual = arreglo[i]	;	
		if(*actual < *anterior){			
			ok = false;
		 	break;

		}
		anterior = actual;
	}
	print_test("Los numeros se ordenaron correctamente", ok);
}

void heapsort_volumen(int n){
	printf("\n PRUEBAS HEAP SORT ORDENANDO UN ARREGLO DE N NUMEROS \n");
	int* numeros = malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++){
		numeros[n] = i;
	}
	void** arreglo = malloc(sizeof(int*)*n);
	if(!arreglo){
		printf("Hubo un problema en la creacion del arreglo para la prueba\n");
		return;
	}
	for(int i = 0 ; i < n ; i++){
		arreglo[i] = &numeros[n - i];
	}
	bool ok = true;
	size_t longitud = n;
	heap_sort(arreglo, longitud, intcmp_heap);
	int* anterior = arreglo[0];
	int* actual;
	for(int i = 0; i < n; i++){
		actual = arreglo[i]	;	
		if(*actual < *anterior){			
			ok = false;
		 	break;

		}
		anterior = actual;
	}
	print_test("Los n numeros se ordenaron correctamente", ok);
	free(arreglo);
	free(numeros);

}
 
void pruebas_heap_alumno(){
	heap_vacio();
	heap_encolar_desencolar();
	heap_arr();
	heapsort();
	heap_volumen(1000);
	heapsort_volumen(1000);
}
