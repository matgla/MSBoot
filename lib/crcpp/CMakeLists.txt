if (NOT EXISTS crcpp)
    file(GLOB_RECURSE crcpp_sources
        "crcpp/inc/*."
    )

    set(CRCpp_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/crcpp/crcpp/inc" CACHE STRING "Path to CRCpp sources")

    add_library(crcpp INTERFACE)
    target_sources(crcpp INTERFACE ${crcpp_sources})
    target_include_directories(crcpp INTERFACE ${CRCpp_INCLUDE_DIR})
endif()