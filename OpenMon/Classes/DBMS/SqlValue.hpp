#pragma once

#include <string>

#define SqlValueToType(type, obj) (static_pointer_cast<OpenMonData::TypedSqlValue<type>>(obj))

namespace OpenMonData 
{
    class SqlValue 
    {
    public:
        SqlValue(const std::string& name)
            : name_(name) { }

        virtual ~SqlValue() { }

        std::string const& GetType() const { return name_; };
    private:
        std::string name_;
    };

    template< typename T > 
    class TypedSqlValue : public SqlValue
    {
    public:
        TypedSqlValue(const std::string& name, const T& data)
            : SqlValue(name), data_(data) { };

        T const& GetValue() const { return data_; };
    private:
        T data_;
    };
}