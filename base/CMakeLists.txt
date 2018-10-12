#
# Copyright 2018 Guolian Zhang.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(base ${sources} ${headers})

target_link_libraries(base reflect crypto event jsoncpp ${Boost_LIBRARIES})

install(FILES 
        ${PROJECT_SOURCE_DIR}/base/base.h
        ${PROJECT_SOURCE_DIR}/base/string.h
        ${PROJECT_SOURCE_DIR}/base/ssl.h
        ${PROJECT_SOURCE_DIR}/base/rand.h
        ${PROJECT_SOURCE_DIR}/base/json.hpp
        DESTINATION /usr/local/include/base/)
install(TARGETS base ARCHIVE DESTINATION /usr/local/lib/)