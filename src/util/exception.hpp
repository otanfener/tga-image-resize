//
// Created by ozan on 2021-05-04.
//

#ifndef UBISOFT_ASSIGMENT_EXCEPTION_H
#define UBISOFT_ASSIGMENT_EXCEPTION_H

#include <exception>
#include <cstdint>
#include <string>
#include <iostream>
class Exception : public std::exception {

public:
    Exception(uint32_t errorCode, const std::string &message) noexcept;
    virtual ~Exception() = default;
    virtual const char* what() const noexcept override;
    const uint32_t GetErrorCode() const;

private:
    uint32_t _errorCode;
    std::string _message;

};

typedef enum{
    SUCCESS=0,
    INVALID_USAGE,
    INVALID_FILE,
    FILE_IS_ALREADY_OPEN,
    FILE_NOT_FOUND,
    INVALID_HEADER,
    INVALID_BUFFER,
    ERR_LAST
}statusCodes_t;

#endif //UBISOFT_ASSIGMENT_EXCEPTION_H
