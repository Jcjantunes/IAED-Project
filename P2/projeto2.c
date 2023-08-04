#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Item.h
#define less(a,b) (strcmp(a,b) < 0)
#define eq(a,b) (strcmp(a,b)==0)

int cont=0;




typedef struct produto {
  char codigoproduto[9];
  int valor;

}*Item;


Item maximo=NULL;

Item new_item(char *codigoproduto , int size_str);
//--------------------------------------------------

//Item.c--------------------------------------
Item new_item(char *codigoproduto , int unidades)
{
    Item new = (Item) malloc(sizeof(struct produto));
    strcpy(new->codigoproduto,codigoproduto);
    new->valor= unidades;
    return new;
}
//-------------------------------------------


//ArvoreBinaria.h---------------------------
typedef struct node {

  Item item;
  int height;
  struct node *l;
  struct node *r;

} *link;


link NewTree(Item item, link l, link r);
link insertTree(link h, Item item);
int height(link h);
link rotL(link h);
link rotR(link h);
link rotLR(link h);
link rotRL(link h);
int Balance(link h);
link AVLbalance(link h);
link max(link h);
void initTree(link*h);
link deleteTree(link h, char* codigoproduto);
//---------------------------------------

//ArvoreBinaria.c
void initTree(link* h)
{
  *h=NULL;
}

link NewTree(Item item, link l, link r)
{
  if(item->valor<0)
  {
    item->valor=0;
  }

  link x = (link) malloc(sizeof(struct node));
	x -> item = item;
	x -> height = 1;
	x -> l = l;
	x -> r = r;

	return x;

}

void traverse(link h)
{
  if (h == NULL)
  return;
  traverse(h->l);
  printf("%s %d\n", h->item->codigoproduto,h->item->valor);
  traverse(h->r);
}


void UpdateMaximo(link h)
{
  if (h == NULL)
    return;
  UpdateMaximo(h->l);
  
  if (maximo==NULL) 
    maximo=h->item;
  else if(h->item->valor > maximo->valor)
    maximo =h->item;
  else if(h->item->valor == maximo->valor && strcmp(h->item->codigoproduto, maximo->codigoproduto)<0)
    maximo = h->item;
  
  UpdateMaximo(h->r);
}


link insertTree(link h, Item item)
{


   if (h == NULL){
      cont++;
      return NewTree(item, NULL, NULL);
   }

   if (less(item->codigoproduto, h->item->codigoproduto))
   {
      h->l = insertTree(h->l, item);

      if (maximo!=NULL)
      {
    
        if(item->valor > maximo->valor)
          maximo = item;
    
        else if(item->valor == maximo->valor && strcmp(item->codigoproduto, maximo->codigoproduto)<0)
          maximo = item;
      }

   }

   else if(strcmp(item->codigoproduto, h->item->codigoproduto)==0)
   {
      h->item->valor+=item->valor;
      
      if(h->item->valor<0)
        h->item->valor=0;

      if (maximo!=NULL)
      {
    
        if(h->item->valor > maximo->valor)
          maximo = h->item;
    
        else if(h->item->valor == maximo->valor && strcmp(h->item->codigoproduto, maximo->codigoproduto)<0)
          maximo = h->item;
      }
  	  return h;
   }
   else
   {
      h->r = insertTree(h->r, item);

      if (maximo!=NULL)
      {
    
        if(item->valor > maximo->valor)
          maximo = item;
    
        else if(item->valor == maximo->valor && strcmp(item->codigoproduto, maximo->codigoproduto)<0)
          maximo = item;
      }

   }
   
  
   h = AVLbalance(h);

   return h;

}


int height(link h)
{
  if (h==NULL)
    return 0;
  return h->height;
}


link rotL(link h)
{

	int height_left, height_right;

    link x = h->r;
    h->r = x->l;
    x->l = h;

    height_left = height(h->l);
    height_right = height(h->r);
    h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(x->r);
    x->height = height_left > height_right ? height_left + 1 : height_right + 1;

    return x;

}

link rotR(link h)
{

	int height_left, height_right;
    link x = h->l;
    h->l = x->r;
    x->r = h;

	height_left = height(h->l);
	height_right = height(h->r);
    h->height = height_left > height_right ?  height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(x->r);
    x->height = height_left > height_right ?  height_left + 1 : height_right + 1;

    return x;

}

link rotLR(link h) /*rotação dupla esquerda direita*/
{
    if (h==NULL)
		return h;

    h->l = rotL(h->l);
    return rotR(h);
}

link rotRL(link h) /*rotação dupla direita esquerda*/
{
    if (h==NULL)
        return h;

    h->r = rotR(h->r);
    return rotL(h);
}

int Balance(link h) /*Balance factor*/
{

    if(h == NULL)
        return 0;

    return height(h->l) - height(h->r);
}



link AVLbalance(link h)
{
	int balanceFactor;

    if (h==NULL)
        return h;

	balanceFactor = Balance(h);

    if(balanceFactor > 1)
    {
        if (Balance(h->l) >= 0)
			h = rotR(h);
        else
            h = rotLR(h);
    }

    else if(balanceFactor < -1)
    {
        if (Balance(h->r) <= 0)
            h = rotL(h);
        else
            h = rotRL(h);
    }

    else
    {
		int height_left = height(h->l);
		int height_right = height(h->r);
        h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    }

    return h;

}


  link max(link h)
  {
    if (h==NULL || h->r==NULL) return h;
    else return max(h->r);
  }



link deleteTree(link h, char* codigoproduto) {
  link aux ;
  if (h==NULL) 
    return h;

  else if (less(codigoproduto, h->item->codigoproduto)) 
    h->l=deleteTree(h->l,codigoproduto);
  
  else if (less(h->item->codigoproduto, codigoproduto)) 
    h->r=deleteTree(h->r,codigoproduto) ;
  
  else
  {
    if (h->l !=NULL && h->r !=NULL ) { /*caso 3*/
      aux=max(h->l);
      h->item = aux->item;
      h->l=deleteTree(h->l, aux->item->codigoproduto);
    }
    else
    { /*casos 1 e 2*/
      aux=h;
      if ( h->l == NULL && h->r == NULL ) 
        h=NULL;
      
      else if (h->l==NULL) 
        h = h->r;
     
      else 
        h = h->l;
      
      free(aux);
    }
  }
  return h;
}
//--------------------------------------------------------------




//prototipos.h<------------------------
void comando_a();
void comando_l();
void comando_m();
void comando_r();
void imprime(Item item);

//-----------------------------------

//MAIN

static link* head;
/* MAIN */
int main()
{
  head  = (link*)malloc(sizeof(link));
  *head=NULL;
  initTree(head);
  char comando;

	while(1)
  {
		comando = getchar();/* le o comando */
		switch (comando)
    {
			case 'a':
				getchar(); // le o espaco
				comando_a(); /* Executa comando a */
				getchar(); // le o /n
				break;
		  case 'l':
       comando_l();
			 getchar();
			 break;
  		case 'm':
        comando_m();
  			getchar();
  			break;
  		case 'r':
  			comando_r();
  			getchar();
  			break;
  		case 'x':
        printf("%d\n",cont);
  			return EXIT_SUCCESS;
  		default:
  			printf("ERRO: Comando [%c] desconhecido\n",comando);
		}
	}
	return EXIT_FAILURE;	//Termina o Programa
}
//------------------------------------------------------------


//prototipos
void comando_a()
{
  Item aux;
  int valor;
  char codigo[9];


  scanf("%s %d",codigo,&valor);
  
  aux = new_item(codigo,valor);

  *head = insertTree(*head , aux);
  
  if (maximo!=NULL)
    if(strcmp(maximo->codigoproduto,aux->codigoproduto)==0 && valor<0){
      maximo=NULL;
    }
}

void comando_l()
{
	traverse(*head);
}

void comando_m()
{
  if(maximo==NULL)
  {
    UpdateMaximo(*head);
    imprime(maximo);
  }

  else if(maximo!=NULL)
    imprime(maximo);
}


void comando_r()
{
	char codigo[9];
  scanf("%s",codigo);

  if (maximo!=NULL)
    if(strcmp(codigo,maximo->codigoproduto)==0)
      maximo=NULL;
  
  *head = deleteTree(*head,codigo);
  if(cont!=0)
    cont--;
  	
}

void imprime(Item item)
{
  if(item!=NULL)
    printf("%s %d\n",item->codigoproduto,item->valor);
}

