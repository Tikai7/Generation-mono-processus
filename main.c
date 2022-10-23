#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//-------------------------------- STRUCTURE DE DONNEES DU PROGRAMME --------------------------------//


typedef struct Operateur{
    char value;
    int index;
}Operateur;

typedef struct Noeud{
    Operateur operateur;
    int precedence;
    int nom;
}Noeud;


//-------------------------------- FONCTION QUI COMPTE CARACTERES D'UNE STRING  --------------------------------//

int count_of(char* string){
    int compteur=0;

    for(int i=0;string[i];i++)
        compteur++;
    

    return compteur;
}


//-------------------------------- FONCTION QUI VERIFIE SI UN CARACTERE EST UN OPERATEUR --------------------------------//


int is_operator(char letter){
  
    if (letter == '+' || letter=='*' ||letter=='/' ||letter=='-')
	    return 1;
	
    
    return 0;
}

//-------------------------------- FONCTION QUI VERIFIE SI UNE CHAINE EST UNE EXPRESSION --------------------------------//


int is_expression(char* string,int nb_letters){

    int boolean = -1;

    for (int i=0;i<nb_letters;i++){
        if(string[i] == '(')
            boolean += 1;
        
        if(string[i] == ')')
            boolean++;
        
    }
    if(boolean>0)
        boolean=1;
    else 
        boolean = 0;

    return boolean;
}

//-------------------------------- FONCTION QUI TROUVE L'OPERATEUR PRINCIPALE --------------------------------//


Operateur find_operator(char *string,int nb_letters){

  
    Operateur operator_principal;
    int first_time = 1;
    int temp = 0;
    int count_nb_parenthese=0;

    for(int i=0;i<nb_letters;i++){

        if (string[i]=='('){
            temp = count_nb_parenthese;
            count_nb_parenthese++;
        }
        else if(string[i]==')'){
            temp = count_nb_parenthese;
            count_nb_parenthese--;
        }
        else if (is_operator(string[i]) == 1 && count_nb_parenthese <= temp){
            operator_principal.value = string[i];
            operator_principal.index = i;
        }

		if(first_time  == 1 && is_operator(string[i])){
			operator_principal.value = string[i];
            operator_principal.index = i;
			first_time = 0;
		}
            
    }

    return operator_principal;
}

//-------------------------------- FONCTION QUI CHERCHE L'EXPRESSION A DROITE --------------------------------//

char* find_left(int index,char*string,int nb_letters){

    int left_nb_letters = index-1;
    int j=0;

    char *left_expression = (char*)malloc(sizeof(char)*left_nb_letters);
    
    for(int i=index-1;i>0;i--){
        left_expression[j]=string[i];
        j++;        
    }
    
    int temp_nb_letter = count_of(left_expression);
    int count;
    char temp;
   
    for(int i= 0;i<(int)temp_nb_letter/2;i++){
        temp=left_expression[i];
        left_expression[i]=left_expression[temp_nb_letter-i-1];
        left_expression[temp_nb_letter-i-1] = temp;
    }

    return left_expression;

}

//-------------------------------- FONCTION QUI CHERCHE L'EXPRESSION A GAUCHE --------------------------------//

char* find_right(int index,char*string,int nb_letters){

    int j=0;
    int right_nb_letters = nb_letters-index-3;
    char *right_expression = (char*)malloc(sizeof(char)*right_nb_letters);

    for(int i=index+1;i<nb_letters-1;i++){
        right_expression[j] = string[i];
        j++;
    }

    return right_expression;
}

//-------------------------------- FONCTION PRINCIPALE QUI GENERE LE GRAPHE DE PRECEDENCE --------------------------------//


char* generate(char *string,int nb_letters,int niveau,int parent){

    printf("%s \n",string);
    printf("Mon pere : %d \n",parent);

        // genere_noeud() generere_tache() genere_precedence()
    Noeud tache;
    Operateur operator = find_operator(string,nb_letters);
    

    char *left_string = find_left(operator.index,string,nb_letters);
    char *right_string = find_right(operator.index,string,nb_letters);


    int nb_left = count_of(left_string);
    int nb_right = count_of(right_string);

    char *expression_left;
    char *expression_right;

  
    if(is_expression(left_string,nb_left)==1)
        expression_left = generate(left_string,nb_left,niveau+1,niveau);
    
    if(is_expression(right_string,nb_right)==1)
        expression_right = generate(right_string,nb_right,niveau+1,niveau); 
    

    tache.nom=niveau;
    tache.operateur = operator;
    tache.precedence = parent;

    return "";
   


}


int main(){

    //char expression[]="((A+B)*(C-(D/E)))";
    char expression[]="(((A+B)*C)-(((D-(F/G))*(H+(K*L)))/((M-N)*O))))";

    int nb_letters = count_of(expression);
    
    generate(expression,nb_letters,1,0);



    return 0;
}