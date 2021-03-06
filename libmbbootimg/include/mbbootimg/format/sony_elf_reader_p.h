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

#include "mbbootimg/format/segment_reader_p.h"
#include "mbbootimg/format/sony_elf_p.h"
#include "mbbootimg/reader.h"
#include "mbbootimg/reader_p.h"


namespace mb
{
namespace bootimg
{
namespace sonyelf
{

class SonyElfFormatReader : public detail::FormatReader
{
public:
    SonyElfFormatReader(Reader &reader);
    virtual ~SonyElfFormatReader();

    MB_DISABLE_COPY_CONSTRUCT_AND_ASSIGN(SonyElfFormatReader)
    MB_DEFAULT_MOVE_CONSTRUCT_AND_ASSIGN(SonyElfFormatReader)

    int type() override;
    std::string name() override;

    int bid(File &file, int best_bid) override;
    bool read_header(File &file, Header &header) override;
    bool read_entry(File &file, Entry &entry) override;
    bool go_to_entry(File &file, Entry &entry, int entry_type) override;
    bool read_data(File &file, void *buf, size_t buf_size,
                   size_t &bytes_read) override;

    static bool find_sony_elf_header(Reader &reader, File &file,
                                     Sony_Elf32_Ehdr &header_out);

private:
    // Header values
    Sony_Elf32_Ehdr _hdr;

    bool _have_header;

    SegmentReader _seg;
};

}
}
}
