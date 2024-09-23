/**
 * @file FormalLogic.cpp
 * @brief Implementation file for the Formal Logic Library
 *
 * This file implements the functions declared in FormalLogic.h. It includes the logic necessary to manage
 * logical propositions stored in an array, such as adding new propositions, setting their truth values,
 * and evaluating the nature of compound propositions through recursive exploration of their atomic constituents.
 *
 * Each function is documented with a description of its purpose, parameters, and return value in the "FormalLogic.h"
 * header file.
 *
 * Implementation is focussed on using basic C++ concepts to ensure accessibility to students new to programming
 * concepts. It avoids classes, complex data structures, or memory management.
 *
 * The Library should NOT be edited or otherwise changed in any way, and must be utilised as-is by
 * students working on the Logic miniproject.
 *
 * Version 1.01 (13.05.24): Compount compositions now correctly determine and display nature. Updated naming conventions
 * to follow Hungarian notation a la https://learn.microsoft.com/en-us/windows/win32/stg/coding-style-conventions
 */

#include "FormalLogic.h"

bool Add_Proposition(int& _riPropositionCount, TProposition _a_Propositions[])
{
    const int kiNumOptions = 4;
    char a_cOptions[kiNumOptions] = { 'a', 'A', 'c' , 'C' };
    std::cout << "Enter 'a' to add an atomic Proposition. Enter 'c' to add a compound Proposition. " << std::endl;
    char cStageOption = Validate_User_Option(a_cOptions, kiNumOptions);

    if (cStageOption == 'a' || cStageOption == 'A')
    {
        return Add_Atomic_Proposition(_riPropositionCount, _a_Propositions);
    }
    else
    {
        return Add_Compound_Proposition(_riPropositionCount, _a_Propositions);
    }
    return false;
}

bool Add_Atomic_Proposition(int& _riPropositionCount, TProposition _a_Propositions[])
{
    // Temporary variables to store user inputs
    char cPropositionalVariable = ' ';
    std::string sPropositionalDescriptor = "";

    bool bPropositionDescStageAccepted = false;
    while (!bPropositionDescStageAccepted)
    {
        system("CLS");

        std::cout << "Labelling an atomic Proposition is done through the use of lower-case letter characters. " << std::endl;
        std::cout << "Enter the character for your propositional variable " << (_riPropositionCount + 1) << ": ";

        char a_cAtomicOptions[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
        cPropositionalVariable = Validate_User_Option(a_cAtomicOptions, 26);

        for (int i = 0; i < _riPropositionCount; i++)
        {
            if (_a_Propositions[i].m_cVariable == cPropositionalVariable)
            {
                std::cout << "\nCharacter: ";
                std::cout << "'" << cPropositionalVariable << "', is already in use for Proposition." << std::endl;
                return false;
            }
        }

        std::cin.ignore(); // Clear the newline character from the cInput stream

        std::cout << "Enter the description for '" << cPropositionalVariable << "': ";
        std::getline(std::cin, sPropositionalDescriptor);

        std::cout << "You have cInput: '" + sPropositionalDescriptor + "' as the Proposition for the variable: " + cPropositionalVariable << std::endl;
        std::cout << "If this is correct, enter 'y' to continue, or 'n' to cancel and go back to menu, or 'z' to enter a new string value for your Proposition" << std::endl;

        char a_cOptions[3] = { 'y', 'n', 'z' };
        char cStageOption = Validate_User_Option(a_cOptions, 3);

        switch (cStageOption)
        {
        case 'y':
        {
            bPropositionDescStageAccepted = true;
        } break;
        case 'n':
        {
            return false;
        } break;
        case 'z':
        {

        } break;
        default:
        {
            std::cout << "Error, should not reach this level in Add_Atomic_Proposition";
            return false;
        } break;
        }
    }

    // Store the cInput in the arrays
    TProposition Proposition;
    Proposition.m_bCompound = false;
    Proposition.m_cVariable = cPropositionalVariable;
    Proposition.m_sDescription = sPropositionalDescriptor;
    _a_Propositions[_riPropositionCount] = Proposition;

    // Increment the count of propositions
    _riPropositionCount++;

    return true;
}

bool Add_Compound_Proposition(int& _riPropositionCount, TProposition _a_Propositions[])
{
    // Temporary variables to store user selections
    ELogicOperator ELogicOperator_option = ELogicOperator::NONE;
    char cPropositionalVariable = ' ';
    char cPropositionalVariableA = ' ';
    char cPropositionalVariableB = ' ';

    bool bPropositionDescStageAccepted = false;
    while (!bPropositionDescStageAccepted)
    {
        system("CLS");

        std::cout << "Labelling a compound Proposition is done through the use of upper-case letter characters. " << std::endl;
        std::cout << "Enter the character for your propositional variable " << (_riPropositionCount + 1) << ": ";

        char a_cOptions[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
        cPropositionalVariable = Validate_User_Option(a_cOptions, 26);

        for (int i = 0; i < _riPropositionCount; i++)
        {
            if (_a_Propositions[i].m_cVariable == cPropositionalVariable)
            {
                std::cout << "\nCharacter: ";
                std::cout << "'" << cPropositionalVariable << "', is already in use for Proposition." << std::endl;
                return false;
            }
        }

        while (ELogicOperator_option == ELogicOperator::NONE)
        {
            system("CLS");

            std::cout << "For implication/if-then, enter: 'IMPLIES'" << std::endl;
            std::cout << "For material equivalence, enter: 'IFF'" << std::endl;
            std::cout << "For negation, enter: 'NOT'" << std::endl;
            std::cout << "For conjunction (and), enter: AND" << std::endl;
            std::cout << "For disjunction (inclusive-or), enter: OR" << std::endl;
            std::cout << "For exclusive disjunction (exclusive-or), enter: XOR" << std::endl;

            std::cout << "\nEnter a string to select for the operation for the Proposition '" << cPropositionalVariable << "': " << std::endl;

            std::cin.ignore(); // Clear the newline character from the cInput stream
            std::string sOption = "";
            std::getline(std::cin, sOption);

            ELogicOperator_option = Get_Logic_Operator_From_String(sOption);

            if (ELogicOperator_option == ELogicOperator::NONE)
            {
                std::cout << "Sorry, but the cInput of " << sOption << ", was not valid. Enter any key to continue and try again." << std::endl;
            }
            else
            {
                std::cout << "You have selected: '" + sOption + "' as the operator for the variable: " + cPropositionalVariable << std::endl;
                std::cout << "If this is correct, enter 'y' to continue to next selection, or 'n' to cancel and go back to menu, or 'z' to go back to start of process for adding a new compound Proposition." << std::endl;

                const int kiNumOptions = 3;
                char a_cOptions[kiNumOptions] = { 'y', 'n', 'z' };
                char cStageOption = Validate_User_Option(a_cOptions, kiNumOptions);

                if (cStageOption == 'n')
                {
                    return false;
                }
                if (cStageOption == 'z')
                {
                    ELogicOperator_option = ELogicOperator::NONE;
                }
            }
        }

        bool bPropositionalVariableAdded_A = false;
        if (ELogicOperator_option != ELogicOperator::NOT)
        {
            while (!bPropositionalVariableAdded_A)
            {
                // Select variable for left-field
                if (Add_Sub_Propositional_Variable_To_Proposition(cPropositionalVariableA, "PLease enter a character for selection of the left-field of the compound Proposition.", _riPropositionCount, _a_Propositions))
                {
                    std::cout << "Propositional variable for left-field has been successfully added for variable: " << cPropositionalVariableA << std::endl;
                    bPropositionalVariableAdded_A = true;
                }
                else
                {
                    std::cout << "Propositional variable for left-field has NOT been successfully added for variable: " << cPropositionalVariableA << std::endl;
                    std::cout << "Enter 'y' to continue to attempt to add a new propositional variable for the left-field, or 'n' to cancel and go back to main menu." << std::endl;
                    const int kiNumOptions = 2;
                    char a_cOptions[kiNumOptions] = { 'y', 'n' };
                    char cStageOption = Validate_User_Option(a_cOptions, kiNumOptions);
                    if (cStageOption == 'n')
                    {
                        return false;
                    }
                }
            }
        }

        // Select variable for right-field
        bool bPropositionalVariableAdded_B = false;
        while (!bPropositionalVariableAdded_B)
        {
            // Select variable for left-field
            if (Add_Sub_Propositional_Variable_To_Proposition(cPropositionalVariableB, "PLease enter a character for selection of the right-field of the compound Proposition.", _riPropositionCount, _a_Propositions))
            {
                std::cout << "Propositional variable for right-field has been successfully added for variable: " << cPropositionalVariableB << std::endl;
                bPropositionalVariableAdded_B = true;
            }
            else
            {
                std::cout << "Propositional variable for right-field has NOT been successfully added for variable: " << cPropositionalVariableB << std::endl;
                std::cout << "Enter 'y' to continue to attempt to add a new propositional variable for the right-field, or 'n' to cancel and go back to main menu." << std::endl;
                const int kiNumOptions = 2;
                char a_cOptions[kiNumOptions] = { 'y', 'n' };
                char cStageOption = Validate_User_Option(a_cOptions, kiNumOptions);
                if (cStageOption == 'n')
                {
                    return false;
                }
            }
        }

        // print out full values for new compound variable
        std::cout << "Compound Proposition being added: " << cPropositionalVariableA << " " << char(ELogicOperator_option) << " " << cPropositionalVariableB << std::endl;
        std::cout << "If this is correct, enter 'y' to continue to next selection, or 'n' to cancel and go back to menu, or 'z' to go back to start of process for adding a new compound Proposition." << std::endl;

        char stage_options[3] = { 'y', 'n', 'z' };
        char cStageOption = Validate_User_Option(stage_options, 3);

        switch (cStageOption)
        {
        case 'y':
        {
            bPropositionDescStageAccepted = true;
        } break;
        case 'n':
        {
            return false;
        } break;
        case 'z':
        {

        } break;
        default:
        {
            std::cout << "Error, should not reach this level in Add_Compound_Proposition";
            return false;
        } break;
        }
    }

    // Store the cInput in the arrays
    TProposition Proposition;
    Proposition.m_bCompound = true;
    Proposition.m_cVariable = cPropositionalVariable;
    Proposition.m_cVariableA = cPropositionalVariableA;
    Proposition.m_cVariableB = cPropositionalVariableB;
    Proposition.m_EOpterator = ELogicOperator_option;
    _a_Propositions[_riPropositionCount] = Proposition;

    // Increment the count of propositions
    _riPropositionCount++;

    return true;
}

bool Add_Sub_Propositional_Variable_To_Proposition(char& _rcVariable, std::string _strInstructions, int& _riPropositionCount, TProposition _a_Propositions[])
{
    bool bVariableSelected = false;
    while (!bVariableSelected)
    {
        system("CLS");

        std::cout << _strInstructions << std::endl;

        const int kiNumOptions = 52;
        char a_cOptions[kiNumOptions] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        ,'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
        char cPropositionalVariable = Validate_User_Option(a_cOptions, kiNumOptions);

        if (Has_Proposition(cPropositionalVariable, _riPropositionCount, _a_Propositions))
        {
            _rcVariable = cPropositionalVariable;
            std::cout << "Propositional variable for operation has been selected as: " << _rcVariable << std::endl;

            std::cout << "If this is correct, enter 'y' to continue to next selection, or 'n' to cancel and go back to menu, or 'z' to go back to start of process for adding a new compound Proposition." << std::endl;

            const int kiNumOptions = 3;
            char a_cOptions[kiNumOptions] = { 'y', 'n', 'z' };
            char cStageOption = Validate_User_Option(a_cOptions, kiNumOptions);

            bVariableSelected = true;

            if (cStageOption == 'n')
            {
                return false;
            }
            if (cStageOption == 'z')
            {
                bVariableSelected = false;
            }
        }
        else
        {
            std::cout << "Selected propositional variable " << cPropositionalVariable << " side of operation is invalid or no such Proposition exists... " << std::endl;
            std::cout << "Enter 'r' to retry selection, or 'n' to cancel and go back." << std::endl;
            const int kiNumOptions = 2;
            char a_cOptions[kiNumOptions] = { 'r', 'n' };
            char cStageOption = Validate_User_Option(a_cOptions, kiNumOptions);
            if (cStageOption == 'n')
            {
                return false;
            }
        }
    }
    return true;
}

ELogicOperator Get_Logic_Operator_From_String(std::string _strOption)
{
    if (_strOption == "IMPLIES")
    {
        return ELogicOperator::IMPLIES;
    }
    if (_strOption == "IFF")
    {
        return ELogicOperator::IFF;
    }
    if (_strOption == "NOT")
    {
        return ELogicOperator::NOT;
    }
    if (_strOption == "AND")
    {
        return ELogicOperator::AND;
    }
    if (_strOption == "OR")
    {
        return ELogicOperator::OR;
    }
    if (_strOption == "XOR")
    {
        return ELogicOperator::XOR;
    }

    return ELogicOperator::NONE;
}

bool Remove_Proposition(int& _riPropositionCount, TProposition _a_Propositions[])
{
    bool bRemovingPropositions = true;
    while (bRemovingPropositions)
    {
        const int kiNumOptions = 52;
        char a_cOptions[kiNumOptions] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        ,'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
        char cPropositionToRemove = Validate_User_Option(a_cOptions, kiNumOptions);

        if (Remove_Proposition_Variable(cPropositionToRemove, _riPropositionCount, _a_Propositions))
        {
            std::cout << "Proposition: " << cPropositionToRemove << " successfully removed." << std::endl;
        }
        else
        {
            std::cout << "Proposition: " << cPropositionToRemove << " NOT removed." << std::endl;
        }
        std::cout << "Would you like to remove additional propositions? Enter 'y' to continue removing propositions, 'n' to finish removal process" << std::endl;

        const int kiNumAbortOptions = 4;
        char a_cAbortOptions[kiNumAbortOptions] = { 'y', 'Y', 'n', 'N' };
        char cUserOption = Validate_User_Option(a_cAbortOptions, kiNumAbortOptions);

        if ((cUserOption == 'n') || (cUserOption == 'N'))
        {
            bRemovingPropositions = false;
        }
    }
    return true;
}

bool Remove_Proposition_Variable(const char _rcVariable, int& _riPropositionCount, TProposition _a_Propositions[])
{
    bool bCharFound = false;
    for (int i = (_riPropositionCount - 1); i >= 0; --i)
    {
        if (_a_Propositions[i].m_cVariable == _rcVariable)
        {
            bCharFound = true;
            for (int n = i; n < _riPropositionCount; n++)
            {
                if ((n + 1) < _riPropositionCount)
                {
                    _a_Propositions[n] = _a_Propositions[n + 1];
                }
            }
            _riPropositionCount--;
        }
    }

    if (bCharFound)
    {
        while (Remove_Invalid_Propositions(_riPropositionCount, _a_Propositions))
        {
            std::cout << "Cleaned up removed/invalid Proposition..." << std::endl;
        }
        return true;
    }
    return false;
}

bool Remove_Invalid_Propositions(int& _riPropositionCount, TProposition _a_Propositions[])
{
    bool bPropositionRemoved = false;
    for (int i = (_riPropositionCount - 1); i >= 0; --i)
    {
        if (_a_Propositions[i].m_bCompound)
        {
            if ((!Has_Proposition(_a_Propositions[i].m_cVariableA, _riPropositionCount, _a_Propositions) && (_a_Propositions[i].m_EOpterator != ELogicOperator::NOT))
                || (!Has_Proposition(_a_Propositions[i].m_cVariableB, _riPropositionCount, _a_Propositions)))
            {
                for (int n = i; n < _riPropositionCount; n++)
                {
                    if ((n + 1) < _riPropositionCount)
                    {
                        _a_Propositions[n] = _a_Propositions[n + 1];
                    }
                }
                _riPropositionCount--;
                bPropositionRemoved = true;
            }
        }
    }
    return bPropositionRemoved;
}

bool Display_Propositions(int& _riPropositionCount, TProposition _a_Propositions[], bool _bDisplayAtomicDescr, bool _bDisplaySubProps)
{
    // Output the propositions
    system("CLS");
    std::cout << "Stored propositions : " << std::endl;
    for (int i = 0; i < _riPropositionCount; i++)
    {
        std::cout << "\n" << _a_Propositions[i].m_cVariable << ": ";
        if (!Display_Proposition(_a_Propositions[i], _riPropositionCount, _a_Propositions, _bDisplayAtomicDescr, _bDisplaySubProps))
        {
            return false;
        }
    }
    return true;
}

bool Has_Proposition(const char _kcPropositionalVariable, int& _riPropositionCount, TProposition _a_Propositions[])
{
    for (int i = 0; i < _riPropositionCount; i++)
    {
        if (_a_Propositions[i].m_cVariable == _kcPropositionalVariable)
        {
            return true;
        }
    }
    return false;
}

bool Display_Proposition(TProposition& _rProposition, int& _riPropositionCount, TProposition _a_Propositions[], bool _bDisplayAtomicDescr, bool _bDisplaySubProps)
{
    if (_rProposition.m_bCompound)
    {
        std::cout << "(";
        // find and display A
        if (_bDisplaySubProps)
        {
            if (Has_Proposition(_rProposition.m_cVariableA, _riPropositionCount, _a_Propositions))
            {
                for (int i = 0; i < _riPropositionCount; i++)
                {
                    if (_a_Propositions[i].m_cVariable == _rProposition.m_cVariableA)
                    {
                        Display_Proposition(_a_Propositions[i], _riPropositionCount, _a_Propositions, _bDisplayAtomicDescr, _bDisplaySubProps);
                    }
                }
            }
            else
            {
                if (_rProposition.m_EOpterator != ELogicOperator::NOT)
                {
                    std::cout << "\nWARNING: Compound Proposition invalid, left side variable 'A' not found, aborting Display_Proposition." << std::endl;
                    return false;
                }
            }
        }
        else
        {
            std::cout << _rProposition.m_cVariableA;
        }

        // display operator
        std::cout << " " << char(_rProposition.m_EOpterator) << " ";

        // find and display B
        if (_bDisplaySubProps)
        {
            if (Has_Proposition(_rProposition.m_cVariableB, _riPropositionCount, _a_Propositions))
            {
                for (int i = 0; i < _riPropositionCount; i++)
                {
                    if (_a_Propositions[i].m_cVariable == _rProposition.m_cVariableB)
                    {
                        Display_Proposition(_a_Propositions[i], _riPropositionCount, _a_Propositions, _bDisplayAtomicDescr, _bDisplaySubProps);
                    }
                }
            }
            else
            {
                std::cout << "\nWARNING: Compound Proposition invalid, left side variable 'A' not found, aborting Display_Proposition." << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << _rProposition.m_cVariableB;
        }

        std::cout << ")";
        return true;
    }
    else
    {
        if (_bDisplayAtomicDescr)
        {
            std::cout << char(34) << _rProposition.m_sDescription << char(34);
        }
        else
        {
            //std::cout << "'" << _rProposition.m_cVariable << "'";
            std::cout << _rProposition.m_cVariable;
        }
        return true;
    }
    return false;
}

char Validate_User_Option(char _a_cValidInputs[], int _iNumValidInputs)
{
    char cInput = ' ';
    bool bInputValid = false;
    while (!bInputValid)
    {
        std::cout << "\nInput one of the valid options:" << std::endl;
        for (int i = 0; i < _iNumValidInputs; i++)
        {
            std::cout << " '" << _a_cValidInputs[i] << "'";
        }
        std::cout << "\nSelection: ";
        std::cin >> cInput;

        for (int i = 0; i < _iNumValidInputs; i++)
        {
            if (cInput == _a_cValidInputs[i])
            {
                bInputValid = true;
                break;
            }
        }
    }
    return cInput;
}

int Get_Proposition_Index_By_Variable(char _kcPropositionalVariable, int& _riPropositionCount, TProposition _a_Propositions[])
{
    for (int i = 0; i < _riPropositionCount; i++)
    {
        if (_a_Propositions[i].m_cVariable == _kcPropositionalVariable)
        {
            return i;
        }
    }
    return -1;
}

bool Resolve_Proposition_Truth_Value(TProposition& _rProposition, int& _riPropositionCount, TProposition _a_Propositions[])
{
    bool bTruthValue = false;
    if (_rProposition.m_bCompound)
    {
        bool bLeftField = false;
        bool bRightField = false;

        if (Has_Proposition(_rProposition.m_cVariableA, _riPropositionCount, _a_Propositions))
        {
            int iIndex = Get_Proposition_Index_By_Variable(_rProposition.m_cVariableA, _riPropositionCount, _a_Propositions);
            if (iIndex >= 0)
            {
                bLeftField = Resolve_Proposition_Truth_Value(_a_Propositions[iIndex], _riPropositionCount, _a_Propositions);
            }
        }

        if (Has_Proposition(_rProposition.m_cVariableB, _riPropositionCount, _a_Propositions))
        {
            int iIndex = Get_Proposition_Index_By_Variable(_rProposition.m_cVariableB, _riPropositionCount, _a_Propositions);
            if (iIndex >= 0)
            {
                bRightField = Resolve_Proposition_Truth_Value(_a_Propositions[iIndex], _riPropositionCount, _a_Propositions);
            }
        }

        switch (_rProposition.m_EOpterator)
        {
        case ELogicOperator::NONE:
        {
            bTruthValue = false;
        } break;
        case ELogicOperator::IMPLIES:
        {
            bTruthValue = (!bLeftField || bRightField);
        } break;
        case ELogicOperator::IFF:
        {
            bTruthValue = (bLeftField == bRightField);
        } break;
        case ELogicOperator::NOT:
        {
            bTruthValue = !bRightField;
        } break;
        case ELogicOperator::AND:
        {
            bTruthValue = (bRightField && bLeftField);
        } break;
        case ELogicOperator::OR:
        {
            bTruthValue = (bRightField || bLeftField);
        } break;
        case ELogicOperator::XOR:
        {
            bTruthValue = (bLeftField != bRightField);
        } break;
        default:
        {
            bTruthValue = false;
        } break;
        }
        _rProposition.m_bTruthValue = bTruthValue;
    }
    else
    {
        bTruthValue = _rProposition.m_bTruthValue;
    }
    return bTruthValue;
}

bool Determine_Nature_Of_Compound_Proposition(int& _riPropositionCount, TProposition _a_Propositions[])
{
    system("CLS");

    std::cout << "Enter compound variable character to determine the truth value based on current state of atomic propositions: " << std::endl;

    const int kiNumOptions = 26;
    char a_cOptions[kiNumOptions] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char cPropositionalVariable = Validate_User_Option(a_cOptions, kiNumOptions);

    if (Has_Proposition(cPropositionalVariable, _riPropositionCount, _a_Propositions))
    {
        int iNumRoots = 0;
        char a_cRoots[26];
        int iCompoundVarIndex = Get_Proposition_Index_By_Variable(cPropositionalVariable, _riPropositionCount, _a_Propositions);

        bool bHasRoots = Find_Compound_Proposition_Roots(cPropositionalVariable, _riPropositionCount, _a_Propositions, iNumRoots, a_cRoots);

        if (!bHasRoots)
        {
            std::cout << "Warning! Error encountered, compound Proposition does not have any valid atomic sub-propositions..." << std::endl;
            return false;
        }

        int iTotalCombinations = pow(2, iNumRoots); // binary, because truth value of a Proposition is T/F. So number of possible worlds is 2 to the power of the number of roots. (ie. atomic props a, b, and c will result in 8 possible combinations)
        int iCompPropResultTruthValues = 0;

        // reset atomic prop states to false
        for (int i = 0; i < iNumRoots; i++)
        {
            char cPropositionalVariable = a_cRoots[i];
            Set_Atomic_Truth_value(cPropositionalVariable, 0, _riPropositionCount, _a_Propositions);
        }

        // recursively determine nature of WWF by iterating roots truth values
        int iPropositionIndex = 0;
        Iterate_Atomic_Truth_Values(iCompPropResultTruthValues, iCompoundVarIndex, _riPropositionCount, _a_Propositions, iNumRoots, a_cRoots, iPropositionIndex);

        if (iTotalCombinations == iCompPropResultTruthValues)
        {
            // tautology
            std::cout << "\n" << cPropositionalVariable << ": resolves to being tautological.";
        }
        else if (iCompPropResultTruthValues == 0)
        {
            // inconsistent or contradictory
            std::cout << "\n" << cPropositionalVariable << ": resolves to being inconsistent or contradictory.";
        }
        else
        {
            // contingent / consistent in at least 1 
            std::cout << "\n" << cPropositionalVariable << ": resolves to being contingent or consistent in at least 1 case.";
        }
        return true;
    }
    return false;
}

bool Find_Compound_Proposition_Roots(char _rProposition, int& _riPropositionCount, TProposition _a_Propositions[], int& _riNumRoots, char _a_cRoots[])
{
    bool bFoundProposition = false;
    int iRootsFound = 0;

    // Find the compound Proposition in the array
    for (int i = 0; i < _riPropositionCount; ++i)
    {
        if (_a_Propositions[i].m_cVariable == _rProposition)
        {
            bFoundProposition = true;

            // Check if this Proposition is compound
            if (_a_Propositions[i].m_bCompound)
            {
                // If the left variable is atomic, add it to roots

                int iLeftIndex = Get_Proposition_Index_By_Variable(_a_Propositions[i].m_cVariableA, _riPropositionCount, _a_Propositions);
                if (iLeftIndex >= 0)
                {
                    if (_a_Propositions[iLeftIndex].m_bCompound)
                    {
                        // If it's a compound Proposition, recursively find its roots...
                        iRootsFound += Find_Compound_Proposition_Roots(_a_Propositions[i].m_cVariableA, _riPropositionCount, _a_Propositions, _riNumRoots, _a_cRoots);
                    }
                    else
                    {
                        Add_Atomic_Proposition_To_Array(_a_Propositions[i].m_cVariableA, _riPropositionCount, _a_Propositions, _riNumRoots, _a_cRoots);
                        iRootsFound++;
                    }
                }

                // Do the same for the right variable
                int iRightIndex = Get_Proposition_Index_By_Variable(_a_Propositions[i].m_cVariableB, _riPropositionCount, _a_Propositions);
                if (iRightIndex >= 0)
                {
                    if (_a_Propositions[iRightIndex].m_bCompound)
                    {
                        // If it's a compound Proposition, recursively find its roots...
                        iRootsFound += Find_Compound_Proposition_Roots(_a_Propositions[i].m_cVariableB, _riPropositionCount, _a_Propositions, _riNumRoots, _a_cRoots);
                    }
                    else
                    {
                        Add_Atomic_Proposition_To_Array(_a_Propositions[i].m_cVariableB, _riPropositionCount, _a_Propositions, _riNumRoots, _a_cRoots);
                        iRootsFound++;
                    }
                }
            }
            else
            {
                // If the Proposition is not compound, it's an atomic root itself
                Add_Atomic_Proposition_To_Array(_a_Propositions[i].m_cVariable, _riPropositionCount, _a_Propositions, _riNumRoots, _a_cRoots);
                iRootsFound++;
            }
            break; // Break the loop after finding and processing the compound Proposition
        }
    }

    return bFoundProposition && iRootsFound > 0; // Return true if the Proposition was found and roots were added
}

bool Add_Atomic_Proposition_To_Array(char _rProposition, int& _riPropositionCount, TProposition _a_Propositions[], int& _riNumRoots, char _a_cRoots[])
{
    bool bCharExistsInArray = false;
    for (int i = 0; i < _riNumRoots; i++)
    {
        if (_a_cRoots[i] == _rProposition)
        {
            bCharExistsInArray = true;
            break;
        }
    }

    if (!bCharExistsInArray)
    {
        _a_cRoots[_riNumRoots] = _rProposition;
        _riNumRoots++;
        return true;
    }

    return false;
}

bool Set_Atomic_Truth_value(char _rProposition, bool _bTruthValue, int& _riPropositionCount, TProposition _a_Propositions[])
{
    for (int i = 0; i < _riPropositionCount; i++)
    {
        if (_a_Propositions[i].m_cVariable == _rProposition)
        {
            _a_Propositions[i].m_bTruthValue = _bTruthValue;
            return true;
        }
    }
    return false;
}

bool Iterate_Atomic_Truth_Values(int& _riCompoundTruthValues, int _iCompPropIndex, int& _riPropositionCount, TProposition _a_Propositions[], int& _riNumRoots, char _a_cRoots[], int _iPropositionIndex)
{
    // recursively determine nature of WWF by iterating roots truth values
    for (int bTruthValue = 0; bTruthValue <= 1; bTruthValue++)
    {
        char cPropositionalVariable = _a_cRoots[_iPropositionIndex];
        Set_Atomic_Truth_value(cPropositionalVariable, bTruthValue, _riPropositionCount, _a_Propositions);

        if (_iPropositionIndex < _riNumRoots)
        {
            int iNextIndex = _iPropositionIndex + 1;
            Iterate_Atomic_Truth_Values(_riCompoundTruthValues, _iCompPropIndex, _riPropositionCount, _a_Propositions, _riNumRoots, _a_cRoots, iNextIndex);
        }

        // if last in chain, determine truth value of WFF
        if (_iPropositionIndex == _riNumRoots - 1)
        {
            _riCompoundTruthValues += Resolve_Proposition_Truth_Value(_a_Propositions[_iCompPropIndex], _riPropositionCount, _a_Propositions);
        }
    }
    return false;
}