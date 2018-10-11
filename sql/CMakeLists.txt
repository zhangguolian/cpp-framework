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

add_library(sql ${sources} ${headers})

target_link_libraries(sql base reflect mysqlclient)

install(FILES 
        ${PROJECT_SOURCE_DIR}/sql/sql.h
        ${PROJECT_SOURCE_DIR}/sql/sql_base.hpp
        ${PROJECT_SOURCE_DIR}/sql/mysql.h
        DESTINATION /usr/local/include/sql/)
install(TARGETS sql ARCHIVE DESTINATION /usr/local/lib/)