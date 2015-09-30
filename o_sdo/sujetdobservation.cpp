#include "sujetdobservation.h"
#include "observateur.h"

void SujetDObservation::attacher(Observateur * obs)
{
    mesObservateurs.insert(obs);
}

void SujetDObservation::detacher(Observateur * obs)
{
    mesObservateurs.erase(obs);
}

void SujetDObservation::notifierChangement()
{
    for (Observateur * e : mesObservateurs)
    {
        e->rafraichir(this);
    }
}
