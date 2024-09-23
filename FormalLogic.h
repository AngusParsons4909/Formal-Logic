/**
 * @file FormalLogic.h
 * @brief Header file for the Formal Logic Library
 *
 * This file contains the declarations of the structs and functions used in the Formal Logic Library.
 * It defines the structure of a logical proposition (TProposition) and enumerates possible logical
 * operators (ELogicOperator). The library provides a range of functions to manipulate and evaluate
 * logical propositions, such as adding propositions to an array, setting truth values, and determining
 * the nature of compound propositions based on their atomic components.
 *
 * The Library should NOT be edited or otherwise changed in any way, and must be utilised as-is by
 * students working on the Logic miniproject.
 *
 * Version 1.01 (13.05.24): Compount compositions now correctly determine and display nature. Updated naming conventions
 * to follow Hungarian notation a la https://learn.microsoft.com/en-us/windows/win32/stg/coding-style-conventions
 */

#pragma once

#include <iostream>
#include <string>

 /**
  * Enumerates the types of logical operators used in compound propositions.
  */
enum ELogicOperator
{
    NONE = 32,
    IMPLIES = 26,
    IFF = 29,
    NOT = 170,
    AND = 38,
    OR = 186,
    XOR = 233
};

/**
 * Struct representing a logical proposition.
 */
struct TProposition
{
    bool m_bTruthValue = true;          // The truth value of the proposition
    bool m_bCompound = false;            // Flag indicating if the proposition is compound and is made up of other propositions
    char m_cVariable = ' ';              // The character that represents this propositional variable. Upper-case for compound, lower-case for atomic.
    char m_cVariableA = ' ';            // The left-hand operand of a compound proposition
    char m_cVariableB = ' ';            // The right-hand operand of a compound proposition
    std::string m_sDescription = "";   // Description of the proposition (for atomic propositions)
    ELogicOperator m_EOpterator = NONE;    // The logical operator connecting A and B (for compound propositions)
};

/**
 * Adds a new proposition to the propositions array.
 * @param _riPropositionCount The current count of propositions.
 * @param _a_Propositions The array of propositions.
 * @return True if the addition was successful, false otherwise.
 */
bool Add_Proposition(int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Adds an atomic proposition to the propositions array.
 * @param _riPropositionCount The current count of propositions.
 * @param _a_Propositions The array of propositions.
 * @return True if the atomic proposition was added successfully, false otherwise.
 */
bool Add_Atomic_Proposition(int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Adds a compound proposition to the propositions array.
 * @param _riPropositionCount The current count of propositions.
 * @param _a_Propositions The array of propositions.
 * @return True if the compound proposition was added successfully, false otherwise.
 */
bool Add_Compound_Proposition(int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Adds a propositional variable to a compound proposition.
 * @param _rcVariable A reference to the character variable to store the propositional variable.
 * @param _strInstructions Instructions or description for the cInput process.
 * @param _riPropositionCount A reference to the current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if the propositional variable was successfully added, false otherwise.
 */
bool Add_Sub_Propositional_Variable_To_Proposition(char& _rcVariable, std::string _strInstructions, int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Converts a string to a corresponding logic operator enum value.
 * @param _strOption The string representation of the logic operator.
 * @return The corresponding ELogicOperator enum value.
 */
ELogicOperator Get_Logic_Operator_From_String(std::string _strOption);

/**
 * Removes a proposition from the propositions array.
 * @param _riPropositionCount A reference to the current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if the proposition was successfully removed, false otherwise.
 */
bool Remove_Proposition(int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Removes a proposition based on its variable identifier.
 * @param _rcVariable The character representing the propositional variable to be removed.
 * @param _riPropositionCount A reference to the current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if the proposition was successfully removed, false otherwise.
 */
bool Remove_Proposition_Variable(const char _rcVariable, int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Removes all propositions marked as invalid from the propositions array.
 * @param _riPropositionCount A reference to the current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if any invalid propositions were removed, false otherwise.
 */
bool Remove_Invalid_Propositions(int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Displays all propositions in the propositions array.
 * @param _riPropositionCount The current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @param _bDisplayAtomicDescr Whether to display descriptions for atomic propositions.
 * @param _bDisplaySubProps Whether to display sub-propositions for compound propositions.
 * @return True if the operation was successful, false otherwise.
 */
bool Display_Propositions(int& _riPropositionCount, TProposition _a_Propositions[], bool _bDisplayAtomicDescr, bool _bDisplaySubProps);

/**
 * Checks if a proposition exists based on its propositional variable.
 * @param _kcPropositionalVariable The variable representing the proposition to check for.
 * @param _riPropositionCount The current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if the proposition exists, false otherwise.
 */
bool Has_Proposition(const char _kcPropositionalVariable, int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Displays a single proposition.
 * @param _rProposition The proposition to display.
 * @param _riPropositionCount The current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @param _bDisplayAtomicDescr Whether to display the description for atomic propositions.
 * @param _bDisplaySubProps Whether to display sub-propositions for compound propositions.
 * @return True if the operation was successful, false otherwise.
 */
bool Display_Proposition(TProposition& _rProposition, int& _riPropositionCount, TProposition _a_Propositions[], bool _bDisplayAtomicDescr, bool _bDisplaySubProps);

/**
 * Validates a user cInput against a list of valid inputs.
 * @param _a_cValidInputs The array of valid cInput characters.
 * @param _iNumValidInputs The number of valid inputs in the array.
 * @return The validated user option as a character.
 */
char Validate_User_Option(char _a_cValidInputs[], int _iNumValidInputs);

/**
 * iterates over TProposition array, returning the index at which the
 * proposition containing the specified character, otherwise returns -1
 * @param _kcPropositionalVariable the specified character to check for.
 * @param _riPropositionCount The current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return The index at which the proposition is contained in the array
 */
int Get_Proposition_Index_By_Variable(char _kcPropositionalVariable, int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Resolves the truth value of a proposition, considering atomic values and compound logic.
 * @param _rProposition The proposition whose truth value is to be resolved.
 * @param _riPropositionCount The current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if the truth value was successfully resolved, false otherwise.
 */
bool Resolve_Proposition_Truth_Value(TProposition& _rProposition, int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Determines the nature (tautology, contradiction, contingency) of a compound proposition.
 * @param _riPropositionCount The current count of propositions in the array.
 * @param _a_Propositions The array of propositions.
 * @return True if the nature of the compound proposition was successfully determined, false otherwise.
 */
bool Determine_Nature_Of_Compound_Proposition(int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Finds the atomic propositions (roots) involved in a compound proposition.
 * This function iterates through the given array of propositions to locate the specified compound proposition
 * and then recursively identifies all atomic propositions involved.
 *
 * @param _rProposition The character representing the compound proposition to analyze.
 * @param _riPropositionCount A reference to the total count of propositions in the array.
 * @param _a_Propositions The array of all propositions.
 * @param _riNumRoots A reference to the number of roots found. This will be updated by the function.
 * @param _a_cRoots An array to store the characters representing the atomic propositions found.
 * @return True if at least one atomic proposition is found, false otherwise.
 */
bool Find_Compound_Proposition_Roots(char _rProposition, int& _riPropositionCount, TProposition _a_Propositions[], int& _riNumRoots, char _a_cRoots[]);

/**
 * Adds an atomic proposition to an array if it is not already present.
 * This function is intended to be used in the process of identifying and storing unique atomic propositions
 * (roots) as part of analyzing compound propositions.
 *
 * @param _rProposition The character representing the atomic proposition to be added.
 * @param _riPropositionCount A reference to the total count of propositions in the array.
 * @param _a_Propositions The array of all propositions.
 * @param _riNumRoots A reference to the number of roots currently stored in the _a_cRoots array.
 * @param _a_cRoots The array where the atomic proposition will be added if not already present.
 * @return True if the proposition was successfully added or already exists in the array, false if the array is full.
 */
bool Add_Atomic_Proposition_To_Array(char _rProposition, int& _riPropositionCount, TProposition _a_Propositions[], int& _riNumRoots, char _a_cRoots[]);

/**
 * Sets the truth value for a specified atomic proposition.
 * This function searches for an atomic proposition in the array and updates its truth value according to
 * the provided parameter. This is particularly useful when preparing to evaluate compound propositions
 * based on the truth values of their atomic components.
 *
 * @param _rProposition The character representing the atomic proposition whose truth value is to be set.
 * @param _bTruthValue The truth value to be assigned to the atomic proposition.
 * @param _riPropositionCount A reference to the total count of propositions in the array.
 * @param _a_Propositions The array of all propositions.
 * @return True if the truth value was successfully set, false if the proposition does not exist in the array.
 */
bool Set_Atomic_Truth_value(char _rProposition, bool _bTruthValue, int& _riPropositionCount, TProposition _a_Propositions[]);

/**
 * Iterates over all possible truth value combinations of atomic propositions involved in a compound
 * proposition to determine the compound proposition's truth value under different scenarios.
 * This function is crucial for evaluating the logical consistency of compound propositions
 * by testing every combination of truth values for the atomic propositions (roots).
 *
 * @param _riCompoundTruthValues A reference to an integer to store the count of true evaluations of the compound proposition.
 * @param _iCompPropIndex The index of the compound proposition in the _a_Propositions array whose truth values are being tested.
 * @param _riPropositionCount A reference to the total number of propositions in the array.
 * @param _a_Propositions The array containing all propositions.
 * @param _riNumRoots A reference to the count of atomic propositions (roots) identified as part of the compound proposition.
 * @param _a_cRoots An array containing the characters representing the atomic propositions.
 * @param _iPropositionIndex The current index in the array of truth value combinations being tested.
 *
 * @return Returns true if the function successfully iterates through all combinations and evaluates the compound proposition,
 *         false if an error occurs during processing.
 *
 */
bool Iterate_Atomic_Truth_Values(int& _riCompoundTruthValues, int _iCompPropIndex, int& _riPropositionCount, TProposition _a_Propositions[], int& _riNumRoots, char _a_cRoots[], int _iPropositionIndex);