#include "multiboot2/multiboot2_header.hpp"
#include "stddef.h"

MultibootTwoInfo::MultibootTwoInfo(void *bootInformation)
{
    auto bootptr = static_cast<uint8_t *>(bootInformation);

    // Skip header
    bootptr += sizeof(multiboot_start);

    // Individual tags
    // Find and push addresses to list by its tag.
    multiboot_header_tag *header = static_cast<multiboot_header_tag *>((void *)bootptr);

    while (header->type != MULTIBOOT_TAG::END)
    {
        this->tagLocations[header->type] = (intptr_t)header;

        header = static_cast<multiboot_header_tag *>((void *)bootptr);
    }
}

bool MultibootTwoInfo::HasTag(MULTIBOOT_TAG tag)
{
    return this->tagLocations[tag] != (intptr_t)NULL;
}

template <typename T>
T *MultibootTwoInfo::GetTag(MULTIBOOT_TAG tag)
{
    return (T *)this->tagLocations[tag];
}