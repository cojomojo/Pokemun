#include "Trainer.hpp"
using namespace OpenMonObjects;

Trainer::Trainer(std::string name)
{
    trainer_name_ = name;
    mon_party_.reserve(MAX_PARTY_SIZE);
}

// Returns bool based on the status of the trainer's party of mon.
// If at least 1 mon is not fainted the function will return false
bool Trainer::IsPartyDefeated()
{
    for (auto & mon : mon_party_) {
        if (!mon->fainted()) {
            return false;
        }
    }
    return true;
}
