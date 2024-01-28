#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

enum class Services_e : unsigned short
{
    LOGIN = 1,
    REGISTER,
    FORGET_PASSWORD,
    EXIT
};

const std::string cin_error_f(void);

const std::string out_of_bounds_error_f(const short MIN, const short MAX);

const std::string numeric_detected_error_f(void);

const std::string no_at_sign_error_f(void);

const std::string already_used_error_f(void);

const void not_unique_error_f(const std::string INFO);

const std::string search_not_found_error_f(void);

const std::string search_not_found_error_f(const std::string SEARCH);

const std::string acc_not_found_error_f(void);

const std::string no_data_available_error_f(void);

const std::string insufficient_no_of_reservation_error_f(void);

const std::string invalid_room_type_error_f(void);

const std::string invalid_reservation_date_error_f(void);

const std::string already_reserved_error_f(const std::string ROOM_NAME);

const std::string open_file_error_f(const std::string FILE_NAME);

const std::string memory_allocation_error_f(void);

bool is_valid_str_f(const std::string INPUT, const short MIN, const short MAX);

bool is_valid_str_no_num_f(const std::string INPUT, const short MIN, const short MAX);

bool is_valid_num_f(const short INPUT, const short MIN, const short MAX);

bool is_valid_YN_asnwer(char answer);

bool is_valid_email(const std::string EMAIL);

const std::string force_upper_str_f(std::string input);

const char force_upper_char_f(char input);

const std::string remove_space_str_f(std::string input);

const short compare_str_f(std::string target_str, std::string compare_str);

const short compare_str_no_space_f(std::string target_str, std::string compare_str);

const short compare_str_case_f(std::string target_str, std::string compare_str);

const short compare_str_case_no_space_f(std::string target_str, std::string compare_str);

const short linear_search_f(std::string target, const std::vector<std::string> &VECTOR);

const short linear_search_no_space_f(std::string target, const std::vector<std::string> &VECTOR);

const short linear_search_case_f(std::string target, const std::vector<std::string> &VECTOR);

const short linear_search_case_no_space_f(std::string target, const std::vector<std::string> &VECTOR);

const short binary_search_f(std::string target, const std::vector<std::string> &VECTOR);

const short binary_search_no_space_f(std::string target, const std::vector<std::string> &VECTOR);

const short binary_search_case_f(std::string target, const std::vector<std::string> &VECTOR);

const short binary_search_case_no_space_f(std::string target, const std::vector<std::string> &VECTOR);

const bool is_unique_f(std::string target, const std::vector<std::string> &VECTOR);

const std::string generate_code_f(void);

#endif // UTILITY_H