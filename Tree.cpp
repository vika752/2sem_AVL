//графиков нет.. доб эл-та, вращение ....
#include <iostream>
using namespace std;
struct TreeAVL{

    struct TreeAVL *parent;
    struct TreeAVL *left;
    struct TreeAVL *right;
    int key; 
    int bf; // коэф-т
};
//вращение влево
void r_r(struct TreeAVL **root, struct TreeAVL *A){

    struct TreeAVL *B = A->right, *p = A->parent;

    A->right = B->left;
    if (A->right) A->right->parent = A;

    B->left = A;
    B->parent = p;
    A->parent = B;

    // Если p == NULL, то элемент A и был корнем
    if (p != NULL){
          if (p->left == A) p->left = B;
          else p->right = B;
     }
     else *root = B;
}
//вращение вправо
void l_l(struct TreeAVL ** root, struct TreeAVL *A){
    
   struct TreeAVL *B = A->left, *p = A->parent;

      A->left = B->right;
      if (A->left) A->left->parent = A;

     B->right = A;
     B->parent = p;
     A->parent = B;

    if (p){
          if (p->left == A) p->left = B;
          else p->right = B;
    }
    else *root = B;
}

void vsota_tree(struct TreeAVL *root,int level,int *h){
// ф-ия vsota_tree опр выссоту дерева
   if(root){
            if(root->right){
                  ++level;
                  vsota_tree(root->right, level, h);
                  --level;
            }
            if(level>*h) *h=level;

            if(root->left){
                  ++level;
                  vsota_tree(root->left, level, h);
                  --level;
            }
      }
}

// функция считает коэфф после вращения
// аргументом явл эл-т, для которого мы считаем bf
void b_f(struct TreeAVL *r){
    int a = 0;
    int b = 0;
    struct TreeAVL *x = r, *y = x->left, *z = x->right;

    if(y) vsota_tree(y, 1, &a);
    if(z) vsota_tree(z, 1, &b);
    x->bf = a-b;

}

//добавление элемента
void addAVL(struct TreeAVL **root, int key){
// осн ф-ия
 
   struct TreeAVL *nowy_element,*p,*r, *d;
      int t;
   // создаем эл-т
      nowy_element = (struct TreeAVL *)malloc(sizeof (struct TreeAVL));
      nowy_element->left = nowy_element->right = nowy_element->parent = NULL;
      nowy_element->key = key;
      nowy_element->bf = 0;
     
      d = *root;
      if (!d){
           nowy_element->parent = NULL;
          *root = nowy_element;
       }
       else{
           while (d){
               if(d->key > key){
                       p = d;
                       d = d->left;
               }else if (d->key < key){
                       p = d;
                       d = d->right;
               }else break;
         }
         if (!d){
               if (p->key>key) p->left = nowy_element;
               else p->right = nowy_element;
               nowy_element->parent = p;
         }
         r=nowy_element;
         while (p){ // цикл подсчитывает bf при доб эл-та
               if (p->left == r) p->bf += 1;
               else if (p->right == r) p->bf -= 1;
               if (p->bf == 2 || p->bf == -2) break; // если не соотв  - выходит
               r = p;
               p = p->parent;
        }
        if (p){ 
               if (p->bf == 2){ // если левое подд-во >
                     if (p->right != r){
                               if (r->bf == -1){ 
                                         r_r(root, p->left);
                                         l_l(root, p);
                               }
                               else l_l(root, p);
                     }
              }
              else{
                     if(p->left != r){
                              if(r->bf == 1){ 
                                        l_l(root, p->right);
                                        r_r(root, p);
                              }
                              else r_r(root,p);
                     }
              }
        p = p->parent; 
        if(p->right)b_f(p->right);
        if(p->left)b_f(p->left);
        b_f(p);
        }
    }
}

//Функция, которая должна выводить дерево (те подсчитать уровень эл-та (на к-м он нах-ся) и поставить пробелы (=уровень эл-та)
// Затем он выводит ключ и bf элемента -> новой строке.... но функция немного не работает...
void write_tree(struct TreeAVL *root,int level){

    if (root){

         if (root->right){
              ++level;
              write_tree (root->right, level);
              --level;
         }
         int i;
         for (i = 0; i < level; ++i) printf (" ");

         printf ("%d bf %d \n", root->key, root->bf);

         if (root->left){
                ++level;
               write_tree (root->left, level);
               --level;
         }
    }
}

