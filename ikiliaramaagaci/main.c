#include <stdio.h>
#include <stdlib.h>
typedef struct n{
int data;
struct n *left;
struct n * right;
}node;

node * ekle(node * agac,int data){
if(agac == NULL){
    agac = (node *)malloc(sizeof(node));
    agac->data = data;
    agac->left = NULL;
    agac->right = NULL;
    return agac;
}
  if(agac->data < data){
    agac->right = ekle(agac->right,data);
    return agac;
  }


  agac->left = ekle(agac->left,data);
  return agac;

}


void inOrderDolas(node * root){
if(node == NULL)
    return NULL;
inOrderDolas(root->left);
printf(" %d ",root->data);
inOrderDolas(root->right);
}

void preOrderDolas(node * root){
if(root == NULL)
    return NULL;
printf("%d ",root->data);
preOrderDolas(root->left);
preOrderDolas(root->right);
}
void postOrderDolas(node * root){
if(root == NULL)
    return NULL;
postOrderDolas(root->left);
postOrderDolas(root->right);
printf("%d ",root->data);
}



int bul(node * agac,int aranan){
if(agac == NULL)
    return -1;
if(agac->data == aranan)
    return 1;
if(bul(agac->right,aranan) == 1)
    return 1;
if(bul(agac->left , aranan) == 1)
    return 1;
return -1;

}
int minBul(node * agac){
while(agac->left != NULL)
    agac = agac->left;
return agac->data;
}
int maxBul(node * agac){
while(agac->right != NULL)
    agac = agac->right;
return agac->data;
}


node * sil(node * agac,int data){
if(agac == NULL)
    return NULL;
    //aradığım veriyi buldum
if(agac->data == data){
     //silinecek nodun sağında ve solunda çocuk yoksa
    if(agac->left == NULL && agac->right == NULL)
        return NULL;
    //Bir diğer ihtimal ağacın solunda veya sağında veya her ikisinde de değer olması durumu
    if(agac->right != NULL){
        agac->data = minBul(agac->right);
        agac->right = sil(agac->right,minBul(agac->right));
        return agac;
    }
    // ağacın sağ tarında hiç değer yoksa o zaman sol tarafından işlem yapmam gerekiyor
    agac->data = maxBul(agac->left);
    agac->left = sil(agac->left,maxBul(agac->left));
    return agac;


}
// aranan değer henüz bulunamadı ama hala ağacın solunda ve sağında değerler varsa
if(agac->data < data){
    agac->right = sil(agac->right,data);
    return agac;
}
else{
    agac->left = sil(agac->left,data);
    return agac;
}
}

void dfsAlgoritmasi( node *agac)
{
    if (agac != NULL)
    {
        if (agac->left)
        {
            dfsAlgoritmasi(agac->left);
        }
        if (agac->right)
        {
            dfsAlgoritmasi(agac->right);
        }
        printf("%d  ", agac->data);
    }
}


int agacYuksekligiHesapla( node* agac)
{
    if (agac == NULL)
        return 0;

    if(agacYuksekligiHesapla(agac->left)> agacYuksekligiHesapla(agac->right))
        return 1+agacYuksekligiHesapla(agac->left);
    else
        return 1+ agacYuksekligiHesapla(agac->right);
}

node * sagSagDondur(node * root){
node * temp;
temp = root->right;
root->right = temp->left;
temp->left = root;
return temp;
}
node * solSolDondur(node * root){
node * temp;
temp = root->left;
root->left = temp->right;
temp->right = root;
return temp;
}

node * solSagDondur(node * root){
node * temp;
temp = root->left;
root->left = sagSagDondur(temp);
return solSolDondur(root);
}


node * sagSolDondur(node * root){
node * temp;
temp = root->right;
root->right = solSolDondur(temp);
return sagSagDondur(root);
}


node * avl(node * agac){
int yukseklikFarki = agacYuksekligiHesapla(agac->left) - agacYuksekligiHesapla(agac->right);
if(yukseklikFarki > 1){
    if(agacYuksekligiHesapla(agac->left->left) - agacYuksekligiHesapla(agac->left->right) > 0)
        agac = solSolDondur(agac);
    else
        agac = solSagDondur(agac);
}
else if(yukseklikFarki <-1){
    if(agacYuksekligiHesapla(agac->right->left) - agacYuksekligiHesapla(agac->right->right)>0)
        agac = sagSolDondur(agac);
    else
        agac = sagSagDondur(agac);
}
return agac;
}


int main()
{
    node * agac = NULL;
    agac = ekle(agac,60);
    agac = ekle(agac,20);
    agac = ekle(agac,65);
    agac = ekle(agac,40);
    agac = ekle(agac,45);
    agac = ekle(agac,10);
    agac = ekle(agac,70);

    printf("\n Agactaki min deger : %d",minBul(agac));
    printf("\n Agactaki max deger : %d",maxBul(agac));
   agac= sil(agac,60);
   printf("\n");

printf("\n \n agac yuksekligi : %d ",agacYuksekligiHesapla(agac));
agac = avl(agac);
printf("\n \n");
    return 0;
}
