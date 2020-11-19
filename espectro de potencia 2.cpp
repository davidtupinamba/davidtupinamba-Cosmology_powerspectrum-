#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double intervalo_ep (double t[5000], double cor[5000], double x, int j);

int main (void){
  int i=0,j;
  double t[5000],cor[5000],h,TOTAL,Y;
  double Soma1=0,Soma2=0,Soma=0,bux,k,x,correlation=0;
  FILE *shell, *correlacao,*ep;
  shell = (FILE *) fopen("escudo.txt","r");
  correlacao = (FILE *) fopen ("cr 1 de 3.txt","r");
  ep = (FILE *) fopen ("espectro final.txt","w+");
  

// parametros iniciais   
 h=0.00009;
 while(fscanf(shell,"%lf",&bux) != EOF){
  t[i]=bux;
  i=i+1;}
  i=0;
 while(fscanf(correlacao,"%lf",&bux) != EOF){
  cor[i]=bux;
  i=i+1;}
  
    
// CALCULO DO ESPECTRO DE POTENCIA  
  
for (k=0.006;k<=0.1;k=k+0.001){
printf("%lf\n",k);
 
 x = 0.0621;
 for(j=0;j<4998;j++){
  Y = intervalo_ep ( t, cor, x, j); 
  correlation = correlation + Y;}
 Soma = Soma + (correlation)*( ((sin(x*k)))/(k*x));

 correlation=0;
 x = 0.4929;
 for(j=0;j<4998;j++){
  Y = intervalo_ep ( t, cor, x, j); 
  correlation = correlation + Y;}
 Soma = Soma + (correlation)*(((sin(x*k)))/(k*x));
   
 correlation=0;
 for(i=1;i<4998;i=i+2){
  x = i*h;
   for(j=0;j<4998;j++){
    Y = intervalo_ep (t, cor, x, j); 
    correlation = correlation + Y;}
 Soma1 = Soma1 + (correlation)*(((sin(x*k)))/(k*x));}

 correlation=0;
 for(i=2;i<4998;i=i+2){
  x = i*h;
   for(j=0;j<4998;j++){
    Y = intervalo_ep (t, cor, x, j); 
    correlation = correlation + Y;}
 Soma2 = Soma2 + (correlation)*(((sin(x*k)))/(k*x));}
   
  TOTAL = (0.012566*h/3)*( Soma + 2*Soma2 + 4*Soma1 );

//printf("%lf\n",TOTAL);

  fprintf(ep,"%lf\n",TOTAL);
}
  
  fclose (ep);   
  fclose (correlacao);
  fclose (shell);
  system ("PAUSE"); 
  return 0;}

double intervalo_ep (double t[5000], double cor[5000], double x, int j){
int l;
double r=0;
l=j;  
 if ( t[l] <= x && x < t[l+1] ){
  r = x*(cor[l+1] - cor[l])/(t[l+1] - t[l]) + (cor[l+1]*t[l] - cor[l]*t[l+1])/(t[l+1] - t[l]);
}
 return r;}
