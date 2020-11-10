#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc (sizeof(LinkedList)); //tamaño de la lista.
    if(this!=NULL)
    {
    	this->pFirstNode = NULL;					//si la inicio, el primero nodo es null.
    	this->size = 0;							   // el size aun es 0.
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
	int returnAux=-1;

	if(this!=NULL)
	{
		returnAux = this->size;
	}
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	int len = ll_len(this);
	Node* node=NULL;

	if(this!=NULL && nodeIndex>-1 && len>nodeIndex)// index dentro del rango.
	{
		node = this->pFirstNode;					//node es igual al primer nodo de la lista.
		for(i=0;i<nodeIndex;i++)					//itero hasta que i sea igual al nodeIndex.
		{
			node = node->pNextNode;
		}
	}
	return node;
}


/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement){
    int returnAux = -1;
    int len = ll_len(this);
    Node* pNewNode=NULL;
    Node* pPrevNode;
    if(this!=NULL && nodeIndex>-1 && len>=nodeIndex)
    {
    	pNewNode = (Node*) malloc(sizeof(Node));          // creo espacio en memoria.
    	if(pNewNode!=NULL)
    	{
    		pNewNode->pElement = pElement;		   		//el nuevo elemento sera el elemento del nodo.
    		if(nodeIndex==0)							//lo agrego al primero.
    		{
				pNewNode->pNextNode = this->pFirstNode;
				this->pFirstNode = pNewNode;
    		}
    		else
    		{
    			pPrevNode = getNode(this, nodeIndex-1);		//obtengo el previo
    			pNewNode->pNextNode=pPrevNode->pNextNode;	// el nuevo apunta al siguiente del previo.
				pPrevNode->pNextNode = pNewNode;			// el siguiente del previo va a ser el nuevo.
    		}
    		this->size++;
    		returnAux=0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len=ll_len(this); //longitud de la lista
    if(this!=NULL && len>-1)
    {
    	addNode(this, len, pElement); //añado a la lista
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* returnAux = NULL;
	int len = ll_len(this);
    Node* node;
    if( this != NULL && index >= -1 && len>index)
    {
    	node = getNode(this, index); //usa getNode que recorre en busca del index.
    	if (node != NULL)
    	{
    		returnAux = node->pElement; //si pasa el if, se asigna el elemento del nodo obtenido con getNode().
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* node;
    if(this!=NULL && index>-1)
    {
    	node = getNode(this, index); //usa getNode que recorre en busca del index.
    	if(node!=NULL)
    	{
    		node->pElement = pElement; // el elemento del nodo va a ser el recibido por argumento
    		returnAux=0;
    	}
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
 {
	int returnAux = -1;
	Node *pNodeToRemove = NULL;
	Node *pPrevNode = NULL;

	if (this != NULL && index >= 0 && index < ll_len(this))
	{
		pNodeToRemove = getNode(this, index);          //obtengo el nodo a remover.
		if (pNodeToRemove != NULL)
		{
			if (index == 0)
			{
				this->pFirstNode = NULL;			// si es el primero, limpio firstNode
			}
			else
			{
				pPrevNode = getNode(this, (index - 1));  //obtengo el previo
				if (pPrevNode != NULL)
				{
					pPrevNode->pNextNode = pNodeToRemove->pNextNode;	//el siguiente del previo va a ser igual al siguiente del nodo a remover.
				}
			}
			free(pNodeToRemove);									//libero el nodo a remover.
			pNodeToRemove = NULL;									//libero el nodo a remover.
			this->size--;											//reduzco la lista.
			returnAux = 0;
		}
	}
	return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
 {
	int returnAux = -1;
	int len;
	Node *node;
	if (this != NULL)
	{
		len = ll_len(this);							//si la lista NO es null, asigno el len
		if (len > 0)
		{
			for (int i = (len - 1); i >= 0; i--)	//elimino del final hacia adelante.
			{
				node = getNode(this, i);      //obtengo por el valor de i

				if (node != NULL)
				{
					free(node);
					node = NULL;
				}
			}
			returnAux = 0;
		}
	}
	return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL && !(ll_clear(this))) // reviso clear
       {
           this = NULL;
           returnAux = 0;
       }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node *node = NULL;
    int len = ll_len(this);

    if (this != NULL && len>-1)
       {
           for (int i = 0; i < len; i++)
           {
               node = getNode(this, i);
               if (node != NULL && node->pElement == pElement)
               {
            	   returnAux = i;
                   break;
               }
           }
       }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if (this != NULL)
      {
    	returnAux = 0;
          if (ll_len(this) <= 0)
          {
        	  returnAux = 1;
          }
      }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if (this != NULL && index >= 0 && index <= ll_len(this))
      {
          if (!(addNode(this, index, pElement)))
          {
        	  returnAux = 0;
          }
      }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node *node = NULL;
     if (this != NULL && index >= 0 && index < ll_len(this))
     {
         node = getNode(this, index);
         if (node != NULL)
         {
        	 returnAux = node->pElement;
             free(node->pElement);
             node->pElement = NULL;
             this->size--;
         }
     }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if (this != NULL)
      {
    	returnAux = 0;
          if (ll_indexOf(this, pElement) >= 0)
          {
        	  returnAux = 1;
          }
      }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int output = -1;


    return output;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;

    return returnAux;

}

