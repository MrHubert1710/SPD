#include "kolejka.hpp"

KolejkaP::KolejkaP(bool priority){
top = nullptr;
high_priority = priority;
}
void KolejkaP::push(zadanie item){
    node *tmp, *q;
    tmp = new node;
    tmp->data = item;
    if(!high_priority){
        if(top == nullptr || item.r < top->data.r){
            tmp->link = top;
            top = tmp;
        }else{
            q = top;
            while(q->link != nullptr && q->link->data.r <= item.r){
                q=q->link;
            }
            tmp->link = q->link;
            q->link = tmp;
        }
    }else{
        if(top == nullptr || item.q > top->data.q){
            tmp->link = top;
            top = tmp;
        }else{
            q = top;
            while(q->link != nullptr && q->link->data.q >= item.q){
                q=q->link;
            }
            tmp->link = q->link;
            q->link = tmp;
        }
    }
}
zadanie KolejkaP::pop(){
    node *tmp;
    zadanie ret;
    if(top == nullptr){
        cerr<<"Kolejka pusta"<<endl;
    }else{
        tmp = top;
        ret=tmp->data;
        top = top->link;
        free(tmp);
    }
    return ret;
}
zadanie KolejkaP::peek(){
    if(top == nullptr){
        cerr<<"Kolejka pusta"<<endl;
    }else{
        return top->data;
    }
}
void KolejkaP::display(ostream &out){
    node *ptr;
    ptr = top;
    if(top == nullptr){
        cerr<<"Kolejka pusta"<<endl;
    }else{
        out<<"Kolejka to:"<<endl;
        out<<"Wartosc      ID"<<endl;
        while(ptr != nullptr){
            if(!high_priority){
                out<<setw(8)<<ptr->data.r<<"      "<<setw(3)<<ptr->data.ID<<endl;
            }else{
                out<<setw(8)<<ptr->data.q<<"      "<<setw(3)<<ptr->data.ID<<endl;
            }
            ptr=ptr->link;
        }
    }

}
bool KolejkaP::isEmpty(){
    if(top==nullptr){
        return true;
    }
    return false;
}
