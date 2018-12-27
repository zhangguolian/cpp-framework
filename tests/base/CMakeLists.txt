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

add_executable(ssl_test "ssl.cpp")
target_link_libraries(ssl_test base)

add_executable(json_test "json.cpp")
target_link_libraries(json_test base)

add_executable(rand_test "rand.cpp")
target_link_libraries(rand_test base)

add_executable(string_test "string.cpp")
target_link_libraries(string_test base)

add_executable(cmd_test "cmd.cpp")
target_link_libraries(cmd_test base)