#
# Copyright 2018, Data61
# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
# ABN 41 687 119 230.
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(DATA61_BSD)
#

cmake_minimum_required(VERSION 3.7.2)

include(${CMAKE_SOURCE_DIR}/projects/cakeml_libs/meta_utils/meta_utils.cmake)

project(cakeml_regex C)

set(FilterRegex "This.*" CACHE STRING "Regular expression that the filter will match inputs against")

# Generate an ML file that defines a single constant containing the regex to use for
# filtering. The main filter script depends on this generated file.
set(regexFile "${CMAKE_CURRENT_BINARY_DIR}/cmakeConstants.sml")
file(GENERATE OUTPUT "${regexFile}" CONTENT
"structure cmakeConstants = struct
   val filter_regex = \"${FilterRegex}\";
 end
")

DeclareCakeMLMetaUtils(
    ${CMAKE_SOURCE_DIR}/projects/cakeml_libs/meta_utils
    meta_utils
    meta_utils_target
    meta_utils_target_files
    meta_utils_path
)

DeclareCAmkESComponent(CakeMLFilter
    SOURCES components/CakeMLFilter/emit_string.c
    CAKEML_SOURCES components/CakeMLFilter/filterProgScript.sml "${regexFile}" components/CakeMLFilter/componentScript.sml
    CAKEML_HEAP_SIZE 100
    CAKEML_INCLUDES ${meta_utils_path} "/$(HOLDIR)/examples/formal-languages/regular" "${CAKEMLDIR}/semantics/proofs"
    CAKEML_DEPENDS meta_utils_target ${meta_utils_target_files}
)

DeclareCAmkESComponent(Producer
    SOURCES components/Producer/producer.c
)

DeclareCAmkESComponent(Consumer
    SOURCES components/Consumer/consumer.c
)

DeclareCAmkESRootserver(cakeml_regex.camkes)
