#pragma once

#include "release.h"
#define stature(p) ((p) ? (p)->height : -1) //节点高度
//节点颜色
enum RBClor
{
    RB_RED, 
    RB_BLACK
};

#define IsRoot(x) ( !((x).parent) ) //判断是否为根节点
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc))  //判断x是否为左孩子节点
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc))  //判断x是否为右孩子节点
#define HasParent(x) ( ! IsRoot(x) )
#define HasRChild(x) ( (x).rc )
#define HasLChild(x) ( (x).lc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子

#define IsLeaf(x) ( ! HasChild(x) )  //判断x节点是否是叶子节点

#define sibling(p)   \
            ( IsLChild(* (p)) ? (p)->parent->rc : (p)->parent->lc )   // 拿到兄弟节点

#define uncle(x)   \
            (  IsLChild( *( (x)->parent )) ? (x)->parent->parent->rc : (x)->parent->parent->lc)  //拿到叔叔节点

#define FromParentTo(x)  \ 
            ( IsRoot(x) ? root_ : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))


template <typename T>
struct Binnode
{
    
public:
    int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
    Binnode<T>* insertAsLC(T const & ); //作为当前节点的左孩子插入
    Binnode<T>* insertAsRC(T const & ); //作为当前节点的右孩子插入
    Binnode<T>* succ();  //取当前节点的直接后续
    template <typename VST> void travLevel( VST& ); //子树层次遍历
    template <typename VST> void travPre( VST& ); //子树先序遍历
    template <typename VST> void travIn( VST& ); //子树中序遍历
    template <typename VST> void travPost( VST& ); //子树后序遍历

public:
    bool operator< (Binnode const& bn) {return data < bn.data; }
    bool operator== (Binnode const& bn) {return data== bn.data;}

public:
    Binnode() : 
        parent(nullptr), lc(nullptr) , rc(nullptr) , height(0) , color(RB_RED) {}
    Binnode(T e, Binnode<T>* p = nullptr, Binnode<T>* lc=nullptr, Binnode<T>* rc=nullptr, int h=0, RBClor c = RB_RED)
              : data(e) , parent(p) , lc(lc) , rc(rc) , height(h), color(c) {}
public:
    T data;
    int height; // 高度
    RBClor color; // 颜色（红黑树）

    Binnode<T>* parent; //父节点
    Binnode<T>* lc;    //左孩子节点
    Binnode<T>* rc;   //右孩子节点
};

template <typename T>
Binnode<T>* Binnode<T>::insertAsLC(T const &e ){
    return lc = new Binnode(e ,this);
}

template <typename T>
Binnode<T>* Binnode<T>::insertAsRC(T const &e ){
    return rc = new Binnode(e ,this);
}

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













