// se igual a verdadeiro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

							/* 
							*	****COMANDOS****
							*A - Adiciona uma mensagem
							*L - Lista todas as mensagens
							*U - Lista todas as mensagens introduzidas por um dado utilizador.
							*O - Lista as mensagens mais longas.
							*T - Escreve o utilizador mais activo na escrita de mensagens
							*S - Lista todas as mensagens por ordem alfabética.
							*C - Escreve o número de ocorrências de uma palavra.
							*X - Termina o programa
							* ***************************************
							*/

/* directivas de pre-compilador, definicao de tipos/estruturas */

# define MAX_PARTICIPANTES 1000
# define MAX_MENSAGENS 10000
# define MAX_LEN 140 

/* definicao da estrutura Mensagem onde sao definidos todos os tipos necessarios a resolucao do projeto*/

typedef struct{
	int id;		// identificador de um participante
	char frase[MAX_LEN+1];	// numero de caracteres de uma mensagem
}Mensagem;

int participantes[MAX_PARTICIPANTES]={0};	// criacao de uma lista em que conta as mensagens de cada utilizador


/* Globais */

static Mensagem forum[MAX_MENSAGENS];    //criacao do forum   

/* prototipos: */

void adiciona_uma_mensagem();
int le_linha(char s[]);
void lista_todas_as_mensagens();
void lista_todas_as_mensagens_introduzidas_por_um_dado_utilizador();
void lista_as_mensagens_mais_longas();
void escreve_o_utilizador_mais_activo_no_forum();
void lista_todas_as_mensagens_por_ordem_alfabetica();
void SelectionSort(int a[], int  l, int r);
int less(int i, int j);
void escreve_o_numero_de_ocorrencias_de_uma_palavra();
int branco(char a);

int cntMessages; // contador ---> total de mensagens

/* MAIN */
int main(){

	char comando;

	while(1){
		comando = getchar();/* le o comando */
		switch (comando) {
		case 'A':
			adiciona_uma_mensagem(); /* Executa comando A */
			break;
		case 'L':
			lista_todas_as_mensagens(); /* Executa comando L */
			getchar(); /* le o '\n' introduzido pelo utilizador */
			break;
		case 'U':
			lista_todas_as_mensagens_introduzidas_por_um_dado_utilizador();/* Executa comando U */
			getchar(); /* le o '\n' introduzido pelo utilizador */
			break;
		case 'O':
			lista_as_mensagens_mais_longas(); /* Executa comando O */
			getchar(); /* le o '\n' introduzido pelo utilizador */
			break;
		case 'T':
			escreve_o_utilizador_mais_activo_no_forum(); /* Executa comando T */
			getchar(); /* le o '\n' introduzido pelo utilizador */
			break;	
		case 'S':
			lista_todas_as_mensagens_por_ordem_alfabetica(); /* Executa comando S */
			getchar(); /* le o '\n' introduzido pelo utilizador */
			break;
		case 'C':
			escreve_o_numero_de_ocorrencias_de_uma_palavra(); /* Executa comando C */
			getchar(); /* le o '\n' introduzido pelo utilizador */
			break;
		case 'X':
			printf("%d\n" ,cntMessages); /* Executa comando X */
			return EXIT_SUCCESS; /* Termina o programa */
		default:
			printf("ERRO: Comando [%c] desconhecido\n",comando);
		}
	}
	return EXIT_FAILURE;	//Termina o Programa  
}


/* Restantes Funcoes */

/*le os caracteres*/
int le_linha(char s[])                        //funcao auxiliar que forma o vetor com a mensagem
{					
	int c, i=0;
	while ((c=getchar()) != '\n' && c !=EOF)
		s[i++] = c;
	s[i] = '\0';
	return i;
}
// ----------------> COMANDO A <-------------------
void adiciona_uma_mensagem()
{
	getchar();                                // le o o espaco entre o comando e o id
	scanf("%d", &forum[cntMessages].id);      // le o id
	getchar();                                // le o espaco entre o id e a mensagem
	le_linha(forum[cntMessages].frase);       // leitura da mensagem com auxilio da funcao le linha
	participantes[forum[cntMessages].id]++;   // contador das mensagens de cada utilizador
	cntMessages++;                            // contador de todas as mensagens no forum
}
//-------------------------------------------------



//---------------> COMANDO L <---------------------
void lista_todas_as_mensagens()
{
	int i;
	printf("*TOTAL MESSAGES:%d\n", cntMessages);
	for (i=0; i < cntMessages; i++)
		printf("%d:%s\n", forum[i].id, forum[i].frase); // coloca no standart output o todas as mensagens com o seu respetivo 
		                                                // utilizador 
}

//-------------------------------------------------



// ----------------> COMANDO U <-------------------
void lista_todas_as_mensagens_introduzidas_por_um_dado_utilizador()
{
	int i,id;

	scanf("%d",&id);
	printf("*MESSAGES FROM USER:%d\n",id);
	
	for (i=0;i < cntMessages; i++)
	{
		if(forum[i].id==id)
			printf("%s\n", forum[i].frase);          // coloca no standart output todas as mensagens de um utilizador especifico
	}
}

//-------------------------------------------------


// ----------------> COMANDO O <-------------------
void lista_as_mensagens_mais_longas()
{
	int i, maior=0,j;
	for(i=0; i < cntMessages; i++)                                           // verifica o comprimento de cada mensagem ao longo do
		if(maior < strlen(forum[i].frase))                                   // forum e determina o maior comprimento
			maior = strlen(forum[i].frase);

	for(j=0; j < cntMessages; j++)                                           // verfica o comprimento de cada mensagem ao longo do 
		if (maior == strlen(forum[j].frase))                                 // forum, caso o comprimento seja igual ao maior 
			printf("*LONGEST SENTENCE:%d:%s\n", forum[j].id,forum[j].frase); // comprimento calculado no ciclo anterior ira ser
	                                                                         // colocado no standart output

}
//-------------------------------------------------

// ----------------> COMANDO T <-------------------
void escreve_o_utilizador_mais_activo_no_forum()
{
	int i, maisAtivo=0;
	for(i=0; i < MAX_PARTICIPANTES; i++)
		if(maisAtivo < participantes[i])                       // verifica o numero de mensagens de cada utilizador determinando
			maisAtivo = participantes[i];                      // a maior quantidade de mensagens escrita por um utilizador
	for(i=0; i < MAX_PARTICIPANTES; i++)
		if (participantes[i]==maisAtivo)
			printf("*MOST ACTIVE USER:%d:%d\n", i, maisAtivo); // verifica se o numero de mensagens de um utilizador é igual a
}                                                              // maior quantidade de mensagens calculado no ciclo anterior e 
                                                               // coloca no standart output o numero de utilizador mais ativo
//-------------------------------------------------               e o seu numero de mensagens



// ----------------> COMANDO S <-------------------
void SelectionSort(int a[], int  l, int r)
{  
	int  i, j; 
    for (i = l; i < r; i++){ 
	int aux,min = i;                                          
        for (j = i+1; j <= r; j++) 
            if (less (a[j], a[min]))                           //utilizacao da funcao less 
                min = j; 
        aux = a[i]; a[i] = a[min]; a[min] = aux;  
    } 
}

void lista_todas_as_mensagens_por_ordem_alfabetica()
{
	int i, aux[MAX_PARTICIPANTES];

	printf("*SORTED MESSAGES:%d\n",cntMessages);

	for (i=0; i < cntMessages; i++)
		aux[i]=i;
	SelectionSort(aux, 0, cntMessages-1);
	for (i=0; i < cntMessages; i++)
		printf("%d:%s\n", forum[aux[i]].id, forum[aux[i]].frase);
}

int less(int i, int j)                                        
{
	int a = strcmp(forum[i].frase, forum[j].frase);           // compara as 2 mensagens verificando qual a maior
	if (a < 0)                                                // caso a forum[i].frase < forum[j].frase ira realizar a troca
		return 1;							
	if (a > 0)                                                // caso a forum[i].frase > forum[j].frase nao realiza a troca
		return 0;
	if (forum[i].id < forum[j].id)                            // caso a=0 verifica qual o menor id 
		return 1; 	                                      
	
	return 0;
}

//-------------------------------------------------


//-------------------> COMANDO C <-----------------

int branco(char a)                                                                        // funcao auxiliar que verifica se o
{                                                                                         // caracter e um espaco branco
	if(a == ';' || a == ',' || a == ' '|| a == '\n' || a == '\t' || a == '.' || a=='\0') 
		return 1;
	return 0;
}

void escreve_o_numero_de_ocorrencias_de_uma_palavra()
{
	char p[MAX_LEN];

	scanf("%s",p);                                                                            //recebe a palavra 
	int i, k, j, cnt=0,l;
	for (i=0;i<cntMessages;i++)                                                               // acede ao forum
	{
		for (j = 0; forum[i].frase[j] != '\0'; j++)                                           // acede as mensagens do forum
			{
				if(j == 0 || branco(forum[i].frase[j-1]))                                     // verifica se a palavra esta no inicio
				                                                                              // da frase ou o caracter anterior ao
				k = j;                                                                        // inicio da palavra na frase é um 
				l = 0;                                                                        // caracter branco
				while (p[l] != '\0' && forum[i].frase[k] != '\0' && forum[i].frase[k] == p[l]) // verifica o se a palavra e igual a
				{	                                                                           // palavra na frase quando se inicia 
					k++;                                                                       // a comparacao
					l++;
				}
			    
				if (p[l] == '\0' && branco(forum[i].frase[k]))                                 // caso a palavra na frase esteja no
				cnt++;                                                                         // meio da frase ter de se verificar 
			}                                                                                  // a posicao da palavra e o \0 
		                                                                                       // e se na palavra da frase o caracter
	}                                                                                          // aseguir e um espaco branco

printf ("*WORD %s:%d\n",p,cnt);
}

//-------------------------------------------------