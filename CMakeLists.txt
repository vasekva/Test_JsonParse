cmake_minimum_required(VERSION 3.21)
project(Test_Exercise)

set(CMAKE_CXX_STANDARD 14)

set(INC_DIR ./json/include)

include_directories(json)
include_directories(json/include)
include_directories(json/include/nlohmann)
include_directories(json/include/nlohmann/detail)
include_directories(json/include/nlohmann/detail/conversions)
include_directories(json/include/nlohmann/detail/input)
include_directories(json/include/nlohmann/detail/iterators)
include_directories(json/include/nlohmann/detail/meta)
include_directories(json/include/nlohmann/detail/meta/call_std)
include_directories(json/include/nlohmann/detail/output)
include_directories(json/include/nlohmann/thirdparty)
include_directories(json/include/nlohmann/thirdparty/hedley)
include_directories(json/single_include)
include_directories(json/single_include/nlohmann)

#add_compile_options(
#        -Werror
#
#        -Wall
#        -Wextra
#)

#disable extensions (it's enabled by default)
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_executable(Test_Exercise
        json/include/nlohmann/detail/conversions/from_json.hpp
        json/include/nlohmann/detail/conversions/to_chars.hpp
        json/include/nlohmann/detail/conversions/to_json.hpp
        json/include/nlohmann/detail/input/binary_reader.hpp
        json/include/nlohmann/detail/input/input_adapters.hpp
        json/include/nlohmann/detail/input/json_sax.hpp
        json/include/nlohmann/detail/input/lexer.hpp
        json/include/nlohmann/detail/input/parser.hpp
        json/include/nlohmann/detail/input/position_t.hpp
        json/include/nlohmann/detail/iterators/internal_iterator.hpp
        json/include/nlohmann/detail/iterators/iter_impl.hpp
        json/include/nlohmann/detail/iterators/iteration_proxy.hpp
        json/include/nlohmann/detail/iterators/iterator_traits.hpp
        json/include/nlohmann/detail/iterators/json_reverse_iterator.hpp
        json/include/nlohmann/detail/iterators/primitive_iterator.hpp
        json/include/nlohmann/detail/meta/call_std/begin.hpp
        json/include/nlohmann/detail/meta/call_std/end.hpp
        json/include/nlohmann/detail/meta/cpp_future.hpp
        json/include/nlohmann/detail/meta/detected.hpp
        json/include/nlohmann/detail/meta/identity_tag.hpp
        json/include/nlohmann/detail/meta/is_sax.hpp
        json/include/nlohmann/detail/meta/type_traits.hpp
        json/include/nlohmann/detail/meta/void_t.hpp
        json/include/nlohmann/detail/output/binary_writer.hpp
        json/include/nlohmann/detail/output/output_adapters.hpp
        json/include/nlohmann/detail/output/serializer.hpp
        json/include/nlohmann/detail/exceptions.hpp
        json/include/nlohmann/detail/hash.hpp
        json/include/nlohmann/detail/json_pointer.hpp
        json/include/nlohmann/detail/json_ref.hpp
        json/include/nlohmann/detail/macro_scope.hpp
        json/include/nlohmann/detail/macro_unscope.hpp
        json/include/nlohmann/detail/string_escape.hpp
        json/include/nlohmann/detail/value_t.hpp
        json/include/nlohmann/thirdparty/hedley/hedley.hpp
        json/include/nlohmann/thirdparty/hedley/hedley_undef.hpp
        json/include/nlohmann/adl_serializer.hpp
        json/include/nlohmann/byte_container_with_subtype.hpp
        json/include/nlohmann/json.hpp
        json/include/nlohmann/json_fwd.hpp
        json/include/nlohmann/ordered_map.hpp
        json/single_include/nlohmann/json.hpp
        console_game.cpp)
