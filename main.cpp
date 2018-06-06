#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <allegro.h>
#define DOSYA_YOLU "input44.txt"
#define outR "outR.txt"
#define outQ "outQ.txt"
using namespace std;


    void init() {
        int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0) depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    if (res != 0) {
    allegro_message(allegro_error);
    exit(-1);
    }
    install_timer();
    install_keyboard();
    install_mouse();
    set_window_title("maZe");
    release_screen();


            if (res != 0) {
            allegro_message(allegro_error);
            }
    show_mouse(screen);


    }











int main()
{
    srand(time(NULL));
    FILE * dosya;
	dosya = fopen(DOSYA_YOLU, "r");
    char c;
    int d[100][100];
    int i=0,j=0;
    int x=0;
    int u;
    int rast1,rast2;
    float gamma=0.8;




    while ((c = fgetc(dosya)) != EOF) {
        if(c==',' || c=='\n'){
            if(c==','){
                j++;
                x=0;
            }
            if(c=='\n'){
                j++;
                d[i][j]=-1;
                i++;
                j=0;
                x=0;
            }
        }else{
            if(x!=0){
                d[i][j]=d[i][j]*10+((int)c)-48;
            }else{
                d[i][j]=((int)c) -48;
                x++;
            }
        }
    }

    int N=i;

    fclose(dosya);

    int baslangic=-1;
    int hedef=-1;
    while(baslangic>i-1 || baslangic<0 || hedef>i-1 || hedef<0){
        printf("Baslangic odacik:");
        scanf("%d",&baslangic);

        printf("Hedef odacik:");
        scanf("%d",&hedef);
    }
    int K;
    printf("Iterasyon sayisi:");
    scanf("%d",&K);

    int R[N][N];

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            R[i][j]=-1;
        }
    }

    for(i=0;i<N;i++){
        for(j=0; d[i][j]!=-1;j++){
            if(d[i][j]!=hedef){
                R[i][d[i][j]]=0;
            }else{
                R[i][d[i][j]]=100;
            }
        }
    }
    R[hedef][hedef]=100;

    dosya = fopen(outR, "w");
    printf("\nR matrisi\n");
    fprintf(dosya,"R Matrisi\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d\t",R[i][j]);
            fprintf(dosya,"%d\t",R[i][j]);
        }
        printf("\n");
        fprintf(dosya,"\n");
    }
    fclose(dosya);

    printf("\n\n");
    //Q matrisi oluşturma

    float Q[N][N];
        for (i=0;i<N;i++) {
            for (j=0;j<N;j++)
            {
                Q[i][j]=0;
            }

        }

   /*     for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d\t",Q[i][j]);

        }
        printf("\n");

    }
    */
    printf("\n\n");
    printf("Q Matrisi\n");
        for (i=0;i<K;i++) {


            int I=0;
            int Y;
            int rast[N];

            rast1=rand()%N;
            int j=0;
            for (j=0;j<N;j++) {

                if (R[rast1][j]==0 || R[rast1][j]==100 )
                {
                 rast[I]=j;
                 I++;
                }

                }
                Y=rand()%I;
            rast2=rast[Y];

            //printf("[%d],[%d]\n",rast1,rast2);


            int l;
            int maxQ=-1;
            int maxDizi[N];
            I=0;
            for(l=0;l<N;l++){
                if(R[rast2][l]!=-1){
                    maxDizi[I]=l;
                    I++;
                }
            }
            for(l=0;l<I;l++){
                if(Q[rast2][maxDizi[l]]>maxQ){
                    maxQ=Q[rast2][maxDizi[l]];
                }
            }
            Q[rast1][rast2]=R[rast1][rast2]+(gamma*maxQ);
            rast1=rast2;




        }





        dosya = fopen(outQ, "w");
        fprintf(dosya,"Q Matrisi\n");
        for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%.1f\t",Q[i][j]);
            fprintf(dosya,"%.1f\t",Q[i][j]);
        }
        printf("\n");
        fprintf(dosya,"\n");
    }




    fclose(dosya);


    int yolDizi[N];
    yolDizi[0]=baslangic;

    int y=0,maxj=0,maxy=0;
    int pDizi=0;
    while(yolDizi[y]!=hedef){
        for(j=0;j<N;j++){
            if(Q[yolDizi[y]][j]>maxy){
                maxy=Q[yolDizi[y]][j];
                maxj=j;
            }
        }
        y++;
        yolDizi[y]=maxj;
        pDizi++;
        maxj=0;
        maxy=0;
    }
    int k=y;



    dosya = fopen("outPath.txt", "w");
    for(i=0;i<y;i++){
        printf("%d, ",yolDizi[i]);
        fprintf(dosya,"%d, ",yolDizi[i]);
    }
    printf("%d",hedef);
    fprintf(dosya,"%d",hedef);



    //GRAFIK


    init();
    int siyah = makecol(0, 0, 0);
    int beyaz = makecol(255, 255, 255);
    int kirmizi = makecol(255, 0, 0);
    int sabit=100;
    int kutuxy[N][N];
    int ilkKorx=20;
    int ilkKory=20;
    int artis=100;




    //KABA LABIRENT CIZIMI
    for(j=0;j<sqrt(N);j++){

        for(i=0;i<sqrt(N);i++){

                rectfill(screen,ilkKorx+i*artis,ilkKory+j*artis,ilkKorx+(i+1)*artis,ilkKory+(j+1)*artis,beyaz);

        }
    }

    for(j=0;j<sqrt(N);j++){

        for(i=0;i<sqrt(N);i++){

                rectfill(screen,ilkKorx+i*artis+10,ilkKory+j*artis+10,ilkKorx+(i+1)*artis-10,ilkKory+(j+1)*artis-10,siyah);

        }
    }

    //BAGLANTILARIN OLUSTURULMASI













        int a;
        int b;
        int ax;
        int ay;
        int bx;
        int by;
        int boyut;
        boyut=sqrt(N);
        for(b=0;b<N;b++){
        for(a=0;a<N;a++){
                    ax=a%boyut;
                    ay=a/boyut;
                    bx=b%boyut;
                    by=b/boyut;

                if (R[a][b]==0) {
                rectfill(screen,ilkKorx+ax*artis+10,ilkKory+ay*artis+10,ilkKorx+(bx+1)*artis-10,ilkKory+(by+1)*artis-10,siyah);

                        }

                    }

                }


        //Yolun Cizdirilmesi


        for (i=0;i<pDizi;i++){

            a=yolDizi[i];
            b=yolDizi[i+1];
            ax=a%boyut;
            ay=a/boyut;
            bx=b%boyut;
            by=b/boyut;
            rectfill(screen,ilkKorx+ax*artis+10,ilkKory+ay*artis+10,ilkKorx+(bx+1)*artis-10,ilkKory+(by+1)*artis-10,kirmizi);


        }

        a=yolDizi[0];
        ax=a%boyut;
        ay=a/boyut;
        textprintf_centre_ex(screen,font,ilkKorx+ax*artis+artis/2,ilkKory+ay*artis+artis/2,beyaz,makecol(255,0, 0),"A");

        a=yolDizi[pDizi];
        ax=a%boyut;
        ay=a/boyut;
        textprintf_centre_ex(screen,font,ilkKorx+ax*artis+artis/2,ilkKory+ay*artis+artis/2,beyaz,makecol(255,0, 0),"B");




    while(!key[KEY_ESC]){}
    return 0;
}
END_OF_MAIN();
