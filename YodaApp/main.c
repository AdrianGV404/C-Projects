#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ARCHIVO 20
#define MAX_PAR 15
#define MAX_CAR 15


bool leerArchivo (char nombreArchivo[MAX_ARCHIVO], char frase[][MAX_PAR*MAX_CAR+ MAX_PAR - 1], int *contadorFrases)
{
    FILE *fp;
    int c;
    bool fin=false;
    int x=0;
    int y=0;

    fp = fopen(nombreArchivo,"r");
    if(fp == NULL)
    {
        return false;
    }
    do
    {
        c = fgetc(fp);
        if(feof(fp))
        {
            fin=true;
        }
        else
        {
            if (c != '\n')
            {
                frase[y][x] = c;
            }
            else
            {
                //printf("/n");
                y++;
                x = 0;
            }
            //printf("%c", frase[y][x]);
            if (c != '.')
            {
                x++;
            }
            else
            {
                c = fgetc(fp);
                //printf("\n");
                //printf("%s", frase[y]);
                y++;
                x = 0;
            }
        }
    }
    while(!fin);
    *contadorFrases = y;
    fclose(fp);
    return(1);
}

bool guardarArchivo(int fila, int col, char fraseFinal[fila][col], int contadorFrases)
{
    FILE *arxiu = fopen("sortida.txt", "w");
    if (arxiu == NULL)
    {
        return false;
    }
    else
    {
        for (int linea = 0; linea < contadorFrases; linea++)
        {
            int i = 0;
            while (fraseFinal[linea][i] != '\0')
            {
                fputc(fraseFinal[linea][i],arxiu);
                i++;
            }
            fputc('\n',arxiu);
        }
    }
    return true;
}

int demanaVelocitat()
{
    bool bucle = true;
    int velocitat = 0;

    printf("\n\nQuin valor de velocitat vols?\n[0 - 1 - 2]: ");  //Velocitat de parla
    while (bucle)
    {
        scanf("%d",&velocitat);            // El valor introduit sempre sera un enter
        if ((velocitat < 0) || (velocitat > 2))
        {
            printf(" - Error! Aquest valor no es possible!\n");
            printf("Torna a escriure el rang de velocitat: ");
        }
        else
        {
            bucle = false;
        }
    }
    return velocitat;
}

int demanaYodificacio()
{
    bool bucle = true;
    int yodificacio = 0;

    printf("Quin valor de yodificacio vols?\n[0 - 1 - 2]: ");
    while (bucle)
    {
        scanf("%d",&yodificacio);            // El valor introduit sempre sera un enter
        if ((yodificacio < 0) || (yodificacio > 2))
        {
            printf(" - Error! Aquest valor no es possible!\n");
            printf("Torna a escriure el rang de yodificacio: ");
        }
        else
        {
            bucle = false;
        }
    }
    return yodificacio;
}

int contarParaules (char frase[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1], int linea)
{
    int paraules = 0, i = 0;
    bool fiFrase = false;
    while (!fiFrase)
    {
        if (frase[linea][i] == '.')
        {
            fiFrase = true;
            paraules++;
        }
        else
        {
            if (frase[linea][i] == ' ')
            {
                paraules++;
            }
        }
        i++;
    }
    return paraules;
}

int aleatori(int min, int max)
{
    return (min + (rand() % (max - min + 1)));
}

void dibuixa_yoda ()
{
    char yoda[4][19] = {{92, 96, 45, 45, 46, 95, 39, 46, 58, 58, 46, 96, 46, 95, 46, 45, 45, 39, 47},
        {32, 92, 32, 32, 32, 96, 32, 95, 95, 58, 58, 95, 95, 32, 39, 32, 32, 32, 47},
        {32, 32, 32, 45, 45, 58, 46, 96, 39, 46, 46, 96, 39, 46, 58, 45, 45, 32, 32},
        {32, 32, 32, 32, 32, 32, 92, 32, 96, 45, 45, 39, 32, 47, 32, 32, 32, 32, 32}
    };
    int i, j;

    printf("\n\n\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 19; j++)
        {
            printf ("%c", yoda[i][j]);
        }
        printf("\n");
    }
    printf("\nDe processar... ha acabat, el fitxer\n\n");
}

void yodifica_1(int contadorFrases, int paraules, char frase[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1], char frasesYodificadas[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1])
{
    printf("\n------------ Frases Yodificades -------------\n\n");
    for (int linea = 0; linea < contadorFrases; linea++)
    {
        //mezclar frase
        paraules = contarParaules(frase, linea);
        if (paraules > 3)
        {
            int historialAleatoris[paraules], aux;
            //---------------Generar Array Aleatorios (solo la mitad de los numeros) ------------------------
            for (int i = 0; i < paraules; i++)
            {
                if (aleatori(0, 1) == 1)
                {
                    aux = aleatori(0, paraules - 1);
                }
                else
                {
                    aux = i;
                }
                bool esta = false;
                int c = 0;
                while (!esta && c < i)
                {
                    if (historialAleatoris[c] == aux)
                    {
                        esta = true;
                        i--;
                    }
                    c++;
                }
                if (!esta)
                {
                    historialAleatoris[i] = aux;
                }
            }
            /*
                   printf("\n");
                    for (int i = 0; i < paraules; i++)
                    {
                        printf(" %d", historialAleatoris[i]);
                    }
                printf("\n");
            */
            //---------------------------------------

            int indexParaules = 0;
            int indexAux = 0;
            while (indexParaules < paraules)
            {
                int i = 0;
                int cuentaEspacios = 0;
                bool encontrado = false;
                while (frase[linea][i] != '.' && !encontrado)
                {
                    if (frase[linea][i] == ' ')
                    {
                        cuentaEspacios++;
                        i++;
                    }
                    if (cuentaEspacios == historialAleatoris[indexParaules])
                    {
                        indexParaules++;
                        encontrado = true;
                        while (frase[linea][i] != ' ' && frase[linea][i] != '.')
                        {
                            frasesYodificadas[linea][indexAux] = frase[linea][i];
                            printf("%c",frasesYodificadas[linea][indexAux]);
                            i++;
                            indexAux++;
                        }
                        if (indexParaules == paraules)
                        {
                            frasesYodificadas[linea][indexAux] = '.';
                        }
                        else
                        {
                            frasesYodificadas[linea][indexAux] = ' ';
                        }
                        printf("%c",frasesYodificadas[linea][indexAux]);
                        indexAux++;
                    }
                    else
                    {
                        i++;
                    }
                }
            }
            printf("\n");
        }
        else
        {
            int indexParaules = 0;
            while (indexParaules < paraules)
            {
                indexParaules++;
                int i = 0;
                while (frase[linea][i] != ' ' && frase[linea][i] != '.')
                {
                    frasesYodificadas[linea][i] = frase[linea][i];
                    printf("%c",frasesYodificadas[linea][i]);
                    i++;
                }

                if (indexParaules == paraules)
                {
                    frasesYodificadas[linea][i] = '.';
                    printf("%c",frasesYodificadas[linea][i]);
                }
                else
                {
                    if (frase[linea][i] != '.')
                    {
                        frasesYodificadas[linea][i] = ' ';
                        printf("%c",frasesYodificadas[linea][i]);
                    }
                }
            }
            printf("\n");
        }
    }
}

void yodifica_2(int contadorFrases, int paraules, char frase[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1], char frasesYodificadas[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1])
{
    for (int linea = 0; linea < contadorFrases; linea++)
    {
        // Es barrejen totes les paraules
        paraules = contarParaules(frase, linea);
        //printf("\n\nParaules: %d",paraules);
        if (paraules > 3)
        {
            int historialAleatoris[paraules], aux;
            //---------------Generar Array Aleatorios------------------------
            for (int i = 0; i < paraules; i++)
            {
                aux = aleatori(0, paraules - 1);
                bool esta = false;
                int c = 0;
                while (!esta && c < i)
                {
                    if (historialAleatoris[c] == aux)
                    {
                        esta = true;
                        i--;
                    }
                    c++;
                }
                if (!esta)
                {
                    historialAleatoris[i] = aux;
                }
            }
            /*
            printf("\n");
            for (int i = 0; i < paraules; i++)
            {
                printf(" %d", historialAleatoris[i]);
            }
            printf("\n");
            */
            //---------------------------------------

            int indexParaules = 0;
            int indexAux = 0;
            printf("\n");
            while (indexParaules < paraules)
            {
                int i = 0;
                int cuentaEspacios = 0;
                bool encontrado = false;
                while (frase[linea][i] != '.' && !encontrado)
                {
                    if (frase[linea][i] == ' ')
                    {
                        cuentaEspacios++;
                        i++;
                    }
                    if (cuentaEspacios == historialAleatoris[indexParaules])
                    {
                        indexParaules++;
                        encontrado = true;
                        while (frase[linea][i] != ' ' && frase[linea][i] != '.')
                        {
                            frasesYodificadas[linea][indexAux] = frase[linea][i];
                            printf("%c",frasesYodificadas[linea][indexAux]);
                            i++;
                            indexAux++;
                        }
                        if (indexParaules == paraules)
                        {
                            frasesYodificadas[linea][indexAux] = '.';
                        }
                        else
                        {
                            frasesYodificadas[linea][indexAux] = ' ';
                        }
                        printf("%c",frasesYodificadas[linea][indexAux]);
                        indexAux++;
                    }
                    else
                    {
                        i++;
                    }
                }
            }
        }
        else
        {
            printf("\n");
            int indexParaules = 0;
            while (indexParaules < paraules)
            {
                indexParaules++;
                int i = 0;
                while (frase[linea][i] != ' ' && frase[linea][i] != '.')
                {
                    frasesYodificadas[linea][i] = frase[linea][i];
                    printf("%c",frasesYodificadas[linea][i]);
                    i++;
                }

                if (indexParaules == paraules)
                {
                    frasesYodificadas[linea][i] = '.';
                    printf("%c",frasesYodificadas[linea][i]);
                }
                else
                {
                    if (frase[linea][i] != '.')
                    {
                        frasesYodificadas[linea][i] = ' ';
                        printf("%c",frasesYodificadas[linea][i]);
                    }
                }
            }
        }
    }
}

void velocitat_1(bool se_ha_yodificado, int contadorFrases, int paraules, char frasesYodificadas[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1], char fraseFinal[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1 + 42], char frase[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1])
{
    if (se_ha_yodificado)
    {
        printf("Se ha yodificado\n\n");
        // S' afegeix el nombre de punts (en el cas maxim)
        for (int linea = 0; linea < contadorFrases; linea++)
        {
            int contadorParaules = 0;
            paraules = contarParaules(frasesYodificadas, linea);
            int i = 0;
            int indexAux = 0;
            while (frasesYodificadas[linea][i] != '.')
            {
                fraseFinal[linea][indexAux] = frasesYodificadas[linea][i];
                printf("%c",fraseFinal[linea][indexAux]);
                i++;
                indexAux++;
                if (frasesYodificadas[linea][i] == ' ')
                {
                    contadorParaules++;
                    if (contadorParaules % 2 == 0)
                    {
                        fraseFinal[linea][indexAux] = '.';
                        printf("%c",fraseFinal[linea][indexAux]);
                        indexAux++;
                        fraseFinal[linea][indexAux] = '.';
                        printf("%c",fraseFinal[linea][indexAux]);
                        indexAux++;
                        fraseFinal[linea][indexAux] = '.';
                        printf("%c",fraseFinal[linea][indexAux]);
                        indexAux++;
                        //SI QUIERES ESPACIO ENTRE LAS PALABRAS QUITA ESTE i++;
                        i++;
                    }
                }
            }
            if (contadorParaules % 2 == 0)
            {
                fraseFinal[linea][indexAux] = '.';
                printf("%c",fraseFinal[linea][indexAux]);
                indexAux++;
                fraseFinal[linea][indexAux] = '.';
                printf("%c",fraseFinal[linea][indexAux]);
                indexAux++;
                fraseFinal[linea][indexAux] = '.';
                printf("%c",fraseFinal[linea][indexAux]);
                indexAux++;
            }
            fraseFinal[linea][indexAux] = '\0';
            indexAux++;
            printf("\n");
        }
    }
    else
    {
        for (int linea = 0; linea < contadorFrases; linea++)
        {
            int contadorParaules = 0;
            paraules = contarParaules(frase, linea);
            int i = 0;
            int indexAux = 0;
            while (frase[linea][i] != '.')
            {
                fraseFinal[linea][indexAux] = frase[linea][i];
                printf("%c",fraseFinal[linea][indexAux]);
                i++;
                indexAux++;
                if (frase[linea][i] == ' ')
                {
                    contadorParaules++;
                    if (contadorParaules % 2 == 0)
                    {
                        fraseFinal[linea][indexAux] = '.';
                        printf("%c",fraseFinal[linea][indexAux]);
                        indexAux++;
                        fraseFinal[linea][indexAux] = '.';
                        printf("%c",fraseFinal[linea][indexAux]);
                        indexAux++;
                        fraseFinal[linea][indexAux] = '.';
                        printf("%c",fraseFinal[linea][indexAux]);
                        indexAux++;
                        //SI QUIERES ESPACIO ENTRE LAS PALABRAS QUITA ESTE i++;
                        i++;
                    }
                }
            }
            if (contadorParaules % 2 == 0)
            {
                fraseFinal[linea][indexAux] = '.';
                printf("%c",fraseFinal[linea][indexAux]);
                indexAux++;
                fraseFinal[linea][indexAux] = '.';
                printf("%c",fraseFinal[linea][indexAux]);
                indexAux++;
                fraseFinal[linea][indexAux] = '.';
                printf("%c",fraseFinal[linea][indexAux]);
                indexAux++;
            }
            fraseFinal[linea][indexAux] = '.';
            printf("%c",fraseFinal[linea][indexAux]);
            indexAux++;
            fraseFinal[linea][indexAux] = '\0';
            indexAux++;
            printf("\n");
        }
    }
}

void velocitat_2(bool se_ha_yodificado, int contadorFrases, int paraules, char frasesYodificadas[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1], char fraseFinal[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1 + 42], char frase[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1])
{
    if (se_ha_yodificado)
    {
        // S' afegeix el nombre de punts (en el cas maxim)
        for (int linea = 0; linea < contadorFrases; linea++)
        {
            paraules = contarParaules(frasesYodificadas, linea);
            int i = 0;
            int indexAux = 0;
            while (frasesYodificadas[linea][i] != '.')
            {
                fraseFinal[linea][indexAux] = frasesYodificadas[linea][i];
                printf("%c",fraseFinal[linea][indexAux]);
                i++;
                indexAux++;
                if (frasesYodificadas[linea][i] == ' ')
                {
                    fraseFinal[linea][indexAux] = '.';
                    printf("%c",fraseFinal[linea][indexAux]);
                    indexAux++;
                    fraseFinal[linea][indexAux] = '.';
                    printf("%c",fraseFinal[linea][indexAux]);
                    indexAux++;
                    fraseFinal[linea][indexAux] = '.';
                    printf("%c",fraseFinal[linea][indexAux]);
                    indexAux++;
                    //SI QUIERES ESPACIO ENTRE LAS PALABRAS QUITA ESTE i++;
                    i++;
                }
            }
            fraseFinal[linea][indexAux] = '.';
            printf("%c",fraseFinal[linea][indexAux]);
            indexAux++;
            fraseFinal[linea][indexAux] = '.';
            printf("%c",fraseFinal[linea][indexAux]);
            indexAux++;
            fraseFinal[linea][indexAux] = '.';
            printf("%c\n",fraseFinal[linea][indexAux]);
            indexAux++;
        }
    }
    else
    {
        for (int linea = 0; linea < contadorFrases; linea++)
        {
            paraules = contarParaules(frase, linea);
            int i = 0;
            int indexAux = 0;
            while (frase[linea][i] != '.')
            {
                fraseFinal[linea][indexAux] = frase[linea][i];
                printf("%c",fraseFinal[linea][indexAux]);
                i++;
                indexAux++;
                if (frase[linea][i] == ' ')
                {
                    fraseFinal[linea][indexAux] = '.';
                    printf("%c",fraseFinal[linea][indexAux]);
                    indexAux++;
                    fraseFinal[linea][indexAux] = '.';
                    printf("%c",fraseFinal[linea][indexAux]);
                    indexAux++;
                    fraseFinal[linea][indexAux] = '.';
                    printf("%c",fraseFinal[linea][indexAux]);
                    indexAux++;
                    //SI QUIERES ESPACIO ENTRE LAS PALABRAS QUITA ESTE i++;
                    i++;
                }
            }
            fraseFinal[linea][indexAux] = '.';
            printf("%c",fraseFinal[linea][indexAux]);
            indexAux++;
            fraseFinal[linea][indexAux] = '.';
            printf("%c",fraseFinal[linea][indexAux]);
            indexAux++;
            fraseFinal[linea][indexAux] = '.';
            printf("%c\n",fraseFinal[linea][indexAux]);
            indexAux++;
        }
    }
}

int main()
{
    int velocitat, yodificacio, paraules = 0, contadorFrases = 0;
    char nombreArchivo[MAX_ARCHIVO],
         frase[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1],
         frasesYodificadas[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1],
         fraseFinal[MAX_ARCHIVO][MAX_PAR * MAX_CAR + MAX_PAR - 1 + 42];
    //La semilla de el aleatori
    time_t t;
    srand((unsigned) time(&t));

    printf("----------- Fonaments de Programacio ----------\n");
    printf("Introdueix el nom de l'arxiu: ");
    //El programa supone que el input siempre tiene .txt al final
    gets(nombreArchivo);

    //if (METODO QUE LEE ARCHIVO)
    if (leerArchivo(nombreArchivo, frase, &contadorFrases))      /*  */
    {
        velocitat = demanaVelocitat();
        yodificacio = demanaYodificacio();
        bool se_ha_yodificado = false;

        switch (yodificacio)
        {
        case 0:
            printf("\n - No es fa res.");
            break;
        case 1:
            printf("\n------------ Frases Yodificades -------------\n\n");
            yodifica_1(contadorFrases, paraules, frase, frasesYodificadas);
            se_ha_yodificado = true;
            break;
        case 2:
            printf("\n------------ Frases Yodificades -------------\n\n");
            yodifica_2(contadorFrases, paraules, frase, frasesYodificadas);
            se_ha_yodificado = true;
            break;
        default:
            printf(" - Error! Velocitat incorrecta!");// Mai hi serà default perquè es controla a demana velocitat
        }

        //SWITCH CON VELOCIDAD
        switch (velocitat)
        {
        case 0:
            printf("\n\n - No es fa res.\n");
            if (se_ha_yodificado)
            {
                guardarArchivo(MAX_ARCHIVO, MAX_PAR * MAX_CAR + MAX_PAR - 1, frasesYodificadas, contadorFrases);
            }
            else
            {
                //Se pasa de la matriz frase original a frasesYodificadas para limpiar caràcteres no deseados
                for (int linea = 0; linea < contadorFrases; linea++)
                {
                    paraules = contarParaules(frase, linea);
                    int i = 0;
                    int indexAux = 0;
                    while (frase[linea][i] != '.')
                    {
                        frasesYodificadas[linea][indexAux] = frase[linea][i];
                        i++;
                        indexAux++;
                    }
                    if (frase[linea][i] == '.')
                    {
                        frasesYodificadas[linea][indexAux] = '.';
                        indexAux++;
                    }
                }
                guardarArchivo(MAX_ARCHIVO, MAX_PAR * MAX_CAR + MAX_PAR - 1, frasesYodificadas, contadorFrases);
            }
            break;
        case 1:
            printf("\n\n----------- Frases amb Velocitat ------------\n\n");
            velocitat_1(se_ha_yodificado, contadorFrases, paraules, frasesYodificadas, fraseFinal, frase);
            guardarArchivo(MAX_ARCHIVO, MAX_PAR * MAX_CAR + MAX_PAR - 1 + 42, fraseFinal, contadorFrases);
            break;
        case 2:

            printf("\n\n----------- Frases amb Velocitat ------------\n\n");
            velocitat_2(se_ha_yodificado, contadorFrases, paraules, frasesYodificadas, fraseFinal, frase);
            guardarArchivo(MAX_ARCHIVO, MAX_PAR * MAX_CAR + MAX_PAR - 1 + 42, fraseFinal, contadorFrases);
            break;
        default:
            printf(" - Error! Velocitat incorrecta!");// Mai hi serà default perquè es controla a demana velocitat
        }
        dibuixa_yoda();
    }
    else
    {
        printf("\n - No existeix un fitxer amb el nom '%s'", nombreArchivo);
    }
}
