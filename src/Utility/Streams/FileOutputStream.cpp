#include "FileOutputStream.h"

#include <cassert>

#include "Utility/Exception.h"

FileOutputStream::FileOutputStream(std::string_view path) {
    open(path);
}

FileOutputStream::~FileOutputStream() {
    closeInternal(false);
}

void FileOutputStream::open(std::string_view path) {
    _path = std::string(path);
    _file = fopen(_path.c_str(), "wb");
    if (!_file)
        Exception::throwFromErrno(_path);
}

void FileOutputStream::write(const void *data, size_t size) {
    assert(isOpen()); // Writing into a closed stream is UB.

    if (fwrite(data, size, 1, _file) != 1)
        Exception::throwFromErrno(_path);
}

void FileOutputStream::flush() {
    assert(isOpen()); // Flushing a closed stream is UB.

    if (fflush(_file) != 0)
        Exception::throwFromErrno(_path);
}

void FileOutputStream::close() {
    closeInternal(true);
}

void FileOutputStream::closeInternal(bool canThrow) {
    if (!isOpen())
        return;

    int status = fclose(_file);
    _file = nullptr;
    if (status != 0 && canThrow)
        Exception::throwFromErrno(_path);
    // TODO(captainurist): !canThrow => log OR attach
}
