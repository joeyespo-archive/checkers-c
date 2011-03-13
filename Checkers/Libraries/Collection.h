// Collection.h
// By Joe Esposito
// 2004-11-24


// Define NULL
#ifndef NULL
#define NULL  (0)
#endif


// Collection exception class
class CollectionException
{
public:
  
  char *lpszMessage;
  
  CollectionException () { lpszMessage = ""; }
  CollectionException (char *lpszMessage) { this->lpszMessage = lpszMessage; }
};



// Collection class
template <class ItemType>
class Collection
{
public:
  
  // Class Construction
  // -------------------
  
  Collection ()
  {
    m_lpItems = NULL;
    m_Count = 0;
  }
  
  Collection (Collection &value)
  {
    m_Count = value.m_Count;
    m_lpItems = new ItemType [m_Count];
    
    for (int i = 0; i < m_Count; i++)
      m_lpItems[i] = value.m_lpItems[i];
  }
  
  ~Collection ()
  { Clear(); }
  
  
  // Overloaded Operators
  // ---------------------
  
  ItemType &operator [] ( int Index )
  { return ItemAt(Index); }
  
  operator ItemType * ()
  { return GetArray(); }
    
  // Assignment Operators
  //Collection <ItemType> &operator = ( const Collection <ItemType> & );
  //Collection <ItemType> &operator += ( Collection <ItemType> & );
  //Collection <ItemType> &operator += ( ItemType );
  //friend Collection <ItemType> operator + ( const Collection <ItemType> &, const Collection <ItemType> & );
  //bool operator == ( const ItemType & );
  //bool operator == ( const Collection <ItemType> & );
  
  
  // Public Functions
  // -----------------
  
  int Count ()
  { return m_Count; }
  
  // General Accessors
  ItemType &ItemAt (int Index)
  {
    if (!((Index >= 0) && (Index < m_Count))) throw CollectionException("Index out of bounds");
    return m_lpItems[Index];
  }
  
  ItemType *GetArray ()
  { return m_lpItems; }
  
  // Additional Resizers
  void Add (ItemType item)
  {
    ItemType *lpResult = new ItemType [m_Count + 1];
    
    for (int i = 0; i < m_Count; i++)
      lpResult[i] = m_lpItems[i];
    lpResult[m_Count] = item;
    
    delete [m_Count] m_lpItems;
    m_lpItems = lpResult;
    m_Count++;
  }
  
  void Insert (int Index, ItemType item)
  {
    if (!((Index >= 0) && (Index <= m_Count))) throw CollectionException("Index out of bounds");
    
    ItemType *lpResult = new ItemType [m_Count + 1];
    
    for (int i = 0; i < Index; i++) lpResult[i] = m_lpItems[i];
    for (int i = Index+1; i <= m_Count; i++) lpResult[i] = m_lpItems[i-1];
    lpResult[Index] = item;
    
    delete [m_Count] m_lpItems;
    m_lpItems = lpResult;
    m_Count++;
  }
  //void AddRange ();
  
  void AddUnique (ItemType item)
  {
    for (int i = 0; i < m_Count; i++)
      if (m_lpItems[i] == item) return;
    Add(item);
  }
  //void AddUniqueRange ();
  
  void RemoveAt (int Index)
  {
    if (!((Index >= 0) && (Index < m_Count))) throw CollectionException("Index out of bounds");
    
    if (--m_Count == 0) {
      delete m_lpItems; m_lpItems = NULL;
      return;
    }
    
    ItemType *lpResult = new ItemType [m_Count];
    for (int i = 0; i < Index; i++) lpResult[i] = m_lpItems[i];
    for (int i = Index+1; i <= m_Count; i++) lpResult[i-1] = m_lpItems[i];
    
    delete [m_Count] m_lpItems;
    m_lpItems = lpResult;
  }
  
  void Remove (ItemType item)
  {
    for (int i = 0; i < m_Count; i++)
    {
      if (m_lpItems[i] == item)
      { RemoveAt(i); return; }
    }
  }
  
  void Clear ()
  {
    if (m_lpItems) delete [m_Count] m_lpItems;
    m_lpItems = NULL;
    m_Count = 0;
  }
  
  void Swap (int Index1, int Index2)
  {
    ItemType temp = m_lpItems[Index1];
    m_lpItems[Index1] = m_lpItems[Index2];
    m_lpItems[Index2] = temp;
  }
  
  bool Exists (ItemType item)
  {
    for (int i = 0; i < m_Count; i++)
    { if (m_lpItems == item) return true; }
    return false;
  }
  
  int IndexOf (ItemType item)
  {
    for (int i = 0; i < m_Count; i++)
    { if (m_lpItems[i] == item) return i; }
    return -1;
  }
  
private:
  int m_Count;            // The number of Items
  ItemType *m_lpItems;   // The actual list of pointers to items
};
