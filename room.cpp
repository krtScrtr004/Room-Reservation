#include "utility.h"
#include "user.h"
#include "room.h"

Room_Type_e room_type;

// PRIVATE METHODS
void Room::m_fetch_room_info_f(const std::string &M_ROOM_TYPE_DIRECTORY)
{
    m_infile.open(M_ROOM_DIRECTORY + M_ROOM_TYPE_DIRECTORY);
    if (!m_infile.is_open())
    {
        std::cerr << open_file_error_f(M_ROOM_TYPE_DIRECTORY);
        exit(EXIT_FAILURE);
    }

    std::string current_code = " ", current_board_type = " ", white_space = " ";
    short current_TV = 0, current_AC = 0, current_availability = 0;

    bool is_alternate = true;
    while (m_infile.peek() != std::ifstream::traits_type::eof())
    {
        if (is_alternate)
        {
            getline(m_infile, current_code);
            getline(m_infile, current_board_type);
            m_infile >> current_TV >> current_AC;
            m_infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            m_info.m_code.push_back(current_code);
            m_info.m_board_type.push_back(current_board_type);
            m_info.m_TV.push_back(current_TV);
            m_info.m_AC.push_back(current_AC);
        }
        else
        {
            getline(m_infile, white_space);
        }

        is_alternate = !is_alternate;
    }

    if (m_info.m_code.size() != 0)
    {
        m_sort_room_f(m_info.m_code, m_info.m_board_type, m_info.m_TV, m_info.m_AC);
    }

    if (m_infile.is_open())
    {
        m_infile.close();
    }

    return;
}

void Room::m_save_room_info_f(const std::string &M_ROOM_TYPE_DIRECTORY)
{
    m_outfile.open(M_ROOM_DIRECTORY + M_ROOM_TYPE_DIRECTORY, std::ios::out);
    if (!m_outfile.is_open())
    {
        std::cerr << open_file_error_f(M_ROOM_TYPE_DIRECTORY);
        exit(EXIT_FAILURE);
    }

    unsigned short i = 0;
    const unsigned short LEN = m_info.m_code.size();
    if (LEN > i)
    {
        bool is_alternate = true;
        while (i < LEN)
        {
            if (is_alternate)
            {
                m_outfile << m_info.m_code[i] << '\n';
                m_outfile << m_info.m_board_type[i] << '\n';
                m_outfile << m_info.m_TV[i] << '\n';
                m_outfile << m_info.m_AC[i] << '\n';
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

    m_info.m_code.clear();
    m_info.m_board_type.clear();
    m_info.m_TV.clear();
    m_info.m_AC.clear();

    return;
}

void Room::m_fetch_room_reserved_info_f(const std::string &M_ROOM_RESERVATED_TYPE_DIRECTORY)
{
    m_infile.open(M_ROOM_DIRECTORY + M_ROOM_RESERVATION_DIRECTORY + M_ROOM_RESERVATED_TYPE_DIRECTORY);

    if (!m_infile.is_open())
    {
        std::cerr << open_file_error_f(M_ROOM_RESERVATED_TYPE_DIRECTORY);
        exit(EXIT_FAILURE);
    }

    unsigned short i = 0U, j = 0U;
    bool is_alternate = true;
    while (m_infile.peek() != std::ifstream::traits_type::eof())
    {
        while (i < MAX_NO_OF_ROOMS)
        {
            while (j < 31)
            {
                if (is_alternate)
                {
                    if (M_ROOM_RESERVATED_TYPE_DIRECTORY == "r_classroom.txt")
                    {
                        m_infile >> m_reservation.m_classroom_reservation_calendar[i][j];
                    }
                    else
                    {
                        m_infile >> m_reservation.m_laboratory_reservation_calendar[i][j];
                    }

                    j++;
                }
                is_alternate = !is_alternate;
            }

            j = 0;
            i++;
        }
        break;
    }

    if (m_infile.is_open())
    {
        m_infile.close();
    }

    return;
}

void Room::m_save_room_reserved_info_f(const std::string &M_ROOM_RESERVATED_TYPE_DIRECTORY)
{
    m_outfile.open(M_ROOM_DIRECTORY + M_ROOM_RESERVATION_DIRECTORY + M_ROOM_RESERVATED_TYPE_DIRECTORY, std::ios::out);
    if (!m_outfile.is_open())
    {
        std::cerr << open_file_error_f(M_ROOM_RESERVATED_TYPE_DIRECTORY);
        exit(EXIT_FAILURE);
    }

    unsigned short i = 0U, j = 0U;
    bool is_alternate = true;
    while (i < MAX_NO_OF_ROOMS)
    {
        while (j < 31)
        {
            if (is_alternate)
            {
                if (M_ROOM_RESERVATED_TYPE_DIRECTORY == "r_classroom.txt")
                {
                    m_outfile << m_reservation.m_classroom_reservation_calendar[i][j] << ' ';
                }
                else
                {
                    m_outfile << m_reservation.m_laboratory_reservation_calendar[i][j] << ' ';
                }

                j++;
            }
            is_alternate = !is_alternate;
        }

        m_outfile << '\n';
        i++;
        j = 0;
    }

    if (m_outfile.is_open())
    {
        m_outfile.close();
    }

    return;
}

void Room::m_fetch_reserver_info_f(const std::string M_RESERVER_DIRECTORY)
{
    m_infile.open(M_ROOM_DIRECTORY + M_ROOM_RESERVATION_DIRECTORY + M_RESERVER_DIRECTORY);
    if (!m_infile.is_open())
    {
        std::cerr << open_file_error_f(M_RESERVER_DIRECTORY);
        exit(EXIT_FAILURE);
    }

    std::string current_reserver = " ", current_reserved_room = " ", white_space = " ";
    time_t current_reserved_day = 0;
    char current_room_type = ' ';
    bool is_alternate = true;
    while (m_infile.peek() != std::ifstream::traits_type::eof())
    {
        if (is_alternate)
        {
            getline(m_infile, current_reserver);
            getline(m_infile, current_reserved_room);
            m_infile >> current_reserved_day >> current_room_type;
            m_infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            m_reservation.m_reserver.push_back(current_reserver);
            m_reservation.m_reserved_room.push_back(current_reserved_room);
            m_reservation.m_reserved_day.push_back(current_reserved_day);
            m_reservation.m_room_type.push_back(current_room_type);
        }
        else
        {
            getline(m_infile, white_space);
        }
        is_alternate = !is_alternate;
    }

    if (m_reservation.m_reserver.size() > 0)
    {
        m_sort_reserved_f(m_reservation.m_reserver, m_reservation.m_reserved_room, m_reservation.m_reserved_day, m_reservation.m_room_type);
    }

    if (m_infile.is_open())
    {
        m_infile.close();
    }

    return;
}

void Room::m_save_reserver_info_f(const std::string M_RESERVER_DIRECTORY)
{
    m_outfile.open(M_ROOM_DIRECTORY + M_ROOM_RESERVATION_DIRECTORY + M_RESERVER_DIRECTORY, std::ios::out);
    if (!m_outfile.is_open())
    {
        std::cerr << open_file_error_f(M_RESERVER_DIRECTORY);
        exit(EXIT_FAILURE);
    }

    unsigned short i = 0U;
    const unsigned short LEN = m_reservation.m_reserved_room.size();
    bool is_alternate = true;
    while (i < LEN)
    {
        if (is_alternate)
        {
            m_outfile << m_reservation.m_reserver[i] << '\n';
            m_outfile << m_reservation.m_reserved_room[i] << '\n';
            m_outfile << m_reservation.m_reserved_day[i] << '\n';
            m_outfile << m_reservation.m_room_type[i] << '\n';
            i++;
        }
        else
        {
            m_outfile << '\n';
        }
        is_alternate = !is_alternate;
    }

    if (m_outfile.is_open())
    {
        m_outfile.close();
    }

    m_reservation.m_reserver.clear();
    m_reservation.m_reserved_room.clear();
    m_reservation.m_reserved_day.clear();
    m_reservation.m_room_type.clear();

    return;
}

void Room::m_load_room_type_f(const char ROOM_TYPE)
{
    switch (ROOM_TYPE)
    {
    case 'C':
    {
        m_room_type_directory = "classroom.txt";
        m_room_reserved_type_directory = "r_classroom.txt";
        break;
    }

    case 'L':
    {
        m_room_type_directory = "laboratory.txt";
        m_room_reserved_type_directory = "r_laboratory.txt";
        break;
    }

    default:
    {
        const Room_Type_e MIN = Room_Type_e::CLASSROOM, MAX = Room_Type_e::LABORATORY;
        std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
    }
    }

    if (m_room_type_directory != "" || m_room_type_directory != " ")
    {
        m_fetch_room_info_f(m_room_type_directory);
    }
    if (m_room_reserved_type_directory != "" || m_room_reserved_type_directory != " ")
    {
        m_fetch_room_reserved_info_f(m_room_reserved_type_directory);
    }

    return;
}

void Room::m_sort_room_compare_f(std::vector<std::string> &arr_code, std::vector<std::string> &arr_board_type,
                                 std::vector<bool> &arr_TV, std::vector<bool> &arr_AC,
                                 std::vector<std::string> left_arr_code, std::vector<std::string> left_arr_board_type,
                                 std::vector<bool> left_arr_TV, std::vector<bool> left_arr_AC,
                                 std::vector<std::string> right_arr_code, std::vector<std::string> right_arr_board_type,
                                 std::vector<bool> right_arr_TV, std::vector<bool> right_arr_AC)
{
    unsigned short i = 0, j = 0, k = 0, left_size = left_arr_code.size(), right_size = right_arr_code.size();
    while (i < left_size && j < right_size)
    {
        if (left_arr_code[i] < right_arr_code[j])
        {
            arr_code[k] = left_arr_code[i];
            arr_board_type[k] = left_arr_board_type[i];
            arr_TV[k] = left_arr_TV[i];
            arr_AC[k] = left_arr_AC[i];

            k++;
            i++;
        }
        else
        {
            arr_code[k] = right_arr_code[j];
            arr_board_type[k] = right_arr_board_type[j];
            arr_TV[k] = right_arr_TV[j];
            arr_AC[k] = right_arr_AC[j];

            k++;
            j++;
        }
    }

    while (i < left_size)
    {
        arr_code[k] = left_arr_code[i];
        arr_board_type[k] = left_arr_board_type[i];
        arr_TV[k] = left_arr_TV[i];
        arr_AC[k] = left_arr_AC[i];

        k++;
        i++;
    }

    while (j < right_size)
    {
        arr_code[k] = right_arr_code[j];
        arr_board_type[k] = right_arr_board_type[j];
        arr_TV[k] = right_arr_TV[j];
        arr_AC[k] = right_arr_AC[j];

        k++;
        j++;
    }
}

void Room::m_sort_room_f(std::vector<std::string> &arr_code, std::vector<std::string> &arr_board_type,
                         std::vector<bool> &arr_TV, std::vector<bool> &arr_AC)
{
    unsigned short size = arr_code.size();
    if (size <= 1)
    {
        return;
    }

    unsigned short left_size = size / 2;

    std::vector<std::string> left_arr_code(arr_code.begin(), arr_code.begin() + left_size);
    std::vector<std::string> left_arr_board_type(arr_board_type.begin(), arr_board_type.begin() + left_size);
    std::vector<bool> left_arr_TV(arr_TV.begin(), arr_TV.begin() + left_size);
    std::vector<bool> left_arr_AC(arr_AC.begin(), arr_AC.begin() + left_size);
 
    std::vector<std::string> right_arr_code(arr_code.begin() + left_size, arr_code.end());
    std::vector<std::string> right_arr_board_type(arr_board_type.begin() + left_size, arr_board_type.end());
    std::vector<bool> right_arr_TV(arr_TV.begin() + left_size, arr_TV.end());
    std::vector<bool> right_arr_AC(arr_AC.begin() + left_size, arr_AC.end());

    m_sort_room_f(left_arr_code, left_arr_board_type, left_arr_TV, left_arr_AC);
    m_sort_room_f(right_arr_code, right_arr_board_type, right_arr_TV, right_arr_AC);

    m_sort_room_compare_f(arr_code, arr_board_type, arr_TV, arr_AC,
                          left_arr_code, left_arr_board_type, left_arr_TV, left_arr_AC,
                          right_arr_code, right_arr_board_type, right_arr_TV, right_arr_AC);

    return;
}

void Room::m_sort_reserved_compare_f(std::vector<std::string> &arr_reserver, std::vector<std::string> &arr_room, std::vector<time_t> &arr_reserved_day, std::vector<char> &arr_room_type,
                                     std::vector<std::string> &left_arr_reserver, std::vector<std::string> &left_arr_room, std::vector<time_t> &left_arr_reserved_day, std::vector<char> &left_arr_room_type,
                                     std::vector<std::string> &right_arr_reserver, std::vector<std::string> &right_arr_room, std::vector<time_t> &right_arr_reserved_day, std::vector<char> &right_arr_room_type)
{
    unsigned short i = 0, j = 0, k = 0, left_size = left_arr_reserver.size(), right_size = right_arr_reserver.size();
    while (i < left_size && j < right_size)
    {
        if (left_arr_reserver[i] < right_arr_reserver[j])
        {
            arr_reserver[k] = left_arr_reserver[i];
            arr_room[k] = left_arr_room[i];
            arr_reserved_day[k] = left_arr_reserved_day[i];
            arr_room_type[k] = left_arr_room_type[i];

            k++;
            i++;
        }
        else
        {
            arr_reserver[k] = right_arr_reserver[j];
            arr_room[k] = right_arr_room[j];
            arr_reserved_day[k] = right_arr_reserved_day[j];
            arr_room_type[k] = right_arr_room_type[j];

            k++;
            j++;
        }
    }

    while (i < left_size)
    {
        arr_reserver[k] = left_arr_reserver[i];
        arr_room[k] = left_arr_room[i];
        arr_reserved_day[k] = left_arr_reserved_day[i];
        arr_room_type[k] = left_arr_room_type[i];

        k++;
        i++;
    }

    while (j < right_size)
    {
        {
            arr_reserver[k] = right_arr_reserver[j];
            arr_room[k] = right_arr_room[j];
            arr_reserved_day[k] = right_arr_reserved_day[j];
            arr_room_type[k] = right_arr_room_type[j];

            k++;
            j++;
        }
    }

    return;
}

void Room::m_sort_reserved_f(std::vector<std::string> &arr_reserver, std::vector<std::string> &arr_room,
                             std::vector<time_t> &arr_reserved_day, std::vector<char> &arr_room_type)
{
    unsigned short size = arr_reserver.size();
    if (size <= 1)
    {
        return;
    }

    unsigned short left_size = size / 2;

    std::vector<std::string> left_arr_reserver(arr_reserver.begin(), arr_reserver.begin() + left_size);
    std::vector<std::string> left_arr_room(arr_room.begin(), arr_room.begin() + left_size);
    std::vector<time_t> left_arr_reserved_day(arr_reserved_day.begin(), arr_reserved_day.begin() + left_size);
    std::vector<char> left_arr_room_type(arr_room_type.begin(), arr_room_type.begin() + left_size);

    std::vector<std::string> right_arr_reserver(arr_reserver.begin() + left_size, arr_reserver.end());
    std::vector<std::string> right_arr_room(arr_room.begin() + left_size, arr_room.end());
    std::vector<time_t> right_arr_reserved_day(arr_reserved_day.begin() + left_size, arr_reserved_day.end());
    std::vector<char> right_arr_room_type(arr_room_type.begin() + left_size, arr_room_type.end());

    m_sort_reserved_f(left_arr_reserver, left_arr_room, left_arr_reserved_day, left_arr_room_type);
    m_sort_reserved_f(right_arr_reserver, right_arr_room, right_arr_reserved_day, right_arr_room_type);

    m_sort_reserved_compare_f(arr_reserver, arr_room, arr_reserved_day, arr_room_type,
                              left_arr_reserver, left_arr_room, left_arr_reserved_day, left_arr_room_type,
                              right_arr_reserver, right_arr_room, right_arr_reserved_day, right_arr_room_type);

    return;
}

inline const std::string Room::m_enter_room_code_f(void) const
{
    std::string temp_room_code = " ";
    bool is_valid = false;
    const unsigned short MIN = 5U, MAX = 15U;
    do
    {
        std::cout << "ENTER ROOM NAME: ";
        getline(std::cin, temp_room_code);
        is_valid = is_valid_str_f(temp_room_code, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);

    return temp_room_code;
}

inline const std::string Room::m_enter_board_type_f(void) const
{
    enum class Board_Type_e : unsigned short
    {
        BLACK_BOARD = 1,
        WHITE_BOARD,
        NONE
    };

    std::cout << "SELECT BOARD TYPE: ";
    std::cout << '\n';
    std::cout << "[1] BLACK BOARD";
    std::cout << '\n';
    std::cout << "[2] WHITE BOARD";
    std::cout << '\n';
    std::cout << "[3] NONE";
    std::cout << '\n';

    Board_Type_e board_type;
    unsigned short choice = 0U;
    bool is_valid = false;
    const Board_Type_e MIN = Board_Type_e::BLACK_BOARD, MAX = Board_Type_e::NONE;
    do
    {
        std::cout << "ENTER HERE: ";
        std::cin >> choice;
        is_valid = (choice, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    board_type = static_cast<Board_Type_e>(choice);

    switch (board_type)
    {
    case Board_Type_e::BLACK_BOARD:
    {
        return "BLACK BOARD";
    }

    case Board_Type_e::WHITE_BOARD:
    {
        return "WHITE BOARD";
    }

    case Board_Type_e::NONE:
    {
        return "NONE";
    }

    default:
    {
        std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
    }
    }

    return "N/A";
}

inline const bool Room::m_enter_has_TV_f(void) const
{
    char answer = ' ';
    bool is_valid = false;
    do
    {
        std::cout << "DOES IT HAVE TELEVISION? (Y/N) ";
        std::cin >> answer;
        is_valid = is_valid_YN_asnwer(answer);
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return (answer == 'Y') ? true : false;
}

inline const bool Room::m_enter_has_AC_f(void) const
{
    char answer = ' ';
    bool is_valid = false;
    do
    {
        std::cout << "DOES IT HAVE AIRCONDITIONING? (Y/N) ";
        std::cin >> answer;
        is_valid = is_valid_YN_asnwer(answer);
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return (answer == 'Y') ? true : false;
}

bool Room::is_valid_reservation_day_f(const char ROOM_TYPE, const unsigned short ROOM_INDEX, time_t RESERVED_DAY)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error_f();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    const unsigned short TEMP_DAY = static_cast<unsigned short>(RESERVED_DAY), MIN = 1U, MAX = 31U;
    if (TEMP_DAY < MIN || TEMP_DAY > MAX)
    {
        std::cerr << out_of_bounds_error_f(MIN, MAX);
        return false;
    }

    switch (ROOM_TYPE)
    {
    case 'C':
    {
        if (m_reservation.m_classroom_reservation_calendar != 0)
        {
            std::cerr << already_reserved_error_f(m_get_room_code_f(ROOM_INDEX));
            return false;
        }
    }

    case 'L':
    {
        if (m_reservation.m_classroom_reservation_calendar != 0)
        {
            std::cerr << already_reserved_error_f(m_get_room_code_f(ROOM_INDEX));
            return false;
        }
    }

    default:
        std::cerr << invalid_room_type_error_f();
        return false;
    }

    return true;
}

void Room::m_remove_reservation_f(const unsigned short CURRENT_INDEX)
{
    const unsigned short ROOM_INDEX = binary_search_no_space_f(m_reservation.m_reserved_room[CURRENT_INDEX], m_reservation.m_reserved_room);

    if (m_reservation.m_room_type[CURRENT_INDEX] == 'C')
    {
        m_reservation.m_classroom_reservation_calendar[ROOM_INDEX][m_reservation.m_reserved_day[CURRENT_INDEX] - 1] = 0;
    }
    else
    {
        m_reservation.m_laboratory_reservation_calendar[ROOM_INDEX][m_reservation.m_reserved_day[CURRENT_INDEX] - 1] = 0;
    }

    m_reservation.m_reserver.erase(m_reservation.m_reserver.begin() + CURRENT_INDEX);
    m_reservation.m_reserved_room.erase(m_reservation.m_reserved_room.begin() + CURRENT_INDEX);
    m_reservation.m_reserved_day.erase(m_reservation.m_reserved_day.begin() + CURRENT_INDEX);

    m_increase_user_reservation_points_f(m_reservation.m_reserver[CURRENT_INDEX]);

    return;
}

void Room::m_increase_user_reservation_points_f(const std::string USER_ID)
{
    switch (acc_type)
    {
    case User_Type_e::STUDENT:
    {
        User temp_student("student.txt");
        const short RESERVER_INDEX = linear_search_no_space_f(USER_ID, temp_student.m_profile.m_id);
        if (RESERVER_INDEX > 0)
        {
            temp_student.m_profile.m_no_of_reserved[RESERVER_INDEX]++;
        }
        break;
    }
    case User_Type_e::EDUCATOR:
    {
        User temp_educator("educator.txt");
        const short RESERVER_INDEX = linear_search_no_space_f(USER_ID, temp_educator.m_profile.m_id);
        if (RESERVER_INDEX > 0)
        {
            temp_educator.m_profile.m_no_of_reserved[RESERVER_INDEX]++;
        }
        break;
    }
    default:
    {
        const User_Type_e MIN = User_Type_e::STUDENT, MAX = User_Type_e::EDUCATOR;
        std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
    }
    }

    return;
}

void Room::m_fetch_user_reservation_f(const std::string &USER_ID, unsigned short &reservations_counter, std::array<unsigned short, 100> &arr_orig_index,
                                      std::array<std::string, 100> &arr_room_code, std::array<time_t, 100> &arr_reserved_day, std::array<char, 100> &arr_room_type) const
{
    const short FIRST_OCCURENCE_INDEX = linear_search_no_space_f(USER_ID, m_reservation.m_reserver);
    if (FIRST_OCCURENCE_INDEX < 0)
    {
        std::cout << "YOU DO NOT HAVE ANY ROOM RESERVATION.\n";
        return;
    }

    arr_orig_index[reservations_counter] = FIRST_OCCURENCE_INDEX;
    arr_room_code[reservations_counter] = m_reservation.m_reserved_room[FIRST_OCCURENCE_INDEX];
    arr_reserved_day[reservations_counter] = m_reservation.m_reserved_day[FIRST_OCCURENCE_INDEX];
    arr_room_type[reservations_counter] = m_reservation.m_room_type[FIRST_OCCURENCE_INDEX];
    reservations_counter++;

    for (unsigned short i = FIRST_OCCURENCE_INDEX + 1, n = m_reservation.m_reserver.size(); i < n; i++)
    {
        if (compare_str_no_space_f(USER_ID, m_reservation.m_reserver[i]) != 0)
        {
            break;
        }
        arr_orig_index[reservations_counter] = i;
        arr_room_code[reservations_counter] = m_reservation.m_reserved_room[i];
        arr_reserved_day[reservations_counter] = m_reservation.m_reserved_day[i];
        arr_room_type[reservations_counter] = m_reservation.m_room_type[i];
        reservations_counter++;
    }

    return;
}

short Room::m_enter_reservation_id_f(const unsigned short &RESERVATION_COUNTER, const unsigned short MIN, const unsigned short MAX) const
{
    if (RESERVATION_COUNTER <= 0)
    {
        return -1;
    }

    unsigned short room_id = 0U;
    bool is_valid = false;
    do
    {
        std::cout << "ENTER RESERVATION ID TO EDIT: ";
        std::cin >> room_id;
        is_valid = is_valid_num_f(room_id, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return room_id;
}

void Room::m_edit_reservation_f(const std::string &USER_ID, const unsigned short reservations_counter, const std::array<unsigned short, 100> &arr_orig_index,
                                const std::array<std::string, 100> &arr_room_code, const std::array<time_t, 100> &arr_reserved_day, const std::array<char, 100> &arr_room_type)
{
    const short ROOM_ID = m_enter_reservation_id_f(reservations_counter, 0U, reservations_counter);
    if (ROOM_ID < 0)
    {
        std::cout << "YOU DO NOT HAVE ANY ROOM RESERVATION.\n";
        return;
    }

    short ROOM_INDEX = 0;
    if (m_reservation.m_room_type[arr_orig_index[ROOM_ID - 1]] == 'C')
    {
        m_load_room_type_f('C');
        ROOM_INDEX = binary_search_no_space_f(arr_room_code[ROOM_ID - 1], m_info.m_code);
    }
    else
    {
        m_load_room_type_f('L');
        ROOM_INDEX = binary_search_no_space_f(arr_room_code[ROOM_ID - 1], m_info.m_code);
    }

    const time_t NEW_RESERVATION_DATE = m_enter_reservation_day_f(ROOM_INDEX);

    m_reservation.m_reserved_day[arr_orig_index[ROOM_ID - 1]] = NEW_RESERVATION_DATE;
    if (m_reservation.m_room_type[arr_orig_index[ROOM_ID - 1]] == 'C')
    {
        m_reservation.m_classroom_reservation_calendar[ROOM_INDEX][arr_reserved_day[ROOM_ID - 1] - 1] = 0;
        m_reservation.m_classroom_reservation_calendar[ROOM_INDEX][NEW_RESERVATION_DATE - 1] = 1;
    }
    else
    {
        m_reservation.m_laboratory_reservation_calendar[ROOM_INDEX][arr_reserved_day[ROOM_ID - 1] - 1] = 0;
        m_reservation.m_laboratory_reservation_calendar[ROOM_INDEX][NEW_RESERVATION_DATE - 1] = 1;
    }

    std::cout << "RESERVATION EDITED!\n";

    return;
}

void Room::m_cancel_reservation_f(const std::string &USER_ID, const unsigned short reservations_counter, const std::array<unsigned short, 100> &arr_orig_index,
                                  const std::array<std::string, 100> &arr_room_code, const std::array<time_t, 100> &arr_reserved_day, const std::array<char, 100> &arr_room_type)
{
    const short ROOM_ID = m_enter_reservation_id_f(reservations_counter, 0U, reservations_counter);
    if (ROOM_ID < 0)
    {
        std::cout << "YOU DO NOT HAVE ANY ROOM RESERVATION.\n";
        return;
    }

    short ROOM_INDEX = 0;
    if (m_reservation.m_room_type[arr_orig_index[ROOM_ID - 1]] == 'C')
    {
        m_load_room_type_f('C');
        ROOM_INDEX = binary_search_no_space_f(arr_room_code[ROOM_ID - 1], m_info.m_code);
        m_reservation.m_classroom_reservation_calendar[ROOM_INDEX][arr_reserved_day[ROOM_ID - 1] - 1] = 0;
    }
    else
    {
        m_load_room_type_f('L');
        ROOM_INDEX = binary_search_no_space_f(arr_room_code[ROOM_ID - 1], m_info.m_code);
        m_reservation.m_laboratory_reservation_calendar[ROOM_INDEX][arr_reserved_day[ROOM_ID - 1] - 1] = 0;
    }

    m_reservation.m_reserver.erase(m_reservation.m_reserver.begin() + arr_orig_index[ROOM_ID - 1]);
    m_reservation.m_reserved_room.erase(m_reservation.m_reserved_room.begin() + arr_orig_index[ROOM_ID - 1]);
    m_reservation.m_reserved_day.erase(m_reservation.m_reserved_day.begin() + arr_orig_index[ROOM_ID - 1]);

    m_increase_user_reservation_points_f(USER_ID);

    std::cout << "RESERVATION CANCELLED!\n";

    return;
}

void Room::m_see_rooms_f(const User *user)
{
    enum class See_Rooms_Option_e : unsigned short
    {
        SEARCH = 1,
        ADD,
        BACK
    };

    enum class Room_Actions_e : unsigned short
    {
        EDIT = 1,
        DELETE,
        BACK
    };

    while (true)
    {
        Room *room = new Room;
        if (room == nullptr)
        {
            std::cerr << memory_allocation_error_f();
            exit(EXIT_FAILURE);
        }

        Room_Type_e room_type = room->m_select_room_type_f();
        if (room_type == Room_Type_e::CANCEL)
        {
            delete room;
            break;
        }

        room->m_room_list_f();
        std::cout << '\n';

        std::cout << "OPTIONS:";
        std::cout << '\n';
        std::cout << "[1] SEARCH";
        std::cout << '\n';
        std::cout << "[2] ADD ROOM";
        std::cout << '\n';
        std::cout << "[3] BACK";
        std::cout << '\n';

        See_Rooms_Option_e select_service;
        unsigned short choice = 0U;

        bool is_valid = false;
        const See_Rooms_Option_e MIN = See_Rooms_Option_e::SEARCH, MAX = See_Rooms_Option_e::BACK;
        do
        {
            std::cout << "ENTER HERE: ";
            std::cin >> choice;
            is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_service = static_cast<See_Rooms_Option_e>(choice);

        if (select_service == See_Rooms_Option_e::SEARCH)
        {
            const short ROOM_INDEX = room->m_select_room_f();
            if (ROOM_INDEX == -1)
            {
                delete room;
                continue;
            }

            if (ROOM_INDEX >= 0)
            {
                std::cout << room->m_info.m_code[ROOM_INDEX] << '\n';
                std::cout << room->m_info.m_board_type[ROOM_INDEX] << '\n';
                std::string is_available = (room->m_info.m_TV[ROOM_INDEX]) ? "AC: AVAILABLE" : "AC: NOT AVAILABLE";
                std::cout << is_available << '\n';
                is_available = (room->m_info.m_AC[ROOM_INDEX]) ? "TV: AVAILABLE" : "TV: NOT AVAILABLE";
                std::cout << is_available << '\n';

                std::cout << "[1] EDIT ROOM INFORMATION";
                std::cout << '\n';
                std::cout << "[2] DELETE ROOM";
                std::cout << '\n';
                std::cout << "[3] BACK";
                std::cout << '\n';

                Room_Actions_e select_action;
                const Room_Actions_e MIN = Room_Actions_e::EDIT, MAX = Room_Actions_e::BACK;
                do
                {
                    std::cout << "SELECT ACTION: ";
                    std::cin >> choice;
                    is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
                } while (!is_valid);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                select_action = static_cast<Room_Actions_e>(choice);

                if (select_action == Room_Actions_e::EDIT)
                {
                    room->m_edit_room_f(user, ROOM_INDEX);
                }
                else if (select_action == Room_Actions_e::DELETE)
                {
                    room->m_delete_room_f(ROOM_INDEX);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                std::cerr << search_not_found_error_f();
            }
        }
        else if (select_service == See_Rooms_Option_e::ADD)
        {
            Room *room = new Room;
            if (room == nullptr)
            {
                std::cerr << memory_allocation_error_f();
                exit(EXIT_FAILURE);
            }

            room->m_add_room_f();

            delete room;
            continue;
        }
        else
        {
            delete room;
            break;
        }

        delete room;
    }

    return;
}

void Room::m_add_room_f(void)
{
    const Room_Type_e temp_room_type = m_select_room_type_f();
    switch (temp_room_type)
    {
    case Room_Type_e::CLASSROOM:
    {
        const std::string room_code = m_enter_room_code_f();
        const std::string board_type = m_enter_board_type_f();
        const bool has_TV = m_enter_has_TV_f();
        const bool has_AC = m_enter_has_AC_f();

        m_set_room_code_f(room_code);
        m_set_board_type_f(board_type);
        m_set_has_TV_f(has_TV);
        m_set_has_AC_f(has_AC);

        std::cout << "ROOM ADDED SUCCESSFULLY!\n";

        break;
    }

    case Room_Type_e::LABORATORY:
    {
        const std::string room_code = m_enter_room_code_f();
        const std::string board_type = m_enter_board_type_f();
        const bool has_TV = m_enter_has_TV_f();
        const bool has_AC = m_enter_has_AC_f();

        m_set_room_code_f(room_code);
        m_set_board_type_f(board_type);
        m_set_has_TV_f(has_TV);
        m_set_has_AC_f(has_AC);

        std::cout << "ROOM ADDED SUCCESSFULLY!\n";

        break;
    }

    case Room_Type_e::CANCEL:
    {
        break;
    }

    default:
    {
        const Room_Type_e MIN = Room_Type_e::CLASSROOM, MAX = Room_Type_e::LABORATORY;
        std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
    }
    }

    return;
}

void Room::m_edit_room_f(const User *user, const unsigned short DEF_ROOM_INDEX)
{
    enum class Info_Type_e : unsigned short
    {
        CODE = 1,
        BOARD_TYPE,
        TV,
        AC,
        CANCEL
    };

    while (true)
    {
        std::cout << "ENTER IFORMATION TO EDIT:";
        std::cout << '\n';
        std::cout << "[1] CODE";
        std::cout << '\n';
        std::cout << "[2] BOARD TYPE";
        std::cout << '\n';
        std::cout << "[3] TV";
        std::cout << '\n';
        std::cout << "[4] AC";
        std::cout << '\n';
        std::cout << "[5] CANCEL";
        std::cout << '\n';

        Info_Type_e select_edit_info;
        unsigned short choice = 0U;

        const Info_Type_e MIN = Info_Type_e::CODE, MAX = Info_Type_e::CANCEL;
        bool is_valid = false;
        do
        {
            std::cout << "SELECT EDIT OPTION: ";
            std::cin >> choice;
            is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_edit_info = static_cast<Info_Type_e>(choice);

        if (select_edit_info == Info_Type_e::CODE)
        {
            std::cout << "CURRENT ROOM CODE: " << m_info.m_code[DEF_ROOM_INDEX] << '\n';
            const std::string NEW_CODE = m_enter_room_code_f();
            if (user->m_password_confirmation_f())
            {
                m_info.m_code[DEF_ROOM_INDEX] = NEW_CODE;
                std::cout << "ROOM CODE EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. ROOM CODE FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else if (select_edit_info == Info_Type_e::BOARD_TYPE)
        {
            std::cout << "CURRENT ROOM BOARD TYPE: " << m_info.m_board_type[DEF_ROOM_INDEX] << '\n';
            const std::string NEW_BOARD_TYPE = m_enter_board_type_f();
            if (user->m_password_confirmation_f())
            {
                m_info.m_board_type[DEF_ROOM_INDEX] = NEW_BOARD_TYPE;
                std::cout << "ROOM BOARD TYPE EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. ROOM BOARD TYPE FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else if (select_edit_info == Info_Type_e::TV)
        {
            std::cout << "CURRENT ROOM TV's AVAILABILITY: " << m_info.m_TV[DEF_ROOM_INDEX] << '\n';
            const bool NEW_TV_AVAILABILITY = m_enter_has_TV_f();
            if (user->m_password_confirmation_f())
            {
                m_info.m_TV[DEF_ROOM_INDEX] = NEW_TV_AVAILABILITY;
                std::cout << "ROOM TV's AVAILABILITY EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. ROOM TV's AVAILABILITY FAILED TO EDIT!\n";
                continue;
            }
            break;
        }
        else if (select_edit_info == Info_Type_e::AC)
        {
            std::cout << "CURRENT ROOM AC's AVAILABILITY: " << m_info.m_AC[DEF_ROOM_INDEX] << '\n';
            const bool NEW_AC_AVAILABILITY = m_enter_has_AC_f();
            if (user->m_password_confirmation_f())
            {
                m_info.m_AC[DEF_ROOM_INDEX] = NEW_AC_AVAILABILITY;
                std::cout << "ROOM AC's AVAILABILITY EDITED SUCCESSFULLY!\n";
            }
            else
            {
                std::cout << "INCORRECT PASSWORD. ROOM AC's AVAILABILITY FAILED TO EDIT!\n";
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

void Room::m_delete_room_f(const unsigned short ROOM_INDEX)
{
    char answer = ' ';
    bool is_valid = false;

    do
    {
        std::cout << "ARE YOU SURE TO DELETE THIS ROOM: " + m_info.m_code[ROOM_INDEX] + " ? (Y/N) ";
        std::cin >> answer;
        answer = force_upper_char_f(answer);
        if (answer == 'Y' || answer == 'N')
        {
            is_valid = true;
        }
        else
        {
            std::cerr << cin_error_f();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (answer)
    {
    case 'Y':
    {
        m_info.m_code.erase(m_info.m_code.begin() + ROOM_INDEX);
        m_info.m_board_type.erase(m_info.m_board_type.begin() + ROOM_INDEX);
        m_info.m_TV.erase(m_info.m_TV.begin() + ROOM_INDEX);
        m_info.m_AC.erase(m_info.m_AC.begin() + ROOM_INDEX);
        std::cout << "ROOM SUCCESSFULLY DELETED!\n";
        break;
    }

    case 'N':
    {
        std::cout << "ROOM HAVE NOT DELETED.\n";
        break;
    }

    default:
    {
        std::cerr << cin_error_f();
    }
    }
    return;
}

// PUBLIC MEHTODS
const Room_Type_e Room::m_select_room_type_f(void)
{
    std::cout << "SELECT ROOM TYPE";
    std::cout << '\n';
    std::cout << "[1] CLASSROOM";
    std::cout << '\n';
    std::cout << "[2] LABORATORY";
    std::cout << '\n';
    std::cout << "[3] CANCEL";
    std::cout << '\n';

    Room_Type_e temp_room_type;
    unsigned short choice = 0U;
    bool is_valid = false;
    do
    {
        const unsigned short MIN = Room_Type_e::CLASSROOM, MAX = Room_Type_e::CANCEL;
        std::cout << "ENTER ROOM TYPE: ";
        std::cin >> choice;
        is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    temp_room_type = static_cast<Room_Type_e>(choice);
    m_set_room_type_f(temp_room_type);

    switch (temp_room_type)
    {
    case Room_Type_e::CLASSROOM:
    {
        m_load_room_type_f('C');
        break;
    }

    case Room_Type_e::LABORATORY:
    {
        m_load_room_type_f('L');
        break;
    }

    case Room_Type_e::CANCEL:
    {
        return Room_Type_e::CANCEL;
    }

    default:
    {
        const Room_Type_e MIN = Room_Type_e::CLASSROOM, MAX = Room_Type_e::LABORATORY;
        std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
    }
    }

    return temp_room_type;
}

const void Room::m_default_room_type_f(void)
{
    Room_Type_e temp_room_type = Room_Type_e::CLASSROOM;
    m_set_room_type_f(temp_room_type);

    m_load_room_type_f('C');

    return;
}

void Room::m_room_list_f(void) const
{
    for (short i = 0, n = m_info.m_code.size(); i < n; i++)
    {
        std::cout << m_get_room_code_f(i) << '\n';
        std::cout << m_get_room_board_type_f(i) << '\n';
        std::string is_available = (m_get_room_TV(i)) ? "TV: AVAILABLE" : "TV: NOT AVAILABLE";
        std::cout << is_available << '\n';
        is_available = (m_get_room_AC(i)) ? "AC: AVAILABLE" : "AC: NOT AVAILABLE";
        std::cout << is_available << '\n';
    }
    std::cout << '\n';

    return;
}

const short Room::m_select_room_f(void)
{
    if (m_info.m_code.size() <= 0)
    {
        std::cerr << no_data_available_error_f();
        return -1;
    }

    std::string temp_room_code = " ";
    bool is_valid = false;
    const unsigned short MIN = 5U, MAX = 10U;
    do
    {
        std::cout << "ENTER ROOM CODE: ";
        getline(std::cin, temp_room_code);
        is_valid = is_valid_str_f(temp_room_code, static_cast<short>(MIN), static_cast<short>(MAX));
    } while (!is_valid);

    short room_index = binary_search_no_space_f(temp_room_code, m_info.m_code);
    if (room_index < 0)
    {
        std::cerr << search_not_found_error_f(m_get_room_code_f(room_index));
        room_index = -1;
    }

    std::cout << "ROOM'S INFORMATION:" << '\n';
    std::cout << m_get_room_code_f(room_index) << '\n';
    std::cout << m_get_room_board_type_f(room_index) << '\n';
    std::string is_available = (m_get_room_TV(room_index)) ? "TV: AVAILABLE" : "TV: NOT AVAILABLE";
    std::cout << is_available << '\n';
    is_available = (m_get_room_AC(room_index)) ? "AC: AVAILABLE" : "AC: NOT AVAILABLE";
    std::cout << is_available << '\n';

    char answer = ' ';
    do
    {
        std::cout << "ARE YOU SURE TO RESERVE THIS ROOM? (Y/N) ";
        std::cin >> answer;
        answer = force_upper_char_f(answer);
        is_valid = is_valid_YN_asnwer(answer);
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (answer != 'Y')
    {
        return -2;
    }

    return room_index;
}

const time_t Room::m_enter_reservation_day_f(const unsigned short ROOM_INDEX)
{
    const unsigned short MIN = static_cast<unsigned short>(current_day), MAX = 31U;
    bool is_valid = false;
    do
    {
        std::cout << "ENTER RESERVATION DATE: (YYYY - MM - DD)\n";
        std::cout << current_year << " : " << current_month << " : ";
        std::cin >> reserved_day;

        bool is_valid_date = is_valid_num_f(reserved_day, static_cast<short>(MIN), static_cast<short>(MAX));
        bool is_already_reserved = false;

        if (m_room_type_directory == "classroom.txt")
        {
            is_already_reserved = (m_reservation.m_classroom_reservation_calendar[ROOM_INDEX][reserved_day - 1] == 0);
        }
        else
        {
            is_already_reserved = (m_reservation.m_laboratory_reservation_calendar[ROOM_INDEX][reserved_day - 1] == 0);
        }

        if (!is_already_reserved)
        {
            std::cerr << already_reserved_error_f(m_get_room_code_f(ROOM_INDEX));
        }

        is_valid = is_valid_date && is_already_reserved;
    } while (!is_valid);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return reserved_day;
}

bool Room::m_set_reservation_info_f(User *user, const char ROOM_TYPE, const std::string &USER_ID, const unsigned short ROOM_INDEX, const time_t RESERVED_DAY)
{
    m_set_reserver_id_f(USER_ID);
    m_set_reservation_code_f(m_get_room_code_f(ROOM_INDEX));
    m_set_reservation_day_f(RESERVED_DAY);
    m_set_reservation_room_type_f(ROOM_TYPE);
    switch (ROOM_TYPE)
    {
    case 'C':
        m_reservation.m_classroom_reservation_calendar[ROOM_INDEX][RESERVED_DAY - 1] = 1;
        break;

    case 'L':
        m_reservation.m_laboratory_reservation_calendar[ROOM_INDEX][RESERVED_DAY - 1] = 1;
        break;

    default:
        std::cerr << invalid_room_type_error_f();
        return false;
    }

    user->m_profile.m_no_of_reserved[static_cast<unsigned short>(user_index)];
    return true;
}

void Room::m_unset_passed_reservation_f()
{
    unsigned short i = 0U;
    const unsigned short LEN = m_reservation.m_reserver.size();

    while (i < LEN)
    {
        if (m_reservation.m_reserved_day[i] < current_day)
        {
            m_remove_reservation_f(i);
        }
        i++;
    }

    return;
}

void Room::m_view_user_reservations_f(const std::string USER_ID)
{
    enum class Reservation_Actions_e : unsigned short
    {
        EDIT = 1,
        CANCEL,
        BACK
    };

    std::array<unsigned short, 100> arr_orig_index{0};
    std::array<std::string, 100> arr_room_code{" "};
    std::array<time_t, 100> arr_reserved_day{0};
    std::array<char, 100> arr_room_type;
    unsigned short reservations_counter = 0U;

    while (true)
    {
        m_fetch_user_reservation_f(USER_ID, reservations_counter, arr_orig_index, arr_room_code, arr_reserved_day, arr_room_type);

        for (unsigned short i = 0U; i < reservations_counter; i++)
        {
            std::cout << i + 1 << ' ' << arr_room_code[i] << ' ' << arr_reserved_day[i] << ' ' << arr_room_type[i] << '\n';
        }
        std::cout << '\n';

        std::cout << "OPTIONS:";
        std::cout << '\n';
        std::cout << "[1] EDIT";
        std::cout << '\n';
        std::cout << "[2] CANCEL";
        std::cout << '\n';
        std::cout << "[3] BACK";
        std::cout << '\n';

        Reservation_Actions_e select_action;
        unsigned short choice = 0U;

        bool is_valid = false;
        const Reservation_Actions_e MIN = Reservation_Actions_e::EDIT, MAX = Reservation_Actions_e::BACK;
        do
        {
            std::cout << "ENTER HERE: ";
            std::cin >> choice;
            is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_action = static_cast<Reservation_Actions_e>(choice);

        if (select_action == Reservation_Actions_e::EDIT)
        {
            m_edit_reservation_f(USER_ID, reservations_counter, arr_orig_index, arr_room_code, arr_reserved_day, arr_room_type);
            break;
        }
        else if (select_action == Reservation_Actions_e::CANCEL)
        {
            m_cancel_reservation_f(USER_ID, reservations_counter, arr_orig_index, arr_room_code, arr_reserved_day, arr_room_type);
            break;
        }
        else if (select_action == Reservation_Actions_e::BACK)
        {
            break;
        }
        else
        {
            std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
        }
    }

    return;
}


