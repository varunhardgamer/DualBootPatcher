/*
 * Copyright (C) 2017  Andrew Gunnerson <andrewgunnerson@gmail.com>
 *
 * This file is part of DualBootPatcher
 *
 * DualBootPatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DualBootPatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DualBootPatcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "mbbootimg/guard_p.h"

#include <vector>

#include <openssl/sha.h>

#include "mbcommon/optional.h"

#include "mbbootimg/format/android_p.h"
#include "mbbootimg/format/segment_writer_p.h"
#include "mbbootimg/writer.h"
#include "mbbootimg/writer_p.h"


namespace mb
{
namespace bootimg
{
namespace loki
{

class LokiFormatWriter : public detail::FormatWriter
{
public:
    LokiFormatWriter(Writer &writer);
    virtual ~LokiFormatWriter();

    MB_DISABLE_COPY_CONSTRUCT_AND_ASSIGN(LokiFormatWriter)
    MB_DEFAULT_MOVE_CONSTRUCT_AND_ASSIGN(LokiFormatWriter)

    int type() override;
    std::string name() override;

    bool init() override;
    bool get_header(File &file, Header &header) override;
    bool write_header(File &file, const Header &header) override;
    bool get_entry(File &file, Entry &entry) override;
    bool write_entry(File &file, const Entry &entry) override;
    bool write_data(File &file, const void *buf, size_t buf_size,
                    size_t &bytes_written) override;
    bool finish_entry(File &file) override;
    bool close(File &file) override;

private:
    // Header values
    android::AndroidHeader _hdr;

    optional<uint64_t> _file_size;

    std::vector<unsigned char> _aboot;

    SHA_CTX _sha_ctx;

    SegmentWriter _seg;
};

}
}
}
