#include <iostream>
#include "List.h"

template <typename T>
List<T>::List()
{
    head=NULL;
    tail=NULL;
    size=0;
}

template <typename T>
void List<T>::remove()
{
    head=NULL;
    tail=NULL;
    size=0;
}

template <typename T>
void List<T>::add(T data)
{
    Node<T>* node = new Node<T>;
    if (head==NULL)
    {
        node->data=data;
        node->prev=NULL;
        node->next=NULL;
        head=node;
        tail=node;
    }
    else
    {
        node->data=data;
        node->next=NULL;
        node->prev=tail;
        tail->next=node;
        tail=node;
    }
    size++;
}

template <typename T>
void List<T>::print()
{
    Node<T>* node = head;
    for(int i=0;i<size;i++)
    {
        std::cout << node->data << " ";
        node=node->next;
    }
}

template <typename T>
void List<T>::popTail()
{
    if (head==NULL)
        return;
    if (head==tail)
    {
        delete head;
        head=NULL;
        tail=NULL;
        size=0;
        return;
    }
    Node<T> *temp = tail;
    tail=tail->prev;
    delete temp;
    tail->next=NULL;
    size--;
}

template <typename T>
void List<T>::popHead()
{
    if (head==NULL)
        return;
    if (head==tail)
    {
        delete head;
        head=NULL;
        tail=NULL;
        size=0;
        return;
    }
    Node<T> *temp=head;
    head=head->next;
    delete temp;
    head->prev=NULL;
    size--;
}

template <typename T>
T List<T>::element(int position)
{
    Node<T> *temp=head;
    if (position<=size)
        for (int i=1;i<position;i++)
            temp=temp->next;
    return temp->data;
}

template <typename T>
Node<T> *List<T>::elect_element(int position)
{
    Node<T> *temp=head;
    if (position<=size)
        for (int i=1;i<position;i++)
            temp=temp->next;
    return temp;
}

template <typename T>
void List<T>::quicksort(int a,int b)
{
    if (b==-2)
        b=size;
    int left=a,right=b;
    T piv=element((left+right)/2);
    while(left<=right)
    {
        while (element(left)<piv)
            left++;
        while (element(right)>piv)
            right--;
        if (left<=right)
        {
            T temp2;
            temp2=elect_element(left)->data;
            elect_element(left)->data=elect_element(right)->data;
            elect_element(right)->data=temp2;
            left++;
            right--;
        }
    }
    if (a<right)
        quicksort(a,right);
    if (b>left)
        quicksort(left,b);
}

template <typename T>
void List<T>::insertionsort()
{
    int i,key,j;
    for (i=2;i<=size;i++)
    {
        key=element(i);
        j=i-1;
        while (j>=1 && element(j)>key)
        {
            elect_element(j+1)->data=elect_element(j)->data;
            j--;
        }
        elect_element(j+1)->data=key;
    }
}

template <typename T>
void List<T>::merge(int left,int m,int right)
{
    int i=1,j=1,k=left;
    int n1=m-left+1;
    int n2=right-m;
    List L,R;
    for (int y=1;y<=n1;y++)
        L.add(element(left+y-1));
    for (int y=1;y<=n2;y++)
        R.add(element(m+y));
    while (i<=n1 && j<=n2)
    {
        if (L.element(i)<R.element(j))
        {
            elect_element(k)->data=L.element(i);
            i++;
        }
        else
        {
            elect_element(k)->data=R.element(j);
            j++;
        }
        k++;
    }

    while (i<=n1)
    {
        elect_element(k)->data=L.element(i);
        i++;
        k++;
    }
    while (j<=n2)
    {
        elect_element(k)->data=R.element(j);
        j++;
        k++;
    }
    L.remove();
    R.remove();
}

template <typename T>
void List<T>::mergesort(int left,int right)
{
    if (right==-2)
        right=size;
    if (left<right)
    {
        int m=(left+right)/2;
        mergesort(left,m);
        mergesort(m+1,right);
        merge(left,m,right);
    }
}

template <typename T>
void List<T>::heap(int n,int i)
{
    int largest=i;
    int left=i*2+1;
    int right=i*2+2;
    if (left<n && element(left+1)>element(largest+1))
        largest=left;
    if (right<n && element(right+1)>element(largest+1))
        largest=right;
    if (largest!=i)
    {
        T temp;
        temp=elect_element(i+1)->data;
        elect_element(i+1)->data=elect_element(largest+1)->data;
        elect_element(largest+1)->data=temp;
        heap(n,largest);
    }
}

template <typename T>
void List<T>::heapsort()
{
    for (int i=size/2-1;i>=0;i--)
        heap(size,i);
    for (int i=size-1;i>=0;i--)
    {
        T temp;
        temp=elect_element(1)->data;
        elect_element(1)->data=elect_element(i+1)->data;
        elect_element(i+1)->data=temp;
        heap(i,0);
    }
}

template <typename T>
void List<T>::selectionsort()
{
    int i,j,min;
    for (i=0;i<size-1;i++)
    {
        min=i;
        for (j=i+1;j<size;j++)
            if (element(j+1)<element(min+1))
                min=j;
        T temp;
        temp=elect_element(min+1)->data;
        elect_element(min+1)->data=elect_element(i+1)->data;
        elect_element(i+1)->data=temp;
    }
}