#ifndef SET_H
#define SET_H

#include <iostream>
#include <ostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <cstddef>



/**
  @brief classe set

  La classe imlementa una generica lista di elementi T.
  La lista non può contenere elementi duplicati.
  La valutazione se due elementi di tipo T sono uguali è realizzato
  tramite il funtore Eql che prende due elementi a e b, e ritorna
  verso se i due elementi sono uguali. 

*/
template <typename T, typename Eql>
class set
{
  /**
     * @brief Struttura nodo
     * Struttura nodo interna che viene usata per creare la lista
     */
  struct nodo
  {
    T valore;   ///<valore da memorizzare
    nodo *next; ///<puntatore al prossimo nodo della lista

    /**
        Costruttore di default
        @post next == nullptr
        */
    nodo() : next(nullptr) {}

    /**
         * @brief Costruttore secondario
         * Funzione che inizializza un nodo con un valore e un puntatore
         * passato nella funzione
         * @param v valore da copiare
         * @param n puntatore a next
         * 
         * @post next == n
           @post valore == v
         */
    nodo(const T &v, nodo *n) : valore(v), next(n) {}

    /**
         * @brief Copy constructor
         * Funzione che inizializza un nodo copiandio il valore e il puntatore
         * di un altro nodo passato nella funzione
         * @param other nodo da copiare
         * @post valore == other.valore
         * @post next == other.next
         */
    nodo(const nodo &other) : valore(other.valore), next(other.next) {}
    /**
     * @brief operatore di assegnamento
     * Funzione che copia un nodo in un altro nodo
     * @param other nodo da copiare
     * @return reference al nodo this 
     */
    nodo &operator=(const nodo &other)
    {
      valore = other.valore;
      next = other.next;
      return *this;
    }
    /**
      Distruttore. 
    */
    ~nodo() {}
  };
  nodo *_head;        ///< puntatore al primo nodo della lista (testa)
  unsigned int _size; ///< numero di elementi nella lista
  Eql _equals;        ///< funtore per l'uguaglianza tra elementi T

public:
  /**
   * @brief Costruttore di default
   * Funzione che inizializza una set
   * @post _head == nullptr
     @post _size == 0
 */
  set() : _head(nullptr), _size(0) {}
  /**
 * @brief Copy constructor
 * Funzione che inizializza una set copiando i dati di un altra set
 * passata nella funzione
 * @param other lista da copiare
 * @post _size = other._size
 */
  set(const set &other) : _head(nullptr), _size(0)
  {
    nodo *curr = other._head;
    try
    {
      while (curr != nullptr)
      {
        add(curr->valore);
        curr = curr->next;
      }
    }
    catch (...)
    {
      svuota();
      throw;
    }
  }

  /**
    * @brief 
    * 
    * @param other 
    * @return set& 
    */

  /**
   * @brief Operatore di assegnamento
   * Funzione che copia una set in un altra set
   * @param other lista da copiare
   * @return reference alla lista this
   */
  set &operator=(const set &other)
  {
    if (this != &other)
    {
      set tmp(other);
      std::swap(this->_head, tmp._head);
      std::swap(this->_size, tmp._size);
    }
    return *this;
  }
  /**
    Distruttore 
    @post _head == nullptr
    @post _size == 0
  */
  ~set()
  {
    svuota();
  }
  /**
   * @brief Svuota la lista
   * @post _head == nullptr
     @post _size == 0
   */
  void svuota()
  {
    nodo *curr = _head;

    while (curr != nullptr)
    {
      nodo *cnext = curr->next;
      delete curr;
      curr = cnext;
    }
    _size = 0;
    _head = nullptr;
  }
  /**
   * @brief Funzione per vedere se una set è vuota
   * 
   * @return true se la lista è vuota
   * @return false altrimenti
   */
    bool is_empty(){
    return this->size==0;
  }
  /**
    * @brief 
    * Aggiunge un elemento nella lista evitando i duplicati
    * tramite il funtore di tipo Eql.
    * @param v valore da inserire nella lista
    * @post _size = _size+1
    */
  void add(const T &v)
  {

    // Caso di lista vuota
    if (_size == 0)
    {
      nodo *tmp = new nodo(v, nullptr);
      _head = tmp;
      _size = 1;
      return;
    }

    nodo *curr = _head;
    nodo *prev = _head;

    while (curr != nullptr)
    {
      if (_equals(curr->valore, v))
      {
        std::cout << "Valore già presente" << std::endl;
        return;
      }
      prev = curr;
      curr = curr->next;
    }
    nodo *tmp = new nodo(v, nullptr);
    _size++;
    prev->next = tmp;
  }

  /**
   * @brief Dimensione lista
   * Ritorna il numero di elementi nella lista
   * @return il numero di elementi nella lista
   */
  unsigned int size() const
  {
    return _size;
  }

  /**
   * @brief Rimuovi
   * Funzione che permette di rimuovere un valore passatogli dalla lista
   * @param v valore da rimuovere
   */
  void remove(const T &v)
  {
    nodo *curr = _head;
    nodo *prev = nullptr;
    if (_equals(v, curr->valore))
    {
      _head = curr->next;
      delete curr;
      _size--;
      return;
    }
    while (curr != nullptr)
    {
      if (_equals(v, curr->valore))
      {
        prev->next = curr->next;
        delete curr;
        _size--;
        return;
      }
      prev = curr;
      curr = curr->next;
    }
  }

  /**
   * @brief Costruttore iteratore
   * Costruttore che crea una set riempita con dati
     presi da una sequenza identificata da un iteratore di 
     inizio e uno di fine. Gli iteratori possono essere di
     qualunque tipo.  
   * @param b iteratore di inizio
   * @param e iteratore di fine
   */
  template <typename Q>
  set(Q b, Q e) : _head(nullptr), _size(0)
  {
    try
    {
      for (; b != e; ++b)
        add(static_cast<T>(*b)); // la add contiene una new che può fallire
    }
    catch (...)
    {
      // in caso di errore di memoria si svuota la lista
      svuota();
      throw;
    }
  }

  /**
   * @brief Funzione di stream
   * Funzione GLOBALE che implementa l'operatore di stream.
     La funzione è templata sulla sett ed è messa
     friend perchè accediamo ai dati privati di set.
   * @param os stream di output
   * @param s set da spedire sullo stream
   * @return lo stream di output 
   */
  friend std::ostream &operator<<(std::ostream &os, const set &s)
  {
    nodo *curr = s._head;
    while (curr != nullptr)
    {
      os << curr->valore << " ";
      curr = curr->next;
    }

    return os;
  }

  /**
   Gli iteratori devono iterare su elementi inseriti nella classe
   principale. Siccome nella set mettiamo dei elementi di 
   tipo T, l'iteratore deve iterare sui dati di tipo T.
   */
  class const_iterator
  {

  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;

    const_iterator() : ptr(nullptr)
    {
    }

    const_iterator(const const_iterator &other) : ptr(other.ptr)
    {
    }

    const_iterator &operator=(const const_iterator &other)
    {
      ptr = other.ptr;
      return *this;
    }

    ~const_iterator() {}

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const
    {
      return ptr->valore;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const
    {
      return &(ptr->valore);
    }

    // Operatore di iterazione post-incremento
    const_iterator operator++(int)
    {
      const_iterator tmp(*this);
      ptr = ptr->next;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    const_iterator &operator++()
    {
      ptr = ptr->next;
      return *this;
    }

    // Uguaglianza
    bool operator==(const const_iterator &other) const
    {
      return (ptr == other.ptr);
    }

    // Diversita'
    bool operator!=(const const_iterator &other) const
    {
      return !(other == *this);
    }

  private:
    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class set;

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const nodo *p) : ptr(p) {}

    const nodo *ptr;

    // !!! Eventuali altri metodi privati

  }; // classe const_iterator

  // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const
  {
    return const_iterator(_head);
  }

  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const
  {
    return const_iterator(nullptr);
  }

  /**
   * @brief Cerca un valore passato
   * Cerca se un valore passato è presente nella lista. Usa il
     funtore Eql.
   * @param valore valore da cercare nella lista
   * @return true se il valore è stato trovato
   * @return false altrimenti
   */
  bool cerca(const T &valore) const
  {
    nodo *curr = _head;

    while (curr != nullptr)
    {
      if (_equals(valore, curr->valore))

        return true;
      curr = curr->next;
    }
    return false;
  }
  /**
 * @brief 
 * 
 * @param other 
 * @return true 
 * @return false 
 */

  /**
   * @brief Operatore di ugualglianza
   * Controlla se due liste sono uguali tramite il funtore Eql
   * @param other lista da comparare
   * @return true se le due liste sono uguali
   * @return false altrimenti
   */
  bool operator==(const set &other) const
  {
    bool equal = true;
    nodo *curr = _head;
    if (size() == 0 && other.size() == 0)
    {
      return true;
    }
    if (size() == 0 && other.size() != 0)
    {
      return false;
    }
    if (size() != 0 && other.size() == 0)
    {
      return false;
    }
    if (size() != other.size())
    {
      return false;
    }
    if (size() == other.size())
    {
      while (curr != nullptr && equal)
      {
        if (!other.cerca(curr->valore))
        {
          return false;
        }
        else
          curr = curr->next;
      }
      return equal;
    }
    return equal;
  }
  /**
   * @brief Operatore[]
   * Permette di estrarre dalla lista un elemento in una posizione passata nella funzione
   * @param i posizione dell'elemento che si vuole estrarre
   * @return  elemento in posizione i
   */
  const T &operator[](int i) const
  {
    nodo *curr = _head;
    nodo *prev = _head;
    int n;
    assert(i >= 0 && i < size());
    for (n = 0; n <= i; n += 1)
    {
      if (curr != nullptr)
      {
        prev = curr;
        curr = curr->next;
      }
    }
    return prev->valore;
  }
};

/**
 * @brief filter_out
 * Funzione che permette di applicare una condizione (predicato)
 * agli elementi della set restituendo solo quelli che la rispettano
 * @tparam T elemento di tipo T
 * @tparam Eql funtore di uguaglianza
 * @tparam P predicato
 * @param S set passata nella funzione su cui applicare il predicato
 * @return una set con gli elementi che verificano il predicato 
 */
template <typename T, typename Eql, typename P>
set<T, Eql> filter_out(const set<T, Eql> &S, P predicato)
{
  typename set<T, Eql>::const_iterator begin, end;
  set<T, Eql> s1;
  begin = S.begin();
  end = S.end();
  try{
  while (begin != end)
  {
    if (predicato(*begin))
    {
      s1.add(*begin);
    }
    begin++;
  }
  }catch(...){
    s1.svuota();
    throw;
  }
  return s1;
}

/**
 * @brief operatore di unione
 * Funzione che permette di unire due liste senza duplicati
 * @tparam T elemento di tipo T
 * @tparam Eql funtore di uguaglianza
 * @param s1 prima set
 * @param s2 seconda set
 * @return una set in cui all'interno sono presenti tutti gli elementi di entrambe
 * le liste senza duplicati
 */
template <typename T, typename Eql>
set<T, Eql> operator+(const set<T, Eql> &s1, const set<T, Eql> &s2)
{
  set<T, Eql> s3;
  s3 = s1;
  try{
  for (int i = 0; i < s2.size(); i++)
  {
    s3.add(s2[i]);
  }
  }catch(...){
    s3.svuota();
    throw;
  }
  return s3;
}

/**
 * @brief operatore di intersezione
 * Funzione che permette di ottenere una set con all'interno solo elementi comuni
 * alle due set passate nella funzione
 * @tparam T elemento di tipo T
 * @tparam Eql funtore di uguaglianza
 * @param s1 prima set
 * @param s2 seconda set
 * @return set con elementi comuni tra le due set s1 e s2
 */
template <typename T, typename Eql>
set<T, Eql> operator-(const set<T, Eql> &s1, const set<T, Eql> &s2)
{
  set<T, Eql> s3;
  try{
  for (int i = 0; i < s1.size(); i++)
  {
    if (s2.cerca(s1[i]))
    {
      s3.add(s1[i]);
    }
  }
  }catch(...){
    s3.svuota();
    throw;
  }
  return s3;
}
#endif