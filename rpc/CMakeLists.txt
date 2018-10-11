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

add_library(rpc ${sources} ${headers})

target_link_libraries(rpc base grpc++)

install(FILES 
        ${PROJECT_SOURCE_DIR}/rpc/rpc.h
        ${PROJECT_SOURCE_DIR}/rpc/server.h
        ${PROJECT_SOURCE_DIR}/rpc/client.h
        DESTINATION /usr/local/include/rpc/)
install(TARGETS rpc ARCHIVE DESTINATION /usr/local/lib/)