#pragma once

#include <string>

namespace OpenMonData 
{
    // forward declare TypedSqlValue
    template<typename T> 
    class TypedSqlValue;

    class SqlValue 
    {
    public:
        SqlValue(const std::string& name)
            : name_(name) { }

        virtual ~SqlValue() { }

        std::string const& GetType() const { return name_; };
		
    	template<typename T>
		T GetValue()
    	{
			TypedSqlValue<T> *tsv = dynamic_cast<TypedSqlValue<T>*>(this);
			return tsv->GetValue();
    	}
    private:
        std::string name_;
    };

    template<typename T> 
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

