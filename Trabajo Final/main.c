
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string)   "\x1b[31m" string "\x1b[0m"
#define BLUE(string)  "\x1b[34m" string "\x1b[0m"
#define YEL(string)   "\x1b[33m" string "\x1b[0m"
#define MAG(string)   "\x1b[35m" string "\x1b[0m"
#define CYAN(string)  "\x1b[36m" string "\x1b[0m"

const int MAX=30;

typedef struct {
    int bajaCliente;  // 0 si esta activo 1 si esta inactivo
    char domicilio[30];
    char nombre[30],apellido[30],email[30],telefono[8];
    int idCliente;
    long int dni;
    int diaA,mesA,anioA,diaB,mesB,anioB;
    int totPedidos;
} cliente;

typedef struct{
   char producto[30];
   float monto;
   int cantidad;
   float total;

} precio;

typedef struct {
    int idPedido;
    float costoPedido;
    precio descripcionPedido[30];
    int diaP,mesP,anioP;
    int pedidoAnulado;
    int idCliente;
    int cantProductos;
    char nombre[30];
    char apellido[30];
    long int dni;

} pedido;




///Funciones men�.

void menu_principal(char clientes[],char pedidos[]);
int control_menu_opcion(int cant_opciones); ///Controla que la opcion ingresada sea valida.
void menu_administracion_clientes(char clientes[],char pedidos[]); /// Menu de clientes
void menu_administracion_pedidos(char clientes[],char pedidos[]); // para acceder al menu de pedidos


///Funciones de administraci�n de clientes.

void cargar_datos(char clientes[],cliente *aux,char pedidos[]);///Ingresar los datos del usuario
void cliente_carga(char clientes[],cliente aux); //guarda los datos en el archivo clientes
int usuario_id(char clientes[]);   ///ENCUENTRA LA SIGUIENTE ID A USAR
int usuario_exist(char clientes[], long int nuevo_cliente,cliente *datos);  ///RETORNA 0 SI NO ENCONTRo EL USUARIO y actualiza el id
void cliente_alta(char clientes[],char pedidos[]); ///FUNCION PRINCIPAL ALTA
void cliente_baja(char clientes[]);///da de baja el cliente, primero hay que buscarlo por dno
void cliente_modif(char clientes[],char pedidos[]); ///MODIFICA EL CAMPO DE CLIENTE QUE DESEA EL USUARIO
void modif_busca(char clientes[],cliente aux); ///GUARDA TODAS LAS MODIFICACIONES EN EL ARCHIVO CLIENTES.
void modif(cliente *aux, int opcion); ///MODIFICA EL CAMPO DE CLIENTE ELEGIDO
void usuario_mostrar(cliente aux);
void cliente_consulta(char clientes[],char pedidos[]); //muestra la informacion de un cliente
void cliente_listado(char clientes[], char pedidos[]);   ///LISTADO DE CLIENTES
void estructuras_carga(char usuario[], cliente vec[],int *id); //guarda los datos en el arreglo
void dni_seleccion(cliente aux[],int id); //Ordena por el metodo de seleccion los dni
int posicionMenor (cliente vec1[], int pos,int validos);
void lista_clientes(cliente aux[], int total); ///LISTA de clientes ordenados
void nombre_apellido_insercion(cliente aux[], int validos);   ///Ordenacion por insercion de los nombres
void insertar(cliente vec1[], int validos, cliente dato); //



///Funcion de productos
void muestra_productos(precio aux[],int validos);
int total_productos(char precios[],precio aux[],int MAX);       //devuelve la cantidad de productos

///Funciones de pedidos
void cargar_pedido(char clientes[],char pedidos[],precio precios[],int validos);
void alta_pedido(char clientes[],char pedidos[],precio precios[],pedido *aux,int validos);
int pedido_id(char pedidos[]); ///ENCUENTRA LA SIGUIENTE ID A USAR (ultima)
void pedido_baja(char pedidos[],char clientes[]); //busca en el archivo clientes y cuando encuentra busca los pedidos
void pedido_archivo(char pedidos[],pedido aux); //guarda los pedidos en el archivo
void pedido_modificar(char pedidos[],pedido aux); //elimina el pedido seleccionado
void ver_pedido(precio aux[],int validos);
void pedido_modif(char clientes[],char pedidos[],precio precios[],int validos);
void pedido_agregar(pedido *aux_pedido,precio precios[],int validos,char pedidos[]);
void pedido_quitar(pedido *aux_pedido,precio precios[],int validos,char pedidos[]);
void pedido_consulta(char clientes[],char pedidos[]);
void pedido_listado(char clientes[],char pedidos[]);
void estructuras_carga_pedidos(char pedidos[], pedido vec[],int *validos);//guarda los datos en el arreglo
void lista_pedidos(pedido aux[],int validos);
//////////////////////////////////////////////////////////////////
////Funciones Listadas
int  posicion_menor(pedido vec1[], int i,int validos);
void ordena_pedido_insertar(pedido vec1[], int validos);
void insertar_mejor(cliente vec1[], int validos,cliente  dato);
void mejor_insercion (cliente vec1[], int validos);
void lista_mejor(cliente aux[],int validos);
//////////////////////////////////







int main()
{


    char clientes[]= {"clientes.dat"};  ///nombre archivo clientes
    char pedidos[]= {"pedidos.dat"};  ///nombre archivo pedidos
    ///Funciones
    menu_principal(clientes,pedidos);


    return 0;
}



void menu_principal(char clientes[],char pedidos[])  /// MENU PRINCIPAL
{

    system("cls");
    printf("Men%c Principal: \n\n", 163);
    printf("1] Administraci%cn de Cliente \n", 162);
    printf("2] Administraci%cn de Pedidos \n", 162);
    printf("0] Salir del programa. \n\n");
    printf("OPCION: ");
    int cant_opciones = 3;

    ///Listado de opciones disponibles en el menu.

    switch(control_menu_opcion(cant_opciones))
    {
    case 1 :
        menu_administracion_clientes(clientes,pedidos);
        break;

    case 2 :
        menu_administracion_pedidos(clientes,pedidos);
        break;
    case 0 :
        exit(0);
        break;
    }
}

int control_menu_opcion(int cant_opciones) ///CONTROLA LA SELECCION DEL MENU
{
    int menu_opcion;
    int exito=0;

    do
    {
        fflush(stdin);
        scanf("%d", &menu_opcion);

        if (menu_opcion < 0 || menu_opcion > cant_opciones-1)
        {
            printf("La opci%cn seleccionada no es valida, intentelo nuevamente\n", 162);
        }
        else
        {
            exito=1;
        }
    }
    while ( exito == 0);

    system("cls");
    return menu_opcion;
}



void menu_administracion_clientes(char clientes[],char pedidos[]) ///MENU DE ADMINISTRACION DE CLIENTES
{
    int control;
    do
    {
        /// Menu Administracion de Clientes
        printf("Men%c Administraci%cn de Cliente: \n\n", 163, 162);
        printf(GREEN("1] Alta cliente \n"));
        printf(RED("2] Baja cliente \n"));
        printf(YEL("3] Modificaciocn cliente \n"));
        printf(BLUE("4] Consulta \n"));
        printf(MAG("5] Listado \n\n"));
        printf(CYAN("0] Volver al menu Principal \n\n"));
        printf("OPCION: ");

        int cant_opciones = 6;

        ///Listado de opciones disponibles en el menu.

        switch(control=control_menu_opcion(cant_opciones))
        {
        case 1 :
            cliente_alta(clientes,pedidos);
            system("cls");
            break;
        case 2 :
            cliente_baja(clientes);
            system("cls");
            break;
        case 3 :
            cliente_modif(clientes,pedidos);
            system("cls");
            break;
        case 4 :
            cliente_consulta(clientes,pedidos);
            system("cls");
            break;
        case 5 :
            cliente_listado(clientes,pedidos);
            system("cls");
            break;
        case 0 :
            menu_principal(clientes,pedidos);
            system("cls");
            break;
        }
    }
    while(control!=0);
}

void menu_administracion_pedidos(char clientes[],char pedidos[]) ///MENU DE ADMINISTRACION DE PEDIDOS
{
    char precios[]= {"precios.txt"};  ///nombre archivo precios
    int validos=0;
    precio aux[MAX];

    if (validos==0){
       validos=total_productos(precios,aux,MAX);
    }

    int control;
    do
    {
        /// Menu Administracion de Clientes
        printf("Men%c Administraci%cn de Cliente: \n\n", 163, 162);
        printf(GREEN("1] Alta Pedido \n"));
        printf(RED("2] Baja Pedido \n"));
        printf(YEL("3] Modificacion Pedido \n"));
        printf(BLUE("4] Consultar Pedido \n"));
        printf(MAG ("5] Listado y estadisticas \n"));
        printf("6] Ver lista de precios actuales \n\n");
        printf( CYAN("0] Volver al menu Principal \n\n"));
        printf("OPCION: ");

        int cant_opciones = 7;

        ///Listado de opciones disponibles en el menu.

        switch(control=control_menu_opcion(cant_opciones))
        {
      case 1 :
            cargar_pedido(clientes,pedidos,aux,validos);
            system("pause");
            system("cls");
            break;
     case 2 :
            pedido_baja(pedidos,clientes);
            system("cls");
            break;
       case 3 :
            pedido_modif(clientes,pedidos,aux,validos);
            system("cls");
            break;
     case 4 :
            printf("\n*** CONSULTA PEDIDOS ***");
            pedido_consulta(clientes,pedidos);
            system("cls");
            break;
        case 5 :
            printf( MAG("\n LISTADO Y ESTADISTICAS \n"));
            pedido_listado(clientes,pedidos);
            system("pause");
            system("cls");
            break;
        case 6 :
            muestra_productos(aux,validos);
            system("pause");
            system("cls");
            break;
        case 0 :
            menu_principal(clientes,pedidos);
            system("cls");
            break;
        }
    }
    while(control!=0);
}



///Administracion de clientes.

void cargar_datos(char clientes[],cliente *aux,char pedidos[]) ///REGISTRO DE USUARIO
{
    long int nuevo_dni;
    int control=0;


    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    aux->idCliente=usuario_id(clientes); ///busca la proxima id a usar
    printf("Id del proximo Cliente: ");
    printf(YEL("%i \n"),aux->idCliente);

    ///USUARIO
    while(control==0)
    {
        printf("\n Ingrese numero de documento sin los puntos:\n ");
        scanf("%ld",&nuevo_dni);
        while(nuevo_dni<2000000 || nuevo_dni>100000000)
        {
            printf(RED("\n DNI invalido, ingrese nuevamente:\n "));
            scanf("%ld",&nuevo_dni);
        }
        control=usuario_exist(clientes,nuevo_dni,aux);

        if(control==0)
        {
            printf(GREEN("\nEl cliente ya existe.\n"));
            usuario_mostrar(*aux);
            printf("\n ************************\n");
            printf("\n Desea ingresar un nuevo usuario ? \n");
            printf("\n 1-Para volver ,0- para volver a cargar\n");
            control=control_menu_opcion(2);
            if(control==1)
            menu_principal(clientes,pedidos);


        }
        else
        {
           aux->dni=nuevo_dni;
           printf("\n Ingrese nombre del cliente \n");
           fflush(stdin);
           gets(aux->nombre);
           printf("\n Ingrese nombre apellido \n");
           fflush(stdin);
           gets(aux->apellido);
           printf("\n Ingrese mail \n");
           fflush(stdin);
           gets(aux->email);
           printf("\n Ingrese telefono \n");
           fflush(stdin);
           gets(aux->telefono);
           printf("\n Ingrese el domicilio \n");
           fflush(stdin);
           gets(aux->domicilio);
           aux->diaA=tm->tm_mday;
           aux->mesA=tm->tm_mon+1;
           aux->anioA=1900+tm->tm_year;
           aux->bajaCliente=0;        // el cliente esta activo 0
           aux->totPedidos=0;
           system("cls");
           usuario_mostrar(*aux);
           printf("\n ingrese [0] para  volver a cargar datos,  [1] para confirmar confimar \n");
            control=control_menu_opcion(2);

        }

    }

    system("pause");
}


void cliente_carga(char clientes[],cliente aux)  //funcion para guardar los datos en el archivo clientes
{
  FILE *cli;
  cli=fopen(clientes,"a+b");
  if(cli!=NULL)
    {


        fwrite(&aux,sizeof(cliente),1,cli);

        fclose(cli);

        system("cls");
        printf(GREEN("La carga se ha realizado con exito!\n\n"));
        system("pause");
        system("cls");

    }


}

int usuario_id(char clientes[]) ///ENCUENTRA LA SIGUIENTE ID A USAR (ultima)
{
    FILE*cli;

    int control=0;

    cli=fopen(clientes,"r+b");

    if(cli!=NULL)
    {
        fseek(cli, 0, SEEK_END);
        control=ftell(cli)/sizeof(cliente);

    }
    fclose(cli);
    return control;
}

int usuario_exist(char clientes[], long int nuevo_dni,cliente *datos ) ///RETORNA 0 SI ENCONTRO EL USUARIO
{
    FILE* cli;

    cliente aux;
    int control=1;

    cli=fopen(clientes,"rb");

    if(cli!=NULL)
    {
        while(!feof(cli)&& control!=0)
        {
            fread(&aux,sizeof(cliente),1,cli);

            if(aux.dni==nuevo_dni)
            {
              control=0;
              *datos=aux;
            }


        }


    }
    fclose(cli);
    return control;
}

void cliente_alta(char clientes[],char pedidos[]) ///gargar_datos guarda los datos y  cliente_carga cargan los datos en el archivo
{

    cliente aux;

    printf(GREEN("ALTA CLIENTE: \n\n"));
    cargar_datos(clientes,&aux,pedidos);
    printf("\n");
    system("cls");
    printf(GREEN("CARGA CLIENTE\n\n"));
    system("pause");
    cliente_carga(clientes,aux);
}

void cliente_baja(char clientes[]) ///Da de baja el cliente, primero busca para saber quien es.
{
    cliente aux;
    int control=1;


    char baja=' ';
    long int dni;

    printf(RED("BAJA CLIENTE\n\n"));
    printf("Ingrese su DNI: ");

    scanf("%ld",&dni);
    control=usuario_exist(clientes,dni,&aux); ///0 encuentra..


    if(control!=0)
    {
        printf(RED("\nEl usuario no es valido. \n"));
    }
    else
    {
        if(aux.bajaCliente==1) ///en caso de que el usuario este eliminado
        {
            printf(RED("\nEl usuario no esta activo. \n"));
        }
        else
        {
                usuario_mostrar(aux);
                printf("\n\nQuiere dar de baja su cuenta? [S]/[N]: ");
                fflush(stdin);
                scanf("%c",&baja);
                if(baja=='s'||baja=='S')
                {
                    baja='n';
                    printf("\nEsta seguro? [S]/[N]: ");
                    fflush(stdin);
                    scanf("%c",&baja);
                    if(baja=='s'||baja=='S')
                    {
                        time_t t;
                        struct tm *tm;
                        t=time(NULL);
                        tm=localtime(&t);
                        aux.bajaCliente=1;
                        aux.diaB= tm->tm_mday;
                        aux.mesB=tm->tm_mon+1;
                        aux.anioB=1900+tm->tm_year;
                        aux.bajaCliente=1;
                        modif_busca(clientes,aux);
                        printf(RED("\n-----------------\n.....Usuario eliminado.....\n-----------------\n"));

                    }
                }

        }
    }
    system("pause");
}

void cliente_modif(char clientes[],char pedidos[]) ///MODIFICA EL CAMPO DE CLIENTE QUE DESEA EL USUARIO
{


    int control=1;
    long int dni;
    cliente aux;

    int cant_opciones=6;



    printf(YEL("Modificar cliente \n"));
    printf("Ingrese su Documento \n");
    scanf("%ld",&dni);

    control=usuario_exist(clientes,dni,&aux); ///0 encuentra..




    if(control!=0)
    {
        printf(RED("El usuario no es valido.\nVolvera al menu administracion.\n"));
        system("pause");
        system("cls");
        menu_administracion_clientes(clientes,pedidos);
    }
    else
    {


         if(aux.bajaCliente==1)
        {
            printf(RED("El usuario ha sido eliminado el dia %i/%i/%i .\n"),aux.diaB,aux.mesB,aux.anioB);
            printf(YEL("\n desea dar de alta al usuario \n"));
            printf("\n ingrese\n [0]-para dar de alta, [1]-para volver al menu \n");
            control=control_menu_opcion(2);
            if(control==1)
                menu_administracion_clientes(clientes,pedidos);
            else
            {
                aux.bajaCliente=0;
                modif_busca(clientes,aux);
                printf(GREEN("\n ***El usuario fue dado de alta***\n"));

            }

        }
        else
        {
            usuario_mostrar(aux);
            control=1;
            while(control!=0 )
            {
                printf(YEL("\n Que campos desea modificar?:\n\n"));
                printf("\n 1] Nombre \n");
                printf("\n 2] Apellido \n");
                printf("\n 3] Domicilio \n");
                printf("\n 4] Email \n");
                printf("\n 5] Telefono \n");
                printf("\n 0] SALIR \n");
                printf("\n\nOPCION: \n ");

                control=control_menu_opcion(cant_opciones);

                if(control!=0)
                {
                    modif(&aux,control);
                    system("pause");
                    system("cls");
                }
                else
                {
                    modif_busca(clientes,aux);      //busca la posicion y guarda la modificacion

                    printf(YEL("\nDatos modificados: \n"));
                    usuario_mostrar(aux);
                    printf(CYAN("\n\nVolvera al menu administracion de clientes.\n"));
                    system("pause");
                    system("cls");

                }
            }
        }


    }
}

void modif_busca(char clientes[],cliente aux) ///GUARDA TODAS LAS MODIFICACIONES EN EL ARCHIVO CLIENTE.
{
    FILE* cli;

    cli=fopen(clientes,"r+b");

    if(cli!=NULL)
    {
        fseek(cli,sizeof(cliente)*(aux.idCliente),SEEK_SET);
        fwrite(&aux,sizeof(cliente),1,cli);
        fclose(cli);
    }
}
void modif(cliente *aux, int opcion) ///MODIFICA EL CAMPO DE CLIENTE ELEGIDO
{


    if(opcion==1)
    {
        printf(YEL("Nuevo nombre: "));
        fflush(stdin);
        gets(aux->nombre);
    }
    else
    {
        if(opcion==2)
        {
            printf(YEL("Nuevo Apellido: "));
            fflush(stdin);
            gets(aux->apellido);
        }
        else
        {
            if(opcion==3)
            {
                printf(YEL("Nueva Domicilio: "));
                fflush(stdin);
                gets(aux->domicilio);
            }
            else
            {
                if(opcion==4)
                {
                 printf(YEL("Nuevo Email: "));
                 fflush(stdin);
                 gets(aux->email);

                }
                else{
                    if(opcion==5)
                    {
                       printf(YEL("Nuevo Telefono: "));
                       fflush(stdin);
                       gets(aux->telefono);
                    }
                    }

                }
            }
        }
}

void usuario_mostrar(cliente aux) ///muestra todos los campos el usuario
{
    printf("\n ***  Informaci%cn del cliente  *** \n",162);
    printf("\n Id del usuario = ");
    printf(YEL("%i \n"),aux.idCliente);
    printf("\n DNI= %ld\n",aux.dni);
    printf("\n Nombre= %s \n",aux.nombre);
    printf("\n Apellido= %s\n",aux.apellido);
    printf("\n Email= %s \n",aux.email);
    printf("\n Telefono= %s \n",aux.telefono);
    if(aux.bajaCliente==0)
        printf("\n Es cliente desde la fecha" YEL("%i/%i/%i\n"),aux.diaA,aux.mesA,aux.anioA);
    else
       printf("\n El usuario fue dado de baja el dia =" RED ("%i/%i/%i\n"),aux.diaB,aux.mesB,aux.anioB);

    printf("\n ******************************** \n");
    system("pause");
}

void cliente_consulta(char clientes[],char pedidos[]) ///CONSULTA
{
    long int dni;
    cliente aux;
    int control=1;
    printf(BLUE("Ingrese numero de documento a consultar \n"));
    fflush(stdin);
    scanf("%ld",&dni);
    control=usuario_exist(clientes,dni,&aux); ///0 encuentra..
    if(control==0)
        {
        usuario_mostrar(aux);

        }
    else
        {
        printf(RED("\n **************\n"));
        printf(RED("El usuario no es valido.\nVolvera al menu administracion.\n"));
        printf(RED("\n **************\n"));
        system("pause");
        system("cls");
        menu_administracion_clientes(clientes,pedidos);

        }



}

void cliente_listado(char clientes[], char pedidos[]) ///LISTADO DE CLIENTES (ID,NOMBRE,DOMICILIO)
{
    int id=0;
    int cant_opciones=4;

    id=usuario_id(clientes);

    cliente aux[id];
    int validos;


    estructuras_carga(clientes,aux,&validos); ///CARGA EL ARRAY DE ESTRUCTURAS DESDE LOS ARCHIVOS


    system("cls");
    printf(MAG("Sub-Menu de Listado de Clientes.\n\nOrdenar por: \n"));
    printf("1] Documento\n");
    printf("2] Nombre y Apellido\n");
    printf("3] ID \n\n");
    printf("0] Volver al menu administrador\n\n");
    printf("OPCION: ");

    fflush(stdin);
    switch (control_menu_opcion(cant_opciones))
    {
     case 1:
        printf(MAG("ORDENACION POR DNI: \n"));///  ordeno los dni por seleccion ya que los ids son generados secuencialmente
        dni_seleccion(aux,validos);           //y se cargan ordenados
        lista_clientes(aux,validos);


        break;
   case 2:
        printf(MAG("ORDENACION POR APELLIDO Y NOMBRE: \n"));
        nombre_apellido_insercion(aux,validos);
        lista_clientes(aux,validos);

        break;
   case 3:
        printf(MAG("ORDENACION POR ID: \n")); //muestro los dni de las personas activas con for ya que estan en orden
        printf("          ID \t\t NOMBRE \t\t APELLIDO\t\t\t DNI\t\t \n");
        for(int i=0;i<validos;i++)
        {
         printf("|%-20i||%-20s||%-20s||%-20ld|\n",aux[i].idCliente,aux[i].nombre,aux[i].apellido,aux[i].dni);

        }
        system("pause");
        break;
    case 0:
        menu_administracion_clientes(clientes,pedidos);
        break;
    }
}

void estructuras_carga(char clientes[], cliente vec[],int *validos) //guarda los datos en el arreglo
{
    FILE* cli;


    int i=0;

    cli=fopen(clientes,"rb");

    if(cli!=NULL )
    {
        fseek(cli,0,SEEK_SET);
        while(!feof(cli) && (fread(&vec[i],sizeof(cliente),1,cli))>0)
        {

            if(vec[i].bajaCliente==0)
            {
              i++;
            }

        }

        fclose(cli);


    }
    else
    {
        printf(RED("El archivo no se pudo abrir."));
    }
    *validos=i;

}

void dni_seleccion (cliente vec1[], int validos)
{
    int posmenor;
    cliente aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor = posicionMenor(vec1,i,validos);
        aux = vec1[posmenor];
        vec1[posmenor]=vec1[i];
        vec1[i]= aux;
        i++;
    }
}

int posicionMenor (cliente vec1[], int pos,int validos)
{
    cliente menor;
    menor.dni=vec1[pos].dni;
    int posmenor = pos;
    int i = pos +1;

    while (i<validos)
    {
        if (menor.dni>vec1[i].dni)
        {
            menor.dni=vec1[i].dni;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

void lista_clientes(cliente arreglo[], int total) ///LISTA de clientes ordenados
{

        printf("\n      DNI \t\t APELLIDO \t\t NOMBRE\t\t \n");
    for(int i=0;i<total;i++)
        {

        printf("|%-20ld| |%-20s| |%-20s| \n",arreglo[i].dni,arreglo[i].apellido,arreglo[i].nombre);

        }
        system("pause");

    if(total==0) {
        printf(RED("No hay cargado ningun usuario.\n"));
    }
}

void nombre_apellido_insercion (cliente vec1[], int validos)
{
    int j = 0;
    while (j<validos-1)
    {
        insertar(vec1,j,vec1[j+1]);
        j++;
    }
}

void insertar(cliente vec1[], int validos,cliente  dato)
{
   int i=validos;

    int control=0;
    while( (i>=0 && (control=strcmp(dato.apellido, vec1[i].apellido))<0  ) ||  (i>=0 && (control=strcmp(dato.apellido, vec1[i].apellido))==0 &&  (control=strcmp(dato.nombre, vec1[i].nombre))<0 )             )
    {
        vec1[i+1]=vec1[i];
        i--;
    }
    vec1[i+1]=dato;
}


///Funciones productos.


void muestra_productos(precio aux[],int validos)

{
    printf("\n************Lista de productos*********");
    printf(BLUE("\n Productos          Precios por unidad\n\n"));
    for(int i=0;i<validos;i++)
    {
        printf("\n%i]- %s\t\t%.2f \n",i,aux[i].producto,aux[i].monto);
    }
}

int total_productos(char precios[],precio aux[],int MAX)

{
    FILE*pro;

    int i=0;
    pro=fopen(precios,"rt");



    if(pro!=NULL)
    {

      while(!feof(pro) && i<MAX)
      {
        fscanf(pro,"%s %f",aux[i].producto,&aux[i].monto);
        i++;
      }
    }
    else
    {
        printf(RED("\n el archivo de precios no existe \n"));
    }
    fclose(pro);
    return i;


}



///Funciones de administraci�n de pedidos.

void cargar_pedido(char clientes[],char pedidos[],precio precios[],int validos){

    pedido aux;

    printf(GREEN("ALTA PEDIDO: \n\n"));
    alta_pedido(clientes,pedidos,precios,&aux,validos);
    printf("\n");
    system("cls");
    printf("CARGA Pedido\n\n");
    system("pause");
    pedido_archivo(pedidos,aux);

}


int pedido_id(char pedidos[]) ///ENCUENTRA LA SIGUIENTE ID A USAR (ultima)
{
    FILE*ped;

    int control=0;

    ped=fopen(pedidos,"r+b");

    if(ped!=NULL)
    {
        fseek(ped, 0, SEEK_END);
        control=ftell(ped)/sizeof(pedido);

        fclose(ped);
    }
    return control;
}

void alta_pedido(char clientes[],char pedidos[],precio precios[],pedido *aux,int validos)
{
    int i=0,opcion=100;
    int control=0;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    long int dni;
    cliente datos_cliente;
    int kilos;

    printf("\n ingrese el numero de DNI del cliente para empezar a cargar el pedido \n");
    scanf("%ld",&dni);
    control=usuario_exist(clientes,dni,&datos_cliente);

    if(control!=0){
        printf(RED("\n El DNI ingresado no es valido"));
        printf(RED("\n Redirigido al menu principal \n"));
        system("pause");
        menu_principal(clientes,pedidos);
    }
    else{
        aux->pedidoAnulado=0; //el pedido esta activo
         strcpy(aux->nombre,datos_cliente.nombre);
         strcpy(aux->apellido,datos_cliente.apellido);
         aux->dni=datos_cliente.dni;


        datos_cliente.totPedidos=datos_cliente.totPedidos+1;
        modif_busca(clientes,datos_cliente);
        aux->costoPedido=0;
        aux->idPedido=pedido_id(pedidos);
        aux->idCliente=datos_cliente.idCliente;
        system("cls");
        printf("\n pedido N: "YEL("%i")  "Cliente: %s \t %s\n",aux->idPedido,datos_cliente.nombre,datos_cliente.apellido);
        while(opcion!=validos)
            {
                muestra_productos(precios,validos);
                printf("\n %i]-Salir",validos);
                printf(GREEN("\n Que producto desea agregar ?:\n"));
                opcion=control_menu_opcion(validos+1);
                if(i==0 && opcion==validos)
                {
                    printf(CYAN("\n Redirigido al menu principal \n"));
                    ver_pedido(aux->descripcionPedido,aux->cantProductos);
                    system("pause");
                    menu_principal(clientes,pedidos);
                }
                if (opcion!=validos)
                    {

                        printf("\n cuantos  " GREEN("kilos") " de %s desea agregar al pedido:\n",precios[opcion].producto);
                        scanf("%i",&kilos);
                        strcpy(aux->descripcionPedido[i].producto,precios[opcion].producto);
                        aux->descripcionPedido[i].cantidad=kilos;
                        aux->descripcionPedido[i].monto=precios[opcion].monto;
                        aux->descripcionPedido[i].total=precios[opcion].monto*kilos;
                        aux->costoPedido=aux->costoPedido+precios[opcion].monto*kilos;
                        i++;
                    }
            }

    }
    aux->cantProductos=i;
    aux->diaP=tm->tm_mday;
    aux->mesP=tm->tm_mon+1;
    aux->anioP=1900+tm->tm_year;
    ver_pedido(aux->descripcionPedido,aux->cantProductos);
    printf("\n***************\n");
    printf("\n El total de la compra es: "GREEN("%.2f")" \n",aux->costoPedido);
    system("pause");


    }




void pedido_baja(char pedidos[],char clientes[]) ///Da de baja el pedido, primero busca para saber quien es.
{

    FILE *ped;
    cliente aux_cliente;
    pedido aux_pedido;
    int control=1;
    ped=fopen(pedidos,"rb");
    char baja=' ';
    long int dni;
    int idpedido;

    printf(RED("BAJA PEDIDO\n\n"));
    printf("Ingrese su DNI: ");
    scanf("%ld",&dni);
    control=usuario_exist(clientes,dni,&aux_cliente); ///0 encuentra..


    if(control!=0)
    {
        printf(RED("\nEl usuario no es valido. \n"));
    }
    else
    {
        if(aux_cliente.bajaCliente==1) ///en caso de que el usuario este eliminado
        {
            printf(RED("\nEl usuario no esta activo. \n"));
        }
        else
        {
            if(aux_cliente.totPedidos==0)
            {
                printf(RED("\n EL CLIENTE NO TIENE PEDIDOS ACTIVOS EN ESTE MOMENTO \n"));

            }
            else
                {



                system("cls");
                printf("\nNombre:%s\tApellido:%s\tDni:%ld\n",aux_cliente.nombre,aux_cliente.apellido,aux_cliente.dni);
                printf(GREEN("\n******PEDIDOS ACTIVOS******\n"));
                    if(ped!=NULL)
                    {

                        while(!feof(ped) &&  (fread(&aux_pedido,sizeof(pedido),1,ped))>0 )

                        {

                            if(aux_pedido.pedidoAnulado==0 && aux_pedido.idCliente==aux_cliente.idCliente)
                            {

                             printf("\n***** PEDIDO NUMERO:" YEL("%i") " Fecha:"GREEN("%i/%i/%i") " \n*****",aux_pedido.idPedido,aux_pedido.diaP,aux_pedido.mesP,aux_pedido.anioP);
                             ver_pedido(aux_pedido.descripcionPedido,aux_pedido.cantProductos);
                                 printf("\n***************\n");
                                 printf("\n El total de la compra es:"GREEN("%.2f \n"),aux_pedido.costoPedido);

                            }

                        }


                    }
                    printf("\n\n INGRESE EL NUMERO DEL PEDIDO A SER" RED(" ANULADO:\n"));
                    scanf("%i",&idpedido);
                    printf("\n SEGURO DESEA ANULAR ESTE PEDIDO ? [S]/[N]");
                    fflush(stdin);
                    scanf("%c",&baja);
                    if(baja=='s'||baja=='S')
                    {
                        baja='n';
                        printf("\nEsta seguro? [S]/[N]: ");
                        fflush(stdin);
                        scanf("%c",&baja);
                        if(baja=='s'||baja=='S')
                        {


                            fseek(ped,sizeof(pedido)*idpedido,SEEK_SET);
                            fread(&aux_pedido,sizeof(pedido),1,ped);
                            aux_pedido.pedidoAnulado=1;
                            aux_cliente.totPedidos=aux_cliente.totPedidos-1;
                            modif_busca(clientes,aux_cliente);
                            pedido_modificar(pedidos,aux_pedido);
                            printf(RED("\n-----------------\n.....Pedido eliminado.....\n-----------------\n"));

                        }
                    }
            }
        }
    }
    fclose(ped);
    system("pause");
}

void pedido_archivo(char pedidos[],pedido aux){////////guarda el  pedido en el archivo de pedidos

  FILE *ped;
  ped=fopen(pedidos,"a+b");
  if(ped!=NULL)
    {
        fwrite(&aux,sizeof(pedido),1,ped);

        fclose(ped);


        printf(GREEN("La carga se ha realizado con exito!\n\n"));
        system("pause");
        system("cls");

    }
}

void pedido_modificar(char pedidos[],pedido aux) ///elimina el usuario buscado.
{

    FILE* ped;
    ped=fopen(pedidos,"r+b");
    if(ped!=NULL)
    {

        fseek(ped,sizeof(pedido)*(aux.idPedido),SEEK_SET);
        fwrite(&aux,sizeof(pedido),1,ped);
    }
    fclose(ped);
}


void ver_pedido(precio aux[],int validos)
{
 printf("------------------------------------------------------------\n");
 printf(BLUE("|Producto   \t||Kg           \t||Precio Producto\t||Total por producto \n"));
 printf("------------------------------------------------------------\n");
 for(int i=0;i<validos;i++)
    {
        printf("|%-16s||%-16i||%-16.2f||%10.2f|\n",aux[i].producto,aux[i].cantidad,aux[i].monto,aux[i].total);
    }

}




/////////////////////////////////////////////////////////////////////////////


void pedido_modif(char clientes[],char pedidos[],precio precios[],int validos)



{

    FILE *ped;
    int control=1;
    long int dni;
    cliente aux_cliente;
    pedido aux_pedido;
    ped=fopen(pedidos,"rb");
    int cant_opciones=3;
    int idpedido;


    printf(YEL("Modificar cliente \n"));
    printf("Ingrese su Documento \n");
    scanf("%ld",&dni);

    control=usuario_exist(clientes,dni,&aux_cliente); ///0 encuentra..
     if(control!=0)
    {
        printf(RED("El usuario no es valido.\nVolvera al menu administracion.\n"));
        system("pause");
        system("cls");
        menu_administracion_clientes(clientes,pedidos);
    }
    else
    {

       if(aux_cliente.bajaCliente==1) ///en caso de que el usuario este eliminado
        {
            printf(RED("\nEl usuario no esta activo. \n"));
        }
        else
        {
            if(aux_cliente.totPedidos==0)
            {
                printf(RED("\n EL CLIENTE NO TIENE PEDIDOS ACTIVOS EN ESTE MOMENTO \n"));

            }
            else
            {

                    system("cls");
                    printf("\nNombre:%s\tApellido:%s\tDni:%ld\n",aux_cliente.nombre,aux_cliente.apellido,aux_cliente.dni);
                    printf(GREEN("\n******PEDIDOS ACTIVOS******\n"));

                        if(ped!=NULL)
                        {

                            while(!feof(ped) &&(fread(&aux_pedido,sizeof(pedido),1,ped))>0 )

                            {
                                if(aux_pedido.pedidoAnulado==0 && aux_pedido.idCliente==aux_cliente.idCliente)
                                {
                                 printf("\n***** PEDIDO NUMERO:" YEL ("%i")  "Fecha:"GREEN("%i/%i/%i") " \n*****",aux_pedido.idPedido,aux_pedido.diaP,aux_pedido.mesP,aux_pedido.anioP);
                                 ver_pedido(aux_pedido.descripcionPedido,aux_pedido.cantProductos);
                                     printf("\n***************\n");
                                     printf("\n El total de la compra es:%.2f \n",aux_pedido.costoPedido);

                                }

                            }


                        }
                    printf(YEL("\n\n INGRESE EL NUMERO DEL PEDIDO A SER MODIFICADO: "));
                    scanf("%i",&idpedido);
                 control=1;
                 while(control!=0)
                 {
                        system("cls");
                        printf(YEL("\n Que desea modificar?:\n\n"));
                        printf(GREEN("\n 1] Agregar productos al pedido \n"));
                        printf(RED("\n 2] Quitar productos al pedido\n"));
                        printf( CYAN("\n 0] SALIR \n"));
                        printf("\n\nOPCION: \n ");
                        control=control_menu_opcion(cant_opciones);


                            fseek(ped,sizeof(pedido)*idpedido,SEEK_SET);
                            fread(&aux_pedido,sizeof(pedido),1,ped);




                        if(control==1) {
                            pedido_agregar(&aux_pedido,precios,validos,pedidos);
                        }
                        else{
                             if(control==2)
                             {
                              pedido_quitar(&aux_pedido,precios,validos,pedidos);
                             }

                        }
                 }
          }

        }

    }
 fclose(ped);
}


void pedido_agregar(pedido *aux_pedido,precio precios[],int validos,char pedidos[])
{


    int opcion=0;
    int kilos;
    int i=aux_pedido->cantProductos;
    while(opcion!=validos)
            {
                muestra_productos(precios,validos);
                printf(CYAN("\n %i]-Salir"),validos);
                printf("\n Que producto desea agregar ?:\n");
                opcion=control_menu_opcion(validos+1);
                if (opcion!=validos)
                    {

                        printf("\n cuantos "GREEN("kilos")" de %s desea agregar al pedido:\n",precios[opcion].producto);
                        scanf("%i",&kilos);
                        strcpy(aux_pedido->descripcionPedido[i].producto,precios[opcion].producto);
                        aux_pedido->descripcionPedido[i].cantidad=kilos;
                        aux_pedido->descripcionPedido[i].monto=precios[opcion].monto;
                        aux_pedido->descripcionPedido[i].total=precios[opcion].monto*kilos;
                        aux_pedido->costoPedido=aux_pedido->costoPedido+precios[opcion].monto*kilos;
                        i++;
                    }
            }
           aux_pedido->cantProductos=i;
          ver_pedido(aux_pedido->descripcionPedido,aux_pedido->cantProductos);
          printf("\n***************\n");
          printf("\n El total de la compra es:"GREEN("%.2f \n"),aux_pedido->costoPedido);
         pedido_modificar(pedidos,*aux_pedido);


}


void pedido_quitar(pedido *aux_pedido,precio precios[],int validos,char pedidos[])
{
    int i=aux_pedido->cantProductos;
    int opcion=0;



    while(opcion!=aux_pedido->cantProductos)
            {

                  printf("------------------------------------------------------------\n");
                  printf(BLUE("N-|Producto   \t||Kg           \t||Precio Producto\t||Total por producto \n"));
                  printf("------------------------------------------------------------\n");

                for(int j=0;j<aux_pedido->cantProductos;j++)
                {
                  printf("[%i]|%-16s||%-16i||%-16.2f||%10.2f|\n",j,aux_pedido->descripcionPedido[j].producto ,aux_pedido->descripcionPedido[j].cantidad    ,aux_pedido->descripcionPedido[j].monto,aux_pedido->descripcionPedido[j].total);
                }
                printf("\n***************\n");
                printf("\n El total de la compra es:"GREEN("%.2f")" \n",aux_pedido->costoPedido);
                printf("\n %i]-Salir",aux_pedido->cantProductos);
                printf("\n Que producto desea Quitar ?:\n");
                opcion=control_menu_opcion(aux_pedido->cantProductos+1);
                if (opcion!=aux_pedido->cantProductos)
                    {

                         aux_pedido->costoPedido=aux_pedido->costoPedido-(aux_pedido->descripcionPedido[opcion].total);
                        for(int i=opcion;i<aux_pedido->cantProductos;i++)
                        {
                           strcpy(aux_pedido->descripcionPedido[i].producto,aux_pedido->descripcionPedido[i+1].producto);
                           aux_pedido->descripcionPedido[i].cantidad=aux_pedido->descripcionPedido[i+1].cantidad;
                           aux_pedido->descripcionPedido[i].monto=aux_pedido->descripcionPedido[i+1].monto;
                           aux_pedido->descripcionPedido[i].total=aux_pedido->descripcionPedido[i+1].total;
                        }
                         i--;
                    aux_pedido->cantProductos=i;
                    }
            }
            pedido_modificar(pedidos,*aux_pedido);

}












void pedido_consulta(char clientes[],char pedidos[])
{
    FILE *ped;

    long int dni;
    cliente aux_cliente;
    pedido aux_pedido;
    int control=1;
    printf(BLUE("\n Ingrese numero de documento para consultar los pedidos \n"));

    scanf("%ld",&dni);
    control=usuario_exist(clientes,dni,&aux_cliente); ///0 encuentra..
   if(control!=0)
    {
        printf(RED("\nEl usuario no es valido. \n"));
        system("pause");
    }
    else
    {
        if(aux_cliente.bajaCliente==1) ///en caso de que el usuario este eliminado
        {
            printf(RED("\nEl usuario no esta activo. \n"));
            system("pause");
        }
        else
        {
            if(aux_cliente.totPedidos==0)
            {
                printf(RED("\n EL CLIENTE NO TIENE PEDIDOS ACTIVOS EN ESTE MOMENTO \n"));

            }
            else
                {


                ped=fopen(pedidos,"rb");
                system("cls");
                printf("\nNombre:%s\tApellido:%s\tDni:%ld\n",aux_cliente.nombre,aux_cliente.apellido,aux_cliente.dni);
                printf(GREEN("\n******PEDIDOS ACTIVOS******\n"));
                    if(ped!=NULL)
                    {

                        while(!feof(ped) &&  (fread(&aux_pedido,sizeof(pedido),1,ped))>0 )

                        {

                            if(aux_pedido.pedidoAnulado==0 && aux_pedido.idCliente==aux_cliente.idCliente)
                            {
                             printf("\n***** PEDIDO NUMERO:" YEL("%i")"  Fecha:"GREEN("%i/%i/%i")"  \n*****",aux_pedido.idPedido,aux_pedido.diaP,aux_pedido.mesP,aux_pedido.anioP);
                             ver_pedido(aux_pedido.descripcionPedido,aux_pedido.cantProductos);
                                 printf("\n***************\n");
                                 printf("\n El total de la compra es:"GREEN("%.2f")" \n",aux_pedido.costoPedido);

                            }

                        }


                    }
                 fclose(ped) ;
                }
                system("pause");

        }
    }
}









void pedido_listado(char clientes[],char pedidos[])
{

    int id=0;
    int cant_opciones=4;
    int validos,validos_cliente;
    id=usuario_id(pedidos);

    pedido aux[id];
    id=usuario_id(clientes);

    cliente aux_cliente[id];
    estructuras_carga(clientes,aux_cliente,&validos_cliente);

    estructuras_carga_pedidos(pedidos,aux,&validos); //guarda los datos en el arreglo
    printf(MAG("Sub-Menu\n"));
    printf("1] Pedidos ordenados por fecha\n");
    printf("2] Top ten mejores clientes \n");
    printf("3] Mostrar al peor cliente (menor cantida de pedidos)\n");
    printf("0] Volver al menu administrador\n\n");
    printf("OPCION: ");
    fflush(stdin);
    switch (control_menu_opcion(cant_opciones))
    {
     case 1:

        printf(MAG("\n PEDIDOS ORDENADOS POR FECHA \n"));
        ordena_pedido_insertar(aux,validos);           //se ordenan los datos por fecha
        lista_pedidos(aux,validos);


        break;
   case 2:
        mejor_insercion(aux_cliente,validos_cliente);
        lista_mejor(aux_cliente,validos_cliente);

        break;
   case 3:
        mejor_insercion(aux_cliente,validos_cliente);
        printf(MAG("EL CLIENTE QUE MENOS PEDIDOS REALIZO \n")); //muestro los dni de las personas activas con for ya que estan en orden
        printf("Cantidad de pedidos             ||Nombre:   ||Apellido: ||DNI: \n");
        printf("%i\t\t\t\t||%-10s||%-10s||%-20ld\n",aux_cliente[validos_cliente-1].totPedidos,aux_cliente[validos_cliente-1].nombre,aux_cliente[validos_cliente-1].apellido,aux_cliente[validos_cliente-1].dni);
        break;
    case 0:
        menu_administracion_clientes(clientes,pedidos);
        break;
    }





}




void estructuras_carga_pedidos(char pedidos[], pedido vec[],int *validos) //guarda los datos en el arreglo
{
    FILE* ped;
    int i=0;

    ped=fopen(pedidos,"rb");

    if(ped!=NULL )
    {
        fseek(ped,0,SEEK_SET);
        while(!feof(ped)&&  (fread(&vec[i],sizeof(pedido),1,ped))>0)
        {

            if(vec[i].pedidoAnulado==0)
            {
              i++;
            }
        }

        fclose(ped);
    }
    else
    {
        printf(RED("El archivo no se pudo abrir."));
        system("pause");
    }
    *validos=i;
}




void ordena_pedido_insertar (pedido vec1[], int validos)
{
    int posmenor;
    pedido aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor=posicion_menor(vec1,i,validos);
        aux = vec1[posmenor];
        vec1[posmenor]=vec1[i];
        vec1[i]= aux;
        i++;
    }
}

int posicion_menor(pedido vec1[], int pos,int validos)
{
    pedido menor;
    menor.diaP=vec1[pos].diaP;
    menor.mesP=vec1[pos].mesP;
    menor.anioP=vec1[pos].anioP;
    int posmenor = pos;
    int i = pos +1;

    while (i<validos)
    {

        if( menor.anioP>vec1[i].anioP || (menor.anioP==vec1[i].anioP && menor.mesP>vec1[i].mesP) ||(menor.anioP==vec1[i].anioP && menor.mesP==vec1[i].mesP &&  menor.diaP>=vec1[i].diaP) )

        {
            menor.diaP=vec1[i].diaP;
            menor.mesP=vec1[i].mesP;
            menor.anioP=vec1[i].anioP;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}


void mejor_insercion (cliente vec1[], int validos)
{
    int j = 0;
    while (j<validos-1)
    {
        insertar_mejor(vec1,j,vec1[j+1]);
        j++;
    }
}

void insertar_mejor(cliente vec1[], int validos,cliente  dato)
{
   int i=validos;

    while(i>=0 && vec1[i].totPedidos<=dato.totPedidos  )
    {
        vec1[i+1]=vec1[i];
        i--;
    }
    vec1[i+1]=dato;
}


void lista_mejor(cliente aux[],int validos){

    system("cls");
    printf(MAG("***ORDENACION MEJOR CLIENTE (CANTIDAD DE PEDIDOS)***\n \n"));

    printf("Cantidad de pedidos             ||Nombre:   ||Apellido:  ||DNI: \n");

    if(validos<=10)
     for(int i=0;i<validos;i++)
     {
         if(aux[i].totPedidos!=0);
         printf("%i\t\t\t\t||%-10s||%-10s ||%-20ld\n",aux[i].totPedidos,aux[i].nombre,aux[i].apellido,aux[i].dni);
     }
    else
    {
       if(validos>10)
       {

           for(int i=0;i<validos;i++)
            {
                printf("%i\t\t\t\t||%-10s||%-10s||%-20ld\n",aux[i].totPedidos,aux[i].nombre,aux[i].apellido,aux[i].dni);
            }
       }
    }


}


void lista_pedidos(pedido aux[],int validos){

    system("cls");

    printf("Fecha           ||Nombre:   ||Apellido: ||DNI:                ||Monto pedido:      \n");
 for(int i=0;i<validos;i++)
 {
     printf("%i/%i/%i\t||%-10s||%-10s||%-20ld||%-10.2f\n",aux[i].diaP,aux[i].mesP,aux[i].anioP,aux[i].nombre,aux[i].apellido,aux[i].dni,aux[i].costoPedido);
 }
}
