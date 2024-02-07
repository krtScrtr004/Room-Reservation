#include "utility.h"
#include "user.h"
#include "room.h"

User_Type_e acc_type;
User_Type_e user_index;

// GLOBAL NON-MEMBER FUNCTIONS
const User_Type_e select_acc_type_f(void)
{
    bool is_valid = false;
    User_Type_e user_type;
    unsigned short choice = 0U;
    do
    {
        const User_Type_e MIN = User_Type_e::STUDENT, MAX = User_Type_e::CANCEL;
        std::cout << "SELECT ACCOUNT TYPE: ";
        std::cin >> choice;
        is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    user_type = static_cast<User_Type_e>(choice);

    return user_type;
}

void acc_type_list_f(void)
{
    std::cout << "ACCOUNT TYPE:\n";
    std::cout << "[1] STUDENT\n";
    std::cout << "[2] EDUCATOR\n";
    std::cout << "[3] ADMIN\n";
    std::cout << "[4] EXIT\n";

    return;
}

// USER CLASS
// PROTECTED METHODS
void User::m_fetch_user_info_f(const std::string M_FILE_NAME)
{
    m_infile.open(M_USER_DIRECTORY + M_FILE_NAME);
    if (!m_infile.is_open())
    {
        std::cerr << open_file_error_f(M_FILE_NAME);
        exit(EXIT_FAILURE);
    }

    std::string current_name = " ",
                current_id = " ",
                current_email = " ",
                current_password = " ",
                white_space = " ";
    bool is_alternate = true;
    while (m_infile.peek() != std::ifstream::traits_type::eof())
    {
        if (is_alternate)
        {
            getline(m_infile, current_name);
            getline(m_infile, current_id);
            getline(m_infile, current_email);
            getline(m_infile, current_password);

            m_profile.m_name.push_back(current_name);
            m_profile.m_id.push_back(current_id);
            m_profile.m_email.push_back(current_email);
            m_profile.m_password.push_back(current_password);

            unsigned short current_no_of_reserved = 0U;
            m_infile >> current_no_of_reserved;
            m_profile.m_no_of_reserved.push_back(current_no_of_reserved);

            unsigned short current_suspension_flag = 0;
            m_infile >> current_suspension_flag;
            m_profile.m_is_suspended.push_back((current_suspension_flag > 0) ? true : false);

            m_infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            getline(m_infile, white_space);
        }
        is_alternate = !is_alternate;
    }

    if (m_profile.m_name.size() != 0)
    {
        m_sort_f(this);
    }

    if (m_infile.is_open())
    {
        m_infile.close();
    }

    return;
}

void User::m_save_user_info_f(const std::string M_FILE_NAME)
{
    m_outfile.open(M_USER_DIRECTORY + M_FILE_NAME, std::ios::out);
    if (!m_outfile.is_open())
    {
        std::cerr << open_file_error_f(M_FILE_NAME);
        exit(EXIT_FAILURE);
    }

    unsigned short i = 0U;
    const unsigned short LEN = m_profile.m_name.size();
    if (LEN > i)
    {
        bool is_alternate = true;
        while (i < LEN)
        {
            if (is_alternate)
            {
                m_outfile << m_profile.m_name[i] << '\n';
                m_outfile << m_profile.m_id[i] << '\n';
                m_outfile << m_profile.m_email[i] << '\n';
                m_outfile << m_profile.m_password[i] << '\n';
                m_outfile << m_profile.m_no_of_reserved[i] << '\n';
                m_outfile << ((m_profile.m_is_suspended[i]) ? 1 : 0) << '\n';
                i++;
            }
            else
            {
                m_outfile << '\n';
            }
            is_alternate = !is_alternate;
        }
    }

    if (m_outfile.is_open())
    {
        m_outfile.close();
    }

    m_profile.m_name.clear();
    m_profile.m_id.clear();
    m_profile.m_email.clear();
    m_profile.m_password.clear();
    m_profile.m_no_of_reserved.clear();
    m_profile.m_is_suspended.clear();

    return;
}

void User::m_sort_compare_f(std::vector<std::string> &arr_name, std::vector<std::string> &arr_id, std::vector<std::string> &arr_email, std::vector<std::string> &arr_password,
                            std::vector<unsigned short> &arr_no_of_reserved, std::vector<bool> &arr_is_suspended, std::vector<std::string> &left_arr_name, std::vector<std::string> &left_arr_id,
                            std::vector<std::string> &left_arr_email, std::vector<std::string> &left_arr_password, std::vector<unsigned short> &left_arr_no_of_reserved, std::vector<bool> &left_arr_is_suspended,
                            std::vector<std::string> &right_arr_name, std::vector<std::string> &right_arr_id, std::vector<std::string> &right_arr_email,
                            std::vector<std::string> &right_arr_password, std::vector<unsigned short> &right_arr_no_of_reserved, std::vector<bool> &right_arr_is_suspended)
{
    unsigned short i = 0, j = 0, k = 0, left_size = left_arr_name.size(), right_size = right_arr_name.size();
    while (i < left_size && j < right_size)
    {
        if (left_arr_name[i] < right_arr_name[j])
        {
            arr_name[k] = left_arr_name[i];
            arr_id[k] = left_arr_id[i];
            arr_email[k] = left_arr_email[i];
            arr_password[k] = left_arr_password[i];
            arr_no_of_reserved[k] = left_arr_no_of_reserved[i];
            arr_is_suspended[k] = left_arr_is_suspended[i];

            k++;
            i++;
        }
        else
        {
            arr_name[k] = right_arr_name[j];
            arr_id[k] = right_arr_id[j];
            arr_email[k] = right_arr_email[j];
            arr_password[k] = right_arr_password[j];
            arr_no_of_reserved[k] = right_arr_no_of_reserved[j];
            arr_is_suspended[k] = right_arr_is_suspended[j];

            k++;
            j++;
        }
    }

    while (i < left_size)
    {
        arr_name[k] = left_arr_name[i];
        arr_id[k] = left_arr_id[i];
        arr_email[k] = left_arr_email[i];
        arr_password[k] = left_arr_password[i];
        arr_no_of_reserved[k] = left_arr_no_of_reserved[i];
        arr_is_suspended[k] = left_arr_is_suspended[i];

        k++;
        i++;
    }

    while (j < right_size)
    {
        arr_name[k] = right_arr_name[j];
        arr_id[k] = right_arr_id[j];
        arr_email[k] = right_arr_email[j];
        arr_password[k] = right_arr_password[j];
        arr_no_of_reserved[k] = right_arr_no_of_reserved[j];
        arr_is_suspended[k] = right_arr_is_suspended[j];

        k++;
        j++;
    }
}

void User::m_sort_f(std::vector<std::string> &arr_name, std::vector<std::string> &arr_id,
                    std::vector<std::string> &arr_email, std::vector<std::string> &arr_password,
                    std::vector<unsigned short> &arr_no_of_reserved, std::vector<bool> &arr_is_suspended)
{
    unsigned short size = arr_name.size();
    if (size <= 1)
    {
        return;
    }

    unsigned short left_size = size / 2;

    std::vector<std::string> left_arr_name(arr_name.begin(), arr_name.begin() + left_size);
    std::vector<std::string> left_arr_id(arr_id.begin(), arr_id.begin() + left_size);
    std::vector<std::string> left_arr_email(arr_email.begin(), arr_email.begin() + left_size);
    std::vector<std::string> left_arr_password(arr_password.begin(), arr_password.begin() + left_size);
    std::vector<unsigned short> left_arr_no_of_reserved(arr_no_of_reserved.begin(), arr_no_of_reserved.begin() + left_size);
    std::vector<bool> left_arr_is_suspended(arr_is_suspended.begin(), arr_is_suspended.begin() + left_size);

    std::vector<std::string> right_arr_name(arr_name.begin() + left_size, arr_name.end());
    std::vector<std::string> right_arr_id(arr_id.begin() + left_size, arr_id.end());
    std::vector<std::string> right_arr_email(arr_email.begin() + left_size, arr_email.end());
    std::vector<std::string> right_arr_password(arr_password.begin() + left_size, arr_password.end());
    std::vector<unsigned short> right_arr_no_of_reserved(arr_no_of_reserved.begin() + left_size, arr_no_of_reserved.end());
    std::vector<bool> right_arr_is_suspended(arr_is_suspended.begin() + left_size, arr_is_suspended.end());

    m_sort_f(left_arr_name, left_arr_id, left_arr_email, left_arr_password, left_arr_no_of_reserved, left_arr_is_suspended);
    m_sort_f(right_arr_name, right_arr_id, right_arr_email, right_arr_password, right_arr_no_of_reserved, right_arr_is_suspended);

    m_sort_compare_f(arr_name, arr_id, arr_email, arr_password, arr_no_of_reserved, arr_is_suspended,
                     left_arr_name, left_arr_id, left_arr_email, left_arr_password, left_arr_no_of_reserved, left_arr_is_suspended,
                     right_arr_name, right_arr_id, right_arr_email, right_arr_password, right_arr_no_of_reserved, right_arr_is_suspended);

    return;
}

bool User::m_password_confirmation_f(void) const
{
    const std::string ENTERED_PASSWORD = m_enter_password_f(), PASSWORD = m_get_password_f(static_cast<unsigned short>(user_index));
    if (compare_str_case_f(ENTERED_PASSWORD, PASSWORD) != 0)
    {
        return false;
    }

    return true;
}

void User::m_see_users_f(User *account_type)
{
    enum class See_Users_Option_e : unsigned short
    {
        SEARCH = 1,
        BACK
    };

    while (true)
    {
        const unsigned short LEN = this->m_profile.m_name.size();
        for (short i = 0; i < LEN; i++)
        {
            std::cout << this->m_profile.m_name[i] << ' ' << this->m_profile.m_id[i] << ' '
                      << this->m_profile.m_email[i] << '\n';
        }
        std::cout << '\n';

        std::cout << "OPTIONS:";
        std::cout << '\n';
        std::cout << "[1] SEARCH";
        std::cout << '\n';
        std::cout << "[2] BACK";
        std::cout << '\n';

        See_Users_Option_e select_service;
        unsigned short choice = 0U;

        bool is_valid = false;
        const See_Users_Option_e MIN = See_Users_Option_e::SEARCH, MAX = See_Users_Option_e::BACK;
        do
        {
            std::cout << "ENTER HERE: ";
            std::cin >> choice;
            is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_service = static_cast<See_Users_Option_e>(choice);

        if (select_service == See_Users_Option_e::SEARCH)
        {
            this->m_see_users_search_f(account_type);
            continue;
        }
        else
        {
            break;
        }
    }

    return;
}

void User::m_see_users_search_f(User *account_type)
{
    enum class Acc_Actions_e : unsigned short
    {
        SUSPEND = 1,
        DELETE,
        BACK
    };

    const std::string SEARCH_NAME = this->m_enter_name_f();
    const short SEARCH_INDEX = binary_search_no_space_f(SEARCH_NAME, m_profile.m_name);
    if (SEARCH_INDEX < 0)
    {
        std::cerr << search_not_found_error_f(SEARCH_NAME);
        return;
    }

    std::cout << this->m_profile.m_name[SEARCH_INDEX] << ' ' << this->m_profile.m_id[SEARCH_INDEX] << ' '
              << this->m_profile.m_email[SEARCH_INDEX] << '\n';

    std::cout << "[1] SUSPEND/UNSUSPEND ACCOUNT";
    std::cout << '\n';
    std::cout << "[2] DELETE ACCOUNT";
    std::cout << '\n';
    std::cout << "[3] BACK";
    std::cout << '\n';

    Acc_Actions_e select_action;

    unsigned short choice = 0U;
    bool is_valid = false;
    const Acc_Actions_e MIN = Acc_Actions_e::SUSPEND, MAX = Acc_Actions_e::BACK;
    do
    {
        std::cout << "SELECT ACTION: ";
        std::cin >> choice;
        is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    select_action = static_cast<Acc_Actions_e>(choice);

    if (select_action == Acc_Actions_e::SUSPEND)
    {
        if (!this->m_profile.m_is_suspended[SEARCH_INDEX])
        {
            this->m_suspend_user_f(this, SEARCH_INDEX);
        }
        else
        {
            this->m_unsuspend_user_f(this, SEARCH_INDEX);
        }
    }
    else if (select_action == Acc_Actions_e::DELETE)
    {
        this->m_delete_user_f(this, SEARCH_INDEX);
    }

    return;
}

void User::m_suspend_user_f(User *acc_type, const unsigned short USER_INDEX)
{
    this->m_profile.m_is_suspended[USER_INDEX] = true;
    std::cout << "USER SUCCESSFULLY SUSPENDED!\n";
    return;
}

void User::m_unsuspend_user_f(User *acc_type, const unsigned short USER_INDEX)
{
    this->m_profile.m_is_suspended[USER_INDEX] = false;
    std::cout << "USER SUCCESSFULLY UNSUSPENDED!\n";
    return;
}

void User::m_delete_user_f(User *acc_type, const unsigned short USER_INDEX)
{
    char answer = ' ';
    bool is_valid = false;

    do
    {
        std::cout << "ARE YOU SURE TO DELETE THIS ACCOUNT: " + this->m_get_name_f(static_cast<unsigned short>(user_index)) + " ? (Y/N) ";
        std::cin >> answer;
        is_valid = is_valid_YN_asnwer(answer);
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (answer)
    {
    case 'Y':
    {
        this->m_profile.m_name.erase(m_profile.m_name.begin() + USER_INDEX);
        this->m_profile.m_id.erase(m_profile.m_id.begin() + USER_INDEX);
        this->m_profile.m_email.erase(m_profile.m_email.begin() + USER_INDEX);
        this->m_profile.m_password.erase(m_profile.m_password.begin() + USER_INDEX);
        this->m_profile.m_no_of_reserved.erase(m_profile.m_no_of_reserved.begin() + USER_INDEX);
        this->m_profile.m_is_suspended.erase(m_profile.m_is_suspended.begin() + USER_INDEX);

        std::cout << "ACCOUNT SUCCESSFULLY DELETED!\n";
        break;
    }

    case 'N':
    {
        std::cout << "ACCOUNT HAVE NOT DELETED.\n";
        break;
    }

    default:
    {
        std::cerr << cin_error_f();
    }
    }

    return;
}

// PUBLIC METHODS

const bool User::m_is_unique_f(const std::string &TEMP_INFO, const std::string &INFO_TYPE) const
{
    User temp_student("student.txt");
    User temp_educator("educator.txt");
    User temp_admin("admin.txt");

    if (INFO_TYPE == "ID")
    {
        if (!is_unique_f(TEMP_INFO, temp_student.m_profile.m_id) ||
            !is_unique_f(TEMP_INFO, temp_educator.m_profile.m_id) ||
            !is_unique_f(TEMP_INFO, temp_admin.m_profile.m_id))
        {
            return false;
        }
    }
    else
    {
        if (!is_unique_f(TEMP_INFO, temp_student.m_profile.m_email) ||
            !is_unique_f(TEMP_INFO, temp_educator.m_profile.m_email) ||
            !is_unique_f(TEMP_INFO, temp_admin.m_profile.m_email))
        {
            return false;
        }
    }

    return true;
}


const User_Type_e User::m_check_login_info_f(User *temp_user, const std::string &EMAIL, const std::string &PASSWORD, const unsigned short INDEX) const
{
    User_Type_e user_type = static_cast<User_Type_e>(0);
    const short input_email_index = linear_search_case_f(EMAIL, temp_user->m_profile.m_email);
    if (input_email_index >= 0)
    {
        const int input_password_index = compare_str_case_f(PASSWORD, temp_user->m_profile.m_password[input_email_index]);

        if (input_password_index == 0)
        {
            if (temp_user->m_profile.m_is_suspended[input_email_index])
            {
                std::cout << "YOUR ACCOUNT IS CURRENTLY SUSPENDED!\n";
                user_type = static_cast<User_Type_e>(-1);
            }

            user_index = static_cast<User_Type_e>(input_email_index);
            user_type = static_cast<User_Type_e>(INDEX + 1);
        }
    }

    return user_type;
}

    const bool User::m_forget_password_f(User &temp_user)
    {
        const std::string temp_id = temp_user.m_enter_id_f();
        const short INDEX = linear_search_no_space_f(temp_id, m_profile.m_id);
        if (INDEX < 0)
        {
            std::cerr << search_not_found_error_f(temp_id);
            return false;
        }

        const std::string code = generate_code_f();
        std::cout << "CODE: " + code << '\n';

        std::string entered_code = "";

        bool is_valid = false;
        do
        {
            const unsigned short LIMIT = 8U;
            std::cout << "ENTER 8-CHARACTER CODE: ";
            std::cin >> entered_code;
            is_valid = is_valid_str_f(entered_code, static_cast<short>(LIMIT), static_cast<short>(LIMIT));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (compare_str_case_f(entered_code, code) != 0)
        {
            std::cerr << "YOU HAVE ENTERED INCORRECT CODE\n";
            return false;
        }

        const std::string NEW_PASSWORD = temp_user.m_enter_password_f();
        m_profile.m_password[INDEX] = NEW_PASSWORD;

        return true;
    }


const User_Services_e User::m_select_home_page_service_f(void) const
{
    std::cout << "[1] RESERVE";
    std::cout << '\n';
    std::cout << "[2] MY RESERVATION";
    std::cout << '\n';
    std::cout << "[3] EDIT PROFILE";
    std::cout << '\n';
    std::cout << "[4] LOGOUT";
    std::cout << '\n';

    User_Services_e select_service;
    unsigned short choice = 0U;

    bool is_valid = false;
    const User_Services_e MIN = User_Services_e::RESERVE, MAX = User_Services_e::LOGOUT;
    do
    {
        std::cout << "SELECT MENU OPTION: ";
        std::cin >> choice;
        is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    select_service = static_cast<User_Services_e>(choice);

    return select_service;
}

void User::m_edit_info_f(const unsigned short DEF_USER_INDEX)
{
    enum class Info_Type_e : unsigned short
    {
        NAME = 1,
        ID,
        EMAIL,
        PASSWORD,
        CANCEL
    };

    while (true)
    {
        std::cout << "ENTER IFORMATION TO EDIT:";
        std::cout << '\n';
        std::cout << "[1] NAME";
        std::cout << '\n';
        std::cout << "[2] ID";
        std::cout << '\n';
        std::cout << "[3] EMAIL";
        std::cout << '\n';
        std::cout << "[4] PASSWORD";
        std::cout << '\n';
        std::cout << "[5] CANCEL";
        std::cout << '\n';

        Info_Type_e select_edit_info;
        unsigned short choice = 0U;

        const Info_Type_e MIN = Info_Type_e::NAME, MAX = Info_Type_e::CANCEL;
        bool is_valid = false;
        do
        {
            std::cout << "SELECT EDIT OPTION: ";
            std::cin >> choice;
            is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_edit_info = static_cast<Info_Type_e>(choice);

        if (select_edit_info == Info_Type_e::NAME)
        {
            std::cout << "CURRENT NAME: " << m_get_name_f(static_cast<unsigned short>(user_index)) << '\n';
            const std::string NEW_NAME = m_enter_name_f();
            if (m_password_confirmation_f())
            {
                m_profile.m_name[DEF_USER_INDEX] = NEW_NAME;
                std::cout << "NAME EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. NAME FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else if (select_edit_info == Info_Type_e::ID)
        {
            std::cout << "CURRENT ID: " << m_get_id_f(static_cast<unsigned short>(user_index)) << '\n';
            std::string NEW_ID = "";
            do
            {
                NEW_ID = m_enter_id_f();
            } while (!m_is_unique_f(NEW_ID, "ID"));
            if (m_password_confirmation_f())
            {
                m_profile.m_id[DEF_USER_INDEX] = NEW_ID;
                std::cout << "ID EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. ID FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else if (select_edit_info == Info_Type_e::EMAIL)
        {
            std::cout << "CURRENT EMAIL: " << m_get_email_f(static_cast<unsigned short>(user_index)) << '\n';
            std::string NEW_EMAIL = "";
            do
            {
                NEW_EMAIL = m_enter_email_f();
            } while (!m_is_unique_f(NEW_EMAIL, "EMAIL"));
            if (m_password_confirmation_f())
            {
                m_profile.m_email[DEF_USER_INDEX] = NEW_EMAIL;
                std::cout << "EMAIL EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. EMAIL FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else if (select_edit_info == Info_Type_e::PASSWORD)
        {
            std::cout << "CURRENT PASSWORD: " << m_get_password_f(static_cast<unsigned short>(user_index)) << '\n';
            const std::string NEW_PASSWORD = m_enter_password_f();
            if (m_password_confirmation_f())
            {
                m_profile.m_password[DEF_USER_INDEX] = NEW_PASSWORD;
                std::cout << "INCORRECT PASSWORD. PASSWORD EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "PASSWORD FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else
        {
            break;
        }
    }

    return;
}
