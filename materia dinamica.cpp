#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void distancia (double a,double b,double c, double dist [1000], double v [3000]);
void calculo(double v[3000], double u[3000], double dist[1000],int X,int Y,int Z, int j, double vel[3000]);
double velocidade (double vel[3000], int k, int j, double SOMA);

int main (){
int X=0,Y=0,Z=0,t;
int A,B,C,i=0,j,w;
double u[3000],aux,v[3000],bux;
double R,dist[1000],SOMA=0,vel[3000];
FILE *arqOut, *arqIn, *cr;
 arqIn = (FILE *) fopen ("espectro13000.txt","r");
 arqOut= (FILE *) fopen ("dist.txt","r");
 cr= (FILE *) fopen ("espectro140.txt","w");
// parametros iniciais 
for(t=0;t<3000;t++){
 vel[t]=0;}
while(fscanf(arqIn,"%lf",&aux) != EOF){
 v[i]=aux;
 u[i]=aux;
 i=i+1;}

////   INICIO DO PROGRAMA  ////
//for(t=0;t<20;t++){
//printf("\n\%d\n\n",t);
for(j=0;j<3;j++){    

// for(Z=-1;Z<=1;Z++){ 
//  for(Y=-1;Y<=1;Y++){ 
//   for(X=-1;X<=1;X++){
 printf("%d\n\n\n\n\n",j);  
    calculo(v,u,dist,X,Y,Z,j,vel);

printf("%d",X);
printf("%d",Y);
printf("%d",Z);

//}
//}
//}
}

//for (i=0;i<3000;i++){
//v[i] = u[i];}
//}


///  ESCREVER O PROGRAMA  ///
for (i=0;i<3000;i++){ 
 fprintf(cr,"%lf\n",u[i]);
}

//fechar arquivo
fclose (arqIn); 
fclose (arqOut);
fclose (cr);
system ("PAUSE"); 
return 0;}


void distancia (double a,double b,double c, double dist [1000], double v [3000]){
int i=0,j,p;
double l;
FILE  * arqOut;
arqOut = (FILE *) fopen("dist.txt","w+");
for(j=0;j<3000;j=j+3){
l =(sqrt(pow(v[j]-a,2) + pow(v[j+1]-b,2) + pow(v[j+2]-c,2)));
p = j/3;
dist[p]= l;
fprintf(arqOut,"%lf\n",l);}
fclose (arqOut);} 


void calculo(double v[3000], double u[3000], double dist[1000],int X,int Y,int Z,int j, double vel[3000]){
int k,w,i,per=0;
double SOMA,velo;
FILE * olhe;
olhe = (FILE *) fopen("atencao.txt", "w+");

if( j == 0 ){
  per=X;}
if( j == 1 ){
  per=Y;}
if( j == 2 ){
  per=Z;}          
 
for (k=0;k<1000;k++){
 
 distancia(v[3*k] + X,v[3*k+1] + Y,v[3*k+2] + Z, dist,v);
 SOMA=0;
 for (w=0;w<1000;w++){
  if( dist[w] != 0 ){
   SOMA = SOMA + (1/(pow(dist[w],3)))*(v[3*w+j] - (v[3*k+j] + per));
 }}

velo=velocidade (vel,k,j,SOMA);
fprintf(olhe,"%lf\n",vel[3*k+j]); 

   u[3*k+j] = u[3*k+j] + velo + (6.67384*(pow(10,-11)))*SOMA*(pow(20,2)/2); 
  
  if ( 1.0 <= u[3*k+j] ){
  u[3*k+j]=u[3*k+j]-1;}   
  
  if ( u[3*k+j] <= 0.0 ){
  u[3*k+j]=u[3*k+j]+1;}   
  
  }
fclose(olhe);
}

double velocidade (double vel[3000], int k, int j, double SOMA){

vel[3*k+j] = vel[3*k+j] + (6.67384*(pow(10,-11))*SOMA*20);

return vel[3*k+j];}

