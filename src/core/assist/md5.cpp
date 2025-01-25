/**
 * MIT License
 *
 * Copyright (c) 2024 ylgeeker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "core/assist/md5.h"

#include <openssl/evp.h>
#include <openssl/md5.h>

#include <iomanip>
#include <iostream>
#include <sstream>

namespace ylg {
namespace assist {

std::string MD5::MD5FromString(const std::string& content)
{
    unsigned char digest[MD5_DIGEST_LENGTH] = {0};
    EVP_MD_CTX*   ctx                       = EVP_MD_CTX_new();
    EVP_MD_CTX_init(ctx);

    const EVP_MD* md = EVP_md5();

    EVP_DigestInit_ex(ctx, md, nullptr);
    EVP_DigestUpdate(ctx, content.c_str(), content.size());
    EVP_DigestFinal(ctx, digest, nullptr);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }
    EVP_MD_CTX_free(ctx);

    return ss.str();
}

std::string MD5::MD5FromFile(const std::string& fileName)
{

    FILE* fp = fopen(fileName.c_str(), "rb");
    if (!fp)
    {
        return "";
    }

    int   len  = 0;
    char* data = (char*)malloc(10 * 1024 * 1024);
    if (!data)
    {
        fclose(fp);
        return "";
    }

    unsigned char digest[MD5_DIGEST_LENGTH] = {0};
    EVP_MD_CTX*   ctx                       = EVP_MD_CTX_new();
    EVP_MD_CTX_init(ctx);

    const EVP_MD* md = EVP_md5();
    EVP_DigestInit_ex(ctx, md, nullptr);

    while (0 != (len = fread(data, 1, 10 * 1024 * 1024, fp)))
    {
        EVP_DigestUpdate(ctx, data, len);
    }

    EVP_DigestFinal(ctx, digest, nullptr);

    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    EVP_MD_CTX_free(ctx);

    free(data);
    fclose(fp);

    return ss.str();
}

} // namespace assist
} // namespace ylg
