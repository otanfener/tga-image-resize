//
// Created by ozan on 2021-05-04.
//

#include "exception.hpp"

#include <utility>

TgaException::TgaException(uint32_t errorCode, std::string message) noexcept:
        errorCode_(errorCode), message_(std::move(message)) {
}

/// @brief Returns underlying exception string.
/// @return Exception message as a null terminated character string.
const char *TgaException::what() const noexcept {
    return message_.c_str();
}

/// @brief Returns error code.
/// @return Exception error code as unsigned integer.
uint32_t TgaException::GetErrorCode() const {
    return errorCode_;
}