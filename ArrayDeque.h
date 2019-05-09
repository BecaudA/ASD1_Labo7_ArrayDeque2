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
		 size_type oldCapacity = capacite;
       capacite = !capacite ? 1 : capacite * 2;
       pointer temp = buffer;
       buffer = new value_type[capacite];
       for (size_type i = 0; i < oldCapacity; ++i) {
			*(buffer + i) = *std::move((temp + i_physique(i, oldCapacity)));
		}
       
		// Détruit temp
		// Parcours la Pile, détruit chaque objets
		for (size_t i = 0; i < taille; ++i) {
			(*(temp + (i_physique(i)))).~value_type();
		}
		::operator delete(temp);

		debut = 0;
		
	}

	/**
	 * @brief Getter du dernier élément du vecteur
	 * @return Dernier élément du vecteur
	 */
	reference back() {
		return buffer[i_physique(taille - 1)];
	}

	/**
	 * @brief Setter du dernier élément du vecteur
	 * @return Dernier élément du vecteur
	 */
	T back() const {
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
	T front() const {
		return buffer[debut];
	}

	/**
	 * @brief Ajoute un élément à la fin du vecteur
	 * @param valeur
	 */
	void push_back(value_type valeur) {
		if (taille >= capacity()) {
			nouvelleCapacite();
		}

		if (taille < capacity()) {
			*(buffer + i_physique(taille)) = valeur;
			++taille;
		}
	}

	/**
	 * @brief Ajoute un élément au début du vecteur
	 * @param valeur
	 */
	void push_front(value_type valeur) {
		//Si la taille == la capacité du buffer (buffer.size())
		//alors il faut augmenter la capacité
		if (taille >= capacity()) {
			nouvelleCapacite();
		}

		if (taille < capacity()) {
			debut = i_physique(capacity() - 1);
			front() = valeur;
			++taille;
		}
	}

	/**
	 * @brief Supprime le dernier élément du vecteur
	 */
	void pop_back() {
		if (taille) {
			--taille;
		}
	}

	/**
	 * @brief Supprime le premier élément du vecteur
	 */
	void pop_front() {
		if (taille) {
			debut = i_physique(1);
			--taille;
		}
	}
};

#endif /* ArrayDeque_hpp */
