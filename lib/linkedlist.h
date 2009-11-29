//Templated Linked List
//Author: Provided by Bench http://www.daniweb.com/forums/member63353.html at DaniWeb.com http://www.daniweb.com/code/snippet216960.html#
//Revision: Paul Scarrone (read_next and read_prev) Not Completed

template <typename T>
class DoubleLinked
{
    struct node
    {
        T data;
        node* prev;
        node* next;
        node(T t, node* p, node* n) : data(t), prev(p), next(n) {}
    };
    node* head;
    node* tail;
	int size;

public:
    DoubleLinked() : head( NULL ), tail ( NULL ), size ( 0 ) {}
    template<int N>
    DoubleLinked( T (&arr) [N]) : head( NULL ), tail ( NULL ), size( 0 )
    {
        for( int i(0); i != N; ++i)
            push_back(arr[i]);
    }

    bool empty() const { return ( !head || !tail ); }
    operator bool() const { return !empty(); } 
    void push_back(T);
    void push_front(T);
    T pop_back();
    T pop_front();
	void CopyList(DoubleLinked<T>& rList);
	int GetSize() const { return size; }


    ~DoubleLinked()
    {
		/*node *temp;
		temp = head;
        while(temp!=NULL)
        {
            head = temp;
            temp=temp->next;
            delete head;
        }*/
    }
};

template <typename T>
void DoubleLinked<T>::push_back(T data)
{
    tail = new node(data, tail, NULL);
    if( tail->prev )
        tail->prev->next = tail;

    if( empty() )
        head = tail;

	size++;
}

template <typename T>
void DoubleLinked<T>::push_front(T data)
{
    head = new node(data, NULL, head);
    if( head->next )
        head->next->prev = head;

    if( empty() )
        tail = head;

	size++;
}

template<typename T>
T DoubleLinked<T>::pop_back()
{
    if( empty() )
        throw("DoubleLinked : list empty");
	if(!empty())
		size--;
    node* temp(tail);
    T data( tail->data );
    tail = tail->prev ;

    if( tail )
        tail->next = NULL;
    else
        head = NULL ;

    delete temp;
    return data;
}

template<typename T>
T DoubleLinked<T>::pop_front()
{
    if( empty() )
        throw("DoubleLinked : list empty");
	if(!empty())
		size--;
    node* temp(head);
    T data( head->data );
    head = head->next ;

    if( head )
        head->prev = NULL;
    else
        tail = NULL;

    delete temp;
    return data;
}
template<typename T>
void DoubleLinked<T>::CopyList(DoubleLinked<T>& rList)
{
	long listSize = this->GetSize();
	T temp;
	for(long i = 0; i < listSize; i++)
	{
		temp = this->pop_front();
		rList.push_back(temp);
		this->push_back(temp);
	}
}