#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include "user.h"

enum class User_Type_e : short
{
    STUDENT = 1,
    EDUCATOR,
    ADMIN,
    CANCEL
};

enum class User_Services_e : unsigned short
{
    RESERVE = 1,
    MY_RESERVATION,
    EDIT_PROFILE,
    LOGOUT
};

extern User_Type_e acc_type;   // Current user acccount type
extern User_Type_e user_index; // Current user index

/* GLOBAL NON-MEMBER FUNCTIONS ***********************************************/
const User_Type_e select_acc_type_f(void);
void acc_type_list_f(void);
/*****************************************************************************/

class User
{
    friend class Room;
    friend void admin_page_f(User *user);

protected:
    const std::string M_USER_DIRECTORY = "user\\";
    std::string M_FILE_NAME = " ";

    std::ifstream m_infile;
    std::ofstream m_outfile;

    struct m_Profile_t
    {
        std::vector<std::string> m_name, m_id, m_email, m_password;
        std::vector<unsigned short> m_no_of_reserved;
        std::vector<bool> m_is_suspended;
    } m_profile;

protected:
    /* DATABASE INFO FETCHER ********************************************************/
    void m_fetch_user_info_f(const std::string M_FILE_NAME);
    void m_save_user_info_f(const std::string M_FILE_NAME);
    /*****************************************************************************/

    /* INFO VECTOR SORTER ************************************************************/
    void m_sort_compare_f(std::vector<std::string> &arr_name, std::vector<std::string> &arr_id, std::vector<std::string> &arr_email, std::vector<std::string> &arr_password,
                          std::vector<unsigned short> &arr_no_of_reserved, std::vector<bool> &arr_is_suspended, std::vector<std::string> &left_arr_name, std::vector<std::string> &left_arr_id,
                          std::vector<std::string> &left_arr_email, std::vector<std::string> &left_arr_password, std::vector<unsigned short> &left_arr_no_of_reserved, std::vector<bool> &left_arr_is_suspended,
                          std::vector<std::string> &right_arr_name, std::vector<std::string> &right_arr_id, std::vector<std::string> &right_arr_email,
                          std::vector<std::string> &right_arr_password, std::vector<unsigned short> &right_arr_no_of_reserved, std::vector<bool> &right_arr_is_suspended);
    void m_sort_f(std::vector<std::string> &arr_name, std::vector<std::string> &arr_id,
                  std::vector<std::string> &arr_email, std::vector<std::string> &arr_password,
                  std::vector<unsigned short> &arr_no_of_reserved, std::vector<bool> &arr_is_suspended);
    /*****************************************************************************/

    bool m_password_confirmation_f(void) const;

    /* ADMIN ONLY ACCESSED ********************************************************/
    void m_see_users_f(User *account_type);
    void m_see_users_search_f(User *account_type);
    void m_suspend_user_f(User *acc_type, const unsigned short USER_INDEX);
    void m_unsuspend_user_f(User *acc_type, const unsigned short USER_INDEX);
    void m_delete_user_f(User *acc_type, const unsigned short USER_INDEX);
    /*****************************************************************************/

public:
    User() {}

    User(const std::string &FILE_NAME)
    {
        M_FILE_NAME = FILE_NAME;
        m_fetch_user_info_f(M_FILE_NAME);
    }

    inline void m_sort_f(User *user)
    {
        this->m_sort_f(this->m_profile.m_name, this->m_profile.m_id, this->m_profile.m_email,
                       this->m_profile.m_password, this->m_profile.m_no_of_reserved, this->m_profile.m_is_suspended);
        return;
    }

    /* USER INFO SETTER ************************************************************/
    inline void m_set_name_f(const std::string &USER_NAME)
    {
        m_profile.m_name.push_back(USER_NAME);
        return;
    }
    inline void m_set_id_f(const std::string &USER_ID)
    {
        m_profile.m_id.push_back(USER_ID);
        return;
    }
    inline void m_set_email_f(const std::string &USER_EMAIL)
    {
        m_profile.m_email.push_back(USER_EMAIL);
        return;
    }
    inline void m_set_password_f(const std::string &USER_PASSWORD)
    {
        m_profile.m_password.push_back(USER_PASSWORD);
        return;
    }
    inline void m_set_no_of_reserved(void)
    {
        m_profile.m_no_of_reserved.push_back(100);
        return;
    }

    inline void m_set_is_suspended(void)
    {
        m_profile.m_is_suspended.push_back(false);
        return;
    }
    /*****************************************************************************/

    /* USER INFO GETTERS *************************************************************/
    inline const std::string m_get_name_f(const unsigned short USER_INDEX) const { return m_profile.m_name[USER_INDEX]; }
    inline const std::string m_get_id_f(const unsigned short USER_INDEX) const { return m_profile.m_id[USER_INDEX]; }
    inline const std::string m_get_email_f(const unsigned short USER_INDEX) const { return m_profile.m_email[USER_INDEX]; }
    inline const std::string m_get_password_f(const unsigned short USER_INDEX) const { return m_profile.m_password[USER_INDEX]; }
    inline const unsigned short m_get_no_of_reserved(const unsigned short USER_INDEX) const { return m_profile.m_no_of_reserved[USER_INDEX]; }
    /*****************************************************************************/

    /* USER INFO FORMS *************************************************************/
    inline const std::string m_enter_name_f(void) const
    {
        bool is_valid = true;
        std::string temp_name = " ";
        const unsigned short MIN = 5U, MAX = 25U;
        do
        {
            std::cout << "ENTER NAME: (LN, FN, MI.) ";
            getline(std::cin, temp_name);
            is_valid = is_valid_str_no_num_f(temp_name, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return temp_name;
    }

    inline const std::string m_enter_id_f(void) const
    {
        bool is_valid = true;
        std::string temp_id = " ";
        const unsigned short MIN = 5U, MAX = 25U;
        do
        {
            std::cout << "ENTER ID: (Ex. 2023 - xxxxxx) ";
            getline(std::cin, temp_id);
            temp_id = remove_space_str_f(temp_id);
            is_valid = is_valid_str_f(temp_id, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return temp_id;
    }

    inline const std::string m_enter_email_f(void) const
    {
        bool is_valid = true;
        std::string temp_email = " ";
        do
        {
            std::cout << "ENTER EMAIL: (Ex. abc@gmail.com) ";
            getline(std::cin, temp_email);
            temp_email = remove_space_str_f(temp_email);
            is_valid = is_valid_email(temp_email);
        } while (!is_valid);

        return temp_email;
    }

    inline const std::string m_enter_password_f(void) const
    {
        bool is_valid = true;
        std::string temp_password = " ";
        const unsigned short MIN = 5U, MAX = 25U;
        do
        {
            std::cout << "ENTER PASSWORD: (Ex. abc123) ";
            getline(std::cin, temp_password);
            is_valid = is_valid_str_f(temp_password, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);

        return temp_password;
    }
    /*****************************************************************************/

    // CHECKS EMAIL AND ID ONLY
    const bool m_is_unique_f(const std::string &TEMP_INFO, const std::string &INFO_TYPE) const;

    const User_Type_e m_check_login_info_f(User *temp_user, const std::string &EMAIL, const std::string &PASSWORD, const unsigned short INDEX) const;
    const bool m_forget_password_f(User &temp_user);

    // STUDENT & EDUCATOR USER ONLY
    const User_Services_e m_select_home_page_service_f(void) const;

    void m_edit_info_f(const unsigned short DEF_USER_INDEX = static_cast<unsigned short>(user_index));

    ~User()
    {
        if (M_FILE_NAME != " ")
            m_save_user_info_f(M_FILE_NAME);
    }
};

#endif // USER_H