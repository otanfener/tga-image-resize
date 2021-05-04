//
// Created by ozan on 2021-05-04.
//

#include "exception.hpp"

Exception::Exception(uint32_t errorCode, const std::string &message) noexcept:
        _errorCode(errorCode), _message(message) {
}

/// @brief Returns underlying exception string.
/// @return Exception message as a null terminated character string.
const char *Exception::what() const noexcept {
    return this->_message.c_str();
}

/// @brief Returns error code.
/// @return Exception error code as unsigned integer.
const uint32_t Exception::GetErrorCode() const {
    return this->_errorCode;
}