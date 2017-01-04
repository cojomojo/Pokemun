#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Mon.hpp"

namespace OpenMonObjects {
    
    class Trainer
    {
    public:
        Trainer(std::string name); //TODO pass in the party of mon in the constructor for the trainer?
        
        // Getters and setters
        std::string const& trainer_name() const { return trainer_name_; }
        
        // Other Methods
        bool IsPartyDefeated();
        
        // TODO swap active mon??
        // TODO heal active mon/use item on active mon??
        // TODO use mon move??
        
    private:
        std::string trainer_name_;
        std::vector<std::unique_ptr<Mon>> mon_party_;
        
        // TODO bag object for the usable items at some point
    };
}
