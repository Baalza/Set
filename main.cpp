#include <iostream>
#include <ostream>
#include <cassert>
#include <algorithm>
#include "set.h"

/**
 * @brief Funtore di uguaglianza tra tipi interi
 * 
 */
struct confronto_interi
{
  bool operator()(int a, int b) const
  {
    return a == b;
  }
};
/**
 * @brief Funtore di uguaglianza tra tipi stringhe
 * 
 */
struct confronto_stringhe
{
  bool operator()(const std::string &a, const std::string &b) const
  {
    return (a == b);
  }
};
/**
 * @brief Struttura del punto
 * Punto a due dimensioni
 */
struct punto
{
  int x; ///< coordinata x del punto
  int y; ///< coordinata y del punto

  /**
   * @brief Costruttore di default
   * @post x == 0
   * @post y == 0
   */
  punto() : x(0), y(0) {}
  /**
   * @brief Costruttore Secondario
   * 
   * @param xx valore da copiare nella coordinata x
   * @param yy valore da copaire nella coordinata y
   * @post x == xx
   * @post y == yy
   */
  punto(int xx, int yy) : x(xx), y(yy) {}
  /**
   * @brief Copy constructor
   * 
   * @param other punto da copiare
   * @post x = other.x
   * @post y = other.y
   */
  punto(const punto &other) : x(other.x), y(other.y) {}

  /**
   * @brief Operatore di assegnamento
   * 
   * @param other punto da copiare
   * @return ritorna un punto con coordinate preso dal punto passato alla funzione
   */
  punto &operator=(const punto &other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }
  /**
   * @brief Operatore di uguaglianza tra due punti
   * Verifica che entrambe le coordinate dei due punti siano uguali
   * @param other punto da confrontare
   * @return true se i punti sono uguali
   * @return false se i punti sono diversi
   */
  bool operator==(const punto &other)const{
    return x == other.x && y == other.y;
  }
  /**
   * @brief Operatore di disuguaglianza tra due punti
   * Verifica che entrambe le coordinate dei due punti siano diverse
   * @param other punto da confrontare
   * @return true se i punti sono diversi
   * @return false se i punti sono uguali
   */
  bool operator!=(const punto &other)const{
    return (x != other.x | y != other.y);
  }
  /**
      Distruttore. 
    */
  ~punto() {}

  /**
 * @brief Funzione di stream
 *  Ridefinizione dell'operatore di stream per un punto.
    Necessario per l'operatore di stream della classe set.
 * 
 * @param os os stream di output
 * @param p punto da spedire sullo stream
 * @return lo stream di output  
 */
friend std::ostream &operator<<(std::ostream &os, const punto &p)
{
  os << "(" << p.x << "," << p.y << ")";
  return os;
}
};

/**
 * @brief Funtore di uguaglianza tra tipi punto
 * 
 */
struct confronto_punti
{
  bool operator()(const punto &p1, const punto &p2) const
  {
    return (p1.x == p2.x && p1.y == p2.y);
  }
};
/**
 * @brief Funtore predicato interi
 * Ritorna true se il valore intero passato è pari
 */
struct int_pari
{
  bool operator()(int i) const
  {
    return (i % 2 == 0);
  }
};
/**
 * @brief Funtore predicato interi
 * Ritorna true se il valore intero passato è dispari
 */
struct int_dispari
{
  bool operator()(int i) const
  {
    return (i % 2 != 0);
  }
};
/**
 * @brief Funtore predicato stringhe
 * Ritorna true se la lunghezza della stringa passata è pari
 */
struct string_pari
{
  bool operator()(std::string i) const
  {
    return (i.size() % 2 == 0);
  }
};
/**
 * @brief Funtore predicato stringhe
 * Ritorna true se la lunghezza della stringa passata è dispari
 */
struct string_dispari
{
  bool operator()(std::string i) const
  {
    return (i.size() % 2 != 0);
  }
};
/**
 * @brief Funtore predicato punti
 * Ritorna true se entrambe le coordinate del punto sono pari
 */
struct punto_pari
{
  bool operator()(punto i) const
  {
    return (i.x % 2 == 0 && i.y % 2 == 0);
  }
};
/**
 * @brief Funtore predicato punti
 * Ritorna true se entrambe le coordinate del punto sono dispari
 */
struct punto_dispari
{
  bool operator()(punto i) const
  {
    return (i.x % 2 != 0 && i.y % 2 != 0);
  }
};

/** 
 * Nel seguente metodo vengono effettuati tutti i test su un set di interi
 */
void test_int()
{

  set<int, confronto_interi> lista1;
  set<int, confronto_interi> lista2(lista1);
  set<int, confronto_interi> lista4;
  assert(lista1.size() == 0);
  assert(lista2.size() == 0);
  for (int i = 0; i < 10; i++)
  {
    lista1.add(i);
  }
  assert(lista1.size() == 10);
  set<int, confronto_interi> lista3(lista1);
  assert(lista3.size() == 10);
  lista4 = lista1;
  assert(lista4.size() == 10);
  assert(lista1 == lista3);
  lista1.svuota();
  assert(lista1.size() == 0);
  lista4.remove(0);
  std::cout << lista4 << std::endl;
  lista4.remove(9);
  std::cout << lista4 << std::endl;
  lista4.remove(4);
  std::cout << lista4 << std::endl;
  assert(lista4.size() == 7);
  lista4.add(1);
  int vett[4] = {1, 2, 3, 4};
  set<int, confronto_interi> lista5(vett, vett + 4);
  std::cout << lista5 << std::endl;
  assert(lista4.cerca(5));
  assert(lista4.cerca(1));
  assert(lista4.cerca(8));
  assert(!lista4.cerca(10));
  set<int, confronto_interi> lista6;
  set<int, confronto_interi> lista7;
  lista6.add(1);
  lista6.add(4);
  lista7.add(1);
  lista7.add(4);
  std::cout << "lista6" << std::endl;
  std::cout << lista6 << std::endl;
  std::cout << "lista7" << std::endl;
  std::cout << lista7 << std::endl;
  assert(!(lista6 == lista1));
  assert(!(lista1 == lista4));
  assert(lista1 == lista2);
  assert(lista6 == lista7);
  assert(lista4[2]);
  assert(lista4[0]);
  assert(lista4[6]);
  std::cout << lista4[2] << std::endl;

  int v[5] = {1, 5, 9, 3, 0};
  set<int, confronto_interi> lista8(v, v + 5);
  set<int, confronto_interi>::const_iterator i, b, e;
  assert(b == e);
  i = lista8.begin();
  set<int, confronto_interi>::const_iterator ii(i);
  assert(i == ii);
  assert((*i) == (*ii));
  i++;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));
  ++i;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));

  assert(*i == 9 && *ii == 9);
  i++;
  assert(i != ii);
  assert((*i) != (*ii));
  const int *p = &(*i);
  assert(*p == 3);
  i = ii;
  assert(i == ii);
  set<int, confronto_interi> lista9;
  set<int, confronto_interi> lista10;
  set<int, confronto_interi> lista11;
  lista9.add(1);
  lista9.add(4);
  lista9.add(7);
  lista10.add(1);
  lista10.add(4);
  lista10.add(8);
  std::cout << "lista9" << std::endl;
  std::cout << lista9 << std::endl;
  std::cout << "lista10" << std::endl;
  std::cout << lista10 << std::endl;
  lista11 = lista9 + lista10;
  std::cout << lista11 << std::endl;
  lista11 = lista9 - lista10;
  std::cout << lista11 << std::endl;
  set<int, confronto_interi> lista12;
  set<int, confronto_interi> lista13;
  lista13.add(2);
  lista13.add(4);
  lista13.add(9);
  int_pari ip;
  int_dispari id;
  lista12 = filter_out(lista13, ip);
  std::cout << "lista13" << std::endl;
  std::cout << lista12 << std::endl;
  lista12 = filter_out(lista13, id);
  std::cout << "lista13" << std::endl;
  std::cout << lista12 << std::endl;
}
/** 
 * Nel seguente metodo vengono effettuati tutti i test su un set di stringhe
 */
void test_string()
{

  set<std::string, confronto_stringhe> lista1;
  set<std::string, confronto_stringhe> lista2(lista1);
  set<std::string, confronto_stringhe> lista4;
  assert(lista1.size() == 0);
  assert(lista2.size() == 0);
  lista1.add("pippo");
  lista1.add("pluto");
  lista1.add("paperino");
  lista1.add("cip");
  lista1.add("cip");
  //std::cout<<lista1<<std::endl;
  assert(lista1.size() == 4);
  set<std::string, confronto_stringhe> lista3(lista1);
  assert(lista3.size() == 4);
  lista4 = lista1;
  assert(lista4.size() == 4);
  assert(lista1 == lista3);
  lista1.svuota();
  assert(lista1.size() == 0);
  lista4.remove("pippo");
  std::cout << lista4 << std::endl;
  lista4.remove("cip");
  std::cout << lista4 << std::endl;
  lista4.remove("pluto");
  std::cout << lista4 << std::endl;
  assert(lista4.size() == 1);
  lista4.add("pippo");
  lista4.add("pluto");
  std::string vett[4] = {"pippo", "pluto", "paperino", "cip"};
  set<std::string, confronto_stringhe> lista5(vett, vett + 4);
  std::cout << lista5 << std::endl;
  assert(lista4.cerca("pluto"));
  assert(lista4.cerca("paperino"));
  assert(lista4.cerca("pippo"));
  assert(!lista4.cerca("cip"));
  std::string s = lista4[2];
  set<std::string, confronto_stringhe> lista6;
  set<std::string, confronto_stringhe> lista7;
  lista6.add("pippo");
  lista6.add("pluto");
  lista7.add("pippo");
  lista7.add("pluto");
  std::cout << "lista6" << std::endl;
  std::cout << lista6 << std::endl;
  std::cout << "lista7" << std::endl;
  std::cout << lista7 << std::endl;
  assert(!(lista6 == lista1));
  assert(!(lista1 == lista4));
  assert(lista1 == lista2);
  assert(lista6 == lista7);
  std::cout << lista4[1] << std::endl;
  std::cout << lista4[0] << std::endl;
  std::cout << lista4[2] << std::endl;

  std::string v[4] = {"pippo", "pluto", "paperino", "cip"};
  set<std::string, confronto_stringhe> lista8(v, v + 4);
  set<std::string, confronto_stringhe>::const_iterator i, b, e;
  assert(b == e);
  i = lista8.begin();
  set<std::string, confronto_stringhe>::const_iterator ii(i);
  assert(i == ii);
  assert((*i) == (*ii));
  i++;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));
  ++i;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));

  assert((*i) == "paperino" && *ii == "paperino");
  i++;
  assert(i != ii);
  assert((*i) != (*ii));
  const std::string *p = &(*i);
  assert(*p == "cip");
  i = ii;
  assert(i == ii);
  set<std::string, confronto_stringhe> lista9;
  set<std::string, confronto_stringhe> lista10;
  set<std::string, confronto_stringhe> lista11;
  lista9.add("pippo");
  lista9.add("pluto");
  lista9.add("paperino");
  lista10.add("pippo");
  lista10.add("pluto");
  lista10.add("cip");
  std::cout << "lista9" << std::endl;
  std::cout << lista9 << std::endl;
  std::cout << "lista10" << std::endl;
  std::cout << lista10 << std::endl;
  lista11 = lista9 + lista10;
  std::cout << lista11 << std::endl;
  lista11 = lista9 - lista10;
  std::cout << lista11 << std::endl;
  set<std::string, confronto_stringhe> lista12;
  set<std::string, confronto_stringhe> lista13;
  lista13.add("qwer");
  lista13.add("pippo");
  lista13.add("pluto");
  string_pari sp;
  string_dispari sd;
  lista12 = filter_out(lista13, sp);
  std::cout << "lista13" << std::endl;
  std::cout << lista12 << std::endl;
  lista12 = filter_out(lista13, sd);
  std::cout << "lista13" << std::endl;
  std::cout << lista12 << std::endl;
}
/** 
 * Nel seguente metodo vengono effettuati tutti i test su un set di punti
 */
void test_custom()
{
  set<punto, confronto_punti> lista1;
  set<punto, confronto_punti> lista2(lista1);
  set<punto, confronto_punti> lista4;
  assert(lista1.size() == 0);
  assert(lista2.size() == 0);
  punto punto1(1, 2);
  punto punto2(3, 4);
  punto punto3(5, 6);
  punto punto4(7, 8);
  punto punto5(1, 2);
  lista1.add(punto1);
  lista1.add(punto2);
  lista1.add(punto3);
  lista1.add(punto4);
  lista1.add(punto5);
  assert(lista1.size() == 4);
  set<punto, confronto_punti> lista3(lista1);
  assert(lista3.size() == 4);
  lista4 = lista1;
  assert(lista4.size() == 4);
  assert(lista1 == lista3);
  lista1.svuota();
  assert(lista1.size() == 0);
  lista4.remove(punto1);
  std::cout << lista4 << std::endl;
  lista4.remove(punto4);
  std::cout << lista4 << std::endl;
  lista4.remove(punto3);
  std::cout << lista4 << std::endl;
  assert(lista4.size() == 1);
  lista4.add(punto1);
  lista4.add(punto3);
  punto vett[4] = {punto1, punto2, punto3, punto4};
  set<punto, confronto_punti> lista5(vett, vett + 4);
  std::cout << lista5 << std::endl;
  assert(lista4.cerca(punto1));
  assert(lista4.cerca(punto2));
  assert(lista4.cerca(punto3));
  assert(!lista4.cerca(punto4));
  punto s = lista4[2];
  set<punto, confronto_punti> lista6;
  set<punto, confronto_punti> lista7;
  lista6.add(punto1);
  lista6.add(punto2);
  lista7.add(punto1);
  lista7.add(punto2);
  std::cout << "lista6" << std::endl;
  std::cout << lista6 << std::endl;
  std::cout << "lista7" << std::endl;
  std::cout << lista7 << std::endl;
  assert(!(lista6 == lista1));
  assert(!(lista1 == lista4));
  assert(lista1 == lista2);
  assert(lista6 == lista7);
  std::cout << lista4[1] << std::endl;
  std::cout << lista4[0] << std::endl;
  std::cout << lista4[2] << std::endl;

  punto setPunti[4] = {punto(-1, 6), punto(1, 1), punto(1, -4), punto(1, -3)};
  set<punto, confronto_punti> punto20(setPunti, setPunti + 4);
  set<punto, confronto_punti>::const_iterator i, b, e;
  assert(b == e);
  i = punto20.begin();
  set<punto, confronto_punti>::const_iterator ii(i);
  assert(i == ii);
  assert((*i) == (*ii));
  i++;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));
  ++i;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));
  assert((*i) == punto(1,-4) && *ii == punto(1,-4));
  i++;
  assert(i != ii);
  assert((*i) != (*ii));
  const punto *p = &(*i);
  assert(*p == punto(1, -3));
  i = ii;
  assert(i == ii);
  
  /*punto v[5] = {punto(-1, -5), punto(0, 0), punto(1, -4), punto(-4, -3), punto(10, 3)};
  set<punto, confronto_punti> punto8(v, v + 5);
  set<punto, confronto_punti>::const_iterator i, b, e;
  assert(b == e);
  i = punto8.begin();
  set<punto, confronto_punti>::const_iterator ii(i);
  assert(i == ii);
  assert((*i) == (*ii));
  i++;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));
  ++i;
  ii++;
  assert(i == ii);
  assert((*i) == (*ii));

  assert(*i == 9 && *ii == 9);
  i++;
  assert(i != ii);
  assert((*i) != (*ii));
  const int *p = &(*i);
  assert(*p == 3);
  i = ii;
  assert(i == ii);*/

  set<punto, confronto_punti> lista9;
  set<punto, confronto_punti> lista10;
  set<punto, confronto_punti> lista11;
  lista9.add(punto1);
  lista9.add(punto2);
  lista9.add(punto3);
  lista10.add(punto1);
  lista10.add(punto2);
  lista10.add(punto4);
  std::cout << "lista9" << std::endl;
  std::cout << lista9 << std::endl;
  std::cout << "lista10" << std::endl;
  std::cout << lista10 << std::endl;
  lista11 = lista9 + lista10;
  std::cout << "+" << lista11 << std::endl;
  lista11 = lista9 - lista10;
  std::cout << "-" << lista11 << std::endl;
  set<punto, confronto_punti> lista12;
  set<punto, confronto_punti> lista13;
  punto punto9(2, 4);
  punto punto6(2, 6);
  punto punto7(1, 3);
  punto punto8(3, 7);
  lista13.add(punto9);
  lista13.add(punto6);
  lista13.add(punto7);
  lista13.add(punto8);
  punto_pari pp;
  punto_dispari pd;
  lista12 = filter_out(lista13, pp);
  std::cout << "lista13" << std::endl;
  std::cout << lista12 << std::endl;
  lista12 = filter_out(lista13, pd);
  std::cout << "lista13" << std::endl;
  std::cout << lista12 << std::endl;
}

int main()
{
  test_int();
  test_string();
  test_custom();

  return 0;
}
