#pragma once

namespace OpenMonObjects 
{
    class StatusCondition 
    {
    public:
        StatusCondition();

        int id() const { return id_; }
        std::string condition_name() const { return condition_name_; }
        bool is_persistent() const { return persistent_; }
    private:
        int id_;
        std::string condition_name_;
        bool persistent_;
    };
}