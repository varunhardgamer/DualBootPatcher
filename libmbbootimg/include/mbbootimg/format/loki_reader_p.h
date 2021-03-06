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

#include "mbcommon/optional.h"

#include "mbbootimg/format/android_p.h"
#include "mbbootimg/format/loki_p.h"
#include "mbbootimg/format/segment_reader_p.h"
#include "mbbootimg/reader.h"
#include "mbbootimg/reader_p.h"


namespace mb
{
namespace bootimg
{
namespace loki
{

class LokiFormatReader : public detail::FormatReader
{
public:
    LokiFormatReader(Reader &reader);
    virtual ~LokiFormatReader();

    MB_DISABLE_COPY_CONSTRUCT_AND_ASSIGN(LokiFormatReader)
    MB_DEFAULT_MOVE_CONSTRUCT_AND_ASSIGN(LokiFormatReader)

    int type() override;
    std::string name() override;

    int bid(File &file, int best_bid) override;
    bool read_header(File &file, Header &header) override;
    bool read_entry(File &file, Entry &entry) override;
    bool go_to_entry(File &file, Entry &entry, int entry_type) override;
    bool read_data(File &file, void *buf, size_t buf_size,
                   size_t &bytes_read) override;

    static bool find_loki_header(Reader &reader, File &file,
                                 LokiHeader &header_out, uint64_t &offset_out);
    static bool find_ramdisk_address(Reader &reader, File &file,
                                     const android::AndroidHeader &hdr,
                                     const LokiHeader &loki_hdr,
                                     uint32_t &ramdisk_addr_out);
    static bool find_gzip_offset_old(Reader &reader, File &file,
                                     uint32_t start_offset,
                                     uint64_t &gzip_offset_out);
    static bool find_ramdisk_size_old(Reader &reader, File &file,
                                      const android::AndroidHeader &hdr,
                                      uint32_t ramdisk_offset,
                                      uint32_t &ramdisk_size_out);
    static bool find_linux_kernel_size(Reader &reader, File &file,
                                       uint32_t kernel_offset,
                                       uint32_t &kernel_size_out);
    static bool read_header_old(Reader &reader, File &file,
                                const android::AndroidHeader &hdr,
                                const LokiHeader &loki_hdr,
                                Header &header,
                                uint64_t &kernel_offset_out,
                                uint32_t &kernel_size_out,
                                uint64_t &ramdisk_offset_out,
                                uint32_t &ramdisk_size_out);
    static bool read_header_new(Reader &reader, File &file,
                                const android::AndroidHeader &hdr,
                                const LokiHeader &loki_hdr,
                                Header &header,
                                uint64_t &kernel_offset_out,
                                uint32_t &kernel_size_out,
                                uint64_t &ramdisk_offset_out,
                                uint32_t &ramdisk_size_out,
                                uint64_t &dt_offset_out);

private:
    // Header values
    android::AndroidHeader _hdr;
    LokiHeader _loki_hdr;

    // Offsets
    optional<uint64_t> _header_offset;
    optional<uint64_t> _loki_offset;

    SegmentReader _seg;
};

}
}
}
