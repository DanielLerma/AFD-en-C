#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *crearAlfa(){
	char *alfa = (char*) malloc(100 * sizeof(char));
	int contComas = 0;
	printf("Ingresa tu alfabeto separado de comas, sin espacios (a,b,c...):\n");
  scanf("%s", alfa);
	fflush(stdin);

	for (int j = 0; j < strlen(alfa); j++){
		if(alfa[j] == ',' ){
			contComas++;
		}
	}

	char *newAlfa = (char*) malloc(sizeof(char) * (contComas + 1));

	int k = 0;
	for (int i = 0; i < strlen(alfa); i++){
		if((int)alfa[i] != 44){//código ascii de la coma
			newAlfa[k] = alfa[i];
			k++;
		}
	}

	int j = 0;
	while(newAlfa[j] != '\0'){
		//("%c", newAlfa[j]);
		j++;
	}
	//("\nnewAlfa: %s", newAlfa);
	return newAlfa;
}

int *estFinales(char *str, int lenFin, int stLen){
  int *intFin = (int*) malloc(lenFin * sizeof(int));
  int newI = 0;
  for (int i = 0; i < stLen; i++){
    //printf("finales en %d: %d\n", i, str[i]);
    if((int)str[i] > 47 && (int)str[i] <= 57){
      intFin[newI] = (int)str[i] - 48;
      //printf("intFin: %d\n", intFin[newI]);
      //("finales: %d\n", finales[k]);
      newI++;
      
    }
  }
  return intFin;
}

char *crearEstados(){
	char *strEstados = (char*) malloc(sizeof(char) * 100);
	printf("\nIngresa tus estados separados por comas, sin espacios (q0,q1,q2...):\n");
	//gets(strEstados);
  scanf("%s", strEstados);

	return strEstados;
}

int *intEstados(char *strEstados){
	int contComas = 0;
	for (int i = 0; i < strlen(strEstados); i++){
		if(strEstados[i] == ',')
			contComas++;
	}

	int *estados = (int*) malloc(sizeof(int) * contComas + 1);
	int k = 0;
		for (int i = 0; i < contComas + 1; i++){
		estados[i] = i;
	}

	printf("\nEstos son tus estados:\n");
	for (int i = 0; i < contComas + 1; i++){
		printf("%d ", estados[i]);
	}
  printf("\n");
	return estados;
}

int **crearMat(char *alfa, int *estados, int numLetras, int numEstados){
	int **matTrans = (int**) malloc(1 * sizeof(int*));
  char *text = (char*) malloc(2 * sizeof(char));
	for (int i = 0; i < numLetras; i++){
		matTrans[i] = (int*) malloc(2 * sizeof(int));
		for (int j = 0; j < numEstados; j++){
      printf("Ingresa la transición de: d(q%d, %c) = ", estados[j], alfa[i]);
      getchar();
      scanf("%s", text);
      matTrans[i][j] = atoi(&text[1]);
		}
	}
	return matTrans;
}

char *ingresarPalabra(){
  char *word = (char*) malloc(sizeof(char) * 100);
  
  scanf("%s", word);
  printf("Tu palabra es: %s\n", word);
  return word;
}

int funcTrans(int **mat, char* w, int* estados, char* alfa, int* intAlfa, int estado, int z, int contW, int est2, int posEst){
  
  if(contW == strlen(w))
    return estado;
  if(w[contW] == alfa[z]){//baa
    posEst = estados[est2];
    estado = mat[intAlfa[z]][estados[est2]];
    est2 = estado;
    contW++;
    return(funcTrans(mat, w,  estados, alfa, intAlfa, estado, z, contW, est2, posEst));
  }
  if (w[contW] > alfa[z]){
    //printf("posición en palabra es > que alfa.\n");
    z++;
    return(funcTrans(mat, w,  estados, alfa, intAlfa, estado, z, contW, est2, posEst));
  }
  else if(w[contW] < alfa[z]){
    //printf("posición en palabra es < que alfa.\n");
    z--;
    return(funcTrans(mat, w,  estados, alfa, intAlfa, estado, z, contW, est2, posEst));
  }
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
  
	char* alfa = crearAlfa();
	//printf("\nalfa en main: %s\n", alfa);
	int numLetras = strlen(alfa);
	//printf("\nnumLetras: %d\n", numLetras);
  int *intAlfa = (int*) malloc(sizeof(int) * strlen(alfa) - 1);
  for (int i = 0; i < strlen(alfa); i++){
    intAlfa[i] = i;
  }

  /*for (int i = 0; i < strlen(alfa); i++){
    printf("%d ", intAlfa[i]);
  }*/
	
  char *strEstados = crearEstados();
	int numEstados = 0;
	for (int i = 0; i < strlen(strEstados); i++){
		if(strEstados[i] == ',')
			numEstados++;
	}

	numEstados++;
	//printf("\nnumEstados: %d", numEstados);
	int *estados = intEstados(strEstados);

  char *strFinales = (char*) malloc(sizeof(char) * 100);
  printf("Escribe los estados finales, separados por comas y sin espacios:\n");
  scanf("%s", strFinales);
  int q_s = 0;
  for (int i = 0; i < strlen(strFinales); i++){
    if ((int)strFinales[i] == 113){
      q_s++;
    }
   // printf("estados en i: %c\n", estados[i]);
  }
  //printf("q_s: %d\n", q_s);
  int *finales = estFinales(strFinales, q_s, strlen(strFinales));
  //printf("Finales:\n");
  /*for (int i = 0; i < q_s; i++){
    printf("%d ", finales[i]);
  }*/

  printf("\n");
  int **matTrans = crearMat(alfa, estados, numLetras, numEstados);
  //char *word = ingresarPalabra();
  int posX = 0, est = 0, posY = 0, posAlfa = 0, contW = 0, est2 = 0, posEst = 0;
  char *palabra = (char*) malloc(sizeof(char) * 100);
  int respuesta = 1;
  int es = 0;
  
  while(respuesta != 0){
    es = 0;
    printf("Ingresa tu palabra: ");
    palabra = ingresarPalabra();
    for (int i = 0; i < strlen(palabra); i++){
      for (int j = 0; j < strlen(alfa); j++){
        if(palabra[i] == alfa[j])
          es++;
      }
    }
    //printf("es: %d\n", es);
    if(es == strlen(palabra)){
        int res = funcTrans(matTrans, palabra, estados, alfa, intAlfa, est, posAlfa, contW, est2, posEst);
        //printf("res: %d\n", res);
        int res2 = 0;
        for (int i = 0; i < q_s; i++){
          if (res == finales[i]){
            res2 = 1;
            printf("Palabra aceptada\n");
            break;
          }
        
        
        /*  if(res2 <= q_s || res2 >= q_s){
            printf("Palabra no aceptada.\n");
            break;
          }*/
        }
        if(res2 == 0){
          printf("Palabra no válida.\n");
        }
    }
    else{
      printf("Alguno de los elementos de la palabra/lenguaje es inválido.\n");
    } 
      
  printf("Quieres ingresar otra palabra? (1 -> sí, 0 -> no).");
  scanf("%d", &respuesta);
    
  }
  

	return EXIT_SUCCESS;
}
