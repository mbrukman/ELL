////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     ISerializable.cpp (utilities)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ISerializable.h"
#include "Variant.h"
// stl
#include <string>
#include <iostream>

namespace utilities
{
    //
    // SimpleSerializer
    //
    void SimpleSerializer::SerializeType(std::string typeName)
    {
        std::cout << std::string(2*_indent, ' ');
        std::cout << "type: " << typeName << std::endl;
    }

    void SimpleSerializer::SerializeField(std::string name, const Variant& variant)
    {
        ++_indent;
        std::cout << std::string(2*_indent, ' ');
        if(variant.IsPrimitiveType())
        {            
            std::cout << name << ":\t" << to_string(variant) << std::endl;
        }
        else if(variant.IsSerializable())
        {
            std::cout << name << ":" << std::endl;
            ++_indent;
            Serialize(variant);
            --_indent;
        }
        else
        {
            // punt --- should probably throw an exception
            std::cout << "Cannot serialize field " << name << std::endl;
        }
        --_indent;

    }
}
