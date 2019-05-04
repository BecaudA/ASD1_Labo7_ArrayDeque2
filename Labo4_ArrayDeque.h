#ifndef ArrayDeque_hpp
#define ArrayDeque_hpp

#include <vector>

template < class T >
class ArrayDeque
{
public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

private:
  std::vector<value_type> buffer;
  size_type debut;
  size_type taille;
  
public:
  ArrayDeque(size_type capacity = 0) : debut(0), taille(0), buffer(capacity) {}

   /**
    * @brief Getter de la taille du vecteur
    * @return Taille du vecteur
    */
   size_type size() const { return taille; }

   /**
    * @brief Getter de la capacité du vecteur
    */
   size_type capacity() const { return this->buffer.size(); }

   /**
    * @brief Vérifie si le vecteur est vide
    * @return Vrai si le vecteur est vide
    */
   bool empty() const { return (this->size() == 0); }

   /**
    * @brief Convertisseur d'indice logique à physique
    * @param i_logique
    * @return Indice physique
    */
   size_type i_physique(size_type i_logique) const {
      size_type iP = (debut + i_logique) % capacity();
      if(iP >= 0){
         return iP;
      } else{
         return iP + capacity();
      }
   }

   /**
    * @brief Augmente la capacité du vecteur s'il le faut
    */
   void nouvelleCapacite() {
      //Si le buffer à un capacité de 0, elle sera passée à 1
      //sinon au double de la capacité actuelle
      size_type nouvelleTaille;
      if(!taille){
         nouvelleTaille = 1;
      } else {
         nouvelleTaille = capacity()*2;
      }
      std::vector<value_type> temp(nouvelleTaille);

      for (size_type i = 0; i < capacity(); ++i) {
         temp.at(i) = std::move(buffer.at(i_physique(i)));
      }
      debut = 0;
      swap(temp, buffer);
   }

   /**
    * @brief Getter du dernier élément du vecteur
    * @return Dernier élément du vecteur
    */
   reference back() {
      return buffer.at(i_physique(taille - 1));
   }

   /**
    * @brief Setter du dernier élément du vecteur
    * @return Dernier élément du vecteur
    */
   T back() const {
      return buffer.at(i_physique(taille - 1));
   }

   /**
    * Getter du premier élément du vecteur
    * @return Premier élément du vecteur
    */
   reference front() {
      return buffer.at(debut);
   }

   /**
    * Setter du premier élément du vecteur
    * @return Premier élément du vecteur
    */
   T front() const {
      return buffer.at(debut);
   }

   /**
    * @brief Ajoute un élément à la fin du vecteur
    * @param valeur
    */
   void push_back(value_type valeur) {
     if(taille >= capacity()) {
         nouvelleCapacite();
      }

     if(taille < capacity()) {
         buffer.at(i_physique(taille)) = valeur;
         ++taille;
      }
   }

   /**
    * @brief Ajoute un élément au début du vecteur
    * @param valeur
    */
   void push_front(value_type valeur){
      //Si la taille == la capacité du buffer (buffer.size())
      //alors il faut augmenter la capacité
      if(taille >= capacity()){
         nouvelleCapacite();
      }

      if(taille < capacity()) {
         debut = i_physique(capacity() - 1);
         front() = valeur;
         ++taille;
      }
   }

   /**
    * @brief Supprime le dernier élément du vecteur
    */
   void pop_back() {
      if(taille) {
         --taille;
      }
   }

   /**
    * @brief Supprime le premier élément du vecteur
    */
   void pop_front() {
      if(taille) {
         debut = i_physique(1);
         --taille;
      }
   }
};

#endif /* ArrayDeque_hpp */
