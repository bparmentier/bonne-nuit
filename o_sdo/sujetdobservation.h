/*!
 * \file sujetdobservation.h
 * \brief Définition de la classe SujetDObservation.
 */

#ifndef __SUJETDOBSERVATION__H__
#define __SUJETDOBSERVATION__H__

#include <set>

class Observateur;

/*!
 * \brief Classe de base de tout "sujet d'observation"
 *
 * Classe dont dérive toute source d'événement 
 * (ou "sujet d'observation") du modèle de conception 
 * "Observateur / SujetDObservation".
 *
 * \author GOF (?).
 * \sa Observateur.
 */
class SujetDObservation
{
public:

    /*!
     * \brief Destructeur par défaut.
     */
    virtual ~SujetDObservation() = default;

    /*!
     * \brief Méthode permettant à un observateur de s'enregistrer 
     * comme écouteur du sujet d'observation.
     *
     * \param obs un pointeur vers le candidat observateur.
     */
    virtual void attacher(Observateur * obs);

    /*!
     * \brief Méthode permettant à un observateur de se retirer de la
     * liste des écouteurs patentés du sujet d'observation.
     *
     * \param obs l'adresse de l'observateur désintéressé.
     */
    virtual void detacher(Observateur * obs);

protected:

    /*!
     * \brief Constructeur protégé pour éviter l'instanciation.
     */
    SujetDObservation() = default;

    /*!
     * \brief Méthode qui se charge de prévenir les observateurs d'un
     * changement d'état du sujet d'observation, en invoquant leur
     * méthode rafraichir.
     *
     * \sa Observateur::rafraichir(SujetDObservation *).
     */
    virtual void notifierChangement();

protected:

    /*!
     * \brief Le vecteur d'observateurs enregistrés.
     */
    std::set<Observateur *> mesObservateurs;
};

#endif
