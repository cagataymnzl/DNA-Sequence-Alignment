#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define MAX 50

//Min kosegen bulma
int min(int num1,int num2,int num3){
	int min;
	if(num1<num2){
		if(num1<num3){
			min=num1;
		}
		else{
			min=num3;
		}
	}
	else if(num2<num3){
		min=num2;
	}
	else{
		min=num3;
	}
	return min;
}
// Elemanlar birbirinin aynýsý ise 0 dönüþüm puaný deðilse +1 dönüþüm puaný
int delta(char gen1[],char gen2[],int i,int j){
	if(gen1[i]==gen2[j]){
		return 0;
	}
	else{
		return 1;
	}
}


//DÖNÜÞTÜRME ADIMLARI
int cozum_bul(char gen1[],char gen2[],int m,int n,int matrix[][MAX]){
	if(m==0||n==0){//!ÖNEMLÝ! En az bir gen indisinin 0 deðerine ulaþmasý
		if(m==0&&n!=0){
			printf("%c yi ekle ::: +1 donusum\n",gen2[n-1]);
			return cozum_bul(gen1,gen2,m,n-1,matrix);
		}
		else if(n==0&&m!=0){
			printf("%c yi sil ::: +1 donusum\n",gen1[m-1]);
			return cozum_bul(gen1,gen2,m-1,n,matrix);
		}
		else{
			return 0;
		}
	}

	int hiza,ekle,sil,secim,kontrol;
	
	hiza=matrix[m-1][n-1]+delta(gen1,gen2,m-1,n-1);
	ekle=matrix[m][n-1]+1;
	sil=matrix[m-1][n]+1;
	
	secim=min(hiza,ekle,sil);
	//printf("SECIM:%d ",secim);
	if(secim==ekle&&n!=0){
		printf("%c yi ekle ::: +1 donusum\n",gen2[n-1]);
		return cozum_bul(gen1,gen2,m,n-1,matrix);
	}
	else if(secim==hiza&&m!=0&&n!=0){
		if(gen1[m-1]!=gen2[n-1]){
			printf("%c yi %c ye hizala-->%c yap ::: +1 donusum\n",gen1[m-1],gen2[n-1],gen2[n-1]);
		}
		else{
			printf("%c yi---%c ye hizala ::: +0 donusum\n",gen1[m-1],gen2[n-1]);
		}
		return cozum_bul(gen1,gen2,m-1,n-1,matrix);
	}

	else if(secim==sil&&m!=0){
		printf("%c yi sil ::: +1 donusum\n",gen1[m-1]);
		return cozum_bul(gen1,gen2,m-1,n,matrix);
	}
}
//Grafik Oluþturma Fonksiyonu
void graf(int carpim_dizi_m[],int carpim_dizi_n[],int dizi[],int t){
	int i,j;
	for(i=0;i<t;i++){
		printf("%d.KARSILASTIRMA ",i+1);
		for(j=0;j<dizi[i];j++){
			printf("-");
		}
		printf(" ==> GEN1:%d * GEN2:%d = %d kontrol\n",carpim_dizi_m[i],carpim_dizi_n[i],dizi[i]);
	}		
}
//kontrol sayýsýný donen fonksiyon
int don(char gen1[],char gen2[]){
	int m,n,i,j;
	int kontrol=0;
	m=strlen(gen1);
	n=strlen(gen2);
	int matrix[MAX][MAX];
	for(i=0;i<m+1;i++){
		for(j=0;j<n+1;j++){
			matrix[i][j]= 0;
		}
	}
	for(i=1;i<m+1;i++){
		matrix[i][0]=i;
	}
	for(j=1;j<n+1;j++){
		matrix[0][j]=j;
	}
	for(i=1;i<m+1;i++){
		for(j=1;j<n+1;j++){
			//kosegenlerden en kucuk olaný bul
			matrix[i][j]=min(matrix[i-1][j-1]+delta(gen1,gen2,i-1,j-1),matrix[i-1][j]+1,matrix[i][j-1]+1);
			kontrol++;
		}
	}
	printf("KONTROL SAYISI :::  %d * %d = %d\n",m,n,kontrol);
	return kontrol;
}

//PUAN TABLOSU OLUSTURMA
int hizala(char gen1[],char gen2[]){
	int m,n,i,j;
	m=strlen(gen1);
	n=strlen(gen2);
	int matrix[MAX][MAX];
	for(i=0;i<m+1;i++){
		for(j=0;j<n+1;j++){
			matrix[i][j]= 0;
		}
	}
	for(i=1;i<m+1;i++){
		matrix[i][0]=i;
	}
	for(j=1;j<n+1;j++){
		matrix[0][j]=j;
	}
	for(i=1;i<m+1;i++){
		for(j=1;j<n+1;j++){
			//kosegenlerden en kucuk olaný bul
			matrix[i][j]=min(matrix[i-1][j-1]+delta(gen1,gen2,i-1,j-1),matrix[i-1][j]+1,matrix[i][j-1]+1);
		}
	}
	printf("     ");
	for(i=0;i<n+1;i++){
		printf("%c ",gen2[i]);
	}
	printf("\n");

	int k=0;	
	for(i=0;i<m+1;i++){
		if(i!=0){
			printf("%c ",gen1[k]);
			k++;
		}
		else{
			printf("  ");
		}
	
		printf("[");
		for(j=0;j<n+1;j++){
			printf("%d ",matrix[i][j]);	}
		printf("]\n");
	}
	printf("\nDonusum Adimlari (Sondan Basa):\n\n");
	
	cozum_bul(gen1,gen2,m,n,matrix);
	return matrix[m][n];
}



int main(){
	char gen1[MAX],gen2[MAX];
	int m,n,i;
	char genler[5] = {'A','T','G','C','\0'};
	int carpim_dizi_m[MAX],carpim_dizi_n[MAX];
	int devam =0,t=0,k=0;
	int matrix[MAX][MAX];
	
	int kontrol_dizi[MAX];
	srand(time(NULL));
	while(devam<20){//Ýterasyon sayýsý burdan belirlenebilir!MAX constant deðeri 50 olarak tanýmlanmýþtýr!
		
		m=rand()%10+4;
		n=rand()%10+4;
		for(i=0;i<m;i++){
			gen1[i]=(genler[rand()%4]);
			
		}
		for(i=0;i<n;i++){
			gen2[i]=(genler[rand()%4]);
		}
		m=strlen(gen1);
		n=strlen(gen2);
		printf("GEN1:");puts(gen1);printf("GEN2:");puts(gen2);
		printf("GEN1 --> GEN2'ye donusturulecek\n");	
		
		printf("\nMinimum donusum sayisi:%d\n",hizala(gen1,gen2));
		kontrol_dizi[t]=don(gen1,gen2);
		carpim_dizi_m[t]=m;
		carpim_dizi_n[k]=n;
		t++;k++;
		for(i=0;i<m;i++){
			gen1[i]=NULL;
			
		}
		for(i=0;i<n;i++){
			gen2[i]=NULL;
		}
		//printf("DEVAM :: 1 /// DUR :: 0");
		//scanf("%d",&devam);
		printf("****************************************\n");
		devam++;
		
	}
	graf(carpim_dizi_m,carpim_dizi_n,kontrol_dizi,t);
	//cozum_bul(gen1,gen2,m,n,matrix);
	

	
	return 0;
}
