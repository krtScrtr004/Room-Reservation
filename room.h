#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Room_Type_e : unsigned short
{
    CLASSROOM = 1,
    LABORATORY,
    CANCEL
};

extern Room_Type_e room_type;

class Room
{
    friend void admin_page_f(User *user);

private:
    const std::string M_ROOM_DIRECTORY = "room\\";
    std::string m_room_type_directory = "";

    const std::string M_ROOM_RESERVATION_DIRECTORY = "reservation\\";
    std::string m_room_reserved_type_directory = "";

    std::ifstream m_infile;
    std::ofstream m_outfile;

    Room_Type_e m_room_type;
    const static unsigned short MAX_NO_OF_ROOMS = 100U;

    struct m_Info_t
    {
        std::vector<std::string> m_code, m_board_type;
        std::vector<bool> m_TV, m_AC;
    } m_info;

    time_t now = time(nullptr), current_year = 0, current_month = 0,
           current_day = 0, reserved_day = 0;
    struct m_Reservation_t
    {
        std::vector<std::string> m_reserver, m_reserved_room;
        std::vector<time_t> m_reserved_day;
        std::vector<char> m_room_type;
        unsigned short m_classroom_reservation_calendar[MAX_NO_OF_ROOMS][31] = {0};
        unsigned short m_laboratory_reservation_calendar[MAX_NO_OF_ROOMS][31] = {0};
    } m_reservation;

private:
    /* DATABASE INFO FETCHER ********************************************************/
    void m_fetch_room_info_f(const std::string &M_ROOM_TYPE_DIRECTORY);
    void m_save_room_info_f(const std::string &M_ROOM_TYPE_DIRECTORY);

    void m_save_room_reserved_info_f(const std::string &M_ROOM_RESERVATED_TYPE_DIRECTORY);
    void m_fetch_room_reserved_info_f(const std::string &M_ROOM_RESERVATED_TYPE_DIRECTORY);

    void m_fetch_reserver_info_f(const std::string M_RESERVER_DIRECTORY = "reservation.txt");
    void m_save_reserver_info_f(const std::string M_RESERVER_DIRECTORY = "reservation.txt");
    /*****************************************************************************/

    void m_load_room_type_f(const char ROOM_TYPE);

    /* INFO VECTOR SORTER ************************************************************/
    void m_sort_room_compare_f(std::vector<std::string> &arr_code, std::vector<std::string> &arr_board_type,
                               std::vector<bool> &arr_TV, std::vector<bool> &arr_AC,
                               std::vector<std::string> left_arr_code, std::vector<std::string> left_arr_board_type,
                               std::vector<bool> left_arr_TV, std::vector<bool> left_arr_AC,
                               std::vector<std::string> right_arr_code, std::vector<std::string> right_arr_board_type,
                               std::vector<bool> right_arr_TV, std::vector<bool> right_arr_AC);
    void m_sort_room_f(std::vector<std::string> &arr_code, std::vector<std::string> &arr_board_type,
                       std::vector<bool> &arr_TV, std::vector<bool> &arr_AC);

    void m_sort_reserved_compare_f(std::vector<std::string> &arr_reserver, std::vector<std::string> &arr_room, std::vector<time_t> &arr_reserved_day, std::vector<char> &arr_room_type,
                                   std::vector<std::string> &left_arr_reserver, std::vector<std::string> &left_arr_room, std::vector<time_t> &left_arr_reserved_day, std::vector<char> &left_arr_room_type,
                                   std::vector<std::string> &right_arr_reserver, std::vector<std::string> &right_arr_room, std::vector<time_t> &right_arr_reserved_day, std::vector<char> &right_arr_room_type);
    void m_sort_reserved_f(std::vector<std::string> &arr_reserver, std::vector<std::string> &arr_room,
                           std::vector<time_t> &arr_reserved_day, std::vector<char> &arr_room_type);
    /*****************************************************************************/

    /* ROOM INFO SETTERS *************************************************************/
    inline void m_set_room_type_f(const Room_Type_e TEMP_ROOM_TYPE)
    {
        m_room_type = TEMP_ROOM_TYPE;
        return;
    }
    inline void m_set_room_code_f(const std::string &ROOM_CODE)
    {
        m_info.m_code.push_back(ROOM_CODE);
        return;
    }
    inline void m_set_board_type_f(const std::string &BOARD_TYPE)
    {
        m_info.m_board_type.push_back(BOARD_TYPE);
        return;
    }
    inline void m_set_has_TV_f(const bool HAS_TV)
    {
        m_info.m_TV.push_back(HAS_TV);
        return;
    }
    inline void m_set_has_AC_f(const bool HAS_AC)
    {
        m_info.m_AC.push_back(HAS_AC);
        return;
    }
    /*****************************************************************************/

    /* RESERVER INFO SETTERS ********************************************************/
    inline void m_set_reserver_id_f(const std::string &USER_ID)
    {
        m_reservation.m_reserver.push_back(USER_ID);
        return;
    }
    inline void m_set_reservation_code_f(const std::string &ROOM_CODE)
    {
        m_reservation.m_reserved_room.push_back(ROOM_CODE);
        return;
    }
    inline void m_set_reservation_day_f(const time_t RESERVED_DAY)
    {
        m_reservation.m_reserved_day.push_back(RESERVED_DAY);
        return;
    }
    inline void m_set_reservation_room_type_f(const char ROOM_TYPE)
    {
        m_reservation.m_room_type.push_back(ROOM_TYPE);
        return;
    }
    /*****************************************************************************/

    /* ROOM INFO INPUT FORM ******************************************************/
    inline const std::string m_enter_room_code_f(void) const;
    inline const std::string m_enter_board_type_f(void) const;
    inline const bool m_enter_has_TV_f(void) const;
    inline const bool m_enter_has_AC_f(void) const;
    /*****************************************************************************/

    bool is_valid_reservation_day_f(const char ROOM_TYPE, const unsigned short ROOM_INDEX, time_t RESERVED_DAY);

    void m_remove_reservation_f(const unsigned short CURRENT_INDEX);

    void m_increase_user_reservation_points_f(const std::string USER_ID);

    /* USER: void m_view_user_reservations_f() ************************************/
    void m_fetch_user_reservation_f(const std::string &USER_ID, unsigned short &reservations_counter, std::array<unsigned short, 100> &arr_orig_index,
                                    std::array<std::string, 100> &arr_room_code, std::array<time_t, 100> &arr_reserved_day, std::array<char, 100> &arr_room_type) const;
    short m_enter_reservation_id_f(const unsigned short &RESERVATION_COUNTER, const unsigned short MIN, const unsigned short MAX) const;
    void m_edit_reservation_f(const std::string &USER_ID, const unsigned short reservations_counter, const std::array<unsigned short, 100> &arr_orig_index,
                              const std::array<std::string, 100> &arr_room_code, const std::array<time_t, 100> &arr_reserved_day, const std::array<char, 100> &arr_room_type);
    void m_cancel_reservation_f(const std::string &USER_ID, const unsigned short reservations_counter, const std::array<unsigned short, 100> &arr_orig_index,
                                const std::array<std::string, 100> &arr_room_code, const std::array<time_t, 100> &arr_reserved_day, const std::array<char, 100> &arr_room_type);
    /*****************************************************************************/

    /* ADMIN ACCESSED METHODS ****************************************************/
    void m_see_rooms_f(const User *user);
    void m_add_room_f();
    void m_edit_room_f(const User *user, const unsigned short DEF_ROOM_INDEX);
    void m_delete_room_f(const unsigned short ROOM_INDEX);
    /****************************************************************************/

public:
    Room()
    {
        m_fetch_reserver_info_f();

        std::tm *local_time = localtime(&now);
        current_year = 1900 + local_time->tm_year;
        current_month = 1 + local_time->tm_mon;
        current_day = local_time->tm_mday;
    }

    /* ROOM INFO GETTERS *************************************************************/
    inline const std::string m_get_room_code_f(const unsigned short ROOM_INDEX) const { return m_info.m_code[ROOM_INDEX]; }
    inline const std::string m_get_room_board_type_f(const unsigned short ROOM_INDEX) const { return m_info.m_board_type[ROOM_INDEX]; }
    inline const bool m_get_room_TV(const unsigned short ROOM_INDEX) const { return m_info.m_TV[ROOM_INDEX]; }
    inline const bool m_get_room_AC(const unsigned short ROOM_INDEX) const { return m_info.m_AC[ROOM_INDEX]; }
    /*****************************************************************************/
    
    /* ROOM TYPE SELECTOR ********************************************************/
    const Room_Type_e m_select_room_type_f(void);
    const void m_default_room_type_f(void);
    /*****************************************************************************/

    /* ROOM RESERVATION***********************************************************/
    void m_room_list_f(void) const;
    const short m_select_room_f(void);
    const time_t m_enter_reservation_day_f(const unsigned short ROOM_INDEX);
    bool Room::m_set_reservation_info_f(User *user, const char ROOM_TYPE, const std::string &USER_ID, const unsigned short ROOM_INDEX, const time_t RESERVED_DAY);
    void m_unset_passed_reservation_f(void);
    /*****************************************************************************/

    /* VIEW RESERVATIONS (STUDENT && EDUCATOR ONNY) ******************************/
    void m_view_user_reservations_f(const std::string USER_ID);
    /*****************************************************************************/

    ~Room()
    {
        if (m_room_type_directory != "")
        {
            m_save_room_info_f(m_room_type_directory);
            m_room_type_directory = " ";
        }
        if (m_room_reserved_type_directory != "")
        {
            m_save_room_reserved_info_f(m_room_reserved_type_directory);
            m_room_reserved_type_directory = " ";
        }
        m_save_reserver_info_f();
    }
};

#endif // ROOM_H