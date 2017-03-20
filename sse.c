#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <sys/time.h>



void get_walltime(double *wct) {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}

int main(int argc, char **argv)
{

    int y,x,i,j;

    y=400;
    x=400;


    double te,ts;
    float *pixels,*transform,*result;
    __m128 *pix,*tr,*res,prev,cur,next;



    i=posix_memalign((void **)&pixels,16,x*y*sizeof(float));
    if(i!=0) exit(1);
    i=posix_memalign((void **)&transform,16,x*y*sizeof(float));
    if(i!=0) {free(pixels);exit(1);}
    i=posix_memalign((void **)&result,16,x*y*sizeof(float));
    if(i!=0) {free(pixels);free(transform);exit(1);}

     for(i=0;i<y;i++){

       for(j=0;j<x;j++){
       pixels[i*x+j]=(rand()%50+1)*1.245;
       transform[i*x+j]=(float)(rand()%2==0)? 0.5 : 5.0;
       result[i*x+j]=0;

        }

    }



pix=(__m128 *)pixels;
tr=(__m128 *)transform;
res=(__m128 *)result;


 get_walltime(&ts);

for(i=0;i<y*x;i+=4){

*tr=_mm_mul_ps(*pix,*tr);  //prota ola ta Pn * Kn
pix++;
tr++;

}



for(i=0;i<y;i++){


 for(j=0;j<x;j++){

    if(i==0){ 
      
        prev=_mm_set1_ps(0.0); //ean proti grammi tote den exei proigoumeni

        if(j==0){

           cur=_mm_set_ps(0,transform[(i)*x + j],transform[(i)*x + j +1],0.0f);
           next=_mm_set_ps(0,transform[(i+1)*x + j],transform[(i+1)*x + j +1],0.0f);
          
        }
        else if(j==x-1){


           cur=_mm_set_ps(transform[(i)*x + j-1],transform[(i)*x + j],0.0f,0.0f);
           next=_mm_set_ps(transform[(i+1)*x + j-1],transform[(i+1)*x + j],0.0f,0.0f);

        }

       else {

         cur=_mm_set_ps(transform[(i)*x + j-1],transform[(i)*x + j],transform[(i)*x + j +1],0.0f);
         next=_mm_set_ps(transform[(i+1)*x + j-1],transform[(i+1)*x + j],transform[(i+1)*x + j +1],0.0f);

       }

    }else if(i==y-1){


    next=_mm_set1_ps(0.0); //ean teleutaia den exei epomeni

        if(j==0){


            prev=_mm_set_ps(0,transform[(i-1)*x + j],transform[(i-1)*x + j +1],0.0f);
            cur=_mm_set_ps(0,transform[(i)*x + j],transform[(i)*x + j +1],0.0f);
          
         }
        else if(j==x-1){


          prev=_mm_set_ps(transform[(i-1)*x + j-1],transform[(i-1)*x + j],0,0.0f);
          cur=_mm_set_ps(transform[(i)*x + j-1],transform[(i)*x + j],0,0.0f);

        }

       else {

         prev=_mm_set_ps(transform[(i-1)*x + j-1],transform[(i-1)*x + j],transform[(i-1)*x + j +1],0.0f);
         cur=_mm_set_ps(transform[(i)*x + j-1],transform[(i)*x + j],transform[(i)*x + j +1],0.0f);

       }





    }else{


     if(j==0){


      prev=_mm_set_ps(0,transform[(i-1)*x + j],transform[(i-1)*x + j +1],0.0f);
      cur=_mm_set_ps(0,transform[(i)*x + j],transform[(i)*x + j +1],0.0f);
      next=_mm_set_ps(0,transform[(i+1)*x + j],transform[(i+1)*x + j +1],0.0f);

      }
      else if(j==x-1){


      prev=_mm_set_ps(transform[(i-1)*x + j-1],transform[(i-1)*x + j],0,0.0f);
      cur=_mm_set_ps(transform[(i)*x + j-1],transform[(i)*x + j],0,0.0f);
      next=_mm_set_ps(transform[(i+1)*x + j-1],transform[(i+1)*x + j],0,0.0f);


        }

       else {

      prev=_mm_set_ps(transform[(i-1)*x + j-1],transform[(i-1)*x + j],transform[(i-1)*x + j +1],0.0f);
      cur=_mm_set_ps(transform[(i)*x + j-1],transform[(i)*x + j],transform[(i)*x + j +1],0.0f);
      next=_mm_set_ps(transform[(i+1)*x + j-1],transform[(i+1)*x + j],transform[(i+1)*x + j +1],0.0f);


       }


    }



    prev=_mm_add_ps(prev,_mm_add_ps(cur,next)); //prosthesi twn triwn grammwn
    result[i*x+j]=_mm_cvtss_f32(_mm_add_ss(_mm_shuffle_ps(prev,prev,0),_mm_add_ss(_mm_shuffle_ps(prev,prev,1),_mm_shuffle_ps(prev,prev,2))));



  }



}
  
get_walltime(&te);

printf("%lf \n",te-ts);

}
