#include <string.h>
#include <stdio.h>
#define BUFFER 64
#define BUFFER_CHIQUITO 32
#define PLAN 10

//NOMBRE-APELLIDO-EDAD-MESESINSCRIPTO-TIPOPLAN
//PLAN-PRECIOPLAN-DESCUENTO

void parse_line(char*);
void unparse_line(char*);
int get_total(FILE*, char*,int,int);

int main(){
    int edad,meses_socio, total;
    char plan[PLAN];
    char linea[BUFFER];
    FILE *personas = fopen("personas.txt","r");
    FILE *tabla_planes = fopen("plan.txt","r");
    FILE *personas_actualizado = fopen("personas-actualizado.txt","w");

    while(fscanf(personas,"%s",linea) != EOF){
        parse_line(linea);
        sscanf(linea,"%*s %*s %d %d %s",&edad,&meses_socio,plan);
        unparse_line(linea);
        total = get_total(tabla_planes,plan,edad,meses_socio);
        fprintf(personas_actualizado,"%s-%d\n",linea,total);
    }

    fclose(personas);
    fclose(tabla_planes);
    fclose(personas_actualizado);

    return 0;
}

void parse_line(char *linea){
    int i = 0;
    while(linea[i] != '\0'){
        if(linea[i] == '-'){
            linea[i] = ' ';
        }
        i++;
    }
}
void unparse_line(char *linea){
    int i = 0;
    while(linea[i] != '\0'){
        if(linea[i] == ' '){
            linea[i] = '-';
        }
        i++;
    }
}
int get_total(FILE *fp, char *plan, int edad, int meses){
    float total = 0,discount = 0;
    char linea_plan[BUFFER_CHIQUITO];
    char plan_file[PLAN]; //string que obtiene el tipo de plan del archivo de planes
    rewind(fp);

    do{
        fscanf(fp,"%s",linea_plan);
        parse_line(linea_plan);
        sscanf(linea_plan,"%s %f %f", plan_file,&total,&discount);
    }while(!feof(fp) && strcmp(plan_file,plan));

    if(meses >= 24)
        total = total - total * (discount * 1.0/100.0);

    if(edad < 12 || edad > 65)
        total = total - total * (5.0/100.0);

    return total;
}
