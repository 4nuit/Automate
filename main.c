#include "action.c"
#include "stack.c"

/*
@requires valid file.aut and valid word input 
@assigns nothing
@ensures prints if the word is known or not
*/
int automate(char* input,int n,matrix m_action, matrix m_reduit, matrix m_decale, matrix m_branchement){
    /*État initial mis dans la pile */
    stack stack = new_s();
    push(&stack, 0); /*État initial mis dans la pile */
    for (int i=0;i<=(int)strlen(input);i++){ 
        int BRANCHEMENT_TEST=1; 
        while (BRANCHEMENT_TEST==1){ /*se termine quand on atteint un branchement*/
            if (m_action[last(&stack)][(int)input[i]]==Rejette){ /*last(&stack) = sommet de la pile = état courant*/
                BRANCHEMENT_TEST=0;
                printf("Rejected \n");
                printf("Cause: incorrect %c on position %i\n",input[i],i+1); 
                return 0;
            }
            else if (m_action[last(&stack)][(int)input[i]]==Accepte){
                BRANCHEMENT_TEST=0;
                printf("Accepted \n");   
                return 0;
            }
            else if (m_action[last(&stack)][(int)input[i]]==Decale){
                BRANCHEMENT_TEST=0;
                /*état s'*/
                push(&stack, m_decale[last(&stack)][(int)input[i]]);
            }
            else if (m_action[last(&stack)][(int)input[i]]==Reduit){
                int m = m_reduit[last(&stack)][0];
                int A = m_reduit[n+last(&stack)][0];
                for(int j=0;j<m;j++){ /*on dépile m états*/
                    pop(&stack);
                }
                /*état s'*/
                push(&stack, m_branchement[last(&stack)][A]); /*on reste sur la même lettre grâce à la boucle while*/
            }
        }
    } 
    return 0;
}

/*
@requires valid file.aut and n=number of states of file.aut >=0 
@assigns nothing
@ensures writes the state graph of file.aut in file.dot
*/
int graphe(int n,matrix m_reduit,matrix m_decale, matrix m_branchement){
    char* f;
    if (n==3){
        f="word_bis.dot";
    }
    else if (n==4){
        f="word.dot";
    }
    else if (n==7){
        f="dyck.dot";
    }
    else if (n==30){
        f="arith.dot";
    }
    FILE* new_f;
    char* filename = f;
    new_f = fopen(filename,"w");
    printf("File %s created.\n",filename);
    if (new_f==NULL){
        perror("fopen"); /*écrit la dernière erreur rencontrée par fopen */
        return 0;  
    }
    fprintf(new_f,"digraph { \n");
    for(int i = 0; i < n; i++){ /*liste de tous les sommets*/
        fprintf(new_f,"%d ;\n", i);
    }
    for(int i = 0; i < n; i++){ 
        if (m_reduit[i][0]!=255){ /*création des arêtes pour réduit en bleu*/
            fprintf(new_f,"%i -> \"%i,%c\" [color = blue];\n", i,m_reduit[i][0],m_reduit[i+n][0]);} 
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 128; j++){ /*création des arêtes pour décale en noir*/
            if (m_decale[i][j]!=0){
                /*\" pour imprimer les guillemets*/
                fprintf(new_f,"%i -> %i [color = black,label= \"%c\"];\n", i,m_decale[i][j],j);} 
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 128; j++){ /*création des arêtes pour branchement en rouge*/
            if (m_branchement[i][j]!=0){
                fprintf(new_f,"%i -> %i  [color = red,label= \"%c\"];\n", i,m_branchement[i][j],j);
                /*création des arêtes pour accepte en vert = noeud provenant d'un branchement et ne créeant pas de réduit*/
                if (m_reduit[m_branchement[i][j]][0]==255 && m_decale[m_branchement[i][j]][j]==0){ 
                    fprintf(new_f,"%i -> Accepte [color = green,label= \"%c\"];\n",m_branchement[i][j],j);
                }

            }
        }
    }
    fprintf(new_f,"}\n");
    fclose(new_f);
    system("./graphes.sh"); /* script shell qui génère le graphe à partir du fichier.dot*/ 

    return 0;
}

int main(int argc, char* argv[]){
    /*Ouverture du fichier.aut*/
    FILE *f = NULL;
    f = fopen(argv[1],"rb");

    /*Gestion des erreurs*/
    if(argc != 2){ 
        fprintf(stderr, "%i args, expected 1 \n", argc-1);
        return 0;
    }
    if(f == NULL){
        printf("Cannot open file %s \n",argv[1]);
        return 0;
    }    
    printf("File %s correctly read. Please enter your inputs.\n",argv[1]);
  
    /*Récupération des données*/
    int n = print_states(f);
    matrix m_action = get_action(f,n);
    matrix m_reduit = get_reduit(f,n);
    matrix m_decale = get_decale(f,n);
    matrix m_branchement = get_branchement(f,n);

    /*Affichage des fonctions d'état*/
    //print_matrix(m_action,n,128);
    //print_matrix(m_reduit,2*n,1);
    //print_matrix(m_decale,n,128);
    //print_matrix(m_branchement,n,128);

    /*Création du graphe des états dans fichier.dot*/
    graphe(n,m_reduit,m_decale,m_branchement);

    /*Fermeture du fichier*/
    fclose(f);

    /*Application de l'automate*/
    char input[256];
    for(int iteration=0;iteration<10;iteration++){ /*autorise 10 entrées*/
        fgets(input, 256, stdin);
        automate(input,n,m_action,m_reduit,m_decale,m_branchement);
    }
    
    /*Libère la mémoire utilisée*/
    free_matrix(m_action,n); 
    free_matrix(m_reduit,2*n);
    free_matrix(m_decale,n);
    free_matrix(m_branchement,n);
}
