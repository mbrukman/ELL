
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     FunctionUtils_test.cpp (utilities)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FunctionUtils_test.h"

// testing
#include "testing.h"

// utilities
#include "FunctionUtils.h"

// stl
#include <type_traits>

namespace ell
{
static int g_Value = 0;
void VoidFunction1()
{
    g_Value = 1;
}

void VoidFunction2()
{
    g_Value = 2;
}

void VoidFunction3()
{
    g_Value = 3;
}

void VoidFunction4()
{
    g_Value = 4;
}

void AddToGlobalValue(int value)
{
    g_Value += value;
}

int ReturnIntFunction()
{
    return 1;
}

bool ManyArgFunction(int a, float b, std::string c)
{
    return a==1 && b==2.5 && c == "hello";
}

void TestInOrderFunctionEvaluator()
{
    utilities::InOrderFunctionEvaluator(VoidFunction1, VoidFunction2, VoidFunction3, VoidFunction4);
    testing::ProcessTest("InOrderFunctionEvaluator", g_Value == 4);
}

void TestApplyToEach()
{
    utilities::ApplyToEach(AddToGlobalValue, 1, 2, 3, 4, 5);
    testing::ProcessTest("ApplyToEach", g_Value = 1 + 2 + 3 + 4 + 5);
}

void TestFunctionTraits()
{    
    testing::ProcessTest("FunctionTraits", std::is_same<utilities::FunctionReturnType<decltype(ReturnIntFunction)>, int>::value);
    testing::ProcessTest("FunctionTraits", std::is_same<std::tuple_element_t<0, utilities::FunctionArgTypes<decltype(AddToGlobalValue)>>, int>::value);
}

void TestApplyFunction()
{
    bool success = utilities::ApplyFunction(ManyArgFunction, 1, 2.5f, std::string("hello"));
    testing::ProcessTest("ApplyFunction", success);
}
}
