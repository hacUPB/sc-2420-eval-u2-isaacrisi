#include<stdio.h>
#include<math.h>





float CalcIMC(float, float);
float estatura, peso, imc;

int main(int argc, char const *argv[])
{
    
    char Nombre[30];

    printf("Ingrese su nombre: \n");
    fgets(Nombre, 30, stdin);
    
    printf("ingrese su peso \n");
    scanf("%f", &peso);

    printf("ingrese su estatura \n");
    scanf("%f", &estatura);
    CalcIMC(peso, estatura);
    printf("%ssu imc es igual a %f \n", Nombre,imc);
    
}

float CalcIMC(float peso, float estatura)
{
    imc = peso/pow(estatura,2);
    return imc;
}
