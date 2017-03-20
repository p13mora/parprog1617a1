#include <stdio.h>
#include <emmintrin.h>
#include <sys/time.h>

void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}

int main(int argc, char **argv)
{

    int y,x,i,j,k,m; //x,y resolution , i,j trexon pixel , k,m geitonika pixel
    y=400;
    x=400;

    float *pixels=malloc(sizeof(float)*x*y);
    if(pixels==NULL) exit(1);
    float *transform=malloc(sizeof(float)*x*y);
    if(transform==NULL){free(pixels);exit(1);}
    float *result=malloc(sizeof(float)*x*y);
    if(result==NULL){free(pixels);free(transform);exit(1);}

    double ts,te;

    for(i=0;i<y;i++){

       for(j=0;j<x;j++){
         pixels[i*x+j]=(rand()%50+1)*1.245; //tixaio einai
         transform[i*x+j]=(float)(rand()%2==0)? 0.5 : 5.0;
         result[i*x+j]=0;

        }

    }





get_walltime(&ts);

    for(i=0; i<y; i++) {


        for(j=0; j<x; j++) {


            (i-1<0)? (k=0) : (k=i-1);


            for(;k<=i+1 && k<y; k++) {


                (j-1<0)? (m=0) : (m=j-1);


                for(; m<=j+1 && m<x; m++) {


                    result[i*x+j]+=(pixels[k*x + m]*transform[k*x+m]);




                }

            }


        }

    }

get_walltime(&te);

printf("%lf \n",te-ts);
  
return 0;

}
