#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "action.h"

/*Les valeurs associées à chaque action dans le .aut*/
enum actions{   
    Rejette = 0,
    Accepte = 1,
    Decale = 2,
    Reduit = 3,
};

/*Affiche et retourne le nombre d'états n de l'automate*/ 
int print_states(FILE* f){
    int n;
    fscanf(f, "a %i\n", &n);
    /*printf("Number of states: %i\n", n);*/
    return n;
}

/*Création d'un tableau 2D afin de stocker les données lues*/
matrix create_matrix(int line, int column){
    matrix mat = (matrix) malloc(line*sizeof(int*));
    int i;
    for (i=0;i<line;i+=1){
        mat[i]=(int*) malloc(column*sizeof(int));/*chaque case 1D pointe vers un tableau 1D*/
    }
    return mat;
}

/*Libère la mémoire utilisée*/
void free_matrix(matrix mat, int line){
    int i;
    for(i = 0; i < line; i++){
        free(mat[i]);}
    free(mat);
}

/*Affichage test*/
void print_matrix(matrix mat,int line, int column){
    int i,j;
    for(i=0;i<line;i++){
        printf("|");
        for(j=0;j<column;j++){
            printf("%i",mat[i][j]);
            if(j<column-1){
                printf(",");}
        }
        printf("|\n");
    }
}

/* Les actions pour chaque paire état/caractère*/
matrix get_action(FILE* f,int n){
    char buf[BUFSIZ];
    fgets(buf, sizeof(buf), f);
    matrix m_action = create_matrix(n,128);
    int i,j;
    for (i = 0; i < n; i++){
        for (j = 0; j < 128; j++){
            m_action[i][j] = buf[i*128+j];} /*formule des tableaux 1D : tampon 1D dans une tableau 2D*/
    }
    return m_action;
}

 /* Les 2 composantes de réduit pour chaque état*/
matrix get_reduit(FILE* f,int n){
    int line=5; /*nombre de caractères sur la 1ère ligne pour la plupart des .aut*/
    if (n==30){ /*cas de arith.aut*/
        line+=1;
    }
    unsigned char buf[BUFSIZ]; /*unsigned pour éviter que 255 soit lu comme un -1*/
    fseek(f, n*128+line, SEEK_SET);
    fread(buf, BUFSIZ, sizeof(buf), f);
    matrix m_reduit= create_matrix(2*n,1);
    int i;
    for (i = 0; i < n; i++){ /*Reduit(s) = [s'(de 0 à n), A(de n+1 à 2n)]*/
            m_reduit[i][0] = buf[i];
            }
    for (i = n; i < 2*n; i++){ 
            m_reduit[i][0] = buf[i+1]; /*décalage de 1 pour sauter le \n*/
            }
    return m_reduit;
}

/* La composante partielle décale pour chaque paire état/caractère*/
matrix get_decale(FILE* f,int n){ 
    int line=5;
    if (n==30){
        line+=1;}

    char buf[3]; /*buf[0]= ancien état s , buf[1]= caractère lu c, buf[2]= nouvel état s'*/
    fseek(f, n*130+line+2, SEEK_SET); /* on place le curseur au bon endroit ; +2 pour sauter le \n*/
    matrix m_decale= create_matrix(n,128); 

    /*se termine quand (s,c,s')=('\255','\255','\255')= fin de décale*/
    while (fread(buf, sizeof(char), 3, f)!=0 && (buf[0]!='\255' && buf[1]!='\255' && buf[2]!='\255')){ 
        m_decale[(int)buf[0]][(int)buf[1]] = buf[2];}

    return m_decale;
}

/* La composante partielle branchement pour chaque paire état/caractère*/
matrix get_branchement(FILE* f,int n){
    int line=5;
    if (n==30){
        line+=1;}
        
    int taille_decale=0; /*compteur de caractères contenu dans décale afin de placer le curseur pour branchement*/
    if (n==3){
        taille_decale+=159; /*cas de word_bis.aut*/
    } 
    if (n==4){
        taille_decale+=315; /*cas de word.aut*/
    }
    if (n==7){
        taille_decale+=15; /*cas de dyck.aut*/
    }
    if (n==30){
        taille_decale+=375; /*cas de arith.aut*/
    }
    char buf[3]; /*buf[0]=s , buf[1]=A, buf[2]=s'*/
    fseek(f, n*130+line+2+taille_decale, SEEK_SET); /*on place le curseur on bon endroit comme pour decale*/
    matrix m_branchement= create_matrix(n,128); 

    /*se termine quand (s,A,s')=('\255','\255','\255')= fin de branchement*/
    while (fread(buf, sizeof(char), 3, f)!=0 && (buf[0]!='\255' && buf[1]!='\255' && buf[2]!='\255')){ 
        m_branchement[(int)buf[0]][(int)buf[1]] = buf[2];}

    return m_branchement;
}
