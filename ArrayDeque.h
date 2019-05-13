#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <algorithm>
#include <stdexcept>

template<class T>
class ArrayDeque {
public:
	using value_type = T;
	using reference = T & ;
	using const_reference = const T&;
	using rvalue_reference = T && ;
	using pointer = T * ;

	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

private:
	pointer buffer;
	size_type capacite;
	size_type debut;
	size_type taille;

public:
	ArrayDeque(size_type cap = 0) : debut(0), taille(0), capacite(cap) {
		buffer = capacite != 0 ?
			(pointer) ::operator new(capacite * sizeof(value_type))
			: nullptr;
	}
   
   ArrayDeque(const ArrayDeque& deque) : ArrayDeque(deque.capacite)
   {
      debut = deque.debut;
      for (size_type i = 0; i < deque.taille; ++i) 
      {
         new(buffer + i_physique(i)) value_type(deque.at(i));
         ++taille;
      }
   }
   
   ~ArrayDeque() {
      for (size_type i = 0; i < taille; ++i) 
      {
         buffer[i_physique(i)].~value_type();
      }

      ::operator delete(buffer);
   }
   
   ArrayDeque& operator=(const ArrayDeque& deque)
   {
      ArrayDeque temp = deque;
      std::swap(buffer, temp.buffer);
      return *this;
   }
   
	reference at(size_type n) {
		return *(buffer + i_physique(n));
	}

	const_reference at(size_type n) const {
		return *(buffer + i_physique(n));
	}

	/**
	  * @brief Getter de la taille du vecteur
	  * @return Taille du vecteur
	  */
	size_type size() const { return this->taille; }

	/**
	 * @brief Getter de la capacité du vecteur
	 */
	size_type capacity() const { return this->capacite; }

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
		if (iP >= 0) {
			return iP;
		}
		else {
			return iP + capacity();
		}
	}
	
	size_type i_physique(size_type i_logique, size_type otherCapacity) const {
		size_type iP = (debut + i_logique) % otherCapacity;
		if (iP >= 0) {
			return iP;
		}
		else {
			return iP + otherCapacity;
		}
	}

	/**
	 * @brief Augmente la capacité du vecteur s'il le faut
	 */
	void nouvelleCapacite() {
		//Si le buffer à un capacité de 0, elle sera passée à 1
		//sinon au double de la capacité actuelle
		 size_type nouvelleCapacite = capacite == 0 ? 1 : capacite * 2;
       ArrayDeque temp(nouvelleCapacite);
       for (size_type i = 0; i < taille; ++i) {
			new(temp.buffer + i) value_type(std::move(buffer[i_physique(i)]));
			++temp.taille;
		}
       
		std::swap(buffer, temp.buffer);
		std::swap(capacite, temp.capacite);
		std::swap(debut, temp.debut);
	}

	/**
	 * @brief Getter du dernier élément du vecteur
	 * @return Dernier élément du vecteur
	 */
	reference back() {
		return buffer[i_physique(taille - 1)];
	}
	
	const_reference back() const
	{
	   return buffer[i_physique(taille - 1)];
	}

	/**
	 * Getter du premier élément du vecteur
	 * @return Premier élément du vecteur
	 */
	reference front() {
		return buffer[debut];
	}

	/**
	 * Setter du premier élément du vecteur
	 * @return Premier élément du vecteur
	 */
	const_reference front() const {
		return buffer[debut];
	}

	/**
	 * @brief Ajoute un élément à la fin du vecteur
	 * @param valeur
	 */
	void push_back(const_reference valeur) {
		if (taille >= capacity()) {
			nouvelleCapacite();
		}

		if (taille < capacity()) {
			new(buffer + i_physique(taille)) value_type(valeur);
			++taille;
		}
	}
	
	void push_back(rvalue_reference valeur) {
		if (taille >= capacity()) {
			nouvelleCapacite();
		}

		if (taille < capacity()) {
			new(buffer + i_physique(taille)) value_type(std::move(valeur));
			++taille;
		}
	}

	/**
	 * @brief Ajoute un élément au début du vecteur
	 * @param valeur
	 */
	void push_front(const_reference valeur) {
		//Si la taille == la capacité du buffer (buffer.size())
		//alors il faut augmenter la capacité
		if (taille >= capacity()) {
			nouvelleCapacite();
		}

		if (taille < capacity()) {
		   new(buffer + i_physique(capacite - 1)) value_type(valeur);
		   debut = i_physique(capacite - 1);
			++taille;
		}
	}
	
	void push_front(rvalue_reference valeur) {
		//Si la taille == la capacité du buffer (buffer.size())
		//alors il faut augmenter la capacité
		if (taille >= capacity()) {
			nouvelleCapacite();
		}

		if (taille < capacity()) {
		   new(buffer + i_physique(capacite - 1)) value_type(std::move(valeur));
		   debut = i_physique(capacite - 1);
			++taille;
		}
	}

	/**
	 * @brief Supprime le dernier élément du vecteur
	 */
	void pop_back() {
		if (taille) {
		   buffer[i_physique(taille - 1)].~value_type();
			--taille;
		}
	}

	/**
	 * @brief Supprime le premier élément du vecteur
	 */
	void pop_front() {
		if (taille) {
		   buffer[debut].~value_type();
			debut = i_physique(1);
			--taille;
		}
	}
};

#endif /* ArrayDeque_hpp */
