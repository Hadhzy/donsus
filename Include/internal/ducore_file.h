#ifndef _DUCORE_FILE_H_
#define _DUCORE_FILE_H_

struct donsus_file{
    char* file_content;
    size_t size;
};

struct donsus_file* handle_file(_DU_ARGV* args, struct donsus_file* file_struct);

#endif