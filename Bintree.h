#pragma once

#include <stack>
#include <queue>
#include "release.h"
#include "Binnode.h"


template <typename T> 
class Bintree
{

public:
    Bintree() : size_(0) , root_(nullptr) {}
    int size() const {return size_;}
    bool empty() const { return !root_; }
    Binnode<T>* root() { return root_; }
    Binnode<T>* insertAsRoot(const T& e);
    Binnode<T>* insertAsLC(Binnode<T>*  x, const T& e); // e作为x的左孩子插入，原无
    Binnode<T>* insertAsRC(Binnode<T>*  x, const T& e); // e作为x的右孩子插入，原无
    Binnode<T>* attachAsLC(Binnode<T>*  x, Bintree<T>* l);//
    Binnode<T>* attachAsRC(Binnode<T>*  x, Bintree<T>* r);

    int remove(Binnode<T>*  x); //初除以位置x处节点为根的子树，返回该子树原先的规模
    Bintree<T>* secede(Binnode<T>*  x); //将子树从当前树中摘除，并将其转换为一颗独立子树

    template<typename VST>
    void travLevel( VST& vlist) { if(root_) root_->travLevel(vlist);} //层次遍历

    template<typename VST>
    void travPre(VST& vlist) { if(root_) root_->travPre(vlist); } //先序遍历

    template<typename VST>
    void travIn(VST& vlist) { if(root_) root_->travIn(vlist); } //中序遍历

    template<typename VST>
    void travPost(VST& vlist) { if(root_) root_->travPost(vlist); } //后序遍历

    bool operator< (const Bintree<T> & t) { return root_ && t.root_ ; }

    bool operator== (const Bintree<T> & t) { return root_ && t.root_ && (root_ == t.root_) ;}

protected:
    int size_;
    Binnode<T>* root_;
    virtual int updateHeight(Binnode<T>* x); //更新节点x的高度
    void updateHeightAbove(Binnode<T>* x);   //更新节点x及其祖先的高度

};

template <typename T>
int Bintree<T>::updateHeight(Binnode<T>* x){
    return x->height = 1 + max( stature( x->lc ) , stature( x->rc ) );
}

template <typename T>
void Bintree<T>::updateHeightAbove(Binnode<T>* x){
    while (x)
    {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
Binnode<T>* Bintree<T>::insertAsRoot(const T& e){
    size_ = 1;
    return root_ = new Binnode<T>(e); //将e作为根节点插入空的二叉树
}

//为x插入一个右节点 e
template <typename T>
Binnode<T>* Bintree<T>::insertAsRC(Binnode<T>*  x, const T& e){
    size_++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}
//为x插入一个左节点 e
template <typename T>
Binnode<T>* Bintree<T>::insertAsLC(Binnode<T>*  x, const T& e){
    size_++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->rc;
}

//为x插入一颗右子树
template <typename T>
Binnode<T>* Bintree<T>::attachAsRC(Binnode<T>*  x, Bintree<T>* r){
    if( x->rc = r->root_) r->root_->parent = x; //接入
    size_ += r->size_;
    updateHeightAbove(x);
    r->root_ = nullptr;
    r->size_ = 0;
    release(r);
    r = nullptr;
    return x;
}

//为x插入一颗左子树
template <typename T>
Binnode<T>* Bintree<T>::attachAsLC(Binnode<T>*  x, Bintree<T>* l){
    if( x->lc = l->root_) l->root_->parent = x; //接入
    size_ += l->size_;
    updateHeightAbove(x);
    l->root_ = nullptr;
    l->size_ = 0;
    release(l);
    l = nullptr;
    return x;
}

//删除二叉树中位置x处的节点及其后代，返回被删除节点的数量
template <typename T> 
int Bintree<T>::remove(Binnode<T>*  x){
    FromParentTo(*x) = nullptr; //切断来自父节点的指针
    updateHeightAbove(x->parent); //更新祖先的高度
    int n = removeAt(x);
    size_ -= n ;
    return n;
}

//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T>
static int removeAt(Binnode<T>*  x){
    if( !x ) return 0;
    int n = 1 + removeAt(x->rc) + removeAt(x->lc); // 递归释放左右子树
    release( x->data);
    release( x );
    return n;
}

//子树分离，返回分离的子树
template <typename T>
Bintree<T>* Bintree<T>::secede(Binnode<T>*  x){
    FromParentTo( *x )  = nullptr;
    updateHeightAbove( x->parent );
    Bintree<T>* S = new Bintree<T>();
    S->root_ = x; 
    x->parent = nullptr;
    S->size_ = x->size();
    size_ -= S->size_;
    return S;
}

//二叉树先序遍历算法（递归版）
template <typename T, typename VST>
void travPre_R(Binnode<T>* x, VST& vlist){
    if( !x ) return;
    vlist(x->data);
    travPre_R( x->lc, vlist);
    travPre_R( x->rc, vlist);
}

//二叉树后序遍历 (递归版)
template <typename T, typename VST>
void travPost_R(Binnode<T>* x, VST& vlist){
    if( !x ) return;
    travPost_R(x->lc, vlist);
    travPost_R(x->rc, vlist);
    vlist(x->data);
}

//二叉树中序遍历 (递归版)
template <typename T, typename VST>
void travIn_R(Binnode<T>* x, VST& vlist){
    if( !x ) return;
    travIn_R( x->lc , vlist);
    vlist(x->data);
    travIn_R(x->rc);
}

template <typename T, typename VST>
static void visitAlongLeftBranch(Binnode<T>* x, VST& vlist, std::stack<Binnode<T>*>& S){
    while (x)
    {
        vlist(x->data); //访问当前节点
        S.push(x->rc); //右孩子入栈暂存
        x = x->lc; //沿左分支深入一层
    }
}

//先序遍历，迭代版
template <typename T, typename VST>
void travPre_I2(Binnode<T>* x, VST& vlist){
    std::stack<Binnode<T>*> S; //辅助栈
    while ( true )
    {
        visitAlongLeftBranch(x ,vlist ,S);
        if( S.empty() ) break; //直到栈空
        x = S.pop(); //弹出下一批的起点
    }
    
}

//从当前节点出发，沿着左分支不断深入，直至没有左分支的节点
template <typename T>
static void goAlongLeftBranch(Binnode<T>* x, std::stack<Binnode<T>*> & S){
    while (x)
    {
        S.push(x);
        x = x->lc;
    } 
}

//中序遍历，迭代版本
template <typename T, typename VST>
void travIn_I1(Binnode<T>* x, VST& vlist){
    std::stack<Binnode<T>*> S; //辅助栈
    while (true)
    {
        goAlongLeftBranch(x ,S);
        if(S.empty()) break;
        x = S.pop(); 
        vlist(x->data);
        x = x->rc;
    }
}

//二叉树中序遍历算法（迭代版#2）
template <typename T, typename VST>
void travIn_I2(Binnode<T>* x, VST& vlist){
    std::stack<Binnode<T>*> S; //辅助栈
    while (true)
    {
        if(x){
            S.push(x); //根节点进栈
            x = x->lc; //深入遍历左子树
        } else if (!S.empty()){
            x = S.pop(); //
            vlist(x->data);
            x = x->rc;
        } else {
            break;
        }
    } 
}

//二叉树中序遍历算法（迭代版#3）
template <typename T, typename VST>
void travIn_I3(Binnode<T>* x, VST& vlist){
    bool backtrack = false; // //前一步是否刚从右子树回溯——省去栈，仅O(1)辅助空间
    while (true)
    {
        if( !backtrack && HasLChild(*x)){//若有左子树且不是刚刚回溯，则
            x = x->lc;  //深入遍历左子树
        }else{//否则——无左子树或者刚刚回溯（相当于无左子树）
            vlist(x->data); //访问该节点
            if(HasRChild(*x)){ //若其右子树非空，则
                x = x->rc;     //深入右子树继续遍历
                backtrack = false;
            }else{ //若右子树为空
                if( !( x = x->succ())) break; //回溯，找到x的直接后置节点
                backtrack = true; //设置回溯标志
            }
        }
    }
}

//队列先进先出，层次遍历，广度优先遍历
template <typename T>  template < typename VST >
void Binnode<T>::travLevel(VST& vlist){
    std::queue<Binnode<T>*> Q;
    Q.push(this);
    while ( !Q.empty())
    {
        Binnode<T>* x = Q.pop(); 
        vlist(x->data);
        if(HasLChild(*x)) Q.push( x->lc); //
        if(HasRChild(*x)) Q.push( x->rc);
    }
}






















