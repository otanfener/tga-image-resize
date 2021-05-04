//
// Created by ozan on 2021-05-04.
//

#ifndef UBISOFT_ASSIGMENT_EXCEPTION_H
#define UBISOFT_ASSIGMENT_EXCEPTION_H

#include <exception>
#include <cstdint>
#include <string>
#include <iostream>

class TgaException : public std::exception {

public:
    /// @brief Constructs a custom exception object for given errorCode, and message.
    /// @param errorCode Error code to be used when exceptions are created.
    /// @param message Error message to be used when exceptions are created.
    TgaException(uint32_t errorCode, const std::string &message) noexcept;

    virtual ~TgaException() = default;

    virtual const char *what() const noexcept override;

    const uint32_t GetErrorCode() const;

private:
    uint32_t errorCode_;
    std::string message_;

};

typedef enum {
    SUCCESS = 0,
    INVALID_USAGE,
    INVALID_FILE,
    FILE_IS_ALREADY_OPEN,
    FILE_NOT_FOUND,
    INVALID_HEADER,
    INVALID_BUFFER,
    ERR_LAST
} statusCodes_t;

#endif //UBISOFT_ASSIGMENT_EXCEPTION_H
