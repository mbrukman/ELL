////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     InputPort.h (model)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Port.h"
#include "OutputPort.h"
#include "OutputPortElements.h"

// utilities
#include "Exception.h"

// stl
#include <vector>
#include <cassert>

/// <summary> model namespace </summary>
namespace model
{
    class Node;

    /// <summary> Class representing an input to a node </summary>
    class InputPortBase : public Port
    {
    public:
        /// <summary> Constructor </summary>
        ///
        /// <param name="owningNode"> The node that contains this port </param>
        /// <param name="inputRef"> The input group to fetch input values from </param>
        /// <param name="name"> The name of this port </param>
        /// <param name="dimension"> The dimension of the port </param>
        template <typename ValueType>
        InputPortBase(const class Node* owningNode, const OutputPortElements<ValueType>& inputRef, std::string name, size_t dimension);

        /// <summary> Returns an OutputPortElement containing the referenced location to get the value for a specific input element from </summary>
        ///
        /// <param name="index"> The index of the element </param>
        /// <returns> The OutputPortElement containing the referenced location to get the value from </returns>
        const OutputPortElement& GetOutputPortElement(size_t index) const { return _individualElements[index]; }

        /// <summary> Returns the list of nodes this input port gets values from </summary>
        ///
        /// <returns> The list nodes this input port gets values from </returns>
        const std::vector<const Node*>& GetParentNodes() const { return _parentNodes; }

        /// <summary> Returns the list of port ranges this input port gets values from </summary>
        ///
        /// <returns> The list nodes this input port gets values from </returns>
        const OutputPortElementsUntyped& GetInputRanges() const { return _inputRanges; }

        /// <summary> The dimensionality of the output </summary>
        ///
        /// <returns> The dimensionality of the output </returns>
        size_t Size() const { return _individualElements.size(); }

        /// <summary> Returns the (already-computed) output value corresponding to this input </summary>
        ///
        /// <returns> The (already-computed) output value corresponding to this input </returns>
        template <typename ValueType>
        std::vector<ValueType> GetTypedValue() const;

        /// <summary> Returns an element from the (already-computed) output value corresponding to this input </summary>
        ///
        /// <param name="index"> The index of the element to return </param>
        /// <returns> The output value at the corresponding index </returns>
        template <typename ValueType>
        ValueType GetTypedValue(size_t index) const;

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return "InputPortBase"; }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

    protected:
        /// Subclasses _must_ call this method in their constructor
        void ComputeParentsAndElements();

    private:
        const OutputPortElementsUntyped& _inputRanges; // Just a reference to the typed elements in concrete subclass

        std::vector<OutputPortElement> _individualElements; // individual elements
        std::vector<const Node*> _parentNodes;
    };

    template <typename ValueType>
    class InputPort : public InputPortBase
    {
    public:
        /// <summary> Creates an input port </summary>
        ///
        /// <param name="owningNode"> The node this port belongs to </param>
        /// <param name="input"> A reference to the output port(s) this input port is consuming from </param>
        InputPort(const class Node* owningNode, const OutputPortElements<ValueType>& input, std::string name);

        /// <summary> Returns the (already-computed) output value corresponding to this input </summary>
        ///
        /// <returns> The (already-computed) output value corresponding to this input </returns>
        std::vector<ValueType> GetValue() const { return GetTypedValue<ValueType>(); }

        /// <summary> Returns an element from the (already-computed) output value corresponding to this input </summary>
        ///
        /// <param name="index"> The index of the element to return </param>
        /// <returns> The output value at the corresponding index </returns>
        ValueType GetValue(size_t index) const;

        /// <summary> Returns the OutputPortElements containing the referenced locations this port gets its values from </summary>
        ///
        /// <returns> The OutputPortElements containing the referenced locations to get values from </returns>
        OutputPortElements<ValueType> GetOutputPortElements() const;
        void SetOutputPortElements(const OutputPortElements<ValueType>& elements);

        /// <summary> Returns an element from the (already-computed) output value corresponding to this input </summary>
        ///
        /// <param name="index"> The index of the element to return </param>
        /// <returns> The output value at the corresponding index </returns>
        ValueType operator[](size_t index) const;

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("InputPort"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Writes to a Serializer. </summary>
        ///
        /// <param name="serializer"> The serializer. </param>
        virtual void Serialize(utilities::Serializer& serializer) const override;

        /// <summary> Reads from a Deserializer. </summary>
        ///
        /// <param name="deserializer"> The deserializer. </param>
        /// <param name="context"> The serialization context. </param>
        virtual void Deserialize(utilities::Deserializer& serializer, utilities::SerializationContext& context) override;

    private:
        OutputPortElements<ValueType> _input;
    };
}

#include "../tcc/InputPort.tcc"
