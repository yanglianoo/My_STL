#pragma once


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

//获取当前节点的直接后继，以中序遍历为序
template <typename T>
Binnode<T>* Binnode<T>::succ(){
    Binnode<T>* s = this;
    if( rc ){ //若有右孩子，则直接后继必在右子树中
        s = rc; //右子树
        while (HasChild(*s))
        {
            s = s->lc;   //最靠左的节点
        }
    }else{

        while (IsRChild(*s)) //如果s是右子树
        {
            s = s->parent;
        }
        s = s->parent; //是左子树，向右上方移动一步，即可抵达直接后继
    }
    return s;
}