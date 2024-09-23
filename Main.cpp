#include <iostream>
#include <string>
#include "FormalLogic.h"

/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : Main.cpp
Description : Main function for console window (Starts a menu to allow acess to the FormalLogic.h for propositions)
Author : Angus Parsons
Mail : Angusalanparsons@gmail.com
**/

TProposition PropositionArray[52];
int PropositionCount = 0;
const int NumOptions = 52;
char Options[NumOptions] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char PropositionToChange = 'a';
bool PropositionTruth = false;
int PropositionIndex = 0;
bool Continues = true;
bool* PContinues = &Continues;

//auto selects the proposition instead of prompting user
bool Add_Atomic_Proposition_For_Change(int& _riPropositionCount, TProposition _a_Propositions[],char _index)
{
    // Temporary variables to store user inputs
    char cPropositionalVariable = ' ';
    std::string sPropositionalDescriptor = "";

    bool bPropositionDescStageAccepted = false;
    while (!bPropositionDescStageAccepted)
    {
        system("CLS");
        char a_cAtomicOptions[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
        cPropositionalVariable = _index;

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

//auto selects the proposition instead of prompting user
bool Add_Compound_Proposition_For_Change(int& _riPropositionCount, TProposition _a_Propositions[], char _index)
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


        char a_cOptions[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
        cPropositionalVariable = _index;

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


void Main_Menu()
{
    int MenuOption = 0;
    std::cout << "1.Input Proposition\n2.Modify Proposition\n3.Remove Proposition\n4.Display Propositions\n5.Set Nature of Atomic Proposition\n6.Evaluate Nature of Propositions\n7.Quit\n\nOption: ";
    std::cin >> MenuOption;
    switch (MenuOption)
    {
    case 1: //add proposition
        Add_Proposition(PropositionCount, PropositionArray);
        break;
    case 2://edit proposition
        PropositionToChange = Validate_User_Option(Options, NumOptions);
        PropositionIndex = Get_Proposition_Index_By_Variable(PropositionToChange, PropositionCount, PropositionArray);
        PropositionTruth = PropositionArray[PropositionIndex].m_bCompound;
        Remove_Proposition_Variable(PropositionToChange, PropositionCount, PropositionArray);
        if (PropositionTruth) //compound proposition
        {
            Add_Compound_Proposition_For_Change(PropositionCount, PropositionArray, PropositionToChange);
        }
        else //atomic proposition
        { 
            Add_Atomic_Proposition_For_Change(PropositionCount, PropositionArray, PropositionToChange);
        }
        
        break;
    case 3://remove proposition
        std::cout << "Remove Proposition: " << std::endl;
        Remove_Proposition(PropositionCount, PropositionArray);
        break;
    case 4: //display proposition
        Display_Propositions(PropositionCount, PropositionArray, true, true);
        std::cout << std::endl;
        break;
    case 5://set nature of propositions
        std::cout << "Set Nature of Proposition: " << std::endl;
        PropositionToChange = Validate_User_Option(Options, NumOptions);
        std::cout << "True or false?\nEnter T or F: ";
        char TruthInput;
        std::cin >> TruthInput;
        bool Truth;
        if (TruthInput == 't' or TruthInput == 'T')
        {
            Truth = true;
        }
        else
        {
            Truth = false;
        }

        Set_Atomic_Truth_value(PropositionToChange,Truth,PropositionCount,PropositionArray);
        break;
    case 6: //determine nature of propositions
        Determine_Nature_Of_Compound_Proposition(PropositionCount, PropositionArray);
        std::cout << std::endl;
        break;
    case 7: //exit
        *PContinues = false;
        break;
    default:
        std::cout << "Not a valid input" << std::endl;
        break;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Jeremy()
{
    std::cout << "Please Enter Fullscreen" << std::endl;
    system("pause");
    system("CLS");
    std::cout << " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&#######&&&&&&##&&&&&####&&&&###&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#BBBBB##########&&&&&&&&####&&&&&&&&&&&&&&&#&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&##BBBB#&&&&&@@@@@@&&&&&@@@@&&&&##&&&&&&&&&&&&&&&##&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&###&###&&&&&&&&&&&&@@@@@@@@@@@@@@@@@&####&&&&&&##&&&&&&#####&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@&&#&&&&&&&&&&&&&&&@@@@@@@@@@@@@@@&&&####&&&&&&#########&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&@@@@@@&&&&&&&&&@@@@@@@@@@@&&&&###&##&&&&&#########&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&@@@@@@@&&&&&&&&&@@@@@@@@@@@#&@@&#B####&&&&&&&##&&&#&&@@@@@@@@@@@&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@@@@@@@@@@@@@@&@@@&&&@@@@@@&&@@@&&&&&@@@@@@@@@&#&@@&#BGBB&&&&&&&&&&&&@&&&@@@@@@@@@@@@&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@@@@@@@@@@@@@@&&&&&@@@@@@@&&&&&&&&&&&&&&&&&@&##&&&&#BGBB&&&&&&&@@&&@@@&&&&&&&&@@@@@@@@&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&@@@@@@@&&&&&&&&&@@@@&&&&&##########BB####&&#BB#&#BBGBBB#&&##&&&##&&&&&&##BB#&&&@@@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&@@@@&&&&&&&&&@@@&&&&###BBGGGGGGGGGGPPPPGGBBBBGGGGGPPPGBBBBBBBBGGGBBBBGGGP55Y5B&&@@&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&@@&&&&&@@&&@@@&&&#BBGGPP555YYYYYYJJJJJJJYYY555YYYYJJYYY5555P55YYYYYYYYJJJ?7!7?P#&@@@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&@&&&&@@&&&&&&&##BGPP5YYJJJ??7777!!!!!!777!!77777!!!!!777777??7!!!!!!!!~~~~~~~!7YB&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&@@@@@@&&&&&&#BGGP5YYJJ???77!!!!~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^::::^^^^^^^~~~~~!7JG#&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&&@@@@@&&&&##BGP5YYJJ???77!!!!~~~~~~^^^:::::::::::::::::::::::::::::::::^^^^^~~~~!7JP#&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&&&&@&&&&##BBP5YYJ??77777!!~~~~~~~~~~^^^:::::::::::::::::::::......:::::::^^^^~~~!!7JPB&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&&&&&&&&&##BGG5YJ??77777!!!!~~~~~~~~~~^^^^^::::::::::::::::::::::::::::::::^^^^~~~!!77JP#&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&&&&&##BBGGGP5Y?77777!!!!!!!!!~~~~~~~~~~^^^^^^^:::::::::::::::::::::::::::^^^^^~~~~!!7?5#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&@@@@@&&#BBGPPP5YJ??77777!7!!!!!!!!~~~~~~~~~~~~^^^^^^::::::::::::::::::::::::^^^^^~~~~~!!77YB@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@@@@@&&&&&&&&BG#&@@@@@@@@&#BGPP5YYJJ???777777!!!!!!!!!!!!!~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^~~~~~!!!77YB@@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@@@@&&&&&&&&@&@@@@@@@@@@@&BGP5YYYYJ????77777777!!!!!!!!!!!!!!!~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^~~~~~!!!77YB@@@@@@@@@@@@@@@@@@@@&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@@@@@&&&&&@@@@@@@@@@@@@@@@@#BP5YYJJJJ????7777777777!!!!!!!!!!!!!!!!!~~~~~~~~^^^^~~~~~~~~~~~~~^^^^^~~~~~~!!!77YB@@@@@@@@@@@@@@@@@@@@&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@@@@@@&&&@@@@@@@@@@@@@@@@@@&#GP55YYYJJJJ???777777777!!!!!!!!!!!!!!!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~!!!7Y#@@@@@@@@@@@@@@@@@@@@&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&@@@@@@@&&&@@@@@@@&@@@@@@@@@@@&#GP555YYJJJ??????7777777!!777!!!!!!!!!!!~~~~~~~~~~~~~~~!~~~~~~~^^^^~~~~~~~~~!!7?5#@@@@@@@@@@@@@@@@@@@&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@@@@&&@@@@@@@&&&@@@@@@@@@@@&BGP555YYJ????????77777777!!!!!!!!!!!!!!~~~~~~~~~~~~~~~~~~~~~~^^^^^~~~~~~~~!!!7?5&@@@@@@@@@@@@@@@@@@&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@@@@@@@@@@@@@@&@@@@@@@@@@@@&#GPP55YJJ??????????7777777!!!!!!!!!!!!!~~~~^^^^^^^^~~~~~~^^^^^^^^^~~~~~~~~!!77?5&@@@@@@@@@@@@@@@@@@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#GPP5YYJJ?????????????777!!!!!!!!!!~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^~~~~~~~~!!7?JP&@@@@@@@@@@&&@@@@@&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@&BPP5YJJJJ?????????????77!!!!!!!~~~~~~~~~~~~^^^^^^^~~~^^^^^^^^^^^^^^^^^~~~!!7JYG&@@@@@@@@@@@&&&&&&&@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@@@&&&@@@@@@@@@@@@@@@@@@@@@@@&BP55YJJJJJJJ?JJ??????777!!!!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~~~!!7?JY5G&@@@@@@@@@@@&#BBB&&#BGGB#&&@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@@&&#&&@@@@@@@@@@@@@@@@@@@@@@@@#P5YJJJJJJJJJJJJJ?????77777777!!!!~~~~~~~!!!!!!!!!!!!!!!!!!!~~~~~!!!!77?JY555PB&@@@@@@@@@@@@&####PYPBBPYP&&@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&@@@&BBB#&@@@@@@@@@@@@@@@@@@@@@@@@#P5YJJJJJJJJJJJJJJJJJJJJJJJJJJJ????JJJJJJJJJ???77?777777??JJJJY555P55555555555B@@@@@@@@@@@@@@@@&G?JPGGPY5#&@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&#GJ~^^!B&@@@@@@@@@@@@@@@@@@@@@@@@#P5YJJJJJJJJJJYYYYYYYYYYYYYYY55555PGGBBBBBBBGPP5YYJ??77?YPGBB#####BGPPPPPP5YJYG@@@@@@@@@@@@@@@@&BYYB&&#B#&&@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#GP5Y?~:..^J#@@@@@@@@@@@@@@@@@@@@@@@@@B5YYJJJJJJJJJJYY555PPPPPPPPPPPPPGGGBBB##&&&&#BGP5YJ??77JP#&&&&&&&&&&#BBGP5YJ?JG@@@@@@@@@@@@@@@@&&#PPPGPPB&&@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@J^^^^^^~?5#&&&@@@@@@@@@@@@@@@@@@@@@@@@B5YJJJJJJJJJJJY55PGGBBBBBB#####&&&&&&&&&&&&##BG5YJ?77!7?P#&&###&&&&#BGGPYJ???JG&@@@@@@@@@@@@@@@&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@5~~!!!!?G&@@@@@@@@@@@@@@@@@@@@@@@@@@@@B5YJJJJJJJJJJJYY55PGGGGBBBB####&&&&########BGPPYJ?7!~~~!J5GBBGGPPPP555YJ?777?J5#@@@@@@@@@@@@@@&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#7!777775#&&@@@@@@@@@@@@@@@@@@@@@@@@@@B5YJJJJJJJJJJJJJJJYYY555PPPPGPPPPPPPPPPGBBGP55YYJ7!!~~~~!?JYPPPP55YYJJ?77!!77?YG@@@@@@@@@@@@@&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?!77777JG&&&@@@@@@@@@@@@@@@@@@@@@@@@&B5JJJJJJJJJ??????????JJYYY555555555555YYYYYJJJJJ??7!~~^~!!77777????7777!!!!77?JP&@@@@@@@@@@&&&BB#&&&#BGGGB@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P777????JB&@@@@@@@@@@@@@@@@@@@@@@@@@&GYJJJJJJJJJ??????77777?????JJJJJJJJ??7777?????????7!~^^^~!7!!!~~~~!!!!!!!!777?JP#@@@@@@@@&&&&#?~?#&P7!!7!J@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&????????Y#@@@@@@@@@@@@@@@@@@@@@@@@@&GYJJJJJJJJJJ?????777777777!!!!!!!!!!!!!!!7777?????7!~~^^~~!777!~~~~~~!!!!!77??JP#&@@@@@@&&&&&#?^?##?^!YGG&@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P??????JJ5#@@@@@@@@@@@@@@@@@@@@@@@@&G5JJ?????JJJJ??????777!!!!!!!!!~~~~~~!!!7?JJJJJ???7!!~~^^~!7JYJ?7!!!!!!!!!77??JPBBG&@@@@&&&&&#?~?#&B5?!!J@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&J????JJJJ5#&@@@@@@@@@@@@@@@@@@@@@@&BP5YJ??????JJJJ????77777!!!!!!~~~~~~!!7?Y55YYYJJ?77!!~~^^~~!?5PPYJ?77!!!!!77??JPBPJB@@@@&&&&&B7^J##PPB#B&@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B??JJJJJJJ5B&@@@@@@@@@@@@@@@@@@@@@&#GP5YJJ?????JJJJ?????77777!!!!!!!!!!7?YPGPYJ?????777!!~^^~~!7?5GG5YJ?777!777??YP#G?P&@@@&BYYJ!~!P&BJ~!7G@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@5?JJJJJJJY5B###B#&&@@@@@@@@@@@@@@&#BG55YJJJJ?????????????77777!!!!!77?YPGBBPY?????????7!!~~~~!7?YPGGPYJ??77777??YP##GB&@@@@&PYYYP#&&&&B55&@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&Y?JJJJJJYYYYYYYY5PB#&@@@@@@@@@@@&&#GPP55YYJJJJJJJJ???????777777777?JYPGGGGGPP55555YYYJ??7777?JJJJYPP5YJ???????JYP#&&@@@@@@@@&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&YJJJJJJJYYYYYYYYYY5PB##&@@@@@@@@&#BBGPP55YJJJJJJJJJJJ????????????JYPPPPGBB#&&&&##BBGP555YY5PP5YJJJY5YJJ?????JYPB#&&@@@@@@@@&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&YJJJJJYYYYYYYYYYYYY555PG#&&&&###BBGGPPPP55YYYYJJJJJJJJJJJJ????JJY55PPPB##&&&&&&&########&&&#BGP5YJJJJJJJJJJY5G#&&&&@@@@@@@&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&YJYYYYYYYYYYYYY555YYY55555YJYPBBBGGGGGGGPP55YYYYYYYYYJJJJJJ?JJYY5PPGBB#&&&@@@@&&&&&&&&@@&&####BP5JJJJJJJY5PG#&&&&&@@@@@@@@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&5JYYYYYYYYYYY5555555555YJ??5GBB#######BGGPPPP5555YYYYYJJJJJJJY5PGB####&&&&@@@&&&&&&&&&&&######BG5J??JJY5PB#&&B55P#@@@@@@&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@GJYYYYYYYYYYY55555YYJ?777YPPPG#######BBBBGGGGPP55555YYYJJJJY5GB#######&&&&&&&&&&&&&&&&&&&&&&&#BG5JJJY5GB#&@#Y!!7P&@@@@BY?JJYB@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BYJYYYYYYYYYYJJ???777777J5YY5GBB###########BBGPPPPPP5YYJJYPGB###&&&@&&&&&&&&&&#######BBBB#####GPYJY5PB#&@@&57!7P@@@@&P!~~~5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&PJYYYYYJJ?7777777!7?77?YJJJYPGB###&&#######BBGGGGPP5555PBB###########BBBBGGGGPP55YYJY5Y5PB##BG5Y5PB#&@&&&#Y77G@@@@&5!~7B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#5JJ?7!~~~!777!!7???7?YYJJJYPGB######&&&&&###BBBGPP5PPGB##BBGGGPPPP555YJJJJJJ??????JJJJJ5G##GP5PB#&&&#GG#&BB&@@@@&G?P@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P!~~~~~~!!7!!77???77JYYJJY5PGB####&&&&&&&##&##BGPPPGB##BGP5555YYYYYYYYYYYYYYYYYJJJJJJ?J5B#BGGB&&@@#5Y5#@@@@@@@@@#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y!~~~~!!!!!77????77JYYJJY5PG###&&&&&&&&&&&&#BGGPGB##BGP555YYYYYY55PGPPGGGGGGPP55YJ??JP#&&#&&@@@#J775&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#J~^~~!!!!77?????7?JJJJJJY5GB#&&&&&&&&&&&&##BBBB###BP5YYYYYYY555PPGGGBBBBBBG55Y??7?YB&&@@@@@@#Y7!?G@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y!~~~!!7???????77?JYJJJYYPB#&&&&&&&&&&&&&###&&&&BG5JJ???JJJJYY5555PGGGGGP5J??77J5#&@@@@@&BJ7!!J&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&G?~~!7??77????77?JYJJJJYYPB#&&&&&@@@@&&&&&@@@&#BG5YJ?7777?JJYYYY55PGG55YYYJJY5G&@@@@@&P?777!75&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#57!!7777????77?JYYYJJYY5PB&&@@@@@@@@@@@@@@@&&#BGPYJJJJJJYYYY5PPGGP5Y55PPPGB#&@@@&B5J7777!7Y&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y7!777?????7?JYYYYYYYY5GB#&@@@@@@@@@@@@@@&&&&#BGPP55PP55PPGGGGGPPPGGGB#&&&@&BY77??77YB@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#PJ777???????JYYYYYYYY55G#&@@@@@@@@@@@@@@@@&&##BBBBBGGGGGGGGGGGBBB##&&&&B5?7!!JP#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&B5J???????JY555YYYYY55PGB#&@@@@@@@@@@@@@&&&&&&&#BBBBBB########&####P?7?YG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#PYJ?????Y555YYY55555PPB#&&@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&#BGPB#BB&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&BG5JJJY55555555555PPPGB##&&&@&@@@@@@@@@@@@@@@&&&&##BBB#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&#BGGGPPPPPPPPPPPPGGBB####&&&&&&&&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&##BBBGGGGGGGGGGGBB##&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n ";
    std::cout << std::endl;
    system("pause");
    system("CLS");
}

int main()
{
    Jeremy();
    while (*PContinues) //while exit not chosen
    {
        Main_Menu();
    }
    return 0;
}