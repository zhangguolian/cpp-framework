/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <args/args.h>

// Incoming parameters need --,
// like ./args_test --help
// like ./args_test --type 1
// like ./args_test --type=1
int main(int argc, char* argv[]) {
    // Init a ArgsParse by usage
    args::ArgsParse args_parse("Usage: args_test [options...]");

    // Add parameters help and type
    std::shared_ptr<bool> help = args_parse.Get("help", "help args");
    std::unique_ptr<int> type = args_parse.Get("type", 0, "type args");

    // Parsing command line arguments
    args_parse.Parse(argc, argv);

    // Determine if there is an incoming parameter help
    if (*help) {
        // If you pass the help parameter, the output description
        args_parse.PrintfDescription();
        return 0;
    }

    // Output the value of the passed type
    std::cout << "type:" << *type << std::endl;
  
    return 0;  
}  