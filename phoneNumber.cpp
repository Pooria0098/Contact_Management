/**
 * @brief
 * @author Pooria0098
 * @date 2020 May 31
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

struct Phone
{
    char name[15];
    char family[15];
    char tel[12];

    Phone* next;
};

Phone* startPtr = nullptr;
Phone* currentPtr = nullptr;

void Select(int);
void Add_new();
void Print_all();
void Menu1();
void Menu2();
void Edit_current();
void Delete_current();
void Delete_all();
void Tel_or_name(int);
void Read_from_file();
void Write_to_file();
void Sort_name(int);
void Add_tail_from_file(Phone*);

Phone* Search(char*, int);

enum MENU { ADD = 1, SEARCH_NAME, SEARCH_NO, SORT_NAME, SORT_FAMILY, SHOW_ALL, SAVE, EXIT };
/**
 * Driven function
 * @return
 */
int main()
{
    Read_from_file();

    int choice;

    do{
        Menu1();
        cin >> choice;
        system("cls");
        getchar();
        Select(choice);
    } while (choice != EXIT);

    Write_to_file();

    cout << "Thank you" << endl;
    Delete_all();

    return 0;
}

/**
 * @brief select one of items shown in "Menu1" based on enum "Menu"
 * @param choose
 */
void Select(int choose)
{
    switch (choose)
    {
        case ADD:
            Add_new();
            break;

        case SEARCH_NAME:
            Tel_or_name(1);
            break;

        case SEARCH_NO:
            Tel_or_name(2);
            break;

        case SORT_NAME:
            Sort_name(1);
            break;

        case SORT_FAMILY:
            Sort_name(2);
            break;

        case SHOW_ALL:
            Print_all();
            break;

        case SAVE:
            Write_to_file();
            cout << "We will save your data automatically when your work finished" << endl;
            getchar();
            break;

        case EXIT:
            return;

        default:
            cout << endl<<"Select again :" << endl;
    }
}

/**
 * @brief this function add new phoneNumber to Save in file later
 */
void Add_new()
{
    auto* temp = new Phone;
    Phone* temp2 = startPtr;

    system("cls");

    cout << "Enter Name : ";
    cin >> temp->name;
    cout << "Enter Family : ";
    cin >> temp->family;
    cout << "Enter PhoneNumber : ";
    cin >> temp->tel;

    temp->next = nullptr;

    if (startPtr == nullptr)
    {
        startPtr = temp;
    }else{
        while (temp2->next != nullptr)
        {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
}

void Print_all()
{
    Phone* temp = startPtr;
    char show[35];

    if (startPtr == nullptr)
    {
        cout << "The list is empty!" << endl;
        getchar();
        return;
    }
    else
    {
        cout << "\nName                                Phone       "
             << "\n----------------------------------- ------------" << endl;
        do
        {
            strcpy_s(show, "");
            strcat_s(show, temp->family);
            strcat_s(show, ", ");
            strcat_s(show, temp->name);
            show[0] = toupper(show[0]);
            cout << setiosflags(ios::left)
                 << setw(36) << show << setw(12) << temp->tel << endl;

            temp = temp->next;
        } while (temp != nullptr);
    }
    cout << endl;
    getchar();
}
/*=================Search=======================*/
Phone* Search(char* temp_search, int choice)
{

    if (startPtr == nullptr)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }

    /* Search by name */
    if (choice == 1)
    {
        while (currentPtr != nullptr && strcmp(currentPtr->name, temp_search) != 0)
        {
            currentPtr = currentPtr->next;
        }
    }

    /* Search by tel */
    if (choice == 2)
    {
        while (currentPtr != nullptr && strcmp(currentPtr->tel, temp_search) != 0)
        {
            currentPtr = currentPtr->next;
        }

    }

    /* If record found */
    if (currentPtr != nullptr)
    {
        cout << "Record found" << endl
             << currentPtr->name << " " << currentPtr->family << " : " << currentPtr->tel << endl;

        return currentPtr;
    }
    else
    {
        cout << "Record NOT found" << endl;
        currentPtr = startPtr; //move back the currentPtr pointer to first node
        return nullptr;
    }
}

void Delete_current()
{
    Phone* temp = nullptr;
    Phone* prev = nullptr;

    /* If its the first node */
    if (currentPtr == startPtr)
    {
        temp = startPtr;
        startPtr = startPtr->next; //If we have only 1 node, start_ptr will point to NULL
        delete temp;
        temp = nullptr;
    }
    /* If its in the middle of list or the last node */
    else
    {
        prev = startPtr;
        while (prev->next != currentPtr)
        {
            prev = prev->next;
        }
        prev->next = currentPtr->next;// If its the last node prev will point to NULL
        delete currentPtr;
        currentPtr = startPtr;
    }
}

void Delete_all()
{
    if (startPtr == nullptr)
    {
        return; // we have no memory allocated
    }
    Phone* temp;
    while (startPtr != nullptr)
    {
        temp = startPtr;
        startPtr = startPtr->next;
        delete temp;
    }
}

/**
 * this function used to choosing search base on Telephone or base on Name
 * @param choose
 */
void Tel_or_name(int choose)
{
    Phone* temp_del = nullptr;
    char temp_search[15];
    int choice;

    currentPtr = startPtr;

    cout << "Enter the " << (choose == 1 ? "name" : "tel") << " to search : ";
    cin >> temp_search;

    temp_del = Search(temp_search, choose);

    while (temp_del != nullptr)
    {
        Menu2();
        cin >> choice;
        switch (choice)
        {
            case 1: currentPtr = currentPtr->next; temp_del = Search(temp_search, choose); break;
            case 2: Delete_current(); break;
            case 3: Edit_current();   break;
            case 4: return;
        }
    }
    getchar();
}

void Write_to_file()
{
    Phone* temp = startPtr;
    ofstream outFile("Data.txt", ios::out);

    if (!outFile)
    {
        cerr << "Some error ocured during writing to file." << endl;
        getchar();
        return;
    }

    while (temp != nullptr)
    {
        outFile << temp->name << " " << temp->family << " " << temp->tel;
        if (temp->next != nullptr)
        {
            outFile << endl;
        }
        temp = temp->next;

    }

    outFile.close();

    cout << "Data saved successfully." << endl;
}

void Read_from_file()
{
    ifstream inputFile;
    inputFile.open("Data.txt");
    if (!inputFile)
    {
        cout << "Data could\'nt be loaded." << endl;
        getchar();
        return;
    }

    do{
        auto* temp = new Phone;

        inputFile >> temp->name;
        inputFile >> temp->family;
        inputFile >> temp->tel;
        temp->next = nullptr;

        Add_tail_from_file(temp);

    } while (!inputFile.eof());

    cout << "Data loaded successfully" << endl;
}

void Add_tail_from_file(Phone* temp)
{
    if (startPtr == nullptr) startPtr = temp;
    else
    {
        Phone* temp2 = startPtr;
        while (temp2->next != nullptr)
        {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
}

/**
 * this function used to sort contact list based on which type
 * you chosen from function Tel_or_name()
 * @param choice
 */
void Sort_name(int choice)
{
    /* If list is empty */
    if (startPtr == nullptr)
    {
        cout << "The list is empty!" << endl;
        getchar();
        return;
    }

    /* Determine the size of list */
    int counter = 1;
    Phone* temp = startPtr;

    while (temp->next != nullptr)
    {
        temp = temp->next;
        counter++;
    }

    Phone* sort[1000];

    sort[0] = startPtr;
    for (int cnt = 1; cnt < counter; cnt++)
    {
        sort[cnt] = sort[cnt - 1]->next;
    }
    sort[counter] = nullptr;

    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < counter - i - 1; j++)
        {
            /* Sort by name */
            if (choice == 1)
            {
                if (strcmp(sort[j]->name, sort[j + 1]->name) > 0)
                {
                    Phone* temp2 = sort[j];
                    sort[j] = sort[j + 1];
                    sort[j + 1] = temp2;
                }
            }

            /* Sort by family */
            else
            {
                if (strcmp(sort[j]->family, sort[j + 1]->family) > 0)
                {
                    Phone* temp2 = sort[j];
                    sort[j] = sort[j + 1];
                    sort[j + 1] = temp2;
                }
            }
        }
    }

    /* Showing sorted list */
    char show[35];
    int index = 0;

    cout << "\nName                                Phone       "
         << "\n----------------------------------- ------------" << endl;
    do
    {
        strcpy_s(show, "");
        strcat_s(show, sort[index]->family);
        strcat_s(show, ", ");
        strcat_s(show, sort[index]->name);
        show[0] = toupper(show[0]);
        cout << setiosflags(ios::left)
             << setw(36) << show << setw(12) << sort[index]->tel << endl;

    } while (sort[++index] != nullptr);

    cout << endl;
    getchar();
}

void Menu1()
{
    system("cls");
    cout << "1.  Add new phone      :"
         << "\n2.  Search for name    :"
         << "\n3.  Search for number  :"
         << "\n4.  Sort by name       :"
         << "\n5.  Sort by family     :"
         << "\n6.  Show all list      :"
         << "\n7.  Save data          :"
         << "\n8.  Exit               :"
         << "\n\nYour choice : ";
}

void Menu2()
{
    cout <<"\n1.  Find next              :"
         << "\n2.  Delete currentPtr person  :"
         << "\n3.  Edit currentPtr person    :"
         << "\n4.  continue               :" << endl
         << "\nYour choice : ";
}

void Edit_current()
{
    strcpy_s(currentPtr->name, "");
    strcpy_s(currentPtr->family, "");

    cout << "Enter the name : ";
    cin >> currentPtr->name;
    cout << "Family : ";
    cin >> currentPtr->family;
    cout << "Phone number : ";
    cin >> currentPtr->tel;

    system("cls");
}
