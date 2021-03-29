#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_reader.hpp"

static void show_usage(const char* execName) {
    printf("Invalid command!\n");
    printf("Please run the sample using the following command:\n");
    printf("%s -file <path_to_a_log_file> -filter <regexp_filter>\n", execName);
}

int main(int argc, char* argv[]) {
    char* fileName = NULL;
    char* filter = NULL;
    if (argc != 5) {
        show_usage(argv[0]);
        return 1;
    }
            
    /* TO DO: switch to GFlags later*/
    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-file")) {
            if (i < argc - 1) {
                fileName = argv[i + 1];
            }
            else {
                show_usage(argv[0]);
                return 1;
            }
        }
        else if (0 == strcmp(argv[i], "-filter")) {
            if (i < argc - 1) {
                filter = argv[i + 1];
            }
            else {
                show_usage(argv[0]);
                return 1;
            }
        }
    }
    if (!fileName || !filter) {
        show_usage(argv[0]);
        return 1;
    }

    printf("Hi, I'm Sample!\n");

    CLogReader reader(fileName);
    reader.Open();
    reader.SetFilter(filter);

    /* here we use pre-defined length. If the resulting line is longer
       then it's just truncated */
    int len = 1000;
    char* resultStr = new char[static_cast<size_t>(len)];

    while (reader.GetNextLine(resultStr, len)) {
        printf("Sample: GetNextLine() returned: \"%s\"\n", resultStr);
    }

    reader.Close();
    delete[] resultStr;
    
    printf("Bye...\n");
    return 0;
}
