#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
using namespace std;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define UNDERFLOW -2
#define TREE_SIZE 1
#define TREEINCREMENT 1
#define LH +1
#define EH 0
#define RH -1
typedef int Status;
typedef char TElemType;
typedef enum {LINK,THREAD} PointerTag; //指针标记类型
/*LINK 0 代表指向孩子的指针
THREAD 1 代表为指向前驱后继的线索*/

typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    struct BiThrNode *prior,*next;            //用于全线索二叉树
    PointerTag LTag,RTag;                     //用于全线索二叉树
    int bf;                                   //用于平衡二叉树,节点的平衡因子
}BiThrNode,*BiThrTree,BiNode,*BiTree;

Status PrintElement(TElemType e){
    printf("%s\n", e);
    return OK;
}
Status CreatBiTree(BiThrTree &t){
    TElemType e;
    cin>>e;
    if (e=='#')
        t = NULL;
    else{
        t = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!t)
            return OVERFLOW;
        t->data = e;
        t->lchild = NULL;
        t->rchild = NULL;
        CreatBiTree(t->lchild);
        CreatBiTree(t->rchild);
    }
    return OK;
}

void PreOrderTraverse(BiThrTree T){
    if (T == NULL)
        return ;
    cout<<T->data;
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
Status PreOrderTraverse(BiThrTree t,Status (* Visit)(TElemType e)){//详参见函数指针
    if(t){
        if(Visit(t->data))
            if (PreOrderTraverse(t->lchild,PrintElement))
                if (PreOrderTraverse(t->rchild,PrintElement))
                    return OK;
        return ERROR;
    }
    else return OK;
}
void InOrderTraverse(BiThrTree T){
    if (T == NULL)
        return ;
    PreOrderTraverse(T->lchild);
    cout<<T->data;
    PreOrderTraverse(T->rchild);
}
Status InOrderTraverse(BiThrTree t,Status (* Visit)(TElemType e)){//详参见函数指针
    if(t){
        if (PreOrderTraverse(t->lchild,PrintElement))
            if(Visit(t->data))
                if (PreOrderTraverse(t->rchild,PrintElement))
                    return OK;
        return ERROR;
    }
    else return OK;
}
void PostOrderTraverse(BiThrTree T){
    if (T == NULL)
        return ;
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
    cout<<T->data;
}
Status PostOrderTraverse(BiThrTree t,Status (* Visit)(TElemType e)){//详参见函数指针
    if(t){
        if (PreOrderTraverse(t->lchild,PrintElement))
            if (PreOrderTraverse(t->rchild,PrintElement))
                if(Visit(t->data))
                    return OK;
        return ERROR;
    }
    else return OK;
}



//////////////////////////////////线索二叉树链表构造
BiThrTree pre;
void InThreading(BiThrTree p)
{/*通过中序遍历进行中序线索化*/
    if(p)
    {
        InThreading(p->lchild);/*左子树线索化，递归*/
        if(!p->lchild)/*前驱线索*/
        {
            p->LTag=THREAD;
            p->lchild=pre;
        }
        if(!pre->rchild)/*后继线索*/
        {
            p->RTag = THREAD;
            pre->rchild = p;
        }
        pre=p;
        InThreading(p->rchild);/*右子树线索化*/
    }
}
Status InOrderTraverse_Thr(BiThrTree T){////加有头节点
/*和双向链表结构一样，在二叉树线索链表上添加一个头节点*/
/*T指向头结点，头结点左链lchild指向根节点，头结点右链rchild指向终须遍历的最后一个节点。*/
/*中序遍历二叉线索链表表示的二叉树T*/
    BiThrTree p;
    p = T->lchild;
    while (p != T){
        while (p->LTag == LINK)
            p = p->lchild;
        cout<<p->data;
        while (p->RTag == THREAD && p->rchild != T){
            p = p->rchild;
            cout<<p->data;
        }
        p = p->rchild;
    }
    return OK;
}
Status InOrderTraverse_Thr_Untitled(BiThrTree T){////未加有头节点
    BiThrTree p;
    p = T->lchild;
    while (p != NULL){
        while (p->LTag == LINK)
            p = p->lchild;
        cout<<p->data;
        while (p->RTag == THREAD ){
            p = p->rchild;
            cout<<p->data;
        }
        p = p->rchild;
    }
    return OK;
}
//运用prior和next指针处理
void InThreading_link(BiThrTree p)
{/*通过中序遍历进行中序线索化*/
    if(p)
    {
        InThreading_link(p->lchild);/*左子树线索化，递归*/
        if(!p->lchild)/*前驱线索*/
        {
            p->prior=pre;
        }
        if(!pre->rchild)/*后继线索*/
        {
            pre->next = p;
        }
        pre=p;
        InThreading_link(p->rchild);/*右子树线索化*/
    }
}
Status InOrderTraverse_Thr_link(BiThrTree T){////未加有头节点
    BiThrTree p;
    p = T;
    while (p->prior != NULL)
        p = p->prior;
    cout<<p->data;
    while (p->next != NULL ){
        p = p->next;
        cout<<p->data;
    }
    return OK;
}



///////////////////////////////////二叉排序树构造
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p){
    /*递归查找二叉排序树T是否存在key，
     * 指针f指向T的双亲，其初始调用值为NULL
     * 若查找成功，则指针p指向该数据元素结点，并返回TRUE
     * 否则指针p指向查找路径上访问的最后一个节点并返回FALSE*/
    if(!T){//查找不成功
        *p = f;
        return FALSE;
    }
    else if (key == T->data){//查找成功
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
        return SearchBST(T->lchild, key, T, p);//左子树继续查找
    else
        return SearchBST(T->rchild, key, T, p);//右子树继续查找
}
Status InsertBST(BiTree *T,int key){
    BiTree p,s;
    if (!SearchBST(*T, key, NULL, &p)){
        s = (BiTree)malloc(sizeof(BiNode));
        s->data = key;
        if (!p)
            *T = s;
        else if (key < p->data)
            p->lchild = s;
        else
            p->rchild = s;
        return TRUE;
    }
    else
        return FALSE;
}
//删除二叉树中一个元素
Status Delete(BiTree *p){
    /*删除节点p，并重建左右子树*/
    BiTree q,s;
    if((*p)->rchild == NULL)
        q = *p, *p = (*p)->lchild, free(q);
    else if ((*p)->lchild == NULL)
        q = *p, *p = (*p)->rchild, free(q);
    else{
        q = *p;s = (*p)->lchild;
        while(s->rchild){
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;
        if(q!=*p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        free(s);

    }
    return TRUE;
}
Status DeleteBSF(BiTree *T,int key){
    if (!*T)
        return FALSE;
    else{
        if (key == (*T)->data)
            return Delete(T);
        else if (key < (*T)->data)
            return DeleteBSF(&(*T)->lchild ,key);
        else
            return DeleteBSF(&(*T)->rchild ,key);
    }
}



///////////////平衡二叉树（AVL树）
void R_Rotate(BiTree *p){////////////右旋处理
    BiTree L;
    L = (*p)->lchild;
    (*p)->lchild = L->rchild;
    L->rchild = (*p);
    *p = L;
}
void L_Rotate(BiTree *p){////////左旋处理
    BiTree R;
    R = (*p)->rchild;
    (*p)->rchild = R->lchild;
    R->lchild = (*p);
    *p = R;
}
void LeftBalance(BiTree *T){///////左平衡旋转处理
    BiTree L,Lr;
    L = (*T)->lchild;
    switch (L->bf){
        case LH :
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;
        case RH :
            Lr = L->rchild;
            switch (Lr->bf){
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild);
            R_Rotate(T);
    }
}
void RightBalance(BiTree *T){///////右平衡旋转处理
    BiTree L,Ll;
    L = (*T)->rchild;
    switch (L->bf){
        case RH :
            (*T)->bf = L->bf = EH;
            L_Rotate(T);
            break;
        case LH :
            Ll = L->lchild;
            switch (Ll->bf){
                case RH:
                    (*T)->bf = LH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = L->bf = EH;
                    break;
                case LH:
                    (*T)->bf = EH;
                    L->bf = RH;
                    break;
            }
            Ll->bf = EH;
            R_Rotate(&(*T)->rchild);
            L_Rotate(T);
    }
}
/*若平衡的二叉排序树T中不存在和e有的相同关键字的节点，则插入一个
 * 数据元素为e的新节点并返回1，否则返回0.若因插入而使二叉排序树
 * 失去平衡，则做平衡旋转处理，布尔变量taller反映T长高与否*/
Status InsertAVL(BiTree *T,int e,Status *taller){//逐个元素录入AVL
    if(!*T){
        //插入新节点，树“长高”，置taller为TRUE
        *T = (BiTree)malloc(sizeof(BiThrNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else{
        if(e==(*T)->data){
            //树种已存在和e有相同关键字的结点则不在插入
            *taller = FALSE;
            return FALSE;
        }
        if(e<(*T)->data){
            //应继续在T的左子树中进行搜索
            if(!(InsertAVL(&(*T)->lchild,e,taller)))
                return FALSE;
            if(*taller){
                //已插入到T的左子树且左子树长高
                switch((*T)->bf){
                    case LH://原本左子树比右子树高，需要平衡处理
                        LeftBalance(T);
                        *taller = FALSE;
                        break;
                    case EH://原本左右子树等高，现因左子树增高而增高
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH://原本右子树比左子树高，现左右子树等高
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
            }
        }
        else{
            //应继续在T右子树中进行搜索
            if(!InsertAVL(&(*T)->rchild,e,taller))
                return FALSE;
            if(*taller){
                switch ((*T)->bf){
                    case LH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                    case EH:
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH:
                        RightBalance(T);
                        *taller = FALSE;
                        break;
                }
            }
        }
    }
    return TRUE;
}

void InitAVL(BiTree *T,const int a[],int n,Status *taller){
    for (int j =0 ; j < n ; ++j) {
        InsertAVL(T,a[j],taller);
    }//AVL的创建
}

Status SearchAVL(BiTree T,int key,BiTree f,BiTree *p){
	/*递归查找二叉排序树T是否存在key，
     * 指针f指向T的双亲，其初始调用值为NULL
     * 若查找成功，则指针p指向该数据元素结点，并返回TRUE
     * 否则指针p指向查找路径上访问的最后一个节点并返回FALSE*/
    if(!T){//查找不成功
        *p = f;
        return FALSE;
    }
    else if (key == T->data){//查找成功
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
        return SearchAVL(T->lchild, key, T, p);//左子树继续查找
    else
        return SearchAVL(T->rchild, key, T, p);//右子树继续查找
}
//删除分为了两种方式，第一种是运用三个函数的循环调用，第二种则是将三种函数整合在一起
Status DelLeft(BiTree *T, int e, Status *shorter) {
    if (!DelAVL(&(*T)->lchild, e, shorter))
        return FALSE;
    // 删除成功，左边高度变矮
    if (*shorter == TRUE) {
        switch ((*T)->bf) {
            case LH: {
                // 原左高，变等高，高度改变
                (*T)->bf = EH;
                *shorter = TRUE;
                break;
            }
            case EH: {
                // 原等高，变右高，高度不变
                (*T)->bf = RH;
                *shorter = FALSE;
                break;
            }
            case RH: {
                // 相当于在右边插入节点，使得右边高度相对增大，平衡后高度不变
                RightBalance(T);
                if ((*T)->bf != EH) {
                    *shorter = FALSE;
                }
                break;
            }
        }
    }
    return TRUE;
}
Status DelRight(BiTree *T, int e, Status *shorter) {
    if (!DelAVL(&(*T)->rchild, e, shorter))
        return FALSE;
    if (*shorter == TRUE) {
        switch ((*T)->bf) {
            case LH: {
                // 相当于在左边插入节点，使得左边高度相对增大，平衡后高度不变
                LeftBalance(T);
                if ((*T)->bf != EH) {
                    *shorter = FALSE;
                }
                break;
            }
            case EH: {
                // 原等高，变左高，高度不变
                (*T)->bf = LH;
                *shorter = FALSE;
                break;
            }
            case RH: {
                (*T)->bf = EH;
                *shorter = TRUE;
                break;
            }
            default:
                break;
        }
    }
    return TRUE;
}
Status DelAVL(BiTree *T, int e, Status *shorter) {
    if (NULL == (*T)) {
        // 树为空
        return FALSE;
    } else if ((*T)->data == e) {
        // 找到元素结点
        BiTree p = NULL;
        if (NULL == (*T)->lchild) {
            // 左子树为空
            p = (*T);
            (*T) = (*T)->rchild;
            free(p);
            // 高度变矮
            *shorter = TRUE;
        } else if ((*T)->rchild == NULL) {
            // 右子树为空
            p = *T;
            (*T) = (*T)->lchild;
            free(p);
            // 高度变矮
            *shorter = TRUE;
        } else {
            // 左右子树都存在
            p = (*T)->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            (*T)->data = p->data;
            p->data = e;
            // 在左子树中删除前驱结点
            return DelLeft(&(*T), e, shorter);
        }
    } else if ((*T)->data > e) {
        return DelLeft(&(*T), e, shorter);
    } else {
        return DelRight(&(*T), e, shorter);
    }
    return TRUE;
}
Status DeleteAVL(BiTree *T,int e,Status *shorter){
    if (!(*T)) {
        // 树为空
        return FALSE;
    }
    else if ((*T)->data == e) {
        // 找到元素结点
        BiTree p = NULL;
        if (NULL == (*T)->lchild) {
            // 左子树为空
            p = (*T);
            (*T) = (*T)->rchild;
            free(p);
            // 高度变矮
            *shorter = TRUE;
        } else if ((*T)->rchild == NULL) {
            // 右子树为空
            p = *T;
            (*T) = (*T)->lchild;
            free(p);
            // 高度变矮
            *shorter = TRUE;
        } else {
            // 左右子树都存在
            p = (*T)->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            (*T)->data = p->data;
            p->data = e;
            // 在左子树中删除前驱结点
            return DeleteAVL(&(*T)->lchild, e, shorter);
        }
    }
    else if ((*T)->data > e) {
        if (!DelAVL(&(*T)->lchild, e, shorter))
            return FALSE;
        // 删除成功，左边高度变矮
        if (*shorter == TRUE) {
            switch ((*T)->bf) {
                case LH:
                    // 原左高，变等高，高度改变
                    (*T)->bf = EH;
                    *shorter = TRUE;
                    break;
                case EH:
                    // 原等高，变右高，高度不变
                    (*T)->bf = RH;
                    *shorter = FALSE;
                    break;
                case RH:
                    // 相当于在右边插入节点，使得右边高度相对增大，平衡后高度不变
                    RightBalance(T);
                    if ((*T)->bf != EH) {
                        *shorter = FALSE;
                    }
                    break;
            }
        }
        return TRUE;
    } else {
        if (!DelAVL(&(*T)->rchild, e, shorter))
            return FALSE;
        if (*shorter == TRUE) {
            switch ((*T)->bf) {
                case LH:
                    // 相当于在左边插入节点，使得左边高度相对增大，平衡后高度不变
                    LeftBalance(T);
                    if ((*T)->bf != EH) {
                        *shorter = FALSE;
                    }
                    break;
                case EH:
                    // 原等高，变左高，高度不变
                    (*T)->bf = LH;
                    *shorter = FALSE;
                    break;
                case RH:
                    (*T)->bf = EH;
                    *shorter = TRUE;
                    break;
            }
        }
        return TRUE;
    }
    return TRUE;
}



////////////////////赫夫曼树 & 赫夫曼编码
/*
* 赫夫曼树是指带权路径长度WPL最小的二叉树成为赫夫曼树（节点路径长度和结点上的权的乘积）
*
*
* 在赫夫曼编码是前缀编码，需要注意任意一个字符串的编码都不是另一个字符的编码前缀
*
* 首先需要将字符集各个字符出现的次数或频率进行集合，以字符为叶子节点，以次数或者频率
* 为权值来构造一棵赫夫曼树，规定做分枝为0，有分支为1，从根节点到叶子节点所经过的路径
* 分枝组成的0和1变为该结点对应字符的编码，这就是赫夫曼编码
*/





