#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "utility.h"
#include "user.h"
#include "room.h"

const void forget_password_f()
{
    acc_type_list_f();
    User_Type_e temp_user_type = select_acc_type_f();
    std::string file_name = "";
    switch (temp_user_type)
    {
    case User_Type_e::STUDENT:
        file_name = "student.txt";
        break;

    case User_Type_e::EDUCATOR:
        file_name = "educator.txt";
        break;

    case User_Type_e::ADMIN:
        file_name = "admin.txt";
        break;

    default:
    {
        const User_Type_e MIN = User_Type_e::STUDENT, MAX = User_Type_e::CANCEL;
        std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
        return;
    }
    }

    User temp_user(file_name);
    if (temp_user.m_forget_password_f(temp_user))
    {
        std::cout << "PASSWORD SUCCESSFULLY RESET!\n";
    }
    else 
    {
        std::cout << "PASSWORD FAILED TO RESET!\n";
    }

    return;
}

const User_Type_e login_f(User *user)
{
    const std::string input_email = user->m_enter_email_f();
    const std::string input_password = user->m_enter_password_f();

    User_Type_e user_index = static_cast<User_Type_e>(0);
    bool is_suspended = false;
    const std::array<std::string, 3> user_types = {"student", "educator", "admin"};
    for (unsigned short i = 0, n = user_types.size(); i < n; i++)
    {
        User temp_user(user_types[i] + ".txt");
        user_index = user->m_check_login_info_f(&temp_user, input_email, input_password, i);
        if (user_index != static_cast<User_Type_e>(0))
        {
            break;
        }
    }

    if (user_index == static_cast<User_Type_e>(0))
    {
        std::cerr << acc_not_found_error_f();
    }

    return user_index;
}

void register_f(User *user)
{
    std::string temp_name = user->m_enter_name_f();
    std::string temp_id = " ";
    do
    {
        temp_id = user->m_enter_id_f();
    } while (!user->m_is_unique_f(temp_id, "ID"));
    std::string temp_email = " ";
    do
    {
        temp_email = user->m_enter_email_f();
    } while (!user->m_is_unique_f(temp_email, "EMAIL"));
    std::string temp_password = user->m_enter_password_f();

    user->m_set_name_f(temp_name);
    user->m_set_id_f(temp_id);
    user->m_set_email_f(temp_email);
    user->m_set_password_f(temp_password);
    user->m_set_no_of_reserved();
    user->m_set_is_suspended();

    user->m_sort_f(user);
    std::cout << "ACCOUNT HAS BEEN REGISTERED SUCCESSFULLY!\n";

    return;
}

void student_page_f(User *student)
{
    std::cout << "HOME PAGE\n";

    while (true)
    {
        const User_Services_e select_service = student->m_select_home_page_service_f();
        if (select_service == User_Services_e::RESERVE)
        {
            // Check user's current number of reservation points
            if (student->m_get_no_of_reserved(static_cast<unsigned short>(user_index)) < 1)
            {
                std::cerr << insufficient_no_of_reservation_error_f();
                continue;
            }

            Room *room = new Room;
            if (room == nullptr)
            {
                std::cerr << memory_allocation_error_f();
                exit(EXIT_FAILURE);
            }

            room->m_default_room_type_f();
            room->m_room_list_f();
            room->m_unset_passed_reservation_f(); // Remove all outdated reservations

            const short ROOM_INDEX = room->m_select_room_f();
            if (ROOM_INDEX < 0)
            {
                delete room;
                continue;
            }

            if (ROOM_INDEX >= 0)
            {
                const time_t RESERVED_DAY = room->m_enter_reservation_day_f(ROOM_INDEX);
                const std::string USER_ID = student->m_get_id_f(static_cast<unsigned short>(user_index));
                if (room->m_set_reservation_info_f(student, 'C', USER_ID, ROOM_INDEX, RESERVED_DAY))
                {
                    std::cout << "ROOM SUCCESSFULLY RESERVED!\n";
                }
                else
                {
                    std::cout << "ROOM FAILED TO GET RESERVED!\n";
                }
            }
            else
            {
                std::cerr << search_not_found_error_f();
            }

            delete room;
            continue;
        }
        else if (select_service == User_Services_e::MY_RESERVATION)
        {
            Room *room = new Room;
            if (room == nullptr)
            {
                std::cerr << memory_allocation_error_f();
                exit(EXIT_FAILURE);
            }

            room->m_view_user_reservations_f(student->m_get_id_f(static_cast<unsigned short>(user_index)));

            delete room;
            continue;
        }
        else if (select_service == User_Services_e::EDIT_PROFILE)
        {
            student->m_edit_info_f();
            continue;
        }
        else if (select_service == User_Services_e::LOGOUT)
        {
            break;
        }
        else
        {
            const User_Services_e MIN = User_Services_e::RESERVE, MAX = User_Services_e::LOGOUT;
            std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
            continue;
        }
    }

    return;
}

void educator_page_f(User *educator)
{
    std::cout << "HOME PAGE\n";

    while (true)
    {
        const User_Services_e select_service = educator->m_select_home_page_service_f();
        if (select_service == User_Services_e::RESERVE)
        {
            if (educator->m_get_no_of_reserved(static_cast<unsigned short>(user_index)) < 1)
            {
                std::cerr << insufficient_no_of_reservation_error_f();
                continue;
            }

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
                continue;
            }
            room->m_room_list_f();
            room->m_unset_passed_reservation_f();

            const short ROOM_INDEX = room->m_select_room_f();
            if (ROOM_INDEX < 0)
            {
                delete room;
                continue;
            }

            if (ROOM_INDEX >= 0)
            {
                const time_t RESERVED_DAY = room->m_enter_reservation_day_f(ROOM_INDEX);
                const std::string USER_ID = educator->m_get_id_f(static_cast<unsigned short>(user_index));
                switch (room_type)
                {
                case Room_Type_e::CLASSROOM:
                {
                    if (room->m_set_reservation_info_f(educator, 'C', USER_ID, ROOM_INDEX, RESERVED_DAY))
                    {
                        std::cout << "ROOM SUCCESSFULLY RESERVED!\n";
                    }
                    else
                    {
                        std::cout << "ROOM FAILED TO GET RESERVED!\n";
                    }
                    break;
                }

                case Room_Type_e::LABORATORY:
                {
                    if (room->m_set_reservation_info_f(educator, 'L', USER_ID, ROOM_INDEX, RESERVED_DAY))
                    {
                        std::cout << "ROOM SUCCESSFULLY RESERVED!\n";
                    }
                    else
                    {
                        std::cout << "ROOM FAILED TO GET RESERVED!\n";
                    }
                    break;
                }

                default:
                {
                    std::cerr << invalid_room_type_error_f();
                }
                }
            }
            else
            {
                std::cerr << search_not_found_error_f();
            }
            delete room;
            continue;
        }
        else if (select_service == User_Services_e::MY_RESERVATION)
        {
            Room *room = new Room;
            if (room == nullptr)
            {
                std::cerr << memory_allocation_error_f();
                exit(EXIT_FAILURE);
            }

            room->m_view_user_reservations_f(educator->m_get_id_f(static_cast<unsigned short>(user_index)));

            delete room;
            continue;
        }
        else if (select_service == User_Services_e::EDIT_PROFILE)
        {
            educator->m_edit_info_f();
            continue;
        }
        else if (select_service == User_Services_e::LOGOUT)
        {
            acc_type = static_cast<User_Type_e>(0);
            break;
        }
        else
        {
            const User_Services_e MIN = User_Services_e::RESERVE, MAX = User_Services_e::LOGOUT;
            std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
            continue;
        }
    }

    return;
}

void admin_page_f(User *admin)
{
    enum class Admin_Services_e : unsigned short
    {
        SEE_USERS = 1,
        SEE_ROOMS,
        EDIT_PROFILE,
        LOGOUT
    };

    std::cout << "HOME PAGE\n";

    while (true)
    {
        std::cout << "[1] SEE USERS";
        std::cout << '\n';
        std::cout << "[2] SEE ROOMS";
        std::cout << '\n';
        std::cout << "[3] EDIT PROFILE";
        std::cout << '\n';
        std::cout << "[4] LOGOUT";
        std::cout << '\n';

        Admin_Services_e select_service;
        unsigned short choice = 0U;
        bool is_valid = false;
        const Admin_Services_e MIN = Admin_Services_e::SEE_USERS, MAX = Admin_Services_e::LOGOUT;
        do
        {
            std::cout << "SELECT MENU OPTION: ";
            std::cin >> choice;
            is_valid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!is_valid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_service = static_cast<Admin_Services_e>(choice);

        if (select_service == Admin_Services_e::SEE_USERS)
        {
            acc_type_list_f();
            const User_Type_e temp_acc_type = select_acc_type_f();

            switch (temp_acc_type)
            {
            case User_Type_e::STUDENT:
            {
                User temp_student{"student.txt"};
                temp_student.m_see_users_f(&temp_student);
                break;
            }

            case User_Type_e::EDUCATOR:
            {
                User temp_educator{"educator.txt"};
                temp_educator.m_see_users_f(&temp_educator);
                break;
            }

            case User_Type_e::ADMIN:
            {
                User temp_admin{"admin.txt"};
                temp_admin.m_see_users_f(&temp_admin);
                break;
            }

            case User_Type_e::CANCEL:
            {
                break;
            }

            default:
            {
                const User_Type_e MIN = User_Type_e::STUDENT, MAX = User_Type_e::CANCEL;
                std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
            }
            }
            continue;
        }
        else if (select_service == Admin_Services_e::SEE_ROOMS)
        {
            Room *room = new Room;
            if (room == nullptr)
            {
                std::cerr << memory_allocation_error_f();
                exit(EXIT_FAILURE);
            }

            room->m_see_rooms_f(admin);

            delete room;
        }
        else if (select_service == Admin_Services_e::EDIT_PROFILE)
        {
            admin->m_edit_info_f();
            continue;
        }
        else if (select_service == Admin_Services_e::LOGOUT)
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

int main(void)
{
    std::cout << "CLASSROOM RESERVATION SYSTEM!\n";

    while (true)
    {
        std::cout << "[1] LOGIN";
        std::cout << '\n';
        std::cout << "[2] REGISTRATION";
        std::cout << '\n';
        std::cout << "[3] FORGET PASSWORD";
        std::cout << '\n';
        std::cout << "[4] EXIT";
        std::cout << '\n';

        // Input menu option
        Services_e select_service;
        unsigned short choice = 0U;
        bool isValid = false;
        do
        {
            const Services_e MIN = Services_e::LOGIN, MAX = Services_e::EXIT;
            std::cout << "SELECT MENU OPTION: ";
            std::cin >> choice;
            isValid = is_valid_num_f(choice, static_cast<short>(MIN), static_cast<short>(MAX));
        } while (!isValid);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        select_service = static_cast<Services_e>(choice);

        if (select_service == Services_e::LOGIN)
        {
            std::cout << "LOGIN\n";
            User user;
            acc_type = login_f(&user);

            switch (acc_type)
            {
            case User_Type_e::STUDENT:
            {
                User *student = new User{"student.txt"};
                if (student == nullptr)
                {
                    std::cerr << memory_allocation_error_f();
                    exit(EXIT_FAILURE);
                }
                student_page_f(student);

                delete student;
                break;
            }

            case User_Type_e::EDUCATOR:
            {
                User *educator = new User{"educator.txt"};
                if (educator == nullptr)
                {
                    std::cerr << memory_allocation_error_f();
                    exit(EXIT_FAILURE);
                }

                educator_page_f(educator);

                delete educator;
                break;
            }

            case User_Type_e::ADMIN:
            {
                User *admin = new User{"admin.txt"};
                if (admin == nullptr)
                {
                    std::cerr << memory_allocation_error_f();
                    exit(EXIT_FAILURE);
                }

                admin_page_f(admin);

                delete admin;
                continue;
            }

            default:
            {
                // DO NOTHING
            }
            }
        }
        else if (select_service == Services_e::REGISTER)
        {
            std::cout << "REGISTER\n";
            acc_type_list_f();
            const User_Type_e temp_user_type = select_acc_type_f();
            acc_type = static_cast<User_Type_e>(temp_user_type); // Sets global account type to user input

            if (acc_type == User_Type_e::STUDENT)
            {
                User *student = new User{"student.txt"};
                if (student == nullptr)
                {
                    std::cerr << memory_allocation_error_f();
                    exit(EXIT_FAILURE);
                }
                register_f(student);

                delete student;

                continue;
            }
            else if (acc_type == User_Type_e::EDUCATOR)
            {
                User *educator = new User{"educator.txt"};
                if (educator == nullptr)
                {
                    std::cerr << memory_allocation_error_f();
                    exit(EXIT_FAILURE);
                }
                register_f(educator);

                delete educator;

                continue;
            }
            else if (acc_type == User_Type_e::ADMIN)
            {
                User *admin = new User{"admin.txt"};
                if (admin == nullptr)
                {
                    std::cerr << memory_allocation_error_f();
                    exit(EXIT_FAILURE);
                }
                register_f(admin);

                delete admin;

                continue;
            }
            else if (acc_type == User_Type_e::CANCEL)
            {
                continue;
            }
            else
            {
                const User_Type_e MIN = User_Type_e::STUDENT, MAX = User_Type_e::CANCEL;
                std::cerr << out_of_bounds_error_f(static_cast<short>(MIN), static_cast<short>(MAX));
                continue;
            }
        }
        else if (select_service == Services_e::FORGET_PASSWORD)
        {
            std::cout << "FORGET PASSWORD\n";
            forget_password_f();            
            continue;
        }
        else if (select_service == Services_e::EXIT)
        {
            break;
        }
    }

    return 0;
}
