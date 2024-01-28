#include "utility.h"

const std::string cin_error_f(void)
{
    return "INVALID INPUT. PLEASE TRY AGAIN.\n";
}

const std::string out_of_bounds_error_f(const short MIN, const short MAX)
{
    return "INPUT OUT OF BOUNDS! MINIMUM: " + std::to_string(MIN) + " MAXSIMUM: " + std::to_string(MAX) + ".\n";
}

const std::string numeric_detected_error_f(void)
{
    return "NUMERIC CHARACTER DETECTED.\n";
}

const std::string no_at_sign_error_f(void)
{
    return "NO \'@\' SIGN. PLEASE TRY AGAIN.\n";
}

const std::string already_used_error_f(void)
{
    return "INPUT IS ALREADY USED. PLEASE TRY ANOTHER ONE.\n";
}

const void not_unique_error_f(const std::string INFO)
{
    std::cerr << INFO + " ALREADY EXISTS. PLEASE USE ANOTHER " + INFO + ".\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return;
}

const std::string search_not_found_error_f(void)
{
    return "SEARCH NOT FOUND.\n";
}

const std::string search_not_found_error_f(const std::string SEARCH)
{
    return SEARCH + " NOT FOUND.\n";
}

const std::string acc_not_found_error_f(void)
{
    return "EMAIL / PASSWORD / ID NOT FOUND.\n";
}

const std::string no_data_available_error_f(void)
{
    return "NO DATA AVAILABLE.\n";
}

const std::string insufficient_no_of_reservation_error_f(void)
{
    return "INSUFFICIENT NUMBER OF AVAILABLE RESERVATION.\n";
}

const std::string invalid_room_type_error_f(void)
{
    return "INVALID ROOM TYPE.\n";
}

const std::string invalid_reservation_date_error_f(void)
{
    return "INVALID RESERVATION DATE.\n";
}

const std::string already_reserved_error_f(const std::string ROOM_NAME)
{
    return ROOM_NAME + " IS ALREADY RESERVED IN THIS DATE.\n";
}

const std::string open_file_error_f(const std::string FILE_NAME)
{
    return FILE_NAME + " CANNOT BE OPENED.\n";
}

const std::string memory_allocation_error_f(void)
{
    return "MEMORY ALLOCATION FAILED. PROGRAM TERMINATES.\n";
}

bool is_valid_str_f(const std::string INPUT, const short MIN, const short MAX)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error_f();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    const short LEN = INPUT.length();
    if (LEN < MIN || LEN > MAX)
    {
        std::cerr << out_of_bounds_error_f(MIN, MAX);
        return false;
    }

    return true;
}

bool is_valid_str_no_num_f(const std::string INPUT, const short MIN, const short MAX)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error_f();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    const short LEN = INPUT.length();
    if (LEN < MIN || LEN > MAX)
    {
        std::cerr << out_of_bounds_error_f(MIN, MAX);
        return false;
    }

    for (short i = 0; i < LEN; i++)
    {
        if (isdigit(INPUT[i]))
        {
            std::cerr << numeric_detected_error_f();
            return false;
        }
    }

    return true;
}

bool is_valid_num_f(const short INPUT, const short MIN, const short MAX)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error_f();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    if (INPUT < MIN || INPUT > MAX)
    {
        std::cerr << out_of_bounds_error_f(MIN, MAX);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

bool is_valid_YN_asnwer(char answer)
{
    answer = force_upper_char_f(answer);

    if ((std::cin.fail()) || (answer != 'Y' && answer != 'N'))
    {
        std::cerr << cin_error_f();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

bool is_valid_email(const std::string EMAIL)
{
    if (std::cin.fail())
    {
        std::cerr << cin_error_f();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    const unsigned short LEN = EMAIL.length();
    const unsigned short MIN = 8U, MAX = 20U;

    if (LEN < MIN || LEN > MAX)
    {
        std::cerr << out_of_bounds_error_f(MIN, MAX);
        return false;
    }

    const char at_sign = '@';
    const unsigned short is_found = EMAIL.find(at_sign);
    if (is_found < 0 || is_found > LEN)
    {
        std::cerr << no_at_sign_error_f();
        return false;
    }

    return true;
}

const std::string force_upper_str_f(std::string input)
{
    const unsigned short LEN = input.length();
    for (short i = 0; i < LEN; i++)
    {
        if (islower(input[i]))
        {
            input[i] = toupper(input[i]);
        }
    }

    return input;
}

const char force_upper_char_f(char input)
{
    return toupper(input);
}

const std::string remove_space_str_f(std::string input)
{
    const unsigned short LEN = input.length();
    for (short i = 0; i < LEN; i++)
    {
        if (isspace(input[i]))
        {
            input.erase(i, 1); // Params: i = index to remove; 1 =  nos. of chars to remove
        }
    }

    return input;
}

// CASE INSENSITIVE
const short compare_str_f(std::string target_str, std::string compare_str)
{
    target_str = force_upper_str_f(target_str);
    compare_str = force_upper_str_f(compare_str);

    return strcmp(target_str.c_str(), compare_str.c_str());
}

// CASE INSENSITIVE && SPACES REMOVED
const short compare_str_no_space_f(std::string target_str, std::string compare_str)
{
    target_str = force_upper_str_f(remove_space_str_f(target_str));
    compare_str = force_upper_str_f(remove_space_str_f(compare_str));

    return strcmp(target_str.c_str(), compare_str.c_str());
}

// CASE SENSITIVE
const short compare_str_case_f(std::string target_str, std::string compare_str)
{
    return strcmp(target_str.c_str(), compare_str.c_str());
}

// CASE SENSITIVE && SPACES REMOVED
const short compare_str_case_no_space_f(std::string target_str, std::string compare_str)
{
    target_str = remove_space_str_f(target_str);
    compare_str = remove_space_str_f(compare_str);

    return strcmp(target_str.c_str(), compare_str.c_str());
}

const short linear_search_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1;
    for (short i = 0; i < VECTOR_SIZE; i++)
    {
        short compare = compare_str_f(target, VECTOR[i]);
        if (compare == 0)
        {
            target_idx = i;
            break;
        }
    }

    return target_idx;
}

const short linear_search_no_space_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1;
    for (short i = 0; i < VECTOR_SIZE; i++)
    {
        short compare = compare_str_no_space_f(target, VECTOR[i]);
        if (compare == 0)
        {
            target_idx = i;
            break;
        }
    }

    return target_idx;
}

const short linear_search_case_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1;
    for (short i = 0; i < VECTOR_SIZE; i++)
    {
        short compare = compare_str_case_f(target, VECTOR[i]);
        if (compare == 0)
        {
            target_idx = i;
            break;
        }
    }

    return target_idx;
}

const short linear_search_case_no_space_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1;
    for (short i = 0; i < VECTOR_SIZE; i++)
    {
        short compare = compare_str_case_no_space_f(target, VECTOR[i]);
        if (compare == 0)
        {
            target_idx = i;
            break;
        }
    }

    return target_idx;
}

const short binary_search_f(std::string target, const std::vector<std::string> &VECTOR)
{

    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1, start = 0, end = VECTOR.size() - 1;
    while (start <= end)
    {
        short mid = (start + end) / 2;
        std::string current_vect_str = VECTOR[mid];
        int comparison = compare_str_f(target, current_vect_str);

        if (comparison == 0)
        {
            target_idx = mid;
            break;
        }
        else if (comparison < 0)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return target_idx;
}

const short binary_search_no_space_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1, start = 0, end = VECTOR.size() - 1;
    while (start <= end)
    {
        short mid = (start + end) / 2;
        std::string current_vect_str = VECTOR[mid];
        int comparison = compare_str_no_space_f(target, current_vect_str);

        if (comparison == 0)
        {
            target_idx = mid;
            break;
        }
        else if (comparison < 0)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return target_idx;
}

const short binary_search_case_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1, start = 0, end = VECTOR.size() - 1;
    while (start <= end)
    {
        short mid = (start + end) / 2;
        std::string current_vect_str = VECTOR[mid];
        int comparison = compare_str_case_f(target, current_vect_str);

        if (comparison == 0)
        {
            target_idx = mid;
            break;
        }
        else if (comparison < 0)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    // NOTE: Returning < 0 || > vector size means no search found
    return target_idx;
}

const short binary_search_case_no_space_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const unsigned short VECTOR_SIZE = VECTOR.size();
    if (VECTOR_SIZE < 1)
    {
        return -1;
    }

    short target_idx = -1, start = 0, end = VECTOR.size() - 1;
    while (start <= end)
    {
        short mid = (start + end) / 2;
        std::string current_vect_str = VECTOR[mid];
        int comparison = compare_str_case_no_space_f(target, current_vect_str);

        if (comparison == 0)
        {
            target_idx = mid;
            break;
        }
        else if (comparison < 0)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return target_idx;
}

const bool is_unique_f(std::string target, const std::vector<std::string> &VECTOR)
{
    const short SEARCH_IDX = binary_search_f(target, VECTOR);
    if (SEARCH_IDX >= 0)
    {
        std::cerr << already_used_error_f();
        return false;
    }

    return true;
}

const std::string generate_code_f(void)
{
    const std::string characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM123456789!@#$%&*?<>";
    std::string code = "";

    srand(time(nullptr));
    for (unsigned short i = 0, code_size = 8U; i < code_size; i++)
    {
        unsigned short index = rand() % characters.size();
        code += characters[index];
    }

    return code;
}