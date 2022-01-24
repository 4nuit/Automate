#ifndef ACTION_H
#define ACTION_H

typedef int **matrix;

/*
requires: f!=NULL
assigns: nothing
ensures: returns int n = number of states of the automaton
*/
int print_states(FILE* f);

/*
requires: width line n>=0 & height column m>=0
assigns: n * sizeof(int) cases in width & m* sizeof(int) cases in height
ensures: returns a 2D array / matrix
*/
matrix create_matrix(int line,int column);

/*
@requires: mat has size m
@assigns: nothing
@ensures: frees memory allocated to mat*/
void free_matrix(matrix mat, int line);

/*
requires: matrix m
assigns: nothing
ensures: prints an extracted matrix of m with new width =n and height=m
*/
void print_matrix(matrix mat,int line, int column);

/*
requires:f!=NULL, n = number of states >=0
assigns: n * sizeof(int) cases in width & 128* sizeof(int) cases in height
ensures: returns m_action
*/
matrix get_action(FILE* f,int n);

/*
requires: file* f!=NULL, int n = number of states >=0
assigns: n * sizeof(int) cases in width
ensures: returns m_reduit
*/
matrix get_reduit(FILE* f,int n);

/*
requires: file* f!=NULL, int n = number of states >=0
assigns: at most n * sizeof(int) cases in width && 128 in height
ensures: returns m_decale
*/
matrix get_decale(FILE* f,int n);

/*
requires:f!=NULL, n = number of states >=0
assigns: at most n * sizeof(int) cases in width && 128 in height
ensures: returns branchement
*/
matrix get_branchement(FILE* f,int n);

#endif