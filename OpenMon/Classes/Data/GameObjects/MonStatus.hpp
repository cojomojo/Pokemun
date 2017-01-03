#pragma once

#include <map>
#include <string>

namespace OpenMonObjects 
{
    class MonStatus 
    {
    public:
        enum class StatusConditions 
        { 
            NONE,
            PARALYZED,
            POISONED,
            BADLY_POISONED,
            BURNED,
            FROZEN,
            FLINCH,
            CONFUSED,
            INFATUATED,
            FAINTED,
            CUSTOM
        };

        MonStatus();

        // Getters/Setters
        int id() const { return id_; }
        std::string name() const { return status_condition_strings.at(condition_); }
        void reset() { condition_ = StatusConditions::NONE; }
        void paralyzed() { condition_ = StatusConditions::PARALYZED; }
        void poisoned() { condition_ = StatusConditions::POISONED; }
        void badly_poisoned() { condition_ = StatusConditions::BADLY_POISONED; }
        void burned() { condition_ = StatusConditions::BURNED; }
        void frozen() { condition_ = StatusConditions::FROZEN; }
        void flinch() { condition_ = StatusConditions::FLINCH; }
        void confused() { condition_ = StatusConditions::CONFUSED; }
        void infatuated() { condition_ = StatusConditions::INFATUATED; }
        void fainted() { condition_ = StatusConditions::FAINTED; }
        void custom() { condition_ = StatusConditions::CUSTOM; }

        // Other methods
        bool IsPersistent();
        bool IsParalyzed();
        bool IsPoisoned();
        bool IsBadlyPoisoned();
        bool IsBurned();
        bool IsFrozen();
        bool IsFlinch();
        bool IsConfused();
        bool IsInfatuated();
        bool IsFainted();
        bool IsCustom();
    private:
        int id_; // id_ is used only when the status condition is "custom"
        StatusConditions condition_; // the condition represented by this MonStatus
        
        static std::map<MonStatus::StatusConditions, std::string> const status_condition_strings;
        static std::map<MonStatus::StatusConditions, bool> const status_condition_volatility; 
    };
}